cmake_minimum_required(VERSION 3.10)

project(horrified-game2)

add_executable(app
    src/Dracula.cpp
    src/invisible-man.cpp
    src/monster.cpp
    src/main.cpp
    src/archaeologist.cpp
    src/BreakOfDawnCard.cpp
    src/DeliveryCard.cpp
    src/dice.cpp
    src/FormOfTheBatCard.cpp
    src/hero.cpp
    src/HurryCard.cpp
    src/item.cpp
    src/itemBag.cpp
    src/LateIntoNightCard.cpp
    src/map.cpp
    src/Mayor.cpp
    src/OverstockCard.cpp
    src/RepelCard.cpp
    src/SunriseCard.cpp
    src/ThiefCard.cpp
    src/villager.cpp
    src/VisitDetectiveCard.cpp
    src/game-controller.cpp
    src/HurriedAssistantCard.cpp
    src/FortuneTellerCard.cpp
    src/EgyptianExpert.cpp
    src/TheInnocent.cpp
    src/TheIchthyologist.cpp
)

include_directories(include)


find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

target_link_libraries(app sfml-graphics sfml-window sfml-system)