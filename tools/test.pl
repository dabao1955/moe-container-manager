#!/bin/perl -w

use strict;

print "Starting Test...\n";

sub check_ruri {
    my $exit_code = system "out/bin/ruri --version";
    if ($exit_code != 0) {
        die "Failed to execute ruri --version. Exit code: $exit_code\n";
    }
}

sub check_rootfstool {
    my $rt = "out/bin/rootfstool";
    my @commands = (
        "bash $rt list -a arm64 -m bfsu",
        "bash $rt search -a arm64 -d ubuntu -m bfsu",
        "bash $rt url -a arm64 -d ubuntu -v bionic -m bfsu"
    );
    for my $cmd (@commands) {
        my $exit_code = system $cmd;
        if ($exit_code != 0) {
            die "Failed to execute command: $cmd. Exit code: $exit_code\n";
        }
    }
}

sub check_libk2v {
    my $mk = "make -C src/libk2v/";
    my $exit_code = system $mk;
    if ($exit_code != 0) {
        die "Failed to execute $mk. Exit code: $exit_code\n";
    }
  
    my @commands = (
        "$mk test",
        "$mk format",
        "$mk check"
    );
  
    for my $cmd (@commands) {
        my $exit_code = system $cmd;
        if ($exit_code != 0) {
            die "Failed to execute command: $cmd. Exit code: $exit_code\n";
        }
    }
}

sub check_sh {
    my $rt = "out/bin/rootfstool";
    my @commands = (
        "shfmt -i 2 -w debian/prerm",
        "shfmt -i 2 -w $rt",
        "shfmt -i 2 -w src/share/*.sh"
    );
    for my $cmd (@commands) {
        my $exit_code = system $cmd;
        if ($exit_code != 0) {
            die "Failed to execute command: $cmd. Exit code: $exit_code\n";
        }
    }
}

sub main {
    check_ruri();
    check_rootfstool();
    check_libk2v();
    check_sh();
}

main();
