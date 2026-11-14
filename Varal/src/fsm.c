#include "fsm.h"
#include "sensors.h"
#include "motor.h"
#include "rgb_led.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include <stdio.h>

static EstadoVaral_t current_state = ESTADO_RETRAIDO;
static SemaphoreHandle_t fsm_mutex = NULL;
static int contador_espera = 0;

void fsm_init(void) {
    fsm_mutex = xSemaphoreCreateMutex();
    current_state = ESTADO_RETRAIDO;
    rgb_set_state_color(current_state);
    retrair();
}

EstadoVaral_t fsm_get_current_state(void) {
    EstadoVaral_t state = ESTADO_RETRAIDO; // Inicialização padrão para evitar aviso do compilador
    if (xSemaphoreTake(fsm_mutex, portMAX_DELAY) == pdTRUE) {
        state = current_state;
        xSemaphoreGive(fsm_mutex);
    }
    return state;
}

void fsm_run_iteration(void) {
    if (xSemaphoreTake(fsm_mutex, pdMS_TO_TICKS(100)) != pdTRUE) {
        return;
    }

    bool chuva = ler_estado_chuva();
    bool btn_manual = verificar_pressionado();
    bool limit_retraido = ler_fim_de_curso_retraido();
    bool limit_estendido = ler_fim_de_curso_estendido();
    float umidade = ler_estado_umidade();

    switch (current_state) {
        case ESTADO_RETRAIDO:
            if (btn_manual) {
                printf("[FSM] Retraído -> Estendendo (Botão Manual)\n");
                estender();
                current_state = ESTADO_ESTENDENDO;
            } else {
                contador_espera++;
                if (contador_espera >= 5) {
                    contador_espera = 0;
                    printf("[FSM] Retraído -> Espera\n");
                    current_state = ESTADO_ESPERA;
                }
            }
            retrair();
            break;

        case ESTADO_ESPERA:
            if (chuva || umidade > 80.0f) {
                printf("[FSM] Espera -> Retraindo (Chuva/Umidade alta)\n");
                retrair();
                current_state = ESTADO_RETRAINDO;
            } else {
                printf("[FSM] Estendendo -> Estendido...\n");
                estender();
                current_state = ESTADO_ESTENDENDO;
            }
            break;

        case ESTADO_ESTENDENDO:
            if (chuva) {
                printf("[FSM] Estendendo -> Retraindo (Chuva detectada)\n");
                retrair();
                current_state = ESTADO_RETRAINDO;
            } else if (limit_estendido) {
                printf("[FSM] Estendendo -> Estendido (Fim de curso atingido)\n");
                parar();
                current_state = ESTADO_ESTENDIDO;
            }
            break;

        case ESTADO_ESTENDIDO:
            if (chuva || btn_manual) {
                printf("[FSM] Estendido -> Retraindo (Chuva ou Botão)\n");
                retrair();
                current_state = ESTADO_RETRAINDO;
            }
            break;

        case ESTADO_RETRAINDO:
            if (limit_retraido) {
                printf("[FSM] Retraindo -> Retraído (Fim de curso atingido)\n");
                parar();
                current_state = ESTADO_RETRAIDO;
            }
            break;
    }

    rgb_set_state_color(current_state);
    xSemaphoreGive(fsm_mutex);
}