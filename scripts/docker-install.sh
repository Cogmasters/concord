#!/bin/bash -x
mypath=$(dirname $(readlink -f $0))

if [ $# != 2 ]; then
    echo "$0 <container> <folder>"
    exit 1;
fi

container=cattleshed_catthesed_1
folder=/sjacket/usr

pushd ${mypath}
for i in *.h; do
    echo $i;
    docker cp $i $container:$folder/include
done

for i in *.a; do
    echo $i;
    docker cp $i $container:$folder/lib
done
popd
