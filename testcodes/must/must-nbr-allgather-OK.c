/* ///////////////////////// The MPI Bug Bench ////////////////////////

  Description: Correct neighborhood collective usage with MPI_Neighbor_allgather

  Version of MPI: 1.0

  Category: COLL

BEGIN_MBB_TESTS
  $ mpirun -np 4 ${EXE}
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

  int *rbuf = (int *)calloc(4 * nprocs, sizeof(int));
  /*MBBERROR_BEGIN*/ MPI_Neighbor_allgather(&cart_rank, 1, MPI_INT, rbuf, 1, MPI_INT, cart_comm); /*MBBERROR_END*/

  free(rbuf);
  MPI_Comm_free(&cart_comm);

  MPI_Finalize();
  printf("Rank %d finished normally\n", rank);
  return 0;
}
