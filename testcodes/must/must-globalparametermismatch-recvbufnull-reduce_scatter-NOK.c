/* ///////////////////////// The MPI Bug Bench ////////////////////////

  Description: Reduce_scatter - recvbuf is NULL where recvcount != 0

  Version of MPI: 1.0

 This testcase can result in a Deadlock


  Category: COLL

BEGIN_MBB_TESTS
  $ mpirun -np 2 ${EXE}
  | ERROR GlobalParameterMissmatch
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

  int *rbuf = NULL;
  if (rank == 0) {
    rbuf = (int *)calloc(10, sizeof(int));
  }
  int *sbuf = (int *)calloc(10, sizeof(int));
  int recvcounts[2] = {5, 5};
  /*MBBERROR_BEGIN*/ MPI_Reduce_scatter(sbuf, rbuf, recvcounts, MPI_INT,
                                        MPI_SUM,
                                        MPI_COMM_WORLD); /*MBBERROR_END*/

  free(rbuf);
  free(sbuf);

  MPI_Finalize();
  printf("Rank %d finished normally\n", rank);
  return 0;
}
