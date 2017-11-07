// defined std::unique_ptr
#include <memory>
// defines Var and Lit
#include "minisat/core/SolverTypes.h"
// defines Solver
#include "minisat/core/Solver.h"

// defined std::cout
#include <iostream>

int main(void) {
    // -- allocate on the heap so that we can reset later if needed
    std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());

    Minisat::Lit l1, l2, l3, l4;

    // create 4 positive literals over 4 new variables
    l1 = Minisat::mkLit(solver->newVar());
    l2 = Minisat::mkLit(solver->newVar());
    l3 = Minisat::mkLit(solver->newVar());
    l4 = Minisat::mkLit(solver->newVar());

    // create 3 positive literals over 3 new variables
    Minisat::Lit b0, b1, b2;
    b0 = Minisat::mkLit(solver->newVar());
    b1 = Minisat::mkLit(solver->newVar());
    b2 = Minisat::mkLit(solver->newVar());

    // (l1 || b0)
    solver->addClause(l1, b0);
    // (!b0 || l2 || b1)
    solver->addClause(~b0, l2, b1);
    // (!b1 || l3 || b2)
    solver->addClause(~b1, l3, b2);
    // (!b2|| l4)
    solver->addClause(~b2, l4);

    bool res = solver->solve();
    std::cout << "The result is: " << res << "\n";

    std::cout << "satisfying assignment is: "
              << "l1=" << Minisat::toInt(solver->modelValue(l1)) << " "
              << "l2=" << Minisat::toInt(solver->modelValue(l2)) << " "
              << "l3=" << Minisat::toInt(solver->modelValue(l3)) << " "
              << "l4=" << Minisat::toInt(solver->modelValue(l4)) << " "
              << "b0=" << Minisat::toInt(solver->modelValue(b0)) << " "
              << "b1=" << Minisat::toInt(solver->modelValue(b1)) << " "
              << "b2=" << Minisat::toInt(solver->modelValue(b2)) << std::endl;

    // more clauses can be added to the solver
    std::cout << "Adding more clauses...\n";
    solver->addClause (~l1);
    solver->addClause (~l2);
    solver->addClause (~l3);
    solver->addClause (~l4);

    // check whether the CNF in the solver is still satisfiable
    res = solver->solve();
    std::cout << "New result is: " << res << "\n";

    // the next line de-allocates existing solver and allocates a new
    // one in its place.
    solver.reset (new Minisat::Solver());

    // at this point the solver is ready. You must create new
    // variable and new clauses
    return 0;
}
