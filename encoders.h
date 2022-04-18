#ifndef ENCODERS_H_
#define ENCODERS_H_
#include <stdint.h>
#include "robot_types.h"

void initialize_encoders(uint32_t clk_freq);
float32_t calc_w_r(void);
float32_t calc_w_l(void);

#endif /* ENCODERS_H_ */
