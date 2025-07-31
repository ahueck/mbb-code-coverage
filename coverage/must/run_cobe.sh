#!/usr/bin/env zsh

MUST_DIR=/my/installdir/bin/

# Generate folder based on current date and time
FINAL_REPORT_DIR="$PWD/cobe_coverage_$(date +%Y%m%d_%H%M%S)"
LOCAL_REPORT_DIR="$PWD/cobe_coverage_$(date +%Y%m%d_%H%M%S)"
GENCODES_DIR="$PWD/cobe/0-level"
mkdir -p $FINAL_REPORT_DIR

module purge
module load gompi/2024a LLVM/19 Perl

export CC=clang
export CXX=clang++
export OMPI_CC=clang
export OMPI_CXX=clang++
export PATH=$MUST_DIR:$PATH
export MUST_MPIEXEC="mpirun"

# Array of several arguments
MUST_CONFIGS=(
    "--must:distributed --must:typeart --must:output json"
    "--must:typeart --must:output json"
    "--must:tsan --must:output json"
)

MUST_CONFIG_NAMES=(
    "distributed_output_json"
    "centralized_output_json"
    "tsan_output_json"
)

cd mpi-bugbench
rm -rf logs
source venv/bin/activate

# Iterate over both arrays
for i in {1..${#MUST_CONFIGS[@]}}; do
    CONFIG="${MUST_CONFIGS[$i]}"
    CONFIG_NAME="${MUST_CONFIG_NAMES[$i]}" 
    mkdir -p ${LOCAL_REPORT_DIR}/cobe_coverage_${CONFIG_NAME}/profiles
    echo "Running MBB with argument: ${MUST_CONFIGS[$i]}"
    export MUST_ARGUMENTS="${MUST_CONFIGS[$i]}"
    export LLVM_PROFILE_FILE="${LOCAL_REPORT_DIR}/cobe_coverage_${CONFIG_NAME}/profiles/"

    LOGS_DIR="${LOCAL_REPORT_DIR}/cobe_coverage_${CONFIG_NAME}/logs"
    echo $LOGS_DIR
    mkdir -p $LOGS_DIR
    python MBB.py -x must -c run --foreign --gencodes ${GENCODES_DIR} -t 30 -l $LOGS_DIR -n 8
    # Copy files to a save location
    mkdir -p $FINAL_REPORT_DIR
    cp -r ${LOCAL_REPORT_DIR}/cobe_coverage_${CONFIG_NAME} $FINAL_REPORT_DIR
    # Clean up
    rm -r ${LOCAL_REPORT_DIR}/cobe_coverage_${CONFIG_NAME}
done

rm -r ${LOCAL_REPORT_DIR}
cd ..