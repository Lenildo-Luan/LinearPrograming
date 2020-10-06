#include "/home/luan/or-tools/ortools/linear_solver/linear_solver.h"

namespace operations_research {
  void consultantsAllocation(){
    // Create solver instance
    MPSolver solver("misture_problem", MPSolver::GLOP_LINEAR_PROGRAMMING);
    const double infinity = solver.infinity();

    // Create problem variables
    std::vector<const MPVariable*> x(7);
    for(int i = 0; i < 7; i++){ 
      x[i] = solver.MakeNumVar(0, infinity, "x" + std::to_string(i));
    }

    LOG(INFO) << "Number of variables = " << solver.NumVariables();

    // Declare objective function
    MPObjective* const objective = solver.MutableObjective();
    for(int i = 0; i < 4; i++){
      objective->SetCoefficient(x[i], 120);
    }

    for(int i = 4; i < 7; i++){
      objective->SetCoefficient(x[i], 320);
    }

    objective->SetMinimization();

    // Declare problem constraints
    MPConstraint* c0 = solver.MakeRowConstraint(4.0, infinity);
    c0->SetCoefficient(x[0], 1);   
    c0->SetCoefficient(x[4], 1);  

    MPConstraint* c1 = solver.MakeRowConstraint(8.0, infinity);
    c1->SetCoefficient(x[1], 1);   
    c1->SetCoefficient(x[4], 1);
    c1->SetCoefficient(x[5], 1);

    MPConstraint* c2 = solver.MakeRowConstraint(10.0, infinity);
    c2->SetCoefficient(x[2], 1);   
    c2->SetCoefficient(x[5], 1);
    c2->SetCoefficient(x[6], 1);      

    MPConstraint* c3 = solver.MakeRowConstraint(6.0, infinity);
    c3->SetCoefficient(x[3], 1);   
    c3->SetCoefficient(x[6], 1);  

    MPConstraint* c5 = solver.MakeRowConstraint(0, infinity);
    c5->SetCoefficient(x[4], 1); 
    c5->SetCoefficient(x[0], -2);

    MPConstraint* c6 = solver.MakeRowConstraint(0, infinity);
    c6->SetCoefficient(x[4], 1); 
    c6->SetCoefficient(x[5], 1); 
    c6->SetCoefficient(x[1], -2);

    MPConstraint* c7 = solver.MakeRowConstraint(0, infinity);
    c7->SetCoefficient(x[5], 1); 
    c7->SetCoefficient(x[6], 1); 
    c7->SetCoefficient(x[2], -2);

    MPConstraint* c8 = solver.MakeRowConstraint(0, infinity);
    c8->SetCoefficient(x[6], 1);
    c8->SetCoefficient(x[3], -2); 

    LOG(INFO) << "Number of constraints = " << solver.NumConstraints();

    // Solve the problem
    solver.Solve();

    LOG(INFO) << "Solution:" << std::endl;
    LOG(INFO) << "Objective value = " << objective->Value();
    for(int i = 0; i < 7; i++){ 
      LOG(INFO) << x[i]->name() << " = " << x[i]->solution_value();
    }
  }
}  // namespace operations_research

int main() {
  operations_research::consultantsAllocation();
  return EXIT_SUCCESS;
}