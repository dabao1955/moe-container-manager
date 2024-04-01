#!/bin/perl -w

$fileExist = -e "./.git";
if ( $fileExist ) {
        system("git clean -dxf");
    }
    else {
        system("rm -rf out && make -C src clean");
     }
