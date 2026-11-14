#pragma once
#include <stdbool.h>

void sensors_init(void);
bool ler_estado_chuva(void);      // true = molhado, false = seco
bool ler_fim_de_curso_retraido(void); // GPIO 41
bool ler_fim_de_curso_estendido(void);  // GPIO 42
bool verificar_pressionado(void);     // Botão manual
float ler_estado_umidade(void);       // DHT22