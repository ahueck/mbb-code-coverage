/* ///////////////////////// The MPI Bug Bench ////////////////////////

  Description: Overlapping recv buffers

  Version of MPI: 1.0

  Category: P2P

BEGIN_MBB_TESTS
  $ mpirun -np 2 ${EXE}
  | ERROR Array deref
  | array-deref-NOK
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
  MPI_Request mpi_request_0;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (nprocs < 2)
    printf(
        "MBB ERROR: This test needs at least 2 processes to produce a bug!\n");

  int *buf[1];
  buf[0] = calloc(1, sizeof(int));

  if (rank == 0) {
    // buffer is insufficiently dereferenced: pointer->array [mpi-buffer-deref]
    MPI_Irecv(buf, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &mpi_request_0); // ERROR
    MPI_Wait(&mpi_request_0, MPI_STATUS_IGNORE);
  }
  if (rank == 1) {
    MPI_Send(buf[0], 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
  }

  free(buf[0]);

  MPI_Finalize();
  printf("Rank %d finished normally\n", rank);
  return 0;
}
