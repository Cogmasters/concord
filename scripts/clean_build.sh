#!/bin/bash -x
mypath=$(dirname $(readlink -f $0))

pushd ${mypath}/..
make clean purge
make clean_actor_gen
make actor-gen.exe -j 4
make specs
make -j 4
popd
