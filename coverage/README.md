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
