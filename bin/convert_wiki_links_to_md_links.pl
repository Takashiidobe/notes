#!/usr/bin/env perl

# wikilink2link.pl - Convert GitHub wikilinks to Markdown links.
#
# Preserves wikilink-like substrings in delimited code and fenced code
# blocks.
#
# Now lives at: <https://gist.github.com/daf711474eb53318b722>
#
# USAGE
#
# Remember to **always** work in a new throwaway branch
# even if you make backups, because this script overwrites original
# files!
#
#     git checkout -b wiki2html
#     perl wikilink2link.pl [-x LINK_EXTENSION] *.md
#
#     # Check visually that *.md files are OK
#
#     for m in *.md; do h=${m/%.md/.html}; pandoc -o $h $m; done
#     mv *.html somewhere/outside/the/repo
#     git checkout the-branch-i-was-in
#     git branch -d wiki2html
#
# OPTIONS
#
# -x <ext>, --link-extension=<ext>
# :   The file extension to add to links. Default: 'html'.

use utf8;
use strict;
use warnings qw[ FATAL all ];
no warnings qw[ uninitialized ];

use open ':utf8'; # decode/encode input/output
use open ':std';  # decode/encode STDIN/STDOUT/STDERR

use Getopt::Long qw[ :config no_auto_abbrev no_ignore_case ];


my $link_extension = 'html';
GetOptions(
    'link_extension|link-extension|linkextension|x=s'    =>  \$link_extension,
);

$link_extension =~ s/\A\.*/./;

my $code_or_wikilink_re = qr{
    (               # $1 = code string/block
        (?s:
            ( \`+ )     # $2 = opening code delimiter
            .+?         # code text in single-line mode
            \2          # closing delimiter
        )
    )
    |               # or a wikilink
    \[\[
        ( (?s: .+? ) )  # $3 = link text
        (?:             # optional wiki url
            \|          # a literal pipe
            ( .+? )     # $4 = link url text
        )?
    \]\]
}x;

sub wikilink2link {
    my($link_text, $wiki_url) = @_;
    $wiki_url ||= $link_text;
    # Convert spaces to hyphens.
    # Should possibly be $file_name =~ s/\s+/-/g; instead!
    $wiki_url =~ s/\s/-/g;
    return "[$link_text]($wiki_url)";
}

sub slurp_file {
    my($fn) = @_;
    -T $fn or die "Not a (text) file: $fn\n";
    open my $fh, '<', $fn or die "Couldn't open '$fn' for reading: $!\n";
    my $text = do { local $/; <$fh>; };
    close $fh or die "Couldn't close '$fn' after reading: $!\n";
    return \$text; # A reference to the text
}

sub spew_file {
    my($fn, $text_ref) = @_;
    open my $fh, '>', $fn or die "Couldn't open '$fn' for writing: $!\n";
    print {$fh} $$text_ref or die "Couldn't write to '$fn'\n";
    close $fh or die "Couldn't close '$fn' after writing $!\n";
}

FILE:
for my $fn ( @ARGV ) {
    my $text_ref = slurp_file($fn);
    next FILE unless # No use to write files which weren't changed!
    $$text_ref =~ s{$code_or_wikilink_re}
    {

            $1  # leave code alone!
        ||  wikilink2link( $3, $4 )
        ;
    }eg;
    spew_file( $fn, $text_ref );
} # end FILE
