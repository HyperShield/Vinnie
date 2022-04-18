#ifndef PI_SAT_H_
#define PI_SAT_H_
#include "robot_types.h"

void PI_initialize(PI_controller *cont, float32_t _k_p, float32_t _k_i, float32_t _dt, float32_t _u_max);
float32_t PI_calc_u(PI_controller *cont, float32_t error);

#endif /* PI_SAT_H_ */
