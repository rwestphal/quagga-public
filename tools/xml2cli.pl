#!/usr/bin/perl
##
## Parse a XML file containing a tree-like representation of Quagga CLI
## commands and generate a file with:
##
## - a DEFUN function for each command;
## - an initialization function.
##
## See xml2cli.txt for instructions.
##
##
## Copyright (C) 2012 Renato Westphal <renatow@digistar.com.br>
## This file is part of GNU Zebra.
##
## GNU Zebra is free software; you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by the
## Free Software Foundation; either version 2, or (at your option) any
## later version.
##
## GNU Zebra is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with GNU Zebra; see the file COPYING.  If not, write to the Free
## Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
## 02111-1307, USA.
##

use strict;
use warnings;
use Getopt::Std;
use File::Basename qw(fileparse);
use vars qw($opt_d);
use XML::LibXML;

%::input_strs = (
		"word"		=> "WORD",
		"line"		=> ".LINE",
		"ipv4"		=> "A.B.C.D",
		"ipv4m"		=> "A.B.C.D/M",
		"ipv6"		=> "X:X::X:X",
		"ipv6m"		=> "X:X::X:X/M",
		# BGP specific
		"rd"		=> "ASN:nn_or_IP-address:nn",
		"asn"		=> "<1-4294967295>",
		"community"	=> "AA:NN",
		"clist"		=> "<1-500>"
		);

# parse options node and store the corresponding information
# into a global hash of hashes
sub parse_options {
	my $xml_node = $_[0];
	my @cmdstr;

	if (not $xml_node->exists('./@name')) {
		die("error: \"options\" node without \"name\" attribute");
	}
	my $options_name = $xml_node->findvalue('./@name');

	# initialize hash
	$::options{$options_name}{'cmdstr'} = "";
	$::options{$options_name}{'help'} = "";

	my @children = $xml_node->getChildnodes();
	foreach my $child(@children) {
		# skip comments, random text, etc
		if ($child->getType() != XML_ELEMENT_NODE) {
			next;
		}
		my $name = $child->getName();
		my $help = $child->findvalue('./@help');
		if ($name eq "input") {
			if (not $child->exists('./@type')) {
				die("error: \"input\" node without \"type\" attribute");
			}
			my $input_type = $child->findvalue('./@type');
			$name = $::input_strs{$input_type};
		}

		push (@cmdstr, $name);
		$::options{$options_name}{'help'} .= "\n       \"" . $help . "\\n\"";
	}
	$::options{$options_name}{'cmdstr'} = "(" . join('|', @cmdstr) . ")";
}

# given a subtree, replace all the corresponding include nodes by
# this subtree
sub parse_command_subtree {
	my $subtree = $_[0];

	my $subtree_name = $subtree->findvalue('./@name');
	if (not $subtree_name) {
		die("subtree without \"name\" attribute");
	}

	my $query = "//include[\@name='$subtree_name']";
	foreach my $include_node($::xml->findnodes($query)) {
		my @children = $subtree->getChildnodes();
		foreach my $child(reverse @children) {
			my $include_node_parent = $include_node->getParentNode();
			$include_node_parent->insertAfter($child->cloneNode(1),
					$include_node);
		}
		$include_node->unbindNode();
	}
	$subtree->unbindNode();
}

# generate arguments for a given command
sub generate_arguments {
	my @nodes = @_;
	my $arguments;
	my $no_args = 1;
	my $argc = 0;

	$arguments .= "  struct vty_arg *args[] =\n";
	$arguments .= "    {\n";
	for (my $i = 0; $i < @nodes; $i++) {
		my %node = %{$nodes[$i]};
		my $arg_value;

		if (not $node{'arg'}) {
			next;
		}
		$no_args = 0;

		# for input and select nodes, the value of the argument is an
		# argv[] element. for the other types of nodes, the value of the
		# argument is the name of the node
		if ($node{'name'} eq "input" or $node{'name'} eq "select") {
			$arg_value = "argv[" . $argc++ . "]";
		} else {
			$arg_value = '"' . $node{'name'} . '"';
		}

		if ($node{'name'} eq "input" and $node{'input_type'} eq "line") {
			# arguments of the type 'line' may have multiple spaces (i.e
			# they don't fit into a single argv[] element).	to properly
			# handle these arguments, we need to provide direct access
			# to the argv[] array and the argc variable.
			my $argc_str = "argc" . (($argc > 1) ? " - " . ($argc - 1) : "");
			my $argv_str = "argv" . (($argc > 1) ? " + " . ($argc - 1) : "");
			$arguments .= "      &(struct vty_arg) { "
				. ".name = \"" . $node{'arg'} . "\", "
				. ".argc = $argc_str, "
				. ".argv = $argv_str },\n";
		} else {
			# common case - each argument has a name and a single value
			$arguments .= "      &(struct vty_arg) { "
				. ".name = \"" . $node{'arg'} . "\", "
				. ".value = " . $arg_value . " },\n";
		}
	}
	$arguments .= "      NULL\n";
	$arguments .= "    };\n";

	# handle special case
	if ($no_args) {
		return "  struct vty_arg *args[] = { NULL };\n";
	}

	return $arguments;
}

# generate C code
sub generate_code {
	my @nodes = @_;
	my $funcname;
	my $cmdstr;
	my $helpstr;
	my $cmdname = "";
	my %install_nodes;

	for (my $i = 0; $i < @nodes; $i++) {
		my %node = %{$nodes[$i]};
		if ($node{'name'} eq "input") {
			$funcname .= $node{'input_type'} . " ";
			$cmdstr .= $node{'input_str'} . " ";
			$helpstr .= "\n       \"" . $node{'help'} . "\\n\"";
		} elsif ($node{'name'} eq "select") {
			my $options_name = $node{'options'};
			$funcname .= $options_name . " ";
			$cmdstr .= $::options{$options_name}{'cmdstr'} . " ";
			$helpstr .= $::options{$options_name}{'help'};
		} else {
			$funcname .= $node{'name'} . " ";
			$cmdstr .= $node{'realname'} . " ";
			$helpstr .= "\n       \"" . $node{'help'} . "\\n\"";
		}

		# update the 'install_nodes' variable
		if ($node{'nodes'}) {
			my %cmd_nodes = split(/[= ]/, $node{'nodes'});
			foreach my $k (keys %cmd_nodes) {
				delete $install_nodes{$k};
				$install_nodes{$k} = $cmd_nodes{$k};
			}
		}

		# set the command string
		if ($node{'cmd'} ne "inherited") {
			$cmdname = $node{'cmd'};
		}
	}

	# rtrim
	$funcname =~ s/\s+$//;
	$cmdstr =~ s/\s+$//;
	# lowercase
	$funcname = lc($funcname);
	# replace " " by "_"
	$funcname =~ tr/ /_/;
	# replace "-" by "_"
	$funcname =~ tr/-/_/;

	# generate DEFUN
	print STDOUT "DEFUN (" . $funcname . ",\n"
		   . "       " . $funcname . "_cmd,\n"
		   . "       \"" . $cmdstr . "\","
		   . $helpstr . ")\n"
		   . "{\n"
		   . generate_arguments(@nodes)
		   . "  return " . $cmdname . " (vty, args);\n"
		   . "}\n\n";

	# generate one or more calls to install_element()
	foreach my $k (keys %install_nodes) {
		if ($install_nodes{$k} == 0) {
			next;
		}
		$::install_str .= "  install_element (" . $k
			. "_NODE, &" . $funcname . "_cmd);\n";
	}
}

# parse an XML element (recursive function)
sub parse_xml_element {
	# get args
	my $xml_node = $_[0];
	my @nodes = @{$_[1]};

	# push new node (hash) to the nodes stack
	push (@nodes, {});
	# get node from the top of the nodes stack
        my %node = %{$nodes[-1]};

	$node{'name'} = $xml_node->getName();
	$node{'realname'} = $node{'name'};

	# check for error conditions
	if ($node{'name'} eq "include") {
		die("error: can not include \""
		    . $xml_node->findvalue('./@name') . "\"");
	}
	if ($node{'name'} eq "subtree") {
		die("error: subtree \"" . $xml_node->findvalue('./@name')
		    . "\" must be attached to the root node (\"file\")");
	}
	if ($node{'name'} eq "options") {
		parse_options($xml_node);
		return;
	}
	if ($node{'name'} eq "select") {
		if (not $xml_node->exists('./@name')) {
			die("error: \"select\" node without \"name\" attribute");
		}
		$node{'options'} = $xml_node->findvalue('./@name');
	}

	# get node attributes
	$node{'nodes'} = $xml_node->findvalue('./@nodes');
	$node{'arg'} = $xml_node->findvalue('./@arg');
	$node{'help'} = $xml_node->findvalue('./@help');
	$node{'cmd'} = $xml_node->findvalue('./@cmd');
	if ($xml_node->exists('./@realname')) {
		$node{'realname'} = $xml_node->findvalue('./@realname');
	}
	if ($xml_node->exists('./@type')) {
		if ($node{'name'} ne "input") {
			die("error: the \"type\" attribute is only valid for "
			    . "\"input\" nodes");
		}
		$node{'input_type'} = $xml_node->findvalue('./@type');
		$node{'input_str'} = $::input_strs{$node{'input_type'}};
	}
	if ($xml_node->exists('./@ifdef')) {
		my $ifdef = $xml_node->findvalue('./@ifdef');

		# take advantage of the smartmatch operator
		if (not ($ifdef ~~ @::ifdefs)) {
			push(@::ifdefs, $ifdef);
			$node{'ifdef'} = $ifdef;
			$::install_str .= "#ifdef " . $ifdef . "\n";
		}
	}
	if ($node{'name'} eq "input" and not $node{'input_type'}) {
		die("error: \"input\" node without \"type\" attribute");
	}

	# TODO: use a hash reference instead of a local copy
        %{$nodes[-1]} = %node;

	# generate C code
	if ($node{'cmd'}) {
		generate_code(@nodes);
	}

	# recursively process child nodes
	my @children = $xml_node->getChildnodes();
	foreach my $child(@children) {
		# skip comments, random text, etc
		if ($child->getType() != XML_ELEMENT_NODE) {
			next;
		}
		parse_xml_element($child, \@nodes);
	}

	# end '#ifdef' directive
	if ($node{'ifdef'}) {
		pop(@::ifdefs);
		$::install_str .= "#endif /* " . $node{'ifdef'} . " */\n";
	}
}

# parse command-line arguments
if (not getopts('d')) {
	die "usage: xml2cli.pl [-d] FILE\n";
}
my $file = shift;

# initialize the XML parser
my $parser = new XML::LibXML;
$parser->keep_blanks(0);

# parse XML file
$::xml = $parser->parse_file($file);
my $xmlroot = $::xml->getDocumentElement();
if ($xmlroot->getName() ne "file") {
	die("XML root element name must be \"file\"");
}

# read file attributes
my $init_function = $xmlroot->findvalue('./@init');
if (not $init_function) {
	die("Missing the \"init\" attribute in the \"file\" node");
}
my $header = $xmlroot->findvalue('./@header');
if (not $header) {
	die("Missing the \"header\" attribute in the \"file\" node");
}

# replace include nodes by the corresponding subtrees
foreach my $subtree(reverse $::xml->findnodes("/file/subtree")) {
	parse_command_subtree($subtree);
}

# generate source header
print STDOUT "/* Auto-generated from " . fileparse($file) . ". */\n"
	   . "/* Do not edit! */\n\n"
	   . "#include <zebra.h>\n\n"
	   . "#include \"command.h\"\n"
	   . "#include \"vty.h\"\n"
	   . "#include \"$header\"\n\n";

# stack of nodes
my @nodes = qw();

# stack of ifdefs
@::ifdefs = qw();

# string containing the body of the generated initialization function
$::install_str = "";

# process child nodes starting from the XML root node
my @children = $xmlroot->getChildnodes();
foreach my $child(@children) {
	# skip comments, random text, etc
	if ($child->getType() != XML_ELEMENT_NODE) {
		next;
	}
	parse_xml_element($child, \@nodes);
}

# generate install function
print STDOUT "void\n"
	   . $init_function . " (void)\n"
	   . "{\n"
	   .  $::install_str
	   . "}";

# debug flag used to print to stderr the XML file after
# replacing the include nodes by the corresponding subtrees
if($opt_d) {
	print STDERR $::xml->toString(1);
}
