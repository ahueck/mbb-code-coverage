/* ///////////////////////// The MPI Bug Bench ////////////////////////

  Description: datatype missmatch: Buffer: MPI_LONG_LONG MPI_Call: MPI_INT

  Version of MPI: 1.0

  Category: P2P

BEGIN_MBB_TESTS
  $ mpirun -np 2 ${EXE}
  | OK
  | dummy
END_MBB_TESTS
//////////////////////       End of MBI headers        /////////////////// */

#include <mpi.h>

typedef struct {
  double x[2];
} A;

typedef struct {
  A a;
} B;

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  B b;

  if (rank == 0) {
    MPI_Send(&b.a.x, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
  } else if (rank == 1) {
    MPI_Recv(&b.a.x, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

  MPI_Finalize();
  return 0;
}