#!/usr/bin/perl

use strict;
use warnings;

use File::Basename;
use File::Spec;


my $scriptDir = dirname($0);
my $scriptName = basename($0);

print "Running pre-build script: $scriptName\n";

sub pfnName {
    my ($funcName) = @_;
    return "PFN" . (uc $funcName) . "PROC";
}

sub checkFile {
    my ($lines, $file) = @_;

    open (my $ifh, "<", $file) or die "Cannot open file: '$file': $!\n";
    my $lineFromFile = <$ifh>;
    my $lineOfLines = $$lines[0];
    while ($lineFromFile and $lineOfLines) {
        unless ($lineFromFile eq $lineOfLines) {
            close $ifh;
            return 0;
        }
    }
    close $ifh;
    
    return not ($lineFromFile or $lineOfLines);
}

my $glFunctionsFile = File::Spec->catfile($scriptDir, File::Spec->updir(), "configs", "gl-functions.txt");
my $srcDir = File::Spec->catdir($scriptDir, File::Spec->updir());
my $glFuncHeaderFile = File::Spec->catfile($srcDir, "functions.hpp");
my $glFuncSrcFile = File::Spec->catfile($srcDir, "functions.cpp");

print "| Creating GL function files from $glFunctionsFile\n";
print "|     Header: $glFuncHeaderFile\n";
print "|     Source: $glFuncSrcFile\n";

open (my $fh, "<", $glFunctionsFile) or die "Cannot open GL functions file: '$glFunctionsFile': $!\n";
my @funcNames = ();
while (<$fh>) { chomp; push @funcNames, $_; }
close $fh;

my @headerLines = ();
push @headerLines, qq[#ifndef _FUNCTIONS_HPP_\n];
push @headerLines, qq[#define _FUNCTIONS_HPP_\n\n];
push @headerLines, qq[#include <Windows.h>\n];
push @headerLines, qq[#include <gl/GL.h>\n];
push @headerLines, qq[#include "wglext.h"\n];
push @headerLines, qq[#include "glext.h"\n\n];
push @headerLines, map { "extern " . pfnName($_) . " $_;\n" } @funcNames;
push @headerLines, qq[\nvoid LoadGlFunctions();\n\n];
push @headerLines, qq[#endif\n];

open (my $hHeader, ">", $glFuncHeaderFile) or die "Cannot open GL functions header file: '$glFuncHeaderFile': $!\n";
print $hHeader qq[#ifndef _FUNCTIONS_HPP_\n];
print $hHeader qq[#define _FUNCTIONS_HPP_\n\n];
print $hHeader qq[#include <Windows.h>\n];
print $hHeader qq[#include <gl/GL.h>\n];
print $hHeader qq[#include "wglext.h"\n];
print $hHeader qq[#include "glext.h"\n\n];
print $hHeader map { "extern " . pfnName($_) . " $_;\n" } @funcNames;
print $hHeader qq[\nvoid LoadGlFunctions();\n\n];
print $hHeader qq[#endif\n];
close $hHeader;

open (my $hSource, ">", $glFuncSrcFile) or die "Cannot open GL functions source file: '$glFuncSrcFile': $!\n";
print $hSource qq[#include "functions.hpp"\n\n];
print $hSource map { pfnName($_) . " $_;\n" } @funcNames;
print $hSource qq[\nvoid LoadGlFunctions()\n];
print $hSource qq[{\n];
print $hSource map { "    $_ = (" . pfnName($_) . ") wglGetProcAddress(\"$_\");\n" } @funcNames;
print $hSource qq[}\n];
close $hSource;

print "Done\n\n";
