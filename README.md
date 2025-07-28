# Artifact Code Coverage 


## Code Coverage Reports
Visit [https://ahueck.github.io/mbb-code-coverage](https://ahueck.github.io/mbb-code-coverage/)

HTML files are contained in the [docs](docs/) folder.

## Additional MPI-BugBench Tests
For the set of 34 additional tests, see the folder [testcodes](testcodes/).
Each sub folder contains tests that were developed to cover tool-specific MPI analysis.

### Table of Additional Achieved Code Coverage (MPI-BugBench Level 2)


| Filename                                                      |   MUST Covered Lines | MUST Coverage (%)   |   clang-tidy Covered Lines | clang-tidy Coverage (%)   |   PARCOACH Covered Lines | PARCOACH Coverage (%)   |
|:--------------------------------------------------------------|---------------------:|:--------------------|---------------------------:|:--------------------------|-------------------------:|:------------------------|
| must-nbr-alltoallw-OK.c                                       |                  767 | +2.40%              |                          0 | +0.00%                    |                        0 | +0.00%                  |
| must-rma-pscw-OK.c                                            |                  568 | +1.78%              |                          0 | +0.00%                    |                        0 | +0.00%                  |
| must-alltoallw-OK.c                                           |                  488 | +1.53%              |                          0 | +0.00%                    |                        0 | +0.00%                  |
| must-gatherv-OK.c                                             |                  378 | +1.18%              |                          0 | +0.00%                    |                        3 | +0.05%                  |
| must-localparametermismatch-recvcount-negative-gatherv.c      |                  204 | +0.64%              |                          0 | +0.00%                    |                        3 | +0.05%                  |
| must-globalparametermismatch-recvcount-scatterv-NOK.c         |                  198 | +0.62%              |                          0 | +0.00%                    |                        0 | +0.00%                  |
| must-dtype-selfoverlapped-NOK.c                               |                  166 | +0.52%              |                          0 | +0.00%                    |                        3 | +0.05%                  |
| must-localparametermismatch-displ-allgatherv-NOK.c            |                  127 | +0.40%              |                          0 | +0.00%                    |                        0 | +0.00%                  |
| must-dtype-hindexed-OK.c                                      |                  127 | +0.40%              |                          0 | +0.00%                    |                        0 | +0.00%                  |
| must-globalparametermismatch-recvbufnull-reduce_scatter-NOK.c |                  116 | +0.36%              |                          0 | +0.00%                    |                        1 | +0.02%                  |
| must-dtype-hindexed-mismatch-NOK.c                            |                  104 | +0.33%              |                          0 | +0.00%                    |                        0 | +0.00%                  |
| must-dtype-struct-offset-NOK.c                                |                   91 | +0.29%              |                          0 | +0.00%                    |                        3 | +0.05%                  |
| must-graph-create-OK.c                                        |                   77 | +0.24%              |                          0 | +0.00%                    |                        6 | +0.10%                  |
| must-nbr-allgather-OK.c                                       |                   64 | +0.20%              |                          0 | +0.00%                    |                        0 | +0.00%                  |
| must-dtype-struct-size-NOK.c                                  |                   61 | +0.19%              |                          0 | +0.00%                    |                        3 | +0.05%                  |
| must-dtype-struct-NOK.c                                       |                   58 | +0.18%              |                          0 | +0.00%                    |                        3 | +0.05%                  |
| must-dtype-struct-OK.c                                        |                   57 | +0.18%              |                          0 | +0.00%                    |                        3 | +0.05%                  |
| must-dtype-dup-OK.c                                           |                   34 | +0.11%              |                          0 | +0.00%                    |                        0 | +0.00%                  |
| must-rma-winoverlap-OK.c                                      |                   21 | +0.07%              |                          0 | +0.00%                    |                        0 | +0.00%                  |
| must-dtype-no-commit-NOK.c                                    |                   20 | +0.06%              |                          0 | +0.00%                    |                        0 | +0.00%                  |
| must-dtype-double-commit-OK.c                                 |                   18 | +0.06%              |                          0 | +0.00%                    |                        0 | +0.00%                  |
| must-waitall-0-OK.c                                           |                   17 | +0.05%              |                          0 | +0.00%                    |                        0 | +0.00%                  |
| must-rma-no-succeed-fence-NOK.c                               |                   16 | +0.05%              |                          0 | +0.00%                    |                        0 | +0.00%                  |
| must-rma-no-precede-fence-NOK.c                               |                   16 | +0.05%              |                          0 | +0.00%                    |                        0 | +0.00%                  |
| must-dtype-struct-recurse-OK.c                                |                   13 | +0.04%              |                          4 | +0.54%                    |                        0 | +0.00%                  |
| must-allgather-nothing-OK.c                                   |                    9 | +0.03%              |                          0 | +0.00%                    |                        0 | +0.00%                  |
| must-sendrecv-nothing-OK.c                                    |                    9 | +0.03%              |                          0 | +0.00%                    |                        0 | +0.00%                  |
| clang-tidy-waitall-array-OK.c                                            |                    3 | +0.01%              |                         14 | +1.89%                    |                        0 | +0.00%                  |
| clang-tidy-double-nonblocking-NOK.c                                      |                    2 | +0.01%              |                         20 | +2.70%                    |                        0 | +0.00%                  |
| clang-tidy-array-deref-NOK.c                                             |                    0 | +0.00%              |                         16 | +2.16%                    |                        0 | +0.00%                  |
| parcoach-mem-funcs-nobuiltin-OK.c                             |                    0 | +0.00%              |                          0 | +0.00%                    |                       73 | +1.17%                  |
| parcoach-loop-construct-OK.c                                  |                    0 | +0.00%              |                          0 | +0.00%                    |                       71 | +1.14%                  |
| parcoach-mem-access-OK.c                                      |                    0 | +0.00%              |                          0 | +0.00%                    |                       71 | +1.14%                  |
| parcoach-switch-OK.c                                          |                    0 | +0.00%              |                          0 | +0.00%                    |                       18 | +0.29%                  |


## Coverage Setup Scripts
In folder [coverage](coverage/), helper scripts to setup the MPI correctness tools for code coverage exist, see the [readme](coverage/README.md).
