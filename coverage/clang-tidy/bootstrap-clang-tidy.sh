#!/bin/bash

function llvm_modules() {
    module purge
    ml gcc/11 cuda openmpi git python
    ml llvm/19
}

export CC=clang
export CXX=clang++

if [ -z "$1" ]; then
    base_llvm_f=$(pwd)
else
    base_llvm_f="$1"
fi

build_f="$base_llvm_f"/llvm-project-19.1.7.src/build
install_f="$base_llvm_f"/llvm-project-19.1.7.src/install

echo "Base folder $base_llvm_f"
echo "Build to $build_f ; Install to $install_f"

function llvm_fetch() {
    cd "$base_llvm_f"
    wget https://github.com/llvm/llvm-project/releases/download/llvmorg-19.1.7/llvm-project-19.1.7.src.tar.xz
    tar -xf llvm-project-19.1.7.src.tar.xz
}

function llvm_config() {
    mkdir -p "$build_f"
    cd "$build_f"
    cmake -GNinja \
        -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra" \
        -DCMAKE_INSTALL_PREFIX="$install_f" \
        -DCMAKE_BUILD_TYPE=Debug \
        -DLLVM_PARALLEL_LINK_JOBS=2 \
        -DLLVM_DEFAULT_TARGET_TRIPLE=x86_64-pc-linux-gnu \
        -DLLVM_BUILD_INSTRUMENTED_COVERAGE=ON \
        -DCLANG_INSTALL_SCANBUILD=ON ../llvm
}

function llvm_install() {
    cd "$build_f"
    ninja install
}

# llvm_modules
llvm_fetch
llvm_config
llvm_install

echo "##########"
echo "Execute: export PATH="$install_f"/bin:\$PATH"
echo "Execute: export LLVM_PROFILE_FILE="$install_f"/myprofile/clang-tidy-%p.profraw"

