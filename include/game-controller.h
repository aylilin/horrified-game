#pragma once

#include <vector>
#include <memory>
#include <chrono>
#include <ctime>

#include "map.h"
#include "itemBag.h"
#include "perkCard.h"
#include "monster.h"
#include "hero.h"
#include "Dracula.h"
#include "invisible-man.h"
#include "archaeologist.h"
#include "Mayor.h"
#include "courier.h"
#include "scientist.h"
#include "villager.h"
#include "dice.h"
#include "item.h"
// #include "GameView.h"
// #include "game.h"

#include "FormOfTheBatCard.h"
#include "SunriseCard.h"
#include "ThiefCard.h"
#include "DeliveryCard.h"
#include "VisitDetectiveCard.h"
#include "BreakOfDawnCard.h"
#include "OverstockCard.h"
#include "LateIntoNightCard.h"
#include "RepelCard.h"
#include "HurryCard.h"
#include "FortuneTellerCard.h"
#include "FormerEmployerCard.h"
#include "HurriedAssistantCard.h"
#include "TheInnocent.h"
#include "EgyptianExpert.h"
#include "TheIchthyologist.h"

struct PlayerInfo
{
    std::string name;
    std::chrono::system_clock::time_point lastGarlicTime;
    std::string heroName;
};

class GameController
{
private:
    sf::RenderWindow window;
    Map map;
    ItemBag itemBag;
    Dice dice;
    std::vector<Hero*> heroes;
    std::vector<Monster*> monsters;
    std::vector<std::unique_ptr<MonsterCard>> monsterDeck;
    std::vector<std::unique_ptr<PerkCard>> perkDeck;
    std::map<std::string, Hero*> playerToHero;
    std::vector<Villager> allVillagers;
    std::set<std::string> getConnectedLocations(const std::string& location) const;

    std::map<std::string, std::string> heroStartLocations =
    {{"Archaeologist" , "Docks"} , {"Mayor" , "Theatre"} , {"Courier" , "Shop"} , {"Scientist" , "Institute"}};


    sf::Font gameFont;

    bool skipMonsterPhase = false;


    PlayerInfo player1, player2;
    std::string currentPlayerName;

    int terrorLevel = 0;
    int turn = 1;

    void setup();

    void showTerrorLevel() const;
    void cleanup();
    void askPlayersInfo();
    void determineStartingPlayer();
    void displayGameState(sf::RenderWindow&) const;
    void printActionHelp(sf::RenderWindow&) const;
    void printSingleActionHelp(sf::RenderWindow& , int n) const;
    std::chrono::system_clock::time_point get_timePointFromInput();
    void checkDefeat(Hero* hero);
    void setupVillagers();
    void heroPhase(sf::RenderWindow&, Hero* currentHero);
    void monsterPhase(sf::RenderWindow&);

    void setupPerkCards(sf::RenderWindow&);

public:
    std::map<std::string , std::string> getHeroLocations() const;
    Hero* getHero(const std::string& heroName);
    const Hero* getHero(const std::string& heroName) const;
    std::string getHeroLocation(const std::string& heroName) const;
    bool moveHero(const std::string& heroName , const std::string& toLocation);
    bool heroPickUpItem(const std::string& heroName , const std::string& location);
    const std::vector<Item>& getItemsAtLocation(const std::string& location) const;




    void increaseTerrorLevel();

    std::chrono::system_clock::time_point convertToTimePoint(const std::string& timeStr);
    void setUpGame(sf::RenderWindow&);
    void setupPlayers(const std::vector<PlayerInfo>& playerInfos);

    GameController();
    ~GameController();

    void run();  //main game loop
};
