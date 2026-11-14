#include "rgb_led.h"
#include "driver/gpio.h"

#define PIN_RGB_R 20
#define PIN_RGB_G 19
#define PIN_RGB_B 18

void rgb_init(void) {
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << PIN_RGB_R) | (1ULL << PIN_RGB_G) | (1ULL << PIN_RGB_B),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);
}

void rgb_set_state_color(EstadoVaral_t estado) {
    switch (estado) {
        case ESTADO_RETRAIDO:   // Vermelho
            gpio_set_level(PIN_RGB_R, 1);
            gpio_set_level(PIN_RGB_G, 0);
            gpio_set_level(PIN_RGB_B, 0);
            break;
        case ESTADO_ESPERA:     // Amarelo
            gpio_set_level(PIN_RGB_R, 1);
            gpio_set_level(PIN_RGB_G, 1);
            gpio_set_level(PIN_RGB_B, 0);
            break;
        case ESTADO_ESTENDENDO: // Ciano
            gpio_set_level(PIN_RGB_R, 0);
            gpio_set_level(PIN_RGB_G, 1);
            gpio_set_level(PIN_RGB_B, 1);
            break;
        case ESTADO_ESTENDIDO:  // Verde
            gpio_set_level(PIN_RGB_R, 0);
            gpio_set_level(PIN_RGB_G, 1);
            gpio_set_level(PIN_RGB_B, 0);
            break;
        case ESTADO_RETRAINDO:  // Magenta
            gpio_set_level(PIN_RGB_R, 1);
            gpio_set_level(PIN_RGB_G, 0);
            gpio_set_level(PIN_RGB_B, 1);
            break;
    }
}