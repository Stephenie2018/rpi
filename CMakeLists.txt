cmake_minimum_required(VERSION 3.14)
project(FtxuiHelloWorld)

# Gebruik FetchContent om FTXUI binnen te halen
include(FetchContent)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG main
)
FetchContent_MakeAvailable(ftxui)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE ftxui::screen ftxui::dom ftxui::component)
