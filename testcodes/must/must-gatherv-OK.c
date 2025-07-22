/* ///////////////////////// The MPI Bug Bench ////////////////////////

  Description: MPI_Gatherv is correctly used

  Version of MPI: 1.0

  Category: COLL

BEGIN_MBB_TESTS
  $ mpirun -np 2 ${EXE}
  | OK
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
  if (nprocs != 2)
    printf(
        "MBB ERROR: This test needs exactly 2 processes to produce a bug!\n");

  int *buf = (int *)calloc(nprocs * 5, sizeof(int));
  int *recv_buf = (int *)calloc(10 * nprocs, sizeof(int));

  if (rank == 0) {
    int recv_counts[2] = {5, 5};
    int displs[2] = {0, 5};
    MPI_Gatherv(buf, 5, MPI_INT, recv_buf, recv_counts, displs, MPI_INT,
                                    0, MPI_COMM_WORLD);
  } else {
    MPI_Gatherv(buf, 5, MPI_INT, NULL, NULL, NULL, MPI_INT,
                                    0, MPI_COMM_WORLD);
  }
  free(buf);
  free(recv_buf);

  MPI_Finalize();
  printf("Rank %d finished normally\n", rank);
  return 0;
}
