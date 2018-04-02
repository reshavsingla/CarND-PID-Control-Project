#include <iostream>
#include <cmath>
#include "PID.h"

using namespace std;


/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
    prev_cte = -1.0;
    total_cte = 0.0;
    prev_prev_cte = 0.0;
    best_err = 0.0;
    throttle = 0.3;

    params = {Kp,Kd,Ki};
    params_factor = {0,0,0};
    //params_error = {.003,1,0.000003};
    params_error = {0,0,0};
    current_error = 0;
    step_count = 0;
}

void PID::UpdateError(double cte) {
    /*
    double learning_rate = 0.1;
    Kp = Kp + learning_rate * (cte - prev_cte);
    Ki = Ki + learning_rate * (cte);
    Kd = Kd + learning_rate * (prev_cte - prev_prev_cte);
    prev_prev_cte = prev_cte;
     */

    step_count = step_count + 1;
    int i = current_error;
    double param = params[i];
    double param_factor = params_factor[i];
    double param_error = params_error[i];
    double err = pow(cte,2);
    if (param_factor == 0) {
        param = param + param_error;
        param_factor = 1;
    } else if (param_factor == 1) {
        if (err < best_err) {
            best_err = err;
            param_factor = 0;
            param_error = 1.1 * param_error;
            current_error = (current_error + 1)%3;
        } else {
            param_factor = -1;
            param = param - 2 * param_error;
        }
    } else if (param_factor == -1) {
        if (err < best_err) {
            best_err = err;
            param_factor = 0;
            param_error = 1.1 * param_error;
            current_error = (current_error + 1)%3;
        } else {
            param_factor = 0;
            param = param + param_error;
            param_error = 0.9 * param_error;
            current_error = (current_error + 1)%3;
        }
    }

    params[i] = param;
    params_factor[i] = param_factor;
    params_error[i] = param_error;

    /*
    cout<<"--------------------"<<step_count<<"-----------------------"<<endl;
    cout<<"Kp = "<<params[0]<<endl;
    cout<<"Kd = "<<params[1]<<endl;
    cout<<"Ki = "<<params[2]<<endl;
    */
}

double PID::TotalError() {
}

