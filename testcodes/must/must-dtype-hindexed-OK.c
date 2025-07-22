/* ///////////////////////// The MPI Bug Bench ////////////////////////

  Description: Correct usage of MPI_Type_create_hindexed

  Version of MPI: 1.0

  Category: P2P

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
  MPI_Request mpi_request_0 = MPI_REQUEST_NULL;
  MPI_Comm mpi_comm_0 = MPI_COMM_NULL;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (nprocs < 2)
    printf(
        "MBB ERROR: This test needs at least 2 processes to produce a bug!\n");

  MPI_Comm_split(MPI_COMM_WORLD, 1, rank, &mpi_comm_0);

  int *buf = (int *)calloc(10, sizeof(int));

  MPI_Datatype mytype;
  int lengths[3] = {2, 4, 4};
  MPI_Aint displacements[3] = {0, 2 * sizeof(int), 6 * sizeof(int)};

  MPI_Type_create_hindexed(3, lengths, displacements, MPI_INT, &mytype);
  MPI_Type_commit(&mytype);


  if (rank == 0) {
    /*MBBERROR_BEGIN*/ MPI_Recv(buf, 1, mytype, 1, 0, mpi_comm_0,
                                MPI_STATUS_IGNORE); /*MBBERROR_END*/
  }
  if (rank == 1) {
    /*MBBERROR_BEGIN*/ MPI_Send(buf, 1, mytype, 0, 0,
                                mpi_comm_0); /*MBBERROR_END*/
  }
  free(buf);
  MPI_Comm_free(&mpi_comm_0);
  MPI_Type_free(&mytype);

  MPI_Finalize();
  printf("Rank %d finished normally\n", rank);
  return 0;
}
