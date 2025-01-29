#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"

// arquivo .pio
#include "pio_matrix.pio.h"

#include "teclas/tecla1.h"
#include "teclas/tecla3.h"
#include "teclas/tecla4.h"
#include "teclas/tecla0.h"

#define NUM_PIXELS 25
#define OUT_PIN 7

// botões de interrupção
const uint button;

// Definindo pinos das linhas e colunas do teclado matricial
#define R1 9
#define R2 8
#define R3 10
#define R4 6
#define C1 5
#define C2 4
#define C3 3
#define C4 2

#define INTENSIDADE_ALTA 1.0
#define INTENSIDADE_MEDIA 0.8
#define INTENSIDADE_BAIXA 0.5
#define INTENSIDADE_MINIMA 0.2

// Função para inicializar pinos do teclado
void init_teclado()
{
  gpio_init(R1);
  gpio_init(R2);
  gpio_init(R3);
  gpio_init(R4);
  gpio_init(C1);
  gpio_init(C2);
  gpio_init(C3);
  gpio_init(C4);
  gpio_set_dir(R1, GPIO_OUT);
  gpio_set_dir(R2, GPIO_OUT);
  gpio_set_dir(R3, GPIO_OUT);
  gpio_set_dir(R4, GPIO_OUT);
  gpio_set_dir(C1, GPIO_IN);
  gpio_set_dir(C2, GPIO_IN);
  gpio_set_dir(C3, GPIO_IN);
  gpio_set_dir(C4, GPIO_IN);
  gpio_pull_up(C1);
  gpio_pull_up(C2);
  gpio_pull_up(C3);
  gpio_pull_up(C4);
}

// Leitura do teclado
char keypad_leitura()
{
  char teclado[4][4] = {
      {'1', '2', '3', 'A'},
      {'4', '5', '6', 'B'},
      {'7', '8', '9', 'C'},
      {'*', '0', '#', 'D'}};
  int linhas[] = {R1, R2, R3, R4};
  int colunas[] = {C1, C2, C3, C4};

  for (int lin = 0; lin < 4; lin++)
  {
    gpio_put(linhas[lin], 0);
    for (int col = 0; col < 4; col++)
    {
      if (!gpio_get(colunas[col]))
      {
        sleep_ms(100);
        gpio_put(linhas[lin], 1);
        return (teclado[lin][col]);
      }
    }
    gpio_put(linhas[lin], 1);
  }
  return '\0';
}

int main()
{
  PIO pio = pio0;
  bool ok;
  uint32_t cor;

  char tecla = '\0';

  // frequência de clock para 128 MHz
  ok = set_sys_clock_khz(128000, false);

  init_teclado();
  stdio_init_all();

  printf("Iniciando o controle dos LEDs\n");

  uint offset = pio_add_program(pio, &pio_matrix_program);
  uint sm = pio_claim_unused_sm(pio, true);
  pio_matrix_program_init(pio, sm, offset, OUT_PIN);

  while (true)
  {
    while (tecla == '\0')
    {
      tecla = keypad_leitura();
      sleep_ms(50);
    }
    printf("tecla %c\n", tecla);
    if (tecla == 'A')
    {
      cor = matrix_rgb(0.0, 0.0, 0.0);
      controlar_leds(pio, sm, cor);
      printf("Desligando todos os LEDs\n");
    }
    else if (tecla == 'B')
    {
      cor = matrix_rgb(INTENSIDADE_ALTA, 0.0, 0.0); // Azul
      controlar_leds(pio, sm, cor);
      printf("Ligando todos os LEDs na cor azul\n");
    }
    else if (tecla == 'C')
    {
      cor = matrix_rgb(0.0, INTENSIDADE_MEDIA, 0.0); // Vermelho
      controlar_leds(pio, sm, cor);
      printf("Ligando todos os LEDs na cor vermelha\n");
    }
    else if (tecla == 'D')
    {
      cor = matrix_rgb(0.0, 0.0, INTENSIDADE_BAIXA); // Verde
      controlar_leds(pio, sm, cor);
      printf("Ligando todos os LEDs na cor verde\n");
    }
    else if (tecla == '#')
    {
      cor = matrix_rgb(INTENSIDADE_MINIMA, INTENSIDADE_MINIMA, INTENSIDADE_MINIMA); // Branco
      controlar_leds(pio, sm, cor);
      printf("Ligando todos os LEDs na cor branca\n");
    }
    else if (tecla == '*')
    {
      printf("Saindo do modo de execução e habilitando o modo de gravação\n");
      modo_gravacao();
    }
    else if (tecla == '0')
    {
      printf("Exibindo animação quadrado expansivo\n");
      animacao_quadrado_expansivo(pio, sm, INTENSIDADE_ALTA);
    }
    else if (tecla == '1')
    {
      printf("Exibindo os rostos e suas emoções\n");
      animacao_rostos(pio, sm, INTENSIDADE_MEDIA);
    }
    else if (tecla == '3')
    {
      printf("Exibindo animação de chamas\n");
      animacao_chama(pio, sm, INTENSIDADE_BAIXA);
    }
    else if (tecla == '4')
    {
      printf("Exibindo animação da cruz de malta\n");
      animacao_malta_cruz(pio, sm, INTENSIDADE_MEDIA);
    }
    else
    {
      printf("%c", tecla);
    }
    tecla = '\0';
    sleep_ms(100);
  }
}
