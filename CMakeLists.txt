cmake_minimum_required(VERSION 3.19)
project(ship)

set(CMAKE_CXX_STANDARD 20)

add_executable(ship main.cpp lib/Ship.cpp lib/Ship.h lib/Engine.cpp lib/Engine.h lib/Asteroid.cpp lib/Asteroid.h lib/Bullet.cpp lib/Bullet.h)