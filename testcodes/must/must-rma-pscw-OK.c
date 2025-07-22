/* ///////////////////////// The MPI Bug Bench ////////////////////////

  Description: Correct usage of MPI PSCW

  Version of MPI: 2.0

  Category: RMA

BEGIN_MBB_TESTS
  $ mpirun -np 3 ${EXE}
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
  if (nprocs < 2)
    printf(
        "MBB ERROR: This test needs at least 2 processes to produce a bug!\n");

  MPI_Win mpi_win_0;

  int *winbuf = (int *)calloc(10, sizeof(int));

  MPI_Win_create(winbuf, 10 * sizeof(int), sizeof(int), MPI_INFO_NULL,
                 MPI_COMM_WORLD, &mpi_win_0);

  int *buf = (int *)calloc(10, sizeof(int));

  MPI_Group world_group, group;
  MPI_Comm_group(MPI_COMM_WORLD, &world_group);

  if (rank == 0) {
    int target = 1;
    MPI_Group_incl(world_group, 1, &target, &group);
    MPI_Win_start(group, 0, mpi_win_0);
    MPI_Put(buf, 10, MPI_INT, 1, 0, 10, MPI_INT,
                               mpi_win_0);
    MPI_Win_complete(mpi_win_0);
    MPI_Group_free(&group);
  }

  if (rank == 1) {
    int origin = 0;
    MPI_Group_incl(world_group, 1, &origin, &group);
    MPI_Win_post(group, 0, mpi_win_0);
    MPI_Win_wait(mpi_win_0);
    MPI_Group_free(&group);
  }
  MPI_Group_free(&world_group);
  MPI_Win_free(&mpi_win_0);

  MPI_Finalize();
  printf("Rank %d finished normally\n", rank);
  return 0;
}
