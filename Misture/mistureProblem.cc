#include "/home/luan/or-tools/ortools/linear_solver/linear_solver.h"

namespace operations_research {
  void mistureProblem(){
    //Data
    int problemSize = 3;
    std::vector<std::string> nutrients = {"Osso", "Soja", "Peixe", "Ração"};
    std::vector<double> protein = {0.2, 0.5, 0.4, 0.3};
    std::vector<double> calcium = {0.6, 0.4, 0.4, 0.5};
    std::vector<double> cost = {0.56, 0.81, 0.46};

    // Create solver instance
    MPSolver solver("misture_problem", MPSolver::GLOP_LINEAR_PROGRAMMING);
    const double infinity = solver.infinity();

    // Create problem variables
    std::vector<const MPVariable*> x(intensQtd);
    for(int i = 0; i < problemSize; i++){ 
      x[i] = solver.MakeNumVar(0.0, 1.0, "x" + std::to_string(i));
    }

    LOG(INFO) << "Number of variables = " << solver.NumVariables();

    // Declare objective function
    MPObjective* const objective = solver.MutableObjective();
    for(int i = 0; i < problemSize; i++){
      objective->SetCoefficient(x[i], cost[i]);
    }

    objective->SetMinimization();

    // Declare problem constraints
    MPConstraint* const c0 = solver.MakeRowConstraint(protein[intensQtd], infinity);
    for(int i = 0; i < problemSize; i++){
      c0->SetCoefficient(x[i], protein[i]);
    }  

    MPConstraint* const c1 = solver.MakeRowConstraint(calcium[intensQtd], infinity);
    for(int i = 0; i < problemSize; i++){
      c1->SetCoefficient(x[i], calcium[i]);
    }

    MPConstraint* const c2 = solver.MakeRowConstraint(1.0, 1.0);
    for(int i = 0; i < problemSize; i++){
      c2->SetCoefficient(x[i], 1);
    }

    LOG(INFO) << "Number of constraints = " << solver.NumConstraints();

    // Solve the problem
    solver.Solve();

    LOG(INFO) << "Solution:" << std::endl;
    LOG(INFO) << "Objective value = " << objective->Value();
    for(int i = 0; i < problemSize; i++){
      LOG(INFO) << x[i]->name() << " = " << x[i]->solution_value();
    }
  }
}  // namespace operations_research

int main() {
  operations_research::mistureProblem();
  return EXIT_SUCCESS;
}