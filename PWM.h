#ifndef PWM_H_
#define PWM_H_
#include "robot_types.h"

void initialize_pwm(uint32_t clk_freq);
void start_pwm(void);
void stop_pwm(void);
void set_left_pwm(float32_t val);
void set_right_pwm(float32_t val);

#endif /* PWM_H_ */
