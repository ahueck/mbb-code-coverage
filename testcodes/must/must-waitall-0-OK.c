/* ///////////////////////// The MPI Bug Bench ////////////////////////

  Description: Waitall with count 0

  Version of MPI: 1.0

  Category: P2P

BEGIN_MBB_TESTS
  $ mpirun -np 2 ${EXE}
  | OK
  | dummy
END_MBB_TESTS
//////////////////////       End of MBI headers        /////////////////// */

// modded from: LocalConcurrency-mpi_irecv-001.c (level 1)

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
  if (nprocs < 2)
    printf(
        "MBB ERROR: This test needs at least 2 processes to produce a bug!\n");

  MPI_Waitall(0, NULL, MPI_STATUS_IGNORE);

  MPI_Finalize();
  printf("Rank %d finished normally\n", rank);
  return 0;
}
