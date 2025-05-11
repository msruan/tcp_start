# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if(EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(temp_telinha C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

file(GLOB_RECURSE SSD1306_FILES external/ssd1306/*.c)
file(GLOB_RECURSE SRC_FILES src/*.c)
file(GLOB_RECURSE DRIVERS_FILES src/drivers/*.c)

# Add executable. Default name is the project name, version 0.1
add_executable(temp_telinha
    ${SRC_FILES}
    ${DRIVERS_FILES}
    ${SSD1306_FILES}
)

# TODO: Mostrar BLOB como alternativa a esse add_executable infinito

pico_set_program_name(temp_telinha "temp_telinha")
pico_set_program_version(temp_telinha "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(temp_telinha 1)
pico_enable_stdio_usb(temp_telinha 1)

# Add the standard library to the build
target_link_libraries(temp_telinha
    pico_stdlib
)

# Add the standard include files to the build
target_include_directories(temp_telinha PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/src/drivers
    ${CMAKE_CURRENT_LIST_DIR}/external/ssd1306
)


# EXTRA: FETCH CONTENT
include(FetchContent)

# Incluindo bibliotecas externas no momento do build
FetchContent_Declare(
    ws2812b_animation
    GIT_REPOSITORY https://github.com/TuriSc/RP2040-WS2812B-Animation.git
    GIT_TAG main
)
FetchContent_MakeAvailable(ws2812b_animation)

# Add any user requested libraries
target_link_libraries(temp_telinha
    hardware_i2c
    hardware_adc

    ws2812b_animation
)

pico_add_extra_outputs(temp_telinha)

