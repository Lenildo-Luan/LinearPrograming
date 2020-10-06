#include "/home/luan/or-tools/ortools/linear_solver/linear_solver.h"

namespace operations_research {
  void rentPlaning(){
    //Data
    std::vector<double> costRentMonth = {325.0, 400.0, 405.0, 320.0, 190.0};
    std::vector<double> monthlyDiscountConst = {0.0, 70.0, 160.0, 220.0, 300.0};
    std::vector<double> minimumSpaceMonth = {10000.0, 30000.0, 60000.0, 50000.0, 80000.0};
    int problemSize = 5;

    // Create solver instance
    MPSolver solver("misture_problem", MPSolver::GLOP_LINEAR_PROGRAMMING);
    const double infinity = solver.infinity();

    // Create problem variables
    std::vector<const MPVariable*> x(problemSize);
    for(int i = 0; i < problemSize; i++){ 
      x[i] = solver.MakeNumVar(0.0, infinity, "x" + std::to_string(i));
    }

    LOG(INFO) << "Number of variables = " << solver.NumVariables();

    // Declare objective function
    MPObjective* const objective = solver.MutableObjective();
    for(int i = 0; i < problemSize; i++){
      objective->SetCoefficient(x[i], costRentMonth[i] - monthlyDiscountConst[problemSize-i-1]);
    }

    objective->SetMinimization();

    // Declare problem constraints
    std::vector<MPConstraint*> c0(problemSize);
    for(int i = 0; i < problemSize; i++){
      c0[i] = solver.MakeRowConstraint(minimumSpaceMonth[i], infinity);
      for(int j = 0; j < i+1; j++){
        c0[i]->SetCoefficient(x[j], 1);
      }
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
  operations_research::consultantsAllocation();
  return EXIT_SUCCESS;
}