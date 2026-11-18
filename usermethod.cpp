#include <METHODS/usermethod.h>

UserMethod::UserMethod()
{
    addParam(Parameter("population", "50", "Population size"));
    addParam(Parameter("gen_maxiters", "500", "Max iterations"));
    addParam(Parameter("alpha", "0.1", "RSA alpha"));
    addParam(Parameter("beta", "0.005", "RSA beta"));
    addParam(Parameter("tol", "1e-6", "Tolerance for termination"));
    addParam(Parameter("max_stall", "20", "Max iterations without improvement"));
}

void    UserMethod::init()
{
    population = getParam("population").getValue().toInt();
    maxItters = getParam("gen_maxiters").getValue().toInt();
    alpha = getParam("alpha").getValue().toDouble();
    beta = getParam("beta").getValue().toDouble();
    epsilon = getParam("tol").getValue().toDouble();
    max_stall = getParam("max_stall").getValue().toInt();

    dimension = myProblem->getDimension();
    lb_ = myProblem->getLeftMargin();
    ub_ = myProblem->getRightMargin();

    t = 0;
    stall_count = 0;
    Best_Fitness = std::numeric_limits<double>::infinity();
    best_f_old = Best_Fitness;

    X.assign(population, std::vector<double>(dimension));
    fitness.resize(population);

    for (int i = 0; i < population; i++) {
        for (int j = 0; j < dimension; j++) {
            X[i][j] = lb_[j] + (double)rand()/RAND_MAX * (ub_[j] - lb_[j]);
        }
        Data current_x = X[i];
        fitness[i] = myProblem->funmin(current_x);
        if (fitness[i] < Best_Fitness) {
            Best_Fitness = fitness[i];
            Best_Position = X[i];
        }
    }

}

void    UserMethod::step()
{
    double es = 2.0 * ((double)rand()/RAND_MAX - 0.5) * (1.0 - (double)t/maxItters);
    std::vector<std::vector<double>> X_new = X;

    for (int i = 0; i < population; i++) {
        double mean_x = 0;
        for(double val : X[i]) mean_x += val;
        mean_x /= dimension;

        for (int j = 0; j < dimension; j++) {
            int r_idx = rand() % population;
            double r = Best_Position[j] - X[r_idx][j] / (Best_Position[j] + 2.22e-16);
            double p = alpha + (X[i][j] - mean_x) / (Best_Position[j] * (ub_[j] - lb_[j]) + 2.22e-16);
            double eta = Best_Position[j] * p;

            if (t < 0.25 * maxItters)
                X_new[i][j] = Best_Position[j] - eta * beta - r * ((double)rand()/RAND_MAX);
            else if (t < 0.5 * maxItters)
                X_new[i][j] = Best_Position[j] * X[r_idx][j] * es * ((double)rand()/RAND_MAX);
            else if (t < 0.75 * maxItters)
                X_new[i][j] = Best_Position[j] * p * ((double)rand()/RAND_MAX);
            else
                X_new[i][j] = Best_Position[j] - eta * 2.22e-16 - r * ((double)rand()/RAND_MAX);

            // vazo oria
            if (X_new[i][j] < lb_[j]) X_new[i][j] = lb_[j];
            if (X_new[i][j] > ub_[j]) X_new[i][j] = ub_[j];
        }

        Data current_x_new = X_new[i];
        double f_new = myProblem->funmin(current_x_new);
        if (f_new < fitness[i]) {
            X[i] = X_new[i];
            fitness[i] = f_new;
        }
        if (fitness[i] < Best_Fitness) {
            Best_Fitness = fitness[i];
            Best_Position = X[i];
        }
    }
    t++;

}

bool    UserMethod::terminated()
{
    if (t >= maxItters) return true;

    if (std::abs(best_f_old - Best_Fitness) < epsilon) {
        stall_count++;
    } else {
        stall_count = 0;
    }
    best_f_old = Best_Fitness;

    return (stall_count >= max_stall);

}

void    UserMethod::done()
{
    Data final_point = Best_Position;
    double improved_f = localSearch(final_point);

    if (improved_f < Best_Fitness) {
        Best_Fitness = improved_f;
        Best_Position = final_point;
    }

    if(methodLogger) {

        methodLogger->printMessage("Final Optimization Step with Local Search completed.");
    }
}

UserMethod::~UserMethod()
{
    printf("Optimization finished. Best Fitness: %f\n", Best_Fitness);
}
