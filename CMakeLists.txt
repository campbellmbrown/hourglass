cmake_minimum_required(VERSION 3.13)
project(hourglass NONE)

set(SRC_DIR ${CMAKE_SOURCE_DIR})
set(BUILD_DIR ${CMAKE_BINARY_DIR})

# Arduino CLI build command
add_custom_target(hourglass ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${BUILD_DIR}
    COMMAND arduino-cli compile
        --fqbn Seeeduino:nrf52:xiaonRF52840Sense
        --build-path ${BUILD_DIR}
        ${SRC_DIR}
    WORKING_DIRECTORY ${SRC_DIR}
    COMMENT "Building firmware with Arduino CLI"
)
