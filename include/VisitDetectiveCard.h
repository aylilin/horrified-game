#pragma once

#include "perkCard.h"

class VisitDetectiveCard : public PerkCard 
{
public:
    std::string get_name() const override
    {
        return "Visit Detective"; 
    }

    std::string get_description() const override
    {
    return "move the invisible man to your favorite location";
    }

    void apply(Hero& currentHero , std::vector<Hero*>&allHeros , std::vector<Monster*>&monsters , ItemBag& bag , Map& map , bool& skipMonsterPhase) override;

    std::string getImagePath() const override {
    return "assets/perkcards/break_of_dawn.png";
    }
};