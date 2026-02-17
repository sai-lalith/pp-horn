## Repo to track private hornsat work

Our first plan would be to get all the viable solvers as defined by [1]. 
Then one of these solvers or a custom solver would be used to apply to target a subset of datalog or program verification tasks like Pedresen's pointer analysis. This would the future direction.

Bucket list:
- [X] Control flow grammer based algorithm O(N^2)
- [X] Code clean up and better structure
- [ ] Graph based algorithm forward search O(N)
- [ ] Graph based algorithm with backward search O(N) but better for unsat instances
- [ ] Resolution based algorithm. Preferred as this method is shown tractable in MPC setting by [2]

References:

[1] Dowling, William F., and Jean H. Gallier. "Linear-time algorithms for testing the satisfiability of propositional Horn formulae." The Journal of Logic Programming 1.3 (1984): 267-284.

[2] Luo, Ning, et al. "{ppSAT}: Towards {Two-Party} Private {SAT} Solving." 31st USENIX Security Symposium (USENIX Security 22). 2022.

