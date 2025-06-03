#pragma once 

#include "monster.h"
#include <vector>

class InvisibleMan : public Monster
{
private:
    std::vector<std::string> collectedEvidences;
    const std::vector<std::string> evidenceLocations =
    { "Inn" , "Barn" , "Laboratory" , "Institute" , "Mansion" };

public:
    InvisibleMan();

    int get_evidencesCollected() const;
    
    void collectEvidence(const std::string& Location);
    void useSpecialPower() override;
    bool checkDefeatConditions() const override;
};