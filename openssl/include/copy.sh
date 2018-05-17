#!/bin/sh

for link in $(find ./ -type l)
do
    echo
    echo "Link is:"
    echo $link
    loc=$(dirname $link)
    dir=$(readlink -f $link)
    echo "location is:"
    echo $loc
    echo "dir is:"
    echo $dir
    rm $link
    cp $dir $link -rf
done
