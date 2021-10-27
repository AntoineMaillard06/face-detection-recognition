cmake_minimum_required(VERSION 3.18)

project (face-detect-reco)

include_directories("./src")
add_executable(face main.cpp
                    src/class/Image/Image.cpp)
