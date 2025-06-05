#include "invisible-man.h"
#include <iostream>
#include <algorithm>

InvisibleMan::InvisibleMan() : Monster("Invisible Man") {}

void InvisibleMan::useSpecialPower() 
{
    std::cout << "Invisible Man uses STALK UNSEEN!" << std::endl;

}
//functions are not complete!!!

bool InvisibleMan::checkDefeatConditions() const
{
    return collectedEvidences.size() >= 5;
}

void InvisibleMan::collectEvidence(const std::string& Location)
{
    std::string loclower = Location;
    std::transform(loclower.begin() , loclower.end() , loclower.begin() , ::tolower);

    bool validLocation = false;
    for (const auto& loc : evidenceLocations)
    {
        std::string locCopy = loc;
        std::transform(locCopy.begin() , locCopy.end() , locCopy.begin() , ::tolower);
        if (locCopy == loclower)
        {
            validLocation = true;
            break;
        }
    }

    if (!validLocation)
    {
        std::cout << "Invalid evidence location " << Location << std::endl;
        return;
    }

    //checking if location is already collected
    for (const auto& ev : collectedEvidences)
    {
        std::string evCopy = ev;
        std::transform(evCopy.begin() , evCopy.end() , evCopy.begin() , ::tolower);
        if (evCopy == loclower)
        {
            std::cout << "Evidence is already collected from " << Location << std::endl;
            return;
        }
    }

    //add to collected evidences
    for (const auto& loc : evidenceLocations)
    {
        std::string locCopy = loc;
        std::transform(locCopy.begin() , locCopy.end() , locCopy.begin() , ::tolower);
        if (locCopy == loclower)
        {
            collectedEvidences.push_back(loc);
            std::cout << "Evidence is collected from " << loc << "(" << collectedEvidences.size() << "/5 evidences)" << std::endl;
            if (checkDefeatConditions())
            {
                std::cout << "all evidences collected..." << std::endl;
                std::cout << "Invisible Man can be defeated now..." << std::endl;
            }
            return;
        }
    }
}

int InvisibleMan::get_evidencesCollected() const
{
    return collectedEvidences.size();
}
