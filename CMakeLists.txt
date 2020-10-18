cmake_minimum_required(VERSION 3.5)

project(tenzor_test LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)

add_executable(tenzor_test
  fileconfigreader.cpp
  bigxmlhandler.cpp
  main.cpp
)
target_link_libraries(tenzor_test Qt5::Core)
