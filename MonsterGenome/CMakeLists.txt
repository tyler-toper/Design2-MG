cmake_minimum_required(VERSION 3.17)
project(MonsterGenome)

set(CMAKE_CXX_STANDARD 14)

add_executable(MonsterGenome main.cpp
        SourceFiles/Weapon.cpp
        HeaderFiles/Weapon.h
        SourceFiles/Menu.cpp
        HeaderFiles/Menu.h
        SourceFiles/Platforms.cpp
        HeaderFiles/Platforms.h
        SourceFiles/Game.cpp
        HeaderFiles/Game.h
        SourceFiles/GameState.cpp
        HeaderFiles/GameState.h
        SourceFiles/Projectile.cpp
        HeaderFiles/Projectile.h
        SourceFiles/Settings.cpp
        HeaderFiles/Settings.h
        SourceFiles/Pause.cpp
        HeaderFiles/Pause.h
        SourceFiles/Character.cpp
        HeaderFiles/Character.h
        irrXML/CXMLReaderImpl.h
        irrXML/fast_atof.h
        irrXML/heapsort.h
        irrXML/irrArray.h
        irrXML/irrString.h
        irrXML/irrTypes.h
        irrXML/irrXML.cpp
        irrXML/irrXML.h
        SourceFiles/AudioHandler.cpp
        HeaderFiles/AudioHandler.h
        SourceFiles/HeroMod.cpp
        HeaderFiles/HeroMod.h
        SourceFiles/Enemy.cpp
        HeaderFiles/Enemy.h
        SourceFiles/StartMenu.cpp
        HeaderFiles/StartMenu.h
        SourceFiles/SaveLoadMenu.cpp
        HeaderFiles/SaveLoadMenu.h
        SourceFiles/Items.cpp
        HeaderFiles/Items.h
        SourceFiles/Weapons.cpp
        HeaderFiles/Weapons.h
        SourceFiles/MeleeWeapon.cpp
        HeaderFiles/MeleeWeapon.h
        SourceFiles/RangedWeapon.cpp
        HeaderFiles/RangedWeapon.h
        SourceFiles/Sword.cpp
        HeaderFiles/Sword.h
        SourceFiles/Pistol.cpp
        HeaderFiles/Pistol.h
        SourceFiles/Inventory.cpp
        HeaderFiles/Inventory.h)

# SFML
include_directories(headers /usr/include C:/SFML-2.5.1/include)

set(SFML_ROOT "C:/SFML-2.5.1")


if(POLICY CMP0074)
    cmake_policy(SET CMP0074 NEW)
endif()

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    link_directories("../Dependencies/SFML-2.5.1")
    target_link_libraries(MonsterGenome ${SFML_LIBRARIES})
endif()

if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()