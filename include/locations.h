#pragma once

#include <map>
#include <string>

struct Position
{
   float x;
   float y;
};

const std::map<std::string , Position> locations = 
{
    {"Crypt" , {7.f , 586.f}} ,
    {"Graveyard" , {850.f , 220.f}} ,
    {"Tower" , {237.f , 603.f}} ,
    {"Dungeon" , {685.f , 109.f}} ,
    {"Docks" , {388.f , 643.f}} ,
    {"Precinct" , {252.f , 112.f}} ,
    {"Museum" , {1120.f , 620.f}} ,
    {"Theatre" , {433.f , 224.f}} ,
    {"Inn" , {387.f , 57.f}} ,
    {"Laboratory" , {910.f , 900.f}} ,
    {"Barn" , {528.f , 95.f}} ,
    {"Cave" , {49.f , 175.f}} ,
    {"Camp" , {120.f , 121.f}} ,
    {"Shop" , {431.f , 453.f}} ,
    {"Institute" , {657.f , 676.f}} ,
    {"Hospital" , {300.f , 400.f}} ,
    {"Mansion" , {300.f , 900.f}}
};