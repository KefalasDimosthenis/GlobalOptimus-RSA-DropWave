#ifndef USERMETHOD_H
#define USERMETHOD_H
# include <OPTIMUS/optimizer.h>

/**
 * @brief The UserMethod class is the skeleton class for the used defined optimization methods. The user should extend this class.
 */
class UserMethod :public Optimizer
{
private:
    int population, dimension, maxItters, t;
    std::vector<double> lb_, ub_;
    double alpha, beta, epsilon;
    int stall_count, max_stall;
    double best_f_old;

    std::vector<std::vector<double>> X;
    std::vector<double> fitness;
    std::vector<double> Best_Position;
    double Best_Fitness;

public:
    /**
     * @brief UserMethod
     */
    UserMethod();
    /**
     * @brief init
     */
    virtual void init();
    /**
     * @brief step
     */
    virtual void step();
    /**
     * @brief terminated
     * @return
     */
    virtual bool terminated();
    /**
     * @brief done
     */
    virtual void done();
    /**
     * @brief ~UserMethod
     */
    virtual ~UserMethod();
};

#endif // USERMETHOD_H
