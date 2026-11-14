#pragma once

typedef enum {
    ESTADO_RETRAIDO,
    ESTADO_ESPERA,
    ESTADO_ESTENDENDO,
    ESTADO_ESTENDIDO,
    ESTADO_RETRAINDO
} EstadoVaral_t;

void rgb_init(void);
void rgb_set_state_color(EstadoVaral_t estado);