#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"


/*

arquivo de exemplo fornecido no slide. não funciona com o nosso projeto

*/


// Definicao do pino do LED (GPIO 2)
#define LED_PIN GPIO_NUM_2

static const char *TAG = "MAIN";

void app_main(void) {
    // Configura o pino GPIO do LED como saida
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    ESP_LOGI(TAG, "--- ESP32 (ESP-IDF) Iniciado com Sucesso ---");

    while (1) {

        // Liga o LED
        gpio_set_level(LED_PIN, 1);
        ESP_LOGI(TAG, "LED Estado: LIGADO");
        vTaskDelay(pdMS_TO_TICKS(1000));

        // Desliga o LED
        gpio_set_level(LED_PIN, 0);
        ESP_LOGI(TAG, "LED Estado: DESLIGADO");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}