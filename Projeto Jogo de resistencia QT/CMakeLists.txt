cmake_minimum_required(VERSION 3.10.0)

project(resistors)

# Exigir C++17 e ligar as macros do Qt
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Encontra as bibliotecas puras do Qt6
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

# Apanha todos os ficheiros .cpp e .h do professor (e os que vamos criar)
file(GLOB SOURCES "*.cpp" "*.h")

add_executable(${PROJECT_NAME} ${SOURCES})

# Liga o executável ao Qt6
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)