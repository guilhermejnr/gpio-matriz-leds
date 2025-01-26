#ifndef TECLA4_H
#define TECLA4_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"

// Função para converter valores RGB para formato PIO
uint32_t converter_cor(float r, float g, float b) {
    uint32_t cor = 
        ((uint32_t)(r * 255) << 16) |
        ((uint32_t)(g * 255) << 8)  |
        ((uint32_t)(b * 255));
    return cor;
}

// Animation for Malta Cross pattern
void animacao_malta_cruz(PIO pio, uint sm, float intensidade) {
    // Define the Malta Cross pattern frames
    uint32_t cruz_frames[5][25] = {
        // Frame 1: Minimal cross
        {
            0,0,1,0,0,
            0,0,1,0,0,
            1,1,1,1,1,
            0,0,1,0,0,
            0,0,1,0,0
        },
        // Frame 2: Expanding cross (Red)
        {
            0,0,1,0,0,
            0,1,1,1,0,
            1,1,1,1,1,
            0,1,1,1,0,
            0,0,1,0,0
        },
        // Frame 3: Full cross (Green)
        {
            0,1,1,1,0,
            1,1,1,1,1,
            1,1,1,1,1,
            1,1,1,1,1,
            0,1,1,1,0
        },
        // Frame 4: Contracting cross (Blue)
        {
            0,0,1,0,0,
            0,1,1,1,0,
            1,1,1,1,1,
            0,1,1,1,0,
            0,0,1,0,0
        },
        // Frame 5: Back to minimal cross
        {
            0,0,1,0,0,
            0,0,1,0,0,
            1,1,1,1,1,
            0,0,1,0,0,
            0,0,1,0,0
        }
    };

    // Color sequences for each frame
    float colors[5][3] = {
        {0.5, 0.0, 0.0},   // Dark Red
        {0.0, 0.5, 0.0},   // Dark Green
        {0.0, 0.0, 0.5},   // Dark Blue
        {0.5, 0.5, 0.0},   // Yellow-ish
        {0.0, 0.5, 0.5}    // Cyan-ish
    };

    // Animation loop
    for (int repeat = 0; repeat < 3; repeat++) {
        for (int frame = 0; frame < 5; frame++) {
            // Convert frame to LED colors
            for (int i = 0; i < 25; i++) {
                if (cruz_frames[frame][i]) {
                    uint32_t cor = converter_cor(
                        colors[frame][0] * intensidade, 
                        colors[frame][1] * intensidade, 
                        colors[frame][2] * intensidade
                    );
                    pio_sm_put_blocking(pio, sm, cor);
                } else {
                    uint32_t cor = converter_cor(0.0, 0.0, 0.0);
                    pio_sm_put_blocking(pio, sm, cor);
                }
            }
            sleep_ms(300);  // Frame duration
        }
    }
}

#endif // TECLA4_H