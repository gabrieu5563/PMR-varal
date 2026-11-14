#include "sensors.h"
#include "driver/gpio.h"
#include "esp_rom_sys.h"

#define PIN_CHUVA 1
#define PIN_LIMIT_RETRAIDO 41
#define PIN_LIMIT_ESTENDIDO 42
#define PIN_BOTAO_MANUAL 2

void sensors_init(void) {
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << PIN_CHUVA) | (1ULL << PIN_LIMIT_RETRAIDO) | 
                        (1ULL << PIN_LIMIT_ESTENDIDO) | (1ULL << PIN_BOTAO_MANUAL),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);
}

bool ler_estado_chuva(void) {
    // Retorna true se houver sinal ativo (switch fechado para GND -> 0, ou aberto -> 1)
    return gpio_get_level(PIN_CHUVA) == 0;
}

bool ler_fim_de_curso_retraido(void) {
    return gpio_get_level(PIN_LIMIT_RETRAIDO) == 0;
}

bool ler_fim_de_curso_estendido(void) {
    return gpio_get_level(PIN_LIMIT_ESTENDIDO) == 0;
}

bool verificar_pressionado(void) {
    if (gpio_get_level(PIN_BOTAO_MANUAL) == 0) {
        esp_rom_delay_us(50000); // Debounce simples
        return gpio_get_level(PIN_BOTAO_MANUAL) == 0;
    }
    return false;
}

float ler_estado_umidade(void) {
    // Simulação do sensor de umidade DHT22 retornado em porcentagem
    return 65.0f; 
}