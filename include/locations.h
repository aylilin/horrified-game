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
    {"Crypt" , {578.f , 64.f}} ,
    {"Graveyard" , {850.f , 220.f}} ,
    {"Tower" , {910.f , 410.f}} ,
    {"Dungeon" , {900.f , 510.f}} ,
    {"Docks" , {910.f , 610.f}} ,
    {"Precinct" , {700.f , 620.f}} ,
    {"Museum" , {1120.f , 620.f}} ,
    {"Theatre" , {910.f , 700.f}} ,
    {"Inn" , {80.f , 453.f}} ,
    {"Laboratory" , {910.f , 900.f}} ,
    {"Barn" , {910.f , 1000.f}} ,
    {"Cave" , {910.f , 1100.f}} ,
    {"Camp" , {300.f , 700.f}} ,
    {"Shop" , {431.f , 453.f}} ,
    {"Institute" , {657.f , 676.f}} ,
    {"Hospital" , {300.f , 400.f}} ,
    {"Mansion" , {300.f , 900.f}}
};