#!/bin/bash

function parcoach_modules() {
    module purge
    ml gcc/11 cuda openmpi git python
    ml clang/19
}

export CC=clang
export CXX=clang++
export OMPI_CC=clang
export OMPI_CXX=clang++ 

script_dir=$(pwd)

if [ -z "$1" ]; then
    base_parcoach_f=$(pwd)
else
    base_parcoach_f="$1"
fi

build_f="$base_parcoach_f"/parcoach/build
install_f="$base_parcoach_f"/parcoach/install

llvm_15_root_path="/work/groups/da_sc/spack/spapps/gcc-11.4.1/llvm-15.0.7-6s2akzwx6dzg23eqbwh4mn23atkhz3jt"

echo "Base folder $base_parcoach_f"
echo "Build to $build_f ; Install to $install_f"

function parcoach_fetch() {
    cd "$base_parcoach_f"
    git clone https://gitlab.inria.fr/parcoach/parcoach.git
    cd parcoach
    git checkout d600dc168457bf2e9fb6468b224d9b88e88789f7

}

function parcoach_patch() {
    cd "$base_parcoach_f"/parcoach
    git apply "${script_dir}"/parcoach-coverage.patch
    git status
}

function parcoach_config() {
    mkdir -p "$build_f"
    cd "$build_f"

    LLVM_ROOT="$llvm_15_root_path"/lib/cmake/ cmake .. \
        -DCMAKE_C_COMPILER=mpicc \
        -DCMAKE_CXX_COMPILER=mpicxx \
        -DPARCOACH_ENABLE_TESTS=ON \
        -DPARCOACH_ENABLE_COVERAGE=ON \
        -DCMAKE_BUILD_TYPE=Debug
}

function parcoach_install() {
    cd "$build_f"
    make -j16
}

# parcoach_modules
parcoach_fetch
parcoach_patch
parcoach_config
parcoach_install

echo "##########"
echo "Execute: export PATH="$build_f":\$PATH"
echo "Execute: export PATH="$llvm_15_root_path/bin":\$PATH"
echo "Execute: export LLVM_19_BIN=/path/to/llvm/19/bin"
echo "Execute: export LLVM_PROFILE_FILE="$build_f"/myprofile/profile-%p.profraw"
echo "Execute: export LLVM_PROFILE_FOLDER="$build_f"/myprofile/"

