#ifndef ROBOT_TYPES_H_
#define ROBOT_TYPES_H_
#include <stdint.h>
typedef float float32_t;
typedef struct pos_struct{
    float32_t x;
    float32_t y;
}pos_st;
typedef struct PI_controller_struct{
    float32_t k_p;
    float32_t k_i;
    float32_t dt;
    float32_t u_max;
    float32_t i_error;
    uint8_t AW;
}PI_controller;
typedef struct state_struct{
    pos_st pos;
    float32_t th;
}state_st;
typedef struct target_struct{
    float32_t v;
    float32_t w;
}target_st;
typedef struct goal_struct{
    pos_st W0;
    pos_st W1;
}goal_st;

#endif /* ROBOT_TYPES_H_ */
