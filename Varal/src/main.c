#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sensors.h"
#include "motor.h"
#include "rgb_led.h"
#include "fsm.h"

void fsm_task(void *pvParameters) {
    while (1) {
        fsm_run_iteration();
        vTaskDelay(pdMS_TO_TICKS(500)); // Executa a FSM a cada 500ms
    }
}

void app_main(void) {
    printf("=== Inicializando Sistema Varal Inteligente ===\n");
    
    // Inicialização de hardware e módulos
    sensors_init();
    motor_init();
    rgb_init();
    fsm_init();

    // Criação da Tarefa FreeRTOS para a FSM
    xTaskCreate(fsm_task, "fsm_task", 4096, NULL, 5, NULL);
}