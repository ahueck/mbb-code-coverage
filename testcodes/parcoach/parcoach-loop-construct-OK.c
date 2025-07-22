/* ///////////////////////// The MPI Bug Bench ////////////////////////

  Description: Loops

  Version of MPI: 3.0

  Category: RMA

BEGIN_MBB_TESTS
  $ mpirun -np 2 ${EXE}
  | OK
  | Correct-Rank
END_MBB_TESTS
//////////////////////       End of MBI headers        /////////////////// */

// Modified from COBE/correct/test1_94.c

/* -*- Mode: C; c-basic-offset:4 ; indent-tabs-mode:nil ; -*- */
/*
 *  (C) 2001 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */
#include "mpi.h"
#include "stdio.h"

/* tests a series of puts, gets, and accumulate on 2 processes using fence */

#define SIZE 10

int main(int argc, char *argv[]) {
  int rank, nprocs, A[SIZE], B[SIZE], i;
  MPI_Comm CommDeuce;
  MPI_Win win;
  int errs = 0;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (nprocs < 2) {
    printf("Run this program with 2 or more processes\n");
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  MPI_Comm_split(MPI_COMM_WORLD, (rank < 2), rank, &CommDeuce);

  if (rank < 2) {
    if (rank == 0) {
      for (i = 0; i < SIZE; i++)
        A[i] = B[i] = i;
    } else {
      for (i = 0; i < SIZE; i++) {
        A[i] = (-3) * i;
        B[i] = (-4) * i;
      }
    }

    MPI_Win_create(B, SIZE * sizeof(int), sizeof(int), MPI_INFO_NULL, CommDeuce,
                   &win);

    MPI_Win_fence(0, win);

    if (rank == 0) {
      for (i = 0; i < SIZE - 1; i += 2) {
        MPI_Put(A + i, 1, MPI_INT, 1, i, 1, MPI_INT, win);
      }
    } else {
      for (i = 0; i < SIZE - 1; i++) {
        MPI_Get(A + i, 1, MPI_INT, 0, i, 1, MPI_INT, win);
      }

      MPI_Accumulate(A + i, 1, MPI_INT, 0, i, 1, MPI_INT, MPI_SUM, win);
    }
    MPI_Win_fence(0, win);

    MPI_Win_free(&win);
  }
  MPI_Comm_free(&CommDeuce);
  MPI_Finalize();
  return 0;
}
