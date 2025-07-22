/* ///////////////////////// The MPI Bug Bench ////////////////////////

  Description: Self-overlapped MPI datatype.

  Version of MPI: 1.0

  Category: P2P

BEGIN_MBB_TESTS
  $ mpirun -np 2 ${EXE}
  | ERROR LocalParameterMissmatch
  | dummy
END_MBB_TESTS
//////////////////////       End of MBI headers        /////////////////// */

#include <mpi.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int id;
  double value;
} SimpleStruct;

int main(int argc, char **argv) {
  int nprocs = -1;
  int rank = -1;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (nprocs < 2) {
    printf("This test needs at least 2 processes to run!\n");
    MPI_Finalize();
    return 1;
  }


  MPI_Datatype mpi_overlapped;
  int blocklengths[2] = {1, 1};
  int displacements[2] = {0, 0};
  MPI_Type_indexed(2, blocklengths, displacements, MPI_INT, &mpi_overlapped);
  MPI_Type_commit(&mpi_overlapped);

  if (rank == 0) {
    int rbuf[2] = {0, 0};
    MPI_Recv(rbuf, 1, mpi_overlapped, 1, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    printf("Received data: %d, %d\n", rbuf[0], rbuf[1]);
  } else if (rank == 1) {

    int sbuf[2] = {1, 2};
    MPI_Send(sbuf, 1, mpi_overlapped, 0, 0, MPI_COMM_WORLD);
  }

  MPI_Type_free(&mpi_overlapped);

  MPI_Finalize();
  printf("Rank %d finished normally.\n", rank);
  return 0;
}