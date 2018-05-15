cmake_minimum_required(VERSION 3.10)
project(damas)

# sudo apt-get update
# sudo apt-get install build-essential
# sudo apt-get install libslang2-dev

set(CMAKE_CXX_STANDARD 11)

include_directories(./Pacotes)

add_executable(damas_solitarias
        Pacotes/IPC++/mensageiro.cpp
        Pacotes/Utilitarios/cadeia.cpp
        Pacotes/Utilitarios/data.cpp
        Pacotes/Utilitarios/ignoradores.cpp
        Pacotes/Utilitarios/localizacao.cpp
        Pacotes/Slang++/ecra.cpp
        Pacotes/Slang++/menu.cpp
        Pacotes/Slang++/teclado.cpp
        damas_solitarias.cpp)

target_link_libraries(damas_solitarias slang)

add_executable(damas
        Pacotes/IPC++/mensageiro.cpp
        Pacotes/Utilitarios/cadeia.cpp
        Pacotes/Utilitarios/data.cpp
        Pacotes/Utilitarios/ignoradores.cpp
        Pacotes/Utilitarios/localizacao.cpp
        Pacotes/Slang++/ecra.cpp
        Pacotes/Slang++/menu.cpp
        Pacotes/Slang++/teclado.cpp
        damas_entrega_final.cpp)

target_link_libraries(damas slang)