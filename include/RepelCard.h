#pragma once
#include "perkCard.h"

class RepelCard : public PerkCard 
{
public:
    std::string get_name() const override;
    std::string get_description() const override;

    void apply(Hero& currentHero , std::vector<Hero*>&allHeros , std::vector<Monster>&monsters , ItemBag& bag , Map& map , bool& skipMonsterPhase) override;
};