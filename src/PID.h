#ifndef PID_H
#define PID_H
#include "vector"

class PID {
public:
  double prev_prev_cte;
  double prev_cte;
  double total_cte;
  double best_err;
  double throttle;
  int step_count;

  std::vector<double> params;
  std::vector<double > params_factor;
  std::vector<double > params_error;
  int current_error;
    /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();
};

#endif /* PID_H */
