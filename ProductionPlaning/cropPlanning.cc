#include "/home/luan/or-tools/ortools/linear_solver/linear_solver.h"

namespace operations_research {
  void cropPlanning(){
    // Data
    double cultivableArea = 200000.0;
    double warehouseCapacity = 60000.0;
    std::vector<std::string> cultivation = {"Trigo", "Arroz", "Milho"};
    std::vector<double> productivity = {0.2, 0.3, 0.4};
    std::vector<double> profit = {0.11, 0.04, 0.02};
    std::vector<double> demand = {400.0, 800.0, 10000.0};
    int problemSize = cultivation.size();
    
    // Create solver instance
    MPSolver solver("misture_problem", MPSolver::GLOP_LINEAR_PROGRAMMING);
    const double infinity = solver.infinity();

    // Create problem variables
    std::vector<const MPVariable*> x(problemSize);
    for(int i = 0; i < problemSize; i++){ 
      x[i] = solver.MakeNumVar(demand[i], infinity, "x" + std::to_string(i));
    }

    LOG(INFO) << "Number of variables = " << solver.NumVariables();

    // Declare objective function
    MPObjective* const objective = solver.MutableObjective();
    for(int i = 0; i < problemSize; i++){
      objective->SetCoefficient(x[i], productivity[i]*profit[i]);
    }

    objective->SetMaximization();

    // Declare problem constraints
    MPConstraint* const c0 = solver.MakeRowConstraint(0.0, cultivableArea);
    for(int i = 0; i < problemSize; i++){
      c0->SetCoefficient(x[i], 1);
    } 

    MPConstraint* const c1 = solver.MakeRowConstraint(0.0, warehouseCapacity);
    for(int i = 0; i < problemSize; i++){
      c1->SetCoefficient(x[i], productivity[i]);
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
  operations_research::cropPlanning();
  return EXIT_SUCCESS;
}