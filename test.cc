#include "/home/luan/or-tools/ortools/linear_solver/linear_solver.h"

namespace operations_research {
  // Problemas de gestão de produção
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
  void plantingCultivation(){
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
  operations_research::rentPlaning();
  return EXIT_SUCCESS;
}