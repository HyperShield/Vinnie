#ifndef NLGL_H_
#define NLGL_H_
#include "robot_types.h"

void initialize_NLGL(float32_t _L);
void calc_desired(state_st state, goal_st goal, target_st *target);

#endif /* NLGL_H_ */
