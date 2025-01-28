#ifndef BUZZER_H
#define BUZZER_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Define o pino do buzzer
#define BUZZER_A 21

void buzzer_init() {
    stdio_init_all();
    gpio_init(BUZZER_A);
    gpio_set_dir(BUZZER_A, GPIO_OUT);
}


void playTone(int frequency, int duration) {
    int delayValue = 1000000 / frequency / 2; // Período da onda
    int numCycles = frequency * duration / 1000; // Cálculo do número de ciclos

    for (int i = 0; i < numCycles; i++) {
        gpio_put(BUZZER_A, 1);  // Aplica HIGH no pino do buzzer
        sleep_us(delayValue);
        gpio_put(BUZZER_A, 0);  // Aplica LOW no pino do buzzer
        sleep_us(delayValue);
    }
}



#endif