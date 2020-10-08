#include "/home/luan/or-tools/ortools/linear_solver/linear_solver.h"

namespace operations_research {
  void productTransport(){
    //Data
    std::vector< std::vector<double> > transportCost = {{3.0, 7.0, 0.0}, {4.0, 0.0, 9.0}, {0.0, 2.0, 4.0}};
    std::vector<double> factoryProduction = {-80.0, -70.0};
    std::vector<double> alocation = {60.0, 90.0};
    int problemSize = 3;

    // Create solver instance
    MPSolver solver("misture_problem", MPSolver::GLOP_LINEAR_PROGRAMMING);
    const double infinity = solver.infinity();

    // Create problem variables
    std::vector< std::vector<const MPVariable*> > x;

    for(int i = 0; i < problemSize; i++){ 
        std::vector<const MPVariable*> y(problemSize);
        x.push_back(y);
        
        for(int j = 0; j < problemSize; j++){
            x[i][j] = solver.MakeNumVar(0.0, infinity, "x" + std::to_string(i) + std::to_string(j) );
        }
    }

    LOG(INFO) << "Number of variables = " << solver.NumVariables();

    // Declare objective function
    MPObjective* const objective = solver.MutableObjective();
    for(int i = 0; i < problemSize; i++){
        for(int j = 0; j < problemSize; j++){
            objective->SetCoefficient(x[i][j], transportCost[i][j]);
        }
    }

    objective->SetMinimization();

    // Declare problem constraints
    MPConstraint* factory1 = solver.MakeRowConstraint(factoryProduction[0], factoryProduction[0]);
    factory1->SetCoefficient(x[0][0], -1);
    factory1->SetCoefficient(x[0][1], -1);
    factory1->SetCoefficient(x[0][2], -1);

    MPConstraint* factory2 = solver.MakeRowConstraint(factoryProduction[1], factoryProduction[1]);
    factory2->SetCoefficient(x[1][0], -1);
    factory2->SetCoefficient(x[1][1], -1);
    factory2->SetCoefficient(x[1][2], -1);

    MPConstraint* distributionCenter = solver.MakeRowConstraint(0.0, 0.0);
    distributionCenter->SetCoefficient(x[0][0], 1);
    distributionCenter->SetCoefficient(x[1][0], 1);
    distributionCenter->SetCoefficient(x[2][1], -1);
    distributionCenter->SetCoefficient(x[2][2], -1);

    MPConstraint* deposit1 = solver.MakeRowConstraint(alocation[0], alocation[0]); 
    deposit1->SetCoefficient(x[0][1], 1);
    deposit1->SetCoefficient(x[1][1], 1);
    deposit1->SetCoefficient(x[2][1], 1);

    MPConstraint* deposit2 = solver.MakeRowConstraint(alocation[1], alocation[1]); 
    deposit2->SetCoefficient(x[0][2], 1);
    deposit2->SetCoefficient(x[1][2], 1);
    deposit2->SetCoefficient(x[2][2], 1);

    LOG(INFO) << "Number of constraints = " << solver.NumConstraints();

    // Solve the problem
    solver.Solve();

    LOG(INFO) << "Solution:" << std::endl;
    LOG(INFO) << "Objective value = " << objective->Value();
    for(int i = 0; i < problemSize; i++){
        for(int j = 0; j < problemSize; j++){
            LOG(INFO) << x[i][j]->name() << " = " << x[i][j]->solution_value();
        }
    }
  }
  void productTransport2(){
        //Data
    std::vector< std::vector<double> > transportCost = {{880.0, 1020.0, 1080.0}, {1000.0, 1040.0, 1070.0}, {0.0, 40.0, 50.0}};
    std::vector<double> factoryProduction = {-500.0, -500.0};
    std::vector<double> alocation = {400.0, 300.0};
    int problemSize = 3;

    // Create solver instance
    MPSolver solver("misture_problem", MPSolver::GLOP_LINEAR_PROGRAMMING);
    const double infinity = solver.infinity();

    // Create problem variables
    std::vector< std::vector<const MPVariable*> > x;

    for(int i = 0; i < problemSize; i++){ 
        std::vector<const MPVariable*> y(problemSize);
        x.push_back(y);
        
        for(int j = 0; j < problemSize; j++){
            x[i][j] = solver.MakeNumVar(0.0, infinity, "x" + std::to_string(i) + std::to_string(j) );
        }
    }

    LOG(INFO) << "Number of variables = " << solver.NumVariables();

    // Declare objective function
    MPObjective* const objective = solver.MutableObjective();
    for(int i = 0; i < problemSize; i++){
        for(int j = 0; j < problemSize; j++){
            objective->SetCoefficient(x[i][j], transportCost[i][j]);
        }
    }

    objective->SetMinimization();

    // Declare problem constraints
    MPConstraint* factory1 = solver.MakeRowConstraint(factoryProduction[0], 0.0);
    factory1->SetCoefficient(x[0][0], -1);
    factory1->SetCoefficient(x[0][1], -1);
    factory1->SetCoefficient(x[0][2], -1);

    MPConstraint* factory2 = solver.MakeRowConstraint(factoryProduction[1], 0.0);
    factory2->SetCoefficient(x[1][0], -1);
    factory2->SetCoefficient(x[1][1], -1);
    factory2->SetCoefficient(x[1][2], -1);

    MPConstraint* distributionCenter = solver.MakeRowConstraint(0.0, 0.0);
    distributionCenter->SetCoefficient(x[0][0], 1);
    distributionCenter->SetCoefficient(x[1][0], 1);
    distributionCenter->SetCoefficient(x[2][1], -1);
    distributionCenter->SetCoefficient(x[2][2], -1);

    MPConstraint* deposit1 = solver.MakeRowConstraint(alocation[0], alocation[0]); 
    deposit1->SetCoefficient(x[0][1], 1);
    deposit1->SetCoefficient(x[1][1], 1);
    deposit1->SetCoefficient(x[2][1], 1);

    MPConstraint* deposit2 = solver.MakeRowConstraint(alocation[1], alocation[1]); 
    deposit2->SetCoefficient(x[0][2], 1);
    deposit2->SetCoefficient(x[1][2], 1);
    deposit2->SetCoefficient(x[2][2], 1);

    LOG(INFO) << "Number of constraints = " << solver.NumConstraints();

    // Solve the problem
    solver.Solve();

    LOG(INFO) << "Solution:" << std::endl;
    LOG(INFO) << "Objective value = " << objective->Value();
    for(int i = 0; i < problemSize; i++){
        for(int j = 0; j < problemSize; j++){
            LOG(INFO) << x[i][j]->name() << " = " << x[i][j]->solution_value();
        }
    }  
  }
}  // namespace operations_research

int main() {
  operations_research::productTransport2();
  return EXIT_SUCCESS;
}