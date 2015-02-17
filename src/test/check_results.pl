#!/usr/bin/perl -w
use strict;
use warnings;

my $regex = $ARGV[0] or die "missing regex";
my %r=();
while (my $line=<stdin>) {
	chomp $line;
  die "invalid value: '$line'" unless ($line =~ m/$regex/);
	die "value '$line' occurs more than once" if (defined($r{$line}));
	$r{$line}++;
}
my $count = scalar keys %r;
print "$count";
