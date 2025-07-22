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

  int *sbuf = (int *)calloc(10, sizeof(int));
  int *rbuf = (int *)calloc(10, sizeof(int));

  int sendcounts[2] = {5, 5};
  int senddispls[2] = {0, 5 * sizeof(int)};
  MPI_Datatype sendtypes[2] = {MPI_INT, MPI_INT};
  int recvcounts[2] = {5, 5};
  int recvdispls[2] = {0, 5 * sizeof(int)};
  MPI_Datatype recvtypes[2] = {MPI_INT, MPI_INT};

  MPI_Alltoallw(sbuf, sendcounts, senddispls, sendtypes, rbuf, recvcounts,
                recvdispls, recvtypes, MPI_COMM_WORLD);

  free(sbuf);
  free(rbuf);

  MPI_Finalize();
  printf("Rank %d finished normally\n", rank);
  return 0;
}
