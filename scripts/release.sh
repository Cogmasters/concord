#!/bin/bash -x
mypath=$(dirname $(readlink -f $0))

if [ -f /tmp/orca ]; then
    rm -rf /tmp/orca
fi

mkdir -p /tmp/orca

pushd $mypath/..
for i in discord-common.h libdiscord.h common/*.h lib/libdiscord.a; do
    cp $i /tmp/orca
done
popd

pushd $mypath
cp docker-install.sh /tmp/orca
tar cvf orca.tar /tmp/orca
popd
