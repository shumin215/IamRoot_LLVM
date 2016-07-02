#!/usr/bin/env bash

export VERSION=3.7.0

# Download address can be gotten from "Copy link location" of right clicking 
# mouse on firefox browser on llvm.org download page.
curl -O http://llvm.org/releases/${VERSION}/llvm-${VERSION}.src.tar.xz
curl -O http://llvm.org/releases/${VERSION}/cfe-${VERSION}.src.tar.xz

