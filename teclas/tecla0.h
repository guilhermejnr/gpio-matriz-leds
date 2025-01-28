#ifndef TECLA0_H
#define TECLA0_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"

// Função para converter valores RGB para formato PIO
uint32_t converter_cor(float r, float g, float b)
{
  uint32_t cor =
      ((uint32_t)(r * 255) << 16) |
      ((uint32_t)(g * 255) << 8) |
      ((uint32_t)(b * 255));
  return cor;
}

// Função para apagar os LEDs
void apagar_leds(PIO pio, uint sm)
{
  for (int i = 0; i < 25; i++)
  {
    pio_sm_put_blocking(pio, sm, converter_cor(0.0, 0.0, 0.0));
  }
}

// Animação para padrão de expansão e contração de quadrado
void animacao_quadrado_expansivo(PIO pio, uint sm, float intensidade)
{
  // Definição dos frames para o padrão de quadrado expansivo e contrátil
  uint32_t quadrado_frames[5][25] = {
      // Frame 1: Ponto mínimo
      {
          0, 0, 0, 0, 0,
          0, 0, 0, 0, 0,
          0, 0, 1, 0, 0,
          0, 0, 0, 0, 0,
          0, 0, 0, 0, 0},
      // Frame 2: Quadrado pequeno
      {
          0, 0, 0, 0, 0,
          0, 0, 1, 0, 0,
          0, 1, 1, 1, 0,
          0, 0, 1, 0, 0,
          0, 0, 0, 0, 0},
      // Frame 3: Quadrado médio
      {
          0, 0, 1, 0, 0,
          0, 1, 1, 1, 0,
          1, 1, 1, 1, 1,
          0, 1, 1, 1, 0,
          0, 0, 1, 0, 0},
      // Frame 4: Quadrado grande
      {
          0, 1, 1, 1, 0,
          1, 1, 1, 1, 1,
          1, 1, 1, 1, 1,
          1, 1, 1, 1, 1,
          0, 1, 1, 1, 0},
      // Frame 5: Contração de volta ao ponto
      {
          0, 0, 0, 0, 0,
          0, 0, 1, 0, 0,
          0, 1, 1, 1, 0,
          0, 0, 1, 0, 0,
          0, 0, 0, 0, 0}};

  // Sequências de cores para cada frame
  float colors[5][3] = {
      {0.3, 0.0, 0.5}, // Roxo
      {0.5, 0.3, 0.0}, // Laranja
      {0.0, 0.5, 0.3}, // Verde-azulado
      {0.3, 0.3, 0.5}, // Azul-roxo suave
      {0.5, 0.0, 0.5}  // Roxo brilhante
  };

  // Loop da animação
  for (int repeat = 0; repeat < 3; repeat++)
  {
    for (int frame = 0; frame < 5; frame++)
    {
      // Converte o frame para cores dos LEDs
      for (int i = 0; i < 25; i++)
      {
        if (quadrado_frames[frame][i])
        {
          uint32_t cor = converter_cor(
              colors[frame][0] * intensidade,
              colors[frame][1] * intensidade,
              colors[frame][2] * intensidade);
          pio_sm_put_blocking(pio, sm, cor);
        }
        else
        {
          uint32_t cor = converter_cor(0.0, 0.0, 0.0);
          pio_sm_put_blocking(pio, sm, cor);
        }
      }
      sleep_ms(300); // Duração do frame
    }
  }
  // Apaga os LEDs após a animação
  apagar_leds(pio, sm);
}

#endif // TECLA0_H
