/* ///////////////////////// The MPI Bug Bench ////////////////////////

  Description: C memfuncs, use -fno-builtin during compilation!

  Version of MPI: 3.0

  Category: RMA

BEGIN_MBB_TESTS
  $ mpirun -np 2 ${EXE}
  | OK
  | Correct-Rank
END_MBB_TESTS
//////////////////////       End of MBI headers        /////////////////// */

#include "mpi.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int a;
  // 1. 'memset' to initialize the memory for 'a' to all zeros.
  memset(&a, 0, sizeof(int));

  const int source_val = 1;
  // 2. 'memcpy' to copy the value 1 into 'a'.
  memcpy(&a, &source_val, sizeof(int));

  int *b;
  int *source_ptr = &a;
  // 3. 'memmove' to copy the address of 'a' into the pointer 'b'.
  //    For non-overlapping memory, this works just like memcpy.
  memmove(&b, &source_ptr, sizeof(int *));

  if (a > 0)
    MPI_Barrier(MPI_COMM_WORLD);

  MPI_Comm_rank(MPI_COMM_WORLD, b);

  if (a > 0)
    MPI_Barrier(MPI_COMM_WORLD);

  MPI_Finalize();
}
