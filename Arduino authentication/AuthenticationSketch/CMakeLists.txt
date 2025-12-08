cmake_minimum_required(VERSION 3.22)
project(Magnussy_IoT_Project_Arduino_authentication)

set(CMAKE_CXX_STANDARD 17)

# ----------------------------------------------------------------------
# Resolve Windows user paths
# ----------------------------------------------------------------------
set(USERPROFILE_PATH "$ENV{USERPROFILE}")
set(LOCALAPPDATA_PATH "$ENV{LOCALAPPDATA}")

# Arduino paths
set(ARDUINO_LIBRARIES_DIR "${USERPROFILE_PATH}/Documents/Arduino/libraries")
set(ARDUINO_HARDWARE_ROOT "${LOCALAPPDATA_PATH}/Arduino15/packages/arduino/hardware/renesas_uno/1.5.1")
set(ARDUINO_CORE_DIR "${ARDUINO_HARDWARE_ROOT}/cores/arduino")
set(ARDUINO_VARIANT_DIR "${ARDUINO_HARDWARE_ROOT}/variants/UNOWIFIR4")
set(ARDUINO_HARDWARE_LIBRARIES_DIR "${ARDUINO_HARDWARE_ROOT}/libraries")

# ----------------------------------------------------------------------
# Project sources
# ----------------------------------------------------------------------
# For IntelliSense only: list your main sketch and any CPP files here
set(SRC
        AuthenticationSketch.ino
)

# ----------------------------------------------------------------------
# Library discovery
# ----------------------------------------------------------------------
file(GLOB_RECURSE ARDUINO_LIB_SRC_DIRS "${ARDUINO_LIBRARIES_DIR}/*/src")
file(GLOB_RECURSE ARDUINO_HARDWARE_LIB_SRC_DIRS "${ARDUINO_HARDWARE_LIBRARIES_DIR}/*/src")
file(GLOB ARDUINO_LIB_WEBSOCKET "${ARDUINO_LIBRARIES_DIR}/ArduinoHttpClient/src")

# ----------------------------------------------------------------------
# Include dirs for IntelliSense
# ----------------------------------------------------------------------
include_directories(
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/include
        ${ARDUINO_CORE_DIR}
        ${ARDUINO_VARIANT_DIR}
        ${ARDUINO_LIB_SRC_DIRS}
        ${ARDUINO_HARDWARE_LIB_SRC_DIRS}
        ${ARDUINO_LIB_WEBSOCKET}
)

# ----------------------------------------------------------------------
# Arduino compile macros
# ----------------------------------------------------------------------
add_definitions(-DARDUINO=10813)
add_definitions(-DARDUINO_ARCH_RENESAS)

# ----------------------------------------------------------------------
# IntelliSense target (dummy CPP ensures CMake can link)
# ----------------------------------------------------------------------
file(WRITE "${CMAKE_BINARY_DIR}/dummy.cpp" "// Dummy file to let CMake determine link language")
add_executable(authentication
        "${CMAKE_BINARY_DIR}/dummy.cpp"
        ${SRC}  # your .ino file for IntelliSense only
)