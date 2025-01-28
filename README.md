# Controle de Matriz de LEDs - Raspberry Pi Pico
## Descrição
Este repositório contém o código para controlar uma matriz de LEDs 5x5 (WS2812) utilizando um Raspberry Pi Pico W. O projeto foi desenvolvido como trabalho em grupo do Embarca Tech, envolvendo diferentes animações controladas através de um teclado matricial 4x4.

## Integrantes do Grupo
- Bruno Schumacher
- Caio Nunes
- José Guilherme Marques
- Lucas Fialho Xavier
- Otiliano Junior

## Componentes Necessários
- Raspberry Pi Pico W
- Matriz de LEDs WS2812 5x5
- Teclado Matricial 4x4
- Buzzer
- Cabo micro-USB para USB-A
- Computador com VS Code e configuração de Pico SDK

## Funcionalidades
O sistema responde aos seguintes comandos do teclado matricial:

### Animações Personalizadas (Teclas 0-4)
- **Tecla 1**: Animação de rostos com diferentes expressões
- **Tecla 2**: Animação de onda crescente em azul
- **Tecla 3**: Animação jogo Snake com cores alternadas
- **Tecla 4**: Animação da Cruz de Malta com cores alternadas

### Controles de LED (Teclas Especiais)
- **Tecla A**: Desliga todos os LEDs
- **Tecla B**: Liga todos os LEDs em azul (100% intensidade)
- **Tecla C**: Liga todos os LEDs em vermelho (80% intensidade)
- **Tecla D**: Liga todos os LEDs em verde (50% intensidade)
- **Tecla #**: Liga todos os LEDs em branco (20% intensidade)
- **Tecla ***: Ativa modo de gravação (bootloader)

## Estrutura do Projeto
### Hardware
- **GPIO 7**: Controle da matriz de LEDs WS2812
- **GPIOs 9, 8, 10, 6**: Linhas do teclado matricial
- **GPIOs 5, 4, 3, 2**: Colunas do teclado matricial

### Software
- `main.c`: Arquivo principal com inicialização e loop de controle
- `config.h`: Configurações e funções auxiliares
- `tecla1.h` - `tecla4.h`: Implementações das diferentes animações
- `pio_matrix.pio`: Código PIO para controle dos LEDs WS2812

## Como Usar
1. **Clone o repositório**:
   ```bash
   git clone https://github.com/guilhermejnr/gpio-matriz-leds
   ```

2. **Configure o ambiente**:
   - Instale o VS Code
   - Configure o Pico SDK seguindo a documentação oficial
   - Instale o plugin do Wokwi para VS Code

3. **Compile o projeto**:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

4. **Carregue o código**:
   - Mantenha pressionado o botão BOOTSEL do Pico
   - Conecte o cabo USB
   - Solte o botão
   - Copie o arquivo .uf2 gerado para o dispositivo

## Vídeo de Demonstração
[Link para o vídeo de demonstração]

## Contribuições
Sinta-se à vontade para contribuir com o projeto através de pull requests. Para contribuir:
1. Faça um fork do repositório
2. Crie uma branch para sua feature
3. Faça commit das alterações
4. Envie um pull request
