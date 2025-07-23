/* ///////////////////////// The MPI Bug Bench ////////////////////////

  Description: Overlapping windows (allowed as long as not used concurrently).

  Version of MPI: 2.0

  Category: RMA

BEGIN_MBB_TESTS
  $ mpirun -np 2 ${EXE}
  | ERROR LocalParameterMismatch
  | dummy
END_MBB_TESTS
//////////////////////       End of MBI headers        /////////////////// */

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

  MPI_Win mpi_win_0;
  MPI_Win mpi_win_1;
  int *winbuf = (int *)calloc(10, sizeof(int));

  MPI_Win_create(&winbuf, 10 * sizeof(int), sizeof(int), MPI_INFO_NULL,
                 MPI_COMM_WORLD, &mpi_win_0);

  MPI_Win_create(&winbuf, 10 * sizeof(int), sizeof(int), MPI_INFO_NULL,
                 MPI_COMM_WORLD, &mpi_win_1);

  MPI_Win_free(&mpi_win_0);
  MPI_Win_free(&mpi_win_1);

  MPI_Finalize();
  printf("Rank %d finished normally\n", rank);
  return 0;
}
