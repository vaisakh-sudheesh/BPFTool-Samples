#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <aosp-path> <project-path>"
    exit 1
fi

AOSP_PATH=$1
PROJECT_PATH=$2

source build/envsetup.sh
lunch aosp_arm64-trunk_staging-userdebug
mma -j12  bpftool libbpf libelf libz_static libzstd

find -D exec out/target/product/generic_arm64/obj/ \( -name libzstd.a -o -name libbpf.a -o -name libelf.a -o -name libz_static.a -o -name libzstd.a \) -print0 | xargs -0 -I {} cp -f {} $PROJECT_PATH/libs/

find -D exec out/target/product/generic_arm64/obj/ \( -name bpftool \) -print0 | xargs -0 -I {} cp -f {} $PROJECT_PATH/bin/

cp -avr out/soong/.intermediates/external/libbpf/libbpf_headers/gen/bpf $PROJECT_PATH/include/