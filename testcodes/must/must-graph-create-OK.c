/* ///////////////////////// The MPI Bug Bench ////////////////////////

  Description: MPI graph communicator defined correctly

  Version of MPI: 1.0

  Category: COLL

BEGIN_MBB_TESTS
  $ mpirun -np 4 ${EXE}
  | ERROR CallOrdering
  | dummy
END_MBB_TESTS
//////////////////////       End of MBI headers        /////////////////// */

#include <mpi.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

int main(int argc, char **argv) {
  int nprocs = -1;
  int rank = -1;
  MPI_Comm graph_comm;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (nprocs != 4)
    printf(
        "MBB ERROR: This test needs exactly 4 processes to produce a bug!\n");

  // Define the graph topology
  int index[4] = {2, 4, 6, 8};             // Cumulative degree per node
  int edges[8] = {1, 3, 0, 2, 1, 3, 0, 2}; // Neighbors for each node

  // Create the new graph topology communicator
  MPI_Graph_create(MPI_COMM_WORLD, 4, index, edges, 0, &graph_comm);
  int new_rank;
  MPI_Comm_rank(graph_comm, &new_rank);

  // Print neighbors of each process
  int nneigh;
  MPI_Graph_neighbors_count(graph_comm, new_rank, &nneigh);
  int neighbors[nneigh];
  MPI_Graph_neighbors(graph_comm, new_rank, nneigh, neighbors);

  printf("Process %d (graph rank %d) has %d neighbors: ", rank, new_rank,
         nneigh);
  for (int i = 0; i < nneigh; i++) {
    printf("%d ", neighbors[i]);
  }
  printf("\n");

  MPI_Comm_free(&graph_comm);
  MPI_Finalize();
  printf("Rank %d finished normally\n", rank);
  return 0;
}
