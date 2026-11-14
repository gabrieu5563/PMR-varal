#pragma once
#include "rgb_led.h"

void fsm_init(void);
void fsm_run_iteration(void);
EstadoVaral_t fsm_get_current_state(void);