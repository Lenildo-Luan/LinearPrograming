#include "/home/luan/or-tools/ortools/linear_solver/linear_solver.h"

namespace operations_research {
  void productionProducts(){
    std::vector<std::string> products = {"A", "B"};
    std::vector<double> price = {10.0, 20.0};
    std::vector<std::string> resources = {"R1", "R2", "R3"};
    std::vector<double> availableResources = {10.0, 20.0, 20.0};
    std::vector< std::vector<double> > requiredResources = {{2.0, 3.0, 2.0},
                                             {1.0, 3.0, 4.0}};
    int productsQtd = products.size();
    int resourcesQtd = resources.size();

    // Create solver instance
    MPSolver solver("misture_problem", MPSolver::GLOP_LINEAR_PROGRAMMING);
    const double infinity = solver.infinity();

    // Create problem variables
    std::vector<const MPVariable*> x(productsQtd);
    for(int i = 0; i < productsQtd; i++){ 
      x[i] = solver.MakeNumVar(0, infinity, "x" + std::to_string(i));
    }

    LOG(INFO) << "Number of variables = " << solver.NumVariables();

    // Declare objective function
    MPObjective* const objective = solver.MutableObjective();
    for(int i = 0; i < productsQtd; i++){
      objective->SetCoefficient(x[i], price[i]);
    }

    objective->SetMaximization();

    // Declare problem constraints
    std::vector<MPConstraint*> c0(resourcesQtd);
    for(int i = 0; i < resourcesQtd; i++){
      c0[i] = solver.MakeRowConstraint(0.0, availableResources[i]);
      for(int j = 0; j < productsQtd; j++){
        c0[i]->SetCoefficient(x[j], requiredResources[j][i]);
      }
    }    

    LOG(INFO) << "Number of constraints = " << solver.NumConstraints();

    // Solve the problem
    solver.Solve();

    LOG(INFO) << "Solution:" << std::endl;
    LOG(INFO) << "Objective value = " << objective->Value();
    for(int i = 0; i < productsQtd; i++){ 
      LOG(INFO) << x[i]->name() << " = " << x[i]->solution_value();
    }
  
  }
}  // namespace operations_research

int main() {
  operations_research::productionProducts();
  return EXIT_SUCCESS;
}