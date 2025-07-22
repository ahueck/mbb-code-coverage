/* ///////////////////////// The MPI Bug Bench ////////////////////////

  Description: Use of special rank MPI_PROC_NULL in valid communication call

  Version of MPI: 3.0

  Category: RMA

BEGIN_MBB_TESTS
  $ mpirun -np 2 ${EXE}
  | OK
  | Correct-Rank
END_MBB_TESTS
//////////////////////       End of MBI headers        /////////////////// */

// Modified from level1/Correct-mpi_bcast-001.c

#include <mpi.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int nprocs = -1;
  int rank = -1;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (nprocs < 2) {
    printf(
        "MBB ERROR: This test needs at least 2 processes to produce a bug!\n");
  }

  signed int *buf_mpi_int = (signed int *)calloc(1, sizeof(signed int));
  int *buf = (int *)calloc(10, sizeof(int));

  switch (rank) {
  case 0:
    MPI_Bcast(buf_mpi_int, 1, MPI_INT, 0, MPI_COMM_WORLD);
    break;

  default: // This block catches all cases where rank is not 0.
    MPI_Bcast(buf_mpi_int, 1, MPI_INT, 0, MPI_COMM_WORLD);
    break;
  }

  free(buf);
  free(buf_mpi_int); // Also free the second allocated buffer

  MPI_Finalize();
  printf("Rank %d finished normally\n", rank);
  return 0;
}
