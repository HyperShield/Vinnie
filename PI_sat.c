#include "PI_sat.h"

void PI_initialize(PI_controller *cont, float32_t _k_p, float32_t _k_i, float32_t _dt, float32_t _u_max)
{
    cont->k_p = _k_p;
    cont->k_i = _k_i;
    cont->dt = _dt;
    cont->u_max = _u_max;
    cont->i_error = 0.0f;
    cont->AW = 0u;
}
float32_t PI_calc_u(PI_controller *cont, float32_t error)
{
    if(cont->AW == 0u){ /*|| error*cont->i_error < 0)*/
        cont->i_error = cont->i_error + (cont->dt*error);
    }
    float32_t u = (cont->k_p*error) + (cont->k_i*cont->i_error);
    if(u >= cont->u_max){
        u = cont->u_max;
        cont->AW = 1u;
    } else if(u < 0.0f){
        u = 0.0f;
        cont->AW = 1u;
    } else {
        cont->AW = 0u;
    }
    return u;
}
