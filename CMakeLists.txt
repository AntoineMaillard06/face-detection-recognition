cmake_minimum_required(VERSION 3.18)

project (face-detect-reco)

find_package(SFML 2.5.1 REQUIRED window graphics)

include_directories("./src")
add_executable(face main.cpp
                    src/class/Exception/Exception.cpp
                    src/class/PGMReader/PGMReader.cpp
                    src/class/Mat/Mat.cpp
                    src/class/Window/Window.cpp)

target_link_libraries(face pthread sfml-window sfml-graphics)
