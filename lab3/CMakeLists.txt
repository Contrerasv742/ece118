cmake_minimum_required(VERSION 3.10)

# Project name
project(PIC32MX320F128H_Project C)

# Generate compile_commands.json for LSP support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the PIC32 microcontroller model
set(MCU "32MX320F128H")

# Find the XC32 compiler
find_program(XC32_CC xc32-gcc)
find_program(XC32_CXX xc32-g++)
find_program(XC32_AR xc32-ar)
find_program(XC32_LD xc32-ld)
find_program(XC32_BIN2HEX xc32-bin2hex)

if(NOT XC32_CC)
    message(FATAL_ERROR "XC32 compiler not found. Please install Microchip XC32 compiler")
endif()

# Set compiler and linker flags
set(CMAKE_C_COMPILER ${XC32_CC})
set(CMAKE_CXX_COMPILER ${XC32_CXX})
set(CMAKE_AR ${XC32_AR})
set(CMAKE_LINKER ${XC32_LD})

# Set processor-specific flags
set(CPU_FLAGS "-mprocessor=${MCU}")

# Common compiler flags
set(COMMON_FLAGS "${CPU_FLAGS} -O1 -ffunction-sections -fdata-sections")

# Set C flags
set(CMAKE_C_FLAGS "${COMMON_FLAGS}")
set(CMAKE_C_FLAGS_DEBUG "${COMMON_FLAGS} -g -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "${COMMON_FLAGS} -O2")

# Include directories - this is the crucial part for LSP to work
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/app
    ${CMAKE_SOURCE_DIR}/include/drivers
    ${CMAKE_SOURCE_DIR}/include/events
    ${CMAKE_SOURCE_DIR}/include/framework
)

# Add source files by directories
file(GLOB APP_SOURCES "src/app/*.c")
file(GLOB DRIVER_SOURCES "src/drivers/*.c") 
file(GLOB EVENTS_SOURCES "src/events/*.c")
file(GLOB FRAMEWORK_SOURCES "src/framework/*.c")

# Create executable
add_executable(${PROJECT_NAME}.elf 
    ${APP_SOURCES}
    ${DRIVER_SOURCES}
    ${EVENTS_SOURCES}
    ${FRAMEWORK_SOURCES}
)

# Generate HEX file
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${XC32_BIN2HEX} $<TARGET_FILE:${PROJECT_NAME}.elf>
    COMMENT "Creating HEX file"
)

# Custom target for flashing the device (you'll need to adjust the command)
add_custom_target(flash
    COMMAND pic32prog -d ${PROJECT_NAME}.hex
    DEPENDS ${PROJECT_NAME}.elf
    COMMENT "Flashing ${PROJECT_NAME}.hex to device"
)

# Set linker options
target_link_options(${PROJECT_NAME}.elf PRIVATE ${CPU_FLAGS} -Wl,--gc-sections)
