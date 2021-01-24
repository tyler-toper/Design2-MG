cmake_minimum_required(VERSION 3.17)
project(MonsterGenome)

set(CMAKE_CXX_STANDARD 14)

add_executable(MonsterGenome main.cpp Weapon.cpp Armor.cpp LoadAssets.cpp Hero.cpp Enemy.cpp Menu.cpp Projectile.cpp Weapon.h Armor.h Menu.h LoadAssets.h Platforms.cpp Platforms.h Game.cpp Game.h Hero.h GameState.cpp GameState.h Projectile.h)

include_directories(headers /usr/include c:/SFML/include)

set(SFML_ROOT "C:/SFML-2.5.1")

if(POLICY CMP0074)
    cmake_policy(SET CMP0074 NEW)
endif()

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    link_directories("C:/SFML-2.5.1")
    target_link_libraries(MonsterGenome ${SFML_LIBRARIES})
endif()

if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()