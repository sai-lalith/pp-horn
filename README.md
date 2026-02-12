## Repo to track private hornsat work

For now the structure is defined as below:
.
└── plain-text 
    └── cfg

Where we plan to first get all the viable solvers as defined by [1]. Inital 

Bucket list:
- [ ] Control flow grammer based algorithm O(N^2)
- [ ] Graph based algorithm forward search O(N)
- [ ] Graph based algorithm with backward search O(N) but better for unsat instances
- [ ] Resolution based algorithm. Preferred as this method is shown tractable in MPC setting by [2]

References:

[1] Dowling, William F., and Jean H. Gallier. "Linear-time algorithms for testing the satisfiability of propositional Horn formulae." The Journal of Logic Programming 1.3 (1984): 267-284.

[2] Luo, Ning, et al. "{ppSAT}: Towards {Two-Party} Private {SAT} Solving." 31st USENIX Security Symposium (USENIX Security 22). 2022.

