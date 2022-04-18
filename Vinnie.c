#include "msp.h"
#include "math.h"
#include "Vinnie.h"
#include "encoders.h"
#include "PWM.h"
#include "PI_sat.h"
#include "NLGL.h"

state_st state;
target_st target;
goal_st waypoints;
float32_t r;
float32_t l;
float32_t dt;

PI_controller PI_left;
PI_controller PI_right;

void initialize_Vinnie(uint32_t clk_freq)
{
    r = 0.035f;
    l = 0.15f/2.0f;
    dt = 0.01f;
    state.pos.x = 0.0f;
    state.pos.y = 0.0f;
    state.th = 0.0f;
    target.v = 0.0f;
    target.w = 0.0f;
    waypoints.W0.x = 0.0f;
    waypoints.W0.y = 1.0f;
    waypoints.W1.x = 1.0f;
    waypoints.W1.y = 2.0f;
    initialize_encoders(clk_freq);
    PI_initialize(&PI_left, 0.1f, 0.5f, dt, 4.5f);
    PI_initialize(&PI_right, 0.1f, 0.5f, dt, 4.5f);
    initialize_pwm(clk_freq);
    initialize_NLGL(0.5f);
    start_pwm();
}

void update_Vinnie(void)
{
    /*Measure wheels velocities*/
    float32_t w_r = calc_w_r();
    float32_t w_l = calc_w_l();
    /*Update state*/
    update_odometry(w_l,w_r);
    /*update_goal(state,&waypoints);*/
    /*Calc desired wheel velocities*/
    calc_desired(state,waypoints,&target);
    float32_t w_r_d = state2w(target.v,target.w,1);
    float32_t w_l_d = state2w(target.v,target.w,-1);
    /*Calc control signal for actuators*/
    float32_t u_l = PI_calc_u(&PI_left, w_l_d-w_l);
    float32_t u_r = PI_calc_u(&PI_right, w_r_d-w_r);
    /*Apply control signal to actuators*/
    set_left_pwm(u_l/PI_left.u_max);
    set_right_pwm(u_r/PI_right.u_max);
}

void update_odometry(float32_t w_l, float32_t w_r)
{
    float32_t v = (r*(w_l+w_r))/2.0f;
    float32_t w = (r*(w_r-w_l))/(2.0f*l);

    float32_t dot_x = v*cosf(state.th);
    float32_t dot_y = v*sinf(state.th);
    float32_t dot_th = w;

    state.pos.x = state.pos.x + (dt*dot_x);
    state.pos.y = state.pos.y + (dt*dot_y);
    state.th = state.th + (dt*dot_th);
}

/*void update_goal(state_st state,goal_st *goal)
{
    if(sqrtf((goal->W1.x-state.pos.x)*(goal->W1.x-state.pos.x)+(goal->W1.y-state.pos.y)*(goal->W1.y-state.pos.y)) < 0.1){
        if(++i>=N)
            i=0;
    }
    goal->W0.x = goal->W1.x;
    goal->W0.y = goal->W1.y;
    goal->W1.x = path[i][0];
    goal->W1.y = path[i][1];
}*/
float32_t state2w(float32_t v, float32_t w, int8_t s)
{
    return s > 0 ? (v+(w*l))/r : (v-(w*l))/r;
}
