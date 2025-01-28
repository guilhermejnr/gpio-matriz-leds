# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
# Generated CMake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Inicializa o SDK do Pico a partir da localização instalada
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()

set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)

if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()

# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Tipo de placa")

# Carregar o SDK do Raspberry Pi Pico (deve ser antes do projeto)
include(pico_sdk_import.cmake)

# Nome do projeto
project(gpio-matriz-leds C CXX ASM)

# Inicializa o SDK do Raspberry Pi Pico
pico_sdk_init()

# Garantir que o caminho do SDK está correto para arquivos de cabeçalho
include_directories(${PICO_SDK_PATH}/src/rp2_common/hardware_gpio/include)

# Criar o executável com o código principal
add_executable(gpio-matriz-leds
    main.c
)

# Caso você utilize um arquivo PIO, garanta que ele será processado corretamente
pico_generate_pio_header(gpio-matriz-leds ${CMAKE_CURRENT_LIST_DIR}/pio_matrix.pio)

# Vincular as dependências comuns
target_link_libraries(gpio-matriz-leds
    pico_stdlib
    hardware_pio
    hardware_adc
    hardware_pwm
)

# Criar arquivos de saída como mapa/bin/hex, etc.
pico_add_extra_outputs(gpio-matriz-leds)

# Adicionar URL do programa, se necessário
# pico_set_program_url(gpio-matriz-leds "https://github.com/seu-repo")
