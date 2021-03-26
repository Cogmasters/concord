#!/bin/bash -x
mypath=$(dirname $(readlink -f $0))
pushd $mypath/..
make purge
make specs_clean
make clean_actor_gen
make actor-gen.exe
make all_headers
make specs
popd
