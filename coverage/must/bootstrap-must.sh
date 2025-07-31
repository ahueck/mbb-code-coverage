#!/usr/bin/env zsh

module purge
module load gompi/2024a LLVM/19 Perl

export CC=clang
export CXX=clang++
export OMPI_CC=clang
export OMPI_CXX=clang++

SCRIPTDIR=$PWD

build="true"

# Build MUST with LLVM coverage
BUILD_DIR=/my/builddir
INSTALL_DIR=/my/installdir
TARBALL_DIR=/my/tarballdir/

if [[ "$build" == "true" ]]; then
    # Get MUST tarball and apply patch to enable LLVM coverage
    cd $TARBALL_DIR
    wget https://hpc.rwth-aachen.de/must/files/MUST-v1.11.0.tar.gz -O $TARBALL_DIR/MUST-v1.11.0.tar.gz
    tar -xvzf MUST-v1.11.0.tar.gz
    cd $TARBALL_DIR/MUST-v1.11.0
    patch -p1 < $SCRIPTDIR/coverage.patch
fi

cd $TARBALL_DIR/MUST-v1.11.0

# Install MUST
# tar -xf /MUST-v1.10.0.tar.gz && \
mkdir -p ${BUILD_DIR}
cmake -S . -B ${BUILD_DIR} \
    -DCMAKE_BUILD_TYPE=Debug \
    -DUSE_BACKWARD=ON \
    -DENABLE_FORTRAN=OFF \
    -DENABLE_TYPEART=ON \
    -DENABLE_TESTS=ON \
    -DENABLE_COVERAGE=ON \
    -DLCOV_FOUND=FALSE \
    -DGENINFO_BIN=FALSE \
    -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}

cmake --build ${BUILD_DIR} -- -j$(nproc --all) install
cmake --build ${BUILD_DIR} -- -j$(nproc --all) install-prebuilds
