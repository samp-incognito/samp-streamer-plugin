#!/bin/bash

# Available configs: Debug, RelWithDebInfo, [Release]
[[ -z "$CONFIG" ]] \
&& config=Release \
|| config="$CONFIG"

docker build \
    -t streamer-omp/build:ubuntu-18.04 ./ \
|| exit 1

folders=('build')
for folder in "${folders[@]}"; do
    if [[ ! -d "./${folder}" ]]; then
        mkdir ${folder}
    fi
    sudo chown -R 1000:1000 ${folder} || exit 1
done

docker run \
    --rm \
    -t \
    -w /code \
    -v $PWD/..:/code \
    -v $PWD/build:/code/build \
    -e CONFIG=${config} \
    streamer-omp/build:ubuntu-18.04
