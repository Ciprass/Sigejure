cmake_minimum_required(VERSION 3.10)

project(Sigejure VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

## Com
# add_executable(Sigejure src/main.cpp test/testlib.cpp)

file(GLOB_RECURSE SOURCES "src/*.cpp")
# add_executable(Sigejure ${SOURCES})
add_executable(Sigejure WIN32 ${SOURCES})

target_include_directories(Sigejure PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

## Static lib
set(CMAKE_EXE_LINKER_FLAGS "-static")

## Resources file
# file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/resources)

# add_custom_command(
#     TARGET ${PROJECT_NAME} POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#     ${CMAKE_SOURCE_DIR}/resources
#     ${CMAKE_BINARY_DIR}/resources
# )

## install
install(TARGETS Sigejure
        RUNTIME DESTINATION bin
)