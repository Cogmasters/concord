#!/bin/bash -x
mypath=$(dirname $(readlink -f $0))

pushd ${mypath}/..
make clean purge
make actor-gen.exe
CC=stensal-c CXX=stensal-c++ make -j 4
popd
