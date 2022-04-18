#include "NLGL.h"
#include "robot_types.h"
#include "math.h"

float32_t L;

void initialize_NLGL(float32_t _L)
{
    L = _L;
}
void calc_desired(state_st state, goal_st goal, target_st *target)
{
    float32_t norm_s = sqrtf(((goal.W1.x-goal.W0.x)*(goal.W1.x-goal.W0.x))+((goal.W1.y-goal.W0.y)*(goal.W1.y-goal.W0.y)));
    float32_t sx = (goal.W1.x-goal.W0.x)/norm_s;
    float32_t sy = (goal.W1.y-goal.W0.y)/norm_s;
    float32_t p0x = goal.W0.x;
    float32_t p0y = goal.W0.y;
    float32_t px = state.pos.x;
    float32_t py = state.pos.y;

    float32_t b = (sx*(p0x-px))+(sy*(p0y-py));
    float32_t c = (((p0x-px)*(p0x-px))+((p0y-py)*(p0y-py)))-(L*L);
    float32_t t;
    if(c < (b*b)){
        t = -b+sqrtf((b*b)-c);
    } else {
        t = -b;
    }
    float32_t p1x = p0x + (t*sx);
    float32_t p1y = p0y + (t*sy);
    float32_t eta = atan2f(p1y-state.pos.y,p1x-state.pos.x)-state.th;

    target->v = 0.4f;
    target->w = (2.0f*target->v*sinf(eta))/L;
}

