/* ///////////////////////// The MPI Bug Bench ////////////////////////

  Description: MPI_Neighbor_allgather is not called by all processes

  Version of MPI: 1.0

  Category: COLL

BEGIN_MBB_TESTS
  $ mpirun -np 4 ${EXE}
  | ERROR CallOrdering
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
  if (nprocs != 4)
    printf(
        "MBB ERROR: This test needs exactly 4 processes to produce a bug!\n");

  int dims[2] = {0, 0};
  MPI_Dims_create(nprocs, 2, dims);
  int periods[2] = {1, 1};
  MPI_Comm cart_comm;
  MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 1, &cart_comm);

  int cart_rank;
  MPI_Comm_rank(cart_comm, &cart_rank);

  int num_neighbors = 4;

  int sendcounts[4] = {1, 1, 1, 1};
  int recvcounts[4] = {1, 1, 1, 1};
  MPI_Aint sdispls[4] = {0, 1*sizeof(int), 2*sizeof(int), 3*sizeof(int)};
  MPI_Aint rdispls[4] = {0, 1*sizeof(int), 2*sizeof(int), 3*sizeof(int)};
  MPI_Datatype sendtypes[4] = {MPI_INT, MPI_INT, MPI_INT, MPI_INT};
  MPI_Datatype recvtypes[4] = {MPI_INT, MPI_INT, MPI_INT, MPI_INT};

  int *rbuf = (int *)calloc(4, sizeof(int));
  int *sbuf = (int *)calloc(4, sizeof(int));
  for (int i = 0; i < nprocs; i++) {
    sbuf[i] = cart_rank;
  }

  MPI_Neighbor_alltoallw(sbuf, sendcounts, sdispls, sendtypes, rbuf, recvcounts, rdispls, recvtypes, cart_comm);

  free(rbuf);
  free(sbuf);
  MPI_Comm_free(&cart_comm);

  MPI_Finalize();
  printf("Rank %d finished normally\n", rank);
  return 0;
}
