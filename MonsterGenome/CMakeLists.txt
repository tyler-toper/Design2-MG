cmake_minimum_required(VERSION 3.17)
project(MonsterGenome)

set(CMAKE_CXX_STANDARD 14)

add_executable(MonsterGenome main.cpp
        SourceFiles/Weapon.cpp
        HeaderFiles/Weapon.h
        SourceFiles/Armor.cpp
        HeaderFiles/Armor.h
        SourceFiles/Menu.cpp
        HeaderFiles/Menu.h
        SourceFiles/LoadAssets.cpp
        HeaderFiles/LoadAssets.h
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
        HeaderFiles/HeroMod.h)

# SFML
include_directories(headers /usr/include ../Dependencies/SFML-2.5.1/include)

set(SFML_ROOT "../Dependencies/SFML-2.5.1")

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

# Boost
set(BOOST_ROOT "../Dependencies/boost_1_73_0")
set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "../Dependencies/boost/include/boost-1_73")
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "../Dependencies/boost/lib")
set(BOOST_INCLUDEDIR "../Dependencies/boost/include/boost-1_73")
set(BOOST_LIBRARYDIR "../Dependencies/boost/lib")
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.73.0 COMPONENTS system filesystem serialization REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories("../Dependencies/boost_1_73_0")
    target_link_libraries(MonsterGenome ${Boost_LIBRARIES})
endif()