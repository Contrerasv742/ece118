cmake_minimum_required(VERSION 3.24.2)

# Compiler
cmake_minimum_required(VERSION 3.24.2)

# Set compiler paths directly
set(CMAKE_C_COMPILER "/opt/microchip/xc32/v4.25/bin/xc32-gcc")
set(CMAKE_CXX_COMPILER "/opt/microchip/xc32/v4.25/bin/xc32-g++")

# Force CMake to skip compiler checks
set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)

# Rest of your CMake configuration
project(Reader C)

# Device Family Pack
set(DFP /opt/microchip/mplabx/v6.20/packs/Microchip/PIC32MX_DFP/1.5.259)

# Device
set(PIC 32MX320F128H)
set(OPTIMIZATION 1)
set(USER_FLAGS -Wall)
set(USER_DEFINITIONS )
set(HEAP 0)

# Define your project structure here
# Adjust these paths to match your directory structure
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(FREERTOS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/FreeRTOS)

# Create these directories if they don't exist
file(MAKE_DIRECTORY ${SRC_DIR})
file(MAKE_DIRECTORY ${INCLUDE_DIR})

# Define your source files here
# Example: Add all C files in the src directory
file(GLOB PROJECT_SOURCES "${SRC_DIR}/*.c")

# If you create a main.c file, add it explicitly:
# set(PROJECT_SOURCES ${PROJECT_SOURCES} ${SRC_DIR}/main.c)

# Include directories
include_directories(${INCLUDE_DIR})

# Only include FreeRTOS if you're using it
if(EXISTS "${FREERTOS_DIR}")
    include_directories(${FREERTOS_DIR}/Source/include)
    include_directories(${FREERTOS_DIR}/Source/portable/MPLAB/PIC32MZ)
    add_subdirectory(${FREERTOS_DIR})
endif()

# Create executable
add_executable(${PROJECT_NAME}.elf ${PROJECT_SOURCES})

# Link FreeRTOS only if it exists
if(EXISTS "${FREERTOS_DIR}")
    target_link_libraries(${PROJECT_NAME}.elf FreeRTOS)
endif()

# Compiler flags and options
set(MPROCESSOR -mprocessor=${PIC})
set(MOPTIMIZATION -O${OPTIMIZATION})
set(DEFINES ${USER_DEFINITIONS})
set(SYM_HEAP --defsym=_min_heap_size=${HEAP})
set(SYM_BUILD --defsym=__MPLAB_BUILD=1)
set(LINKER_OPTS --gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem)
set(LINKER_MAP -Map=${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.map)
set(MEMORY_FILE --memorysummary,${CMAKE_CURRENT_BINARY_DIR}/memoryfile.xml)
set(XC32_LINK_FLAGS
    ${SYM_HEAP},${SYM_BUILD},${LINKER_OPTS},${LINKER_MAP},${MEMORY_FILE}
)

# HEX file build command
add_custom_command(
    OUTPUT ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex
    DEPENDS ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf
    COMMAND /opt/microchip/xc32/v4.21/bin/xc32-bin2hex ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf
)

add_custom_target(${PROJECT_NAME}_hex ALL
    DEPENDS ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex
)

target_compile_options(${PROJECT_NAME}.elf PUBLIC ${USER_FLAGS} ${MPROCESSOR} ${MOPTIMIZATION} -fdata-sections -ffunction-sections -no-legacy-libc -mdfp=${DFP})
target_compile_definitions(${PROJECT_NAME}.elf PUBLIC XPRJ_default=default ${DEFINES})
target_link_options(${PROJECT_NAME}.elf PUBLIC ${MPROCESSOR} ${MOPTIMIZATION})
target_link_libraries(${PROJECT_NAME}.elf "-Wl,${XC32_LINK_FLAGS}")
