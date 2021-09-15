cmake_minimum_required(VERSION 3.20)
project(ServerBreakout)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

set(SFML_INCLUDE_DIR "/home/rewieer/Libraries/SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "/home/rewieer/Libraries/SFML-2.5.1/lib")
set(SFML_DIR "/home/rewieer/Libraries/SFML-2.5.1/lib/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

add_executable(ServerBreakout main.cpp DataStructures/LinkedList.h DataStructures/Node.h Logic/GameManager.h Logic/Bar.h Logic/Player.h Logic/Ball.h Logic/Block.h Socket/SocketServer.h DataStructures/Matrix/Matrix.h DataStructures/Matrix/MatrixNode.h Socket/SocketServer.cpp Socket/TypeMessage.h Socket/JsonManagement.h)
target_link_libraries (ServerBreakout sfml-graphics sfml-window sfml-system)