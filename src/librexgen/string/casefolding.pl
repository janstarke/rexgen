#!/usr/bin/perl -w
use strict;
use warnings;
require LWP::UserAgent;

sub print_foldings($$$) {
    my $fh = shift;
    my $function_name = shift;
    my $foldings = shift;

    print $fh "void\n$function_name";
    print $fh <<'ENDING';
(uint16_t cp, uint16_t& cp0, uint16_t& cp1, uint16_t& cp2) {
  d0 = (uint16_t) 0xFFFF;
  d1 = (uint16_t) 0xFFFF;
  d2 = (uint16_t) 0xFFFF;
  switch (cp) {
ENDING
    foreach my $cp (sort keys %$foldings) {
        my $folding = $foldings->{$cp};
        print $fh "    case 0x$cp:";
        print $fh " cp0 = 0x$folding->[0];" if defined($folding->[0]);
        print $fh " cp1 = 0x$folding->[1];" if defined($folding->[1]);
        print $fh " cp2 = 0x$folding->[2];" if defined($folding->[2]);
        print $fh " break;\n";
    }
    print $fh "  };\n}\n\n";
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

print $FH "#ifndef __CASEFOLDING_H__\n";
print $FH "#define __CASEFOLDING_H__\n";

print_foldings($FH, 'casefold_common', $folding{'C'});
print_foldings($FH, 'casefold_full', $folding{'F'});
print_foldings($FH, 'casefold_simple', $folding{'S'});
print_foldings($FH, 'casefold_special', $folding{'T'});

print $FH "#endif /* __CASEFOLDING_H__ */\n";
close $FH;
