#ifndef CONFIG_H
#define CONFIG_H

// Inclusão de bibliotecas padrão
#include <stdio.h>  // Biblioteca para funções de entrada e saída, como printf e scanf
#include <stdlib.h> // Biblioteca para funções de utilidades gerais, como alocação de memória
#include <math.h>   // Biblioteca para funções matemáticas

#define NUM_PIXELS 25 // Define o número de pixels (LEDs) na matriz como 25

// Definição de tipo de estrutura para armazenar as cores dos LEDs (R, G, B)
typedef struct
{
    double red;   // Intensidade do vermelho (de 0.0 a 1.0)
    double green; // Intensidade do verde (de 0.0 a 1.0)
    double blue;  // Intensidade do azul (de 0.0 a 1.0)
} Led_config;

// Criação de um alias RGB_cod para a estrutura Led_config
typedef Led_config RGB_cod;

// Definição de tipo para a matriz de LEDs (matriz 5x5)
typedef Led_config Matriz_leds_config[5][5];

// Função que converte os valores de cor (RGB) para um valor de 32 bits
// A função recebe valores de cor normalizados entre 0.0 e 1.0 e retorna um valor inteiro
uint32_t matrix_rgb(double b, double r, double g)
{
    unsigned char R, G, B;                   // Variáveis para armazenar os componentes RGB como inteiros (0-255)
    R = r * 255;                             // Converte o valor do vermelho para 0-255
    G = g * 255;                             // Converte o valor do verde para 0-255
    B = b * 255;                             // Converte o valor do azul para 0-255
    return (G << 24) | (R << 16) | (B << 8); // Combina os componentes em um único valor de 32 bits
}

// Função para acionar a matriz de LEDs (ws2812b), passando a cor para cada LED
void controlar_leds(PIO pio, uint sm, uint32_t cor)
{
    // Envia o valor da cor para todos os LEDs da matriz
    for (int16_t i = 0; i < NUM_PIXELS; i++)
    {
        pio_sm_put_blocking(pio, sm, cor); // Envia a cor para o pino de controle do LED
    }
}

// Função para imprimir um desenho na matriz de LEDs
void imprimir_desenho(PIO pio, uint sm, Matriz_leds_config configuracao)
{
    // Percorre as linhas da matriz de LEDs de baixo para cima
    for (int contadorLinha = 4; contadorLinha >= 0; contadorLinha--)
    {
        // Inverte a ordem das colunas para linhas pares
        if (contadorLinha % 2)
        {
            for (int contadorColuna = 0; contadorColuna < 5; contadorColuna++)
            {
                uint32_t valor_cor_binario = matrix_rgb(
                    configuracao[contadorLinha][contadorColuna].blue, // Obtém a cor azul
                    configuracao[contadorLinha][contadorColuna].red,  // Obtém a cor vermelha
                    configuracao[contadorLinha][contadorColuna].green // Obtém a cor verde
                );
                pio_sm_put_blocking(pio, sm, valor_cor_binario); // Envia a cor para o LED correspondente
            }
        }
        else
        {
            // Para linhas ímpares, inverte a ordem das colunas
            for (int contadorColuna = 4; contadorColuna >= 0; contadorColuna--)
            {
                uint32_t valor_cor_binario = matrix_rgb(
                    configuracao[contadorLinha][contadorColuna].blue,
                    configuracao[contadorLinha][contadorColuna].red,
                    configuracao[contadorLinha][contadorColuna].green);
                pio_sm_put_blocking(pio, sm, valor_cor_binario); // Envia a cor para o LED correspondente
            }
        }
    }
}

// Função para obter uma cor personalizada em RGB a partir de valores inteiros (0-255)
RGB_cod obter_cor_por_parametro_RGB(int red, int green, int blue)
{
    // Converte os valores de cor para o formato normalizado entre 0.0 e 1.0
    RGB_cod cor_customizada = {red / 255.0, green / 255.0, blue / 255.0};
    return cor_customizada; // Retorna a cor personalizada
}

// Função para iniciar o modo de gravação do dispositivo
void modo_gravacao()
{
    reset_usb_boot(0, 0); // Ativa o modo de gravação (bootloader)
}

// Função para apagar todos os LEDs da matriz
void apagar_leds(PIO pio, uint sm)
{
    // Defina a cor "apagado" (preto) para todos os LEDs
    uint32_t cor_apagada = matrix_rgb(0.0, 0.0, 0.0);
    
    // Envie a cor apagada para todos os LEDs da matriz
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        pio_sm_put_blocking(pio, sm, cor_apagada); // Envia o valor da cor apagada
    }
}

#endif // Fim da diretiva de inclusão
