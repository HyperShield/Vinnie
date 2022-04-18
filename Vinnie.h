#ifndef VINNIE_H_
#define VINNIE_H_
#include <stdint.h>
#include "robot_types.h"

void initialize_Vinnie(uint32_t clk_freq);
void update_Vinnie(void);
void update_odometry(float32_t w_l, float32_t w_r);
float state2w(float32_t v, float32_t w, int8_t s);
/*void update_goal(state_st state,goal_st *goal);*/

#endif /* VINNIE_H_ */
