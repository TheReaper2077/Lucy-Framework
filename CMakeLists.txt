cmake_minimum_required(VERSION 3.0.0)
project(Test VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB TARGET_SRC "src/*.cpp" "src/OpenGL/*.cpp" "src/Game/*.cpp" "src/Lucy/*.cpp")

set (CMAKE_CXX_STANDARD 20)

include_directories(C:/Users/krishnadev/vcpkg/installed/x64-windows/include src)

add_executable(main ${TARGET_SRC})

find_package(glad CONFIG REQUIRED)
target_link_libraries(main PRIVATE glad::glad)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(main PRIVATE glfw)

# find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
# target_link_libraries(main PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

# If you want SFML to provide an implementation of main():
# target_link_libraries(main PRIVATE sfml-main)

find_path(STB_INCLUDE_DIRS "stb.h")
target_include_directories(main PRIVATE ${STB_INCLUDE_DIRS})

find_package(imgui CONFIG REQUIRED)
target_link_libraries(main PRIVATE imgui::imgui)

find_package(EnTT CONFIG REQUIRED)
target_link_libraries(main PRIVATE EnTT::EnTT)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
