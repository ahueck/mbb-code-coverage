## Coverage Helper Scripts

Each sub folder contains bootstrap scripts to download and build the tool with coverage enabled.
Requirement is a working Clang/LLVM-19 installation to compile the tools.

#### Example
```shell
cd parcoach
chmod +x bootstrap-parcoach.sh
# Follow instructions of:
./bootstrap-parcoach.sh
```

#### Software Environment:
The following shows a list of modules loaded on the *TU Darmstadt Lichtenberg HPC system* to compile PARCOACH with coverage, based on our bootstrap script:

```
Currently Loaded Modules:
  1) gcc/11.4.1            6) perl/5.40.0-7sxq    11) libjpeg-turbo/3.0.3-n4d7
  2) libxml2/2.13.4-etho   7) git/2.47.0-r3on     12) libpng/1.6.39-bmke
  3) cuda/12.6.2-yl5o      8) python/3.11.9-ixrm  13) qt/5.15.15-k2ls
  4) openmpi/4.1.7-ki3o    9) mesa/23.3.6-fx3s    14) cmake/3.30.5-zjpg
  5) curl/8.10.1-7ozj     10) glx/1.4-oot6        15) llvm/19
```

The list of modules loaded on the *RWTH Aachen CLAIX HPC system* to compile MUST with coverage, based on our bootstrap script:

```
Currently Loaded Modules:
  1) GCCcore/.13.3.0 (H,C)   8) libpciaccess/0.18.1  15) UCC/1.3.0             22) SQLite/3.45.3
  2) zlib/1.3.1              9) hwloc/2.10.0         16) OpenMPI/5.0.3   (M)   23) libffi/3.4.5
  3) binutils/2.42          10) OpenSSL/3            17) gompi/2024a     (TC)  24) Python/3.12.3
  4) GCC/13.3.0      (TC)   11) libevent/2.1.12      18) ncurses/6.5           25) GMP/6.3.0
  5) numactl/2.0.18         12) UCX/1.16.0           19) bzip2/1.0.8           26) Z3/4.13.0
  6) XZ/5.4.5               13) PMIx/5.0.2           20) libreadline/8.2       27) LLVM/19.1.1
  7) libxml2/2.12.7         14) PRRTE/3.0.5          21) Tcl/8.6.14            28) Perl/5.38.2
```

### MPI-BugBench

1. Clone MPI-BugBench with coverage-related changes to tool executor scripts:

    ```shell
    # clang-tidy & PARCOACH
    git clone -b toolcoverage --single-branch https://git-ce.rwth-aachen.de/hpc-public/mpi-bugbench.git
    # MUST
    git clone -b must-toolcoverage --single-branch https://git-ce.rwth-aachen.de/hpc-public/mpi-bugbench.git
    ```

2. Prepare Python environment

    ```shell
    python3 -m venv coverage
    source coverage/bin/activate
    pip install numpy matplotlib scan-build tqdm pandas typing-extensions setuptools
    ```

3. Execute with appropriate (path) setup of tool

    ```shell
    python3 MBB.py -c generate --level 1
    python3 MBB.py -x parcoach -c run -g gencodes -n 16
    ```

#### MUST-Specific Scripts

For MUST, there are additional scripts `run_cobe.sh`, `run_mbb.sh`, `run_must_tests.sh`, and `run_new_tests.sh` that run the three different MUST configurations for the different test sets.