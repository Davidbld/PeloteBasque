cmake_minimum_required(VERSION 3.10)
project(PeloteBasque)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add source files
set(SOURCES
    src/main.cpp
    src/Models/Ball.cpp
    src/Models/Player.cpp
    src/Models/GameState.cpp
    src/Views/GameView.cpp
    src/Controllers/GameController.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link SFML
target_link_libraries(${PROJECT_NAME} 
    sfml-graphics
    sfml-window
    sfml-system
)