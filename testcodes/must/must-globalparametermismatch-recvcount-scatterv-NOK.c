/* ///////////////////////// The MPI Bug Bench ////////////////////////

  Description: Scatterv - Wrong recv count

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

  int *rbuf = (int *)calloc(10, sizeof(int));
  int *sbuf = (int *)calloc(10, sizeof(int));
  int sendcounts[2] = {5, 5};
  int displs[2] = {0, 5};

  /*MBBERROR_BEGIN*/ MPI_Scatterv(sbuf, sendcounts, displs, MPI_INT, rbuf, 4,
                                  MPI_INT, 0, MPI_COMM_WORLD); /*MBBERROR_END*/

  free(rbuf);
  free(sbuf);

  MPI_Finalize();
  printf("Rank %d finished normally\n", rank);
  return 0;
}
