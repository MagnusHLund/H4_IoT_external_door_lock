cmake_minimum_required(VERSION 3.22)
project(Magnussy_IoT_Project_Arduino_authentication)

set(CMAKE_CXX_STANDARD 17)

# ----------------------------------------------------------------------
# Windows paths
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
set(SRC
        AuthenticationSketch.ino
        WiFiManager.cpp
        WiFiManager.h
        MqttClient.h
        MqttClient.cpp
)

# ----------------------------------------------------------------------
# Collect all Arduino library "src" folders
# ----------------------------------------------------------------------
file(GLOB_RECURSE USER_LIB_SRC_DIRS "${ARDUINO_LIBRARIES_DIR}/*/src")
file(GLOB_RECURSE HW_LIB_SRC_DIRS "${ARDUINO_HARDWARE_LIBRARIES_DIR}/*/src")

# Add specific missing libs (PubSubClient, WiFiS3)
set(PUBSUBCLIENT_DIR "${ARDUINO_LIBRARIES_DIR}/PubSubClient/src")
set(ADC_HTTPCLIENT_DIR "${ARDUINO_LIBRARIES_DIR}/ArduinoHttpClient/src")
set(WIFI_S3_DIR "${ARDUINO_HARDWARE_LIBRARIES_DIR}/WiFiS3/src")
set(ARDUINO_API_DIR "${ARDUINO_CORE_DIR}/api")
# ----------------------------------------------------------------------
# Include dirs for IntelliSense
# ----------------------------------------------------------------------
include_directories(
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/Include
        ${ARDUINO_CORE_DIR}
        ${ARDUINO_VARIANT_DIR}
        ${USER_LIB_SRC_DIRS}
        ${HW_LIB_SRC_DIRS}
        ${ARDUINO_API_DIR}
        ${PUBSUBCLIENT_DIR}
        ${ADC_HTTPCLIENT_DIR}
        ${WIFI_S3_DIR}
)

# ----------------------------------------------------------------------
# Arduino compile macros
# ----------------------------------------------------------------------
add_definitions(-DARDUINO=10813)
add_definitions(-DARDUINO_ARCH_RENESAS)

# ----------------------------------------------------------------------
# IntelliSense dummy target
# ----------------------------------------------------------------------
file(WRITE "${CMAKE_BINARY_DIR}/dummy.cpp" "// Dummy file to enable IntelliSense")
add_executable(authentication
        "${CMAKE_BINARY_DIR}/dummy.cpp"
        ${SRC}
)
