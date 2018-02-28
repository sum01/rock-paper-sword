cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(Rock-Paper-Sword VERSION 1.0.0 LANGUAGES CXX)

add_executable(rps-game
	src/attack.cpp
	src/entity.cpp
	src/main.cpp
	src/moveset.cpp
)

target_include_directories(rps-game
	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
