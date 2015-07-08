#!/usr/bin/perl -w
use strict;
use warnings;

sub _die($) {
  print shift;
  exit -1;
}

my $regex = $ARGV[0] or die "missing regex\n";
my %r=();
while (my $line=<stdin>) {
	chomp $line;
  _die "invalid value: '$line'\n" unless ($line =~ m/$regex/);
	_die "value '$line' occurs more than once\n" if (defined($r{$line}));
	$r{$line}++;
}
my $count = scalar keys %r;
print $count;
