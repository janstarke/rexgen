#!/usr/bin/perl -w
use strict;
use warnings;
require LWP::UserAgent;

sub print_foldings($$$) {
    my $fh = shift;
    my $function_name = shift;
    my $foldings = shift;

    print $fh "bool\n$function_name";
    print $fh <<'ENDING';
(uint32_t cp, charset cs, binary_character_t* bch) {
  bch[1].ucs4.value = 0xffffffff;
  bch[2].ucs4.value = 0xffffffff;
  switch (cp) {
ENDING
    foreach my $cp (sort keys %$foldings) {
        my $folding = $foldings->{$cp};
        print $fh "    case 0x$cp:\n";
        for my $idx (0..2) {
            if (defined($folding->[$idx])) {
                print $fh "      encode_codepoint(0x$folding->[$idx], cs, &bch[$idx]);\n";
            }
        }
        print $fh "      return true;\n";
    }
    print $fh "  }\n  bch[0].ucs4.value=0xffffffff;  return false;\n}\n\n";
  }

my $outfile = $ARGV[0] or die "Usage: $0 <outfile>\n";

my $ua = LWP::UserAgent->new;
$ua->timeout(10);
$ua->env_proxy;
my $url='http://www.unicode.org/Public/UNIDATA/CaseFolding.txt';

my $response = $ua->get($url);
unless ($response->is_success) {
    die $response->status_line;
}

my %folding=();

my @content = grep(!/^#/, (split "\n", $response->decoded_content));
foreach my $line(@content) {
    chomp $line;
    my @parts = split ";", $line;
    next unless (scalar @parts > 2);
    $parts[0] =~ s/\s//g;
    $parts[1] =~ s/\s//g;
    my @codepoints = split " ", $parts[2];

    $folding{$parts[1]} = {} unless defined ($folding{$parts[1]});
    $folding{$parts[1]}->{$parts[0]} = \@codepoints;
}

open my $FH, ">$outfile" or die "$!\n";

#print $FH "#ifndef __CASEFOLDING_H__\n";
#print $FH "#define __CASEFOLDING_H__\n";

print $FH "#include <librexgen/string/uchar.h>\n";
print_foldings($FH, 'casefold_common', $folding{'C'});
print_foldings($FH, 'casefold_full', $folding{'F'});
print_foldings($FH, 'casefold_simple', $folding{'S'});
print_foldings($FH, 'casefold_special', $folding{'T'});

#print $FH "#endif /* __CASEFOLDING_H__ */\n";
close $FH;
