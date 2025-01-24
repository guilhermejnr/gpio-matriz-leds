#include "pico/stdlib.h"
#include <stdint.h>

// Configurações principais
#define NUMERO_LEDS 25
#define PINO_LED 2

// Definição de cores (formato RGB 24-bit)
#define DESLIGADO 0x000000
#define VERMELHO 0xFF0000
#define VERDE 0x00FF00
#define AZUL 0x0000FF
#define BRANCO 0xFFFFFF

// Matriz global de LEDs
uint32_t leds[NUMERO_LEDS];

// Função para simular atualização de LEDs
void definir_leds(uint32_t* leds, uint32_t num_leds) {
    for (int i = 0; i < num_leds; i++) {
        printf("LED %d: %06X\n", i, leds[i]);
    }
}

// Inicialização dos LEDs
void inicializar_leds() {
    gpio_init(PINO_LED);
    gpio_set_dir(PINO_LED, GPIO_OUT);
    
    for (int i = 0; i < NUMERO_LEDS; i++) {
        leds[i] = DESLIGADO;
    }
    definir_leds(leds, NUMERO_LEDS);
}

// Limpar todos os LEDs
void limpar_leds() {
    for (int i = 0; i < NUMERO_LEDS; i++) {
        leds[i] = DESLIGADO;
    }
    definir_leds(leds, NUMERO_LEDS);
}

// ===== ESPAÇOS PARA ANIMAÇÕES DOS MEMBROS DA EQUIPE =====

// TODO: Membro 1 - Animação para tecla 0
// Requisitos:
// - Mínimo de 5 quadros
// - Use cores personalizadas
// - Animação criativa e fluida
void animacao_tecla_0() {
    // Espaço para implementação do Membro 1
    limpar_leds();
    // Implementar animação aqui
}

// TODO: Membro 2 - Animação para tecla 1
void animacao_tecla_1() {
    // Espaço para implementação do Membro 2
    limpar_leds();
    // Implementar animação aqui
}

// TODO: Membro 3 - Animação para tecla 2
void animacao_tecla_2() {
    // Espaço para implementação do Membro 3
    limpar_leds();
    // Implementar animação aqui
}

// TODO: Membro 4 - Animação para tecla 3
void animacao_tecla_3() {
    // Espaço para implementação do Membro 4
    limpar_leds();
    // Implementar animação aqui
}

// TODO: Membro 5 - Animação para tecla 4
void animacao_tecla_4() {
    // Espaço para implementação do Membro 5
    limpar_leds();
    // Implementar animação aqui
}

// Processamento das teclas
void processar_tecla(char tecla) {
    switch (tecla) {
        case '0': animacao_tecla_0(); break;
        case '1': animacao_tecla_1(); break;
        case '2': animacao_tecla_2(); break;
        case '3': animacao_tecla_3(); break;
        case '4': animacao_tecla_4(); break;
        
        // Funções especiais conforme requisitos
        case 'A': limpar_leds(); break;
        case 'B': 
            for (int i = 0; i < NUMERO_LEDS; i++) leds[i] = AZUL;
            definir_leds(leds, NUMERO_LEDS);
            break;
        case 'C': 
            for (int i = 0; i < NUMERO_LEDS; i++) leds[i] = 0xCC0000;
            definir_leds(leds, NUMERO_LEDS);
            break;
        case 'D': 
            for (int i = 0; i < NUMERO_LEDS; i++) leds[i] = 0x007F00;
            definir_leds(leds, NUMERO_LEDS);
            break;
        case '#': 
            for (int i = 0; i < NUMERO_LEDS; i++) leds[i] = 0x333333;
            definir_leds(leds, NUMERO_LEDS);
            break;
        default: 
            limpar_leds();
            break;
    }
}

int main() {
    stdio_init_all();
    inicializar_leds();

    char tecla;
    while (1) {
        printf("Pressione uma tecla (0-4, A-D, #): ");
        tecla = getchar();
        getchar(); // Consumir quebra de linha
        processar_tecla(tecla);
    }
}