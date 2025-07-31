#!/usr/bin/env zsh

MUST_DIR=/my/installdir/bin/
OLD_PWD=$PWD

module purge
module load gompi/2024a LLVM/19 Perl

export CC=clang
export CXX=clang++
export OMPI_CC=clang
export OMPI_CXX=clang++
export MUST_MPIEXEC="mpirun"

cd $MUST_DIR

LIT_OPTS="-j1 -a" make check-minimal

cd $OLD_PWD