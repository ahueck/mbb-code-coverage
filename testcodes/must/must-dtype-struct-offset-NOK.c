/* ///////////////////////// The MPI Bug Bench ////////////////////////

  Description: datatype missmatch: Buffer: MPI_LONG_LONG MPI_Call: MPI_INT

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

  const int num_members = 2;
  int blocklengths[2] = {1, 1};
  MPI_Datatype types[2] = {MPI_INT, MPI_DOUBLE};
  MPI_Aint displacements[2];
  displacements[0] = offsetof(SimpleStruct, id);
  displacements[1] = 5; // ERROR wrong member for offsetof

  MPI_Datatype mpi_simple_struct_type;
  MPI_Type_create_struct(num_members, blocklengths, displacements, types,
                         &mpi_simple_struct_type);
  MPI_Type_commit(&mpi_simple_struct_type);

  if (rank == 0) {
    SimpleStruct received_data;
    printf("Rank 0: Ready to receive data.\n");

    MPI_Recv(&received_data, 1, mpi_simple_struct_type, 1, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
  } else if (rank == 1) {
    SimpleStruct data_to_send;
    data_to_send.id = 123;
    data_to_send.value = 3.14159;

    MPI_Send(&data_to_send, 1, mpi_simple_struct_type, 0, 0, MPI_COMM_WORLD);
  }

  MPI_Type_free(&mpi_simple_struct_type);

  MPI_Finalize();
  printf("Rank %d finished normally.\n", rank);
  return 0;
}