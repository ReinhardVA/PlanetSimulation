cmake_minimum_required(VERSION 3.15)
project(PlanetSimulation CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Alt klasörleri projeye dahil et
add_subdirectory(Core)
add_subdirectory(App)