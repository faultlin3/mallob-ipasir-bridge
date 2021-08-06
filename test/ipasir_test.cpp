#include "ipasir.h"

int main() {

    //==============
    // Initiate the solver
    //==============
    void* solver = ipasir_init();
    
    ipasir_add(solver, 1);
    ipasir_add(solver, -2);
    ipasir_add(solver, -3);
    ipasir_add(solver, 0);
    ipasir_add(solver, 3);

    ipasir_assume(solver, 2);
    ipasir_assume(solver, 4);

    ipasir_solve(solver);


    //========================
    // Check the written file
    //========================

    
}