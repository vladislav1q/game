cmake_minimum_required(VERSION 3.13)
project(game)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

set(SOURCE_FILES main.cpp)
#add_executable(game main.cpp init.h update.h objects.h paths.h background.h draw.h light.h light.cpp menu.h game.cpp rules.cpp settings.cpp button.h menu.cpp pages.h init.cpp update.cpp paths.cpp difficulty.cpp rating.cpp background.cpp music.h settingsMusic.cpp settingsVolume.cpp settingsMap.cpp settingsVolume.h cmake-build-debug/settingsMusic.h settingsMap.h settingsMusicMenu.h settingsMusicGame.h cmake-build-debug/settingsMusic.h settingsMusic.h wave.h shadows.h endGame.h)

add_executable(game ${SOURCE_FILES})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system graphics window network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()


