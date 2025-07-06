#include "../include/game-controller.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <ctime>

GameController::GameController()
{
    setup();
}

GameController::~GameController()
{
    cleanup();
}

void GameController::setup()
{
    //creating heroes
    monsters.push_back(new Dracula());
    monsters.push_back(new InvisibleMan());

    //adding monster cards
    monsterDeck.push_back(std::make_unique<FormOfTheBatCard>());
    monsterDeck.push_back(std::make_unique<SunriseCard>());
    monsterDeck.push_back(std::make_unique<ThiefCard>());
    monsterDeck.push_back(std::make_unique<DeliveryCard>());
    monsterDeck.push_back(std::make_unique<FortuneTellerCard>());

}


void GameController::showTerrorLevel() const
{
    std::cout << "Terror Level: " << terrorLevel << " / 7\n";
    if (terrorLevel >= 5)
    {
        std::cout << "\nGAME OVER - Terror level too high!\n";
        exit(0);
    }
}

void GameController::cleanup()
{
    for (Hero* h : heroes) delete h;
    for (Monster* m : monsters) delete m;
}

std::chrono::system_clock::time_point GameController::get_timePointFromInput()
{
    int hour, minute;
    std::cout << "Please enter the time you last ate garlic (hours and minutes): ";
    std::cin >> hour >> minute;
    std::cin.ignore();

    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm local_tm = *std::localtime(&now_c);
    local_tm.tm_hour = hour;
    local_tm.tm_min = minute;
    local_tm.tm_sec = 0;

    return std::chrono::system_clock::from_time_t(std::mktime(&local_tm));
}


void GameController::askPlayersInfo() 
{
    std::cout << "First player's name: ";
    std::getline(std::cin, player1.name);
    player1.lastGarlicTime = get_timePointFromInput();

    std::cout << "Second player's name: ";
    std::getline(std::cin, player2.name);
    player2.lastGarlicTime = get_timePointFromInput();
}

void GameController::determineStartingPlayer()
{
    auto now = std::chrono::system_clock::now();
    auto diff1 = std::chrono::duration_cast<std::chrono::minutes>(now - player1.lastGarlicTime).count();
    auto diff2 = std::chrono::duration_cast<std::chrono::minutes>(now - player2.lastGarlicTime).count();

    std::cout << "\n*****Time since last cycle*****\n";
    std::cout << player1.name << ": " << diff1 << " minutes ago!\n";
    std::cout << player2.name << ": " << diff2 << " minutes ago!\n";

    currentPlayerName = (diff1 < diff2) ? player1.name : player2.name;

    std::cout << "\nStarting player: " << currentPlayerName << "\n";
}

void GameController::assignHeroesToPlayers()
{
    std::cout << "\nHeroes:\n";
    std::cout << "1. Archaeologist\n";
    std::cout << "2. Mayor\n";

    int choice;
    std::cout << currentPlayerName << " , please choose(1 or 2)?\n";
    std::cin >> choice;
    std::cin.ignore();

    Hero* h1;
    Hero* h2;

    if (choice == 1)
    {
        h1 = new Archaeologist(player1.name, "Docks");
        h2 = new Mayor(player2.name, "Theatre");
        playerToHero[player1.name] = h1;
        playerToHero[player2.name] = h2;
    } else {
        h1 = new Mayor(player1.name, "Theatre");
        h2 = new Archaeologist(player2.name, "Docks");
        playerToHero[player1.name] = h1;
        playerToHero[player2.name] = h2;
    }

    heroes.push_back(h1);
    heroes.push_back(h2);

    std::cout << "\n***" << player1.name << " ---> " << playerToHero[player1.name]->get_name() << "\n";
    std::cout << "***" << player2.name << " ---> " << playerToHero[player2.name]->get_name() << "\n";

    //showing hero and monster location first
    Dracula* dracula = new Dracula();
    InvisibleMan* invisibleMan = new InvisibleMan();
    dracula->set_location("Barn");
    invisibleMan->set_location("Institute");

    map.placeMonster(dracula, "Cave");
    map.placeMonster(invisibleMan, "Institute");

    map.placeHero(h1 , h1->get_location());
    map.placeHero(h2, h2->get_location());

}

void GameController::displayGameState() const
{
    std::cout << "\n\tTerror Level: " << terrorLevel << " / 7\t\n";
    std::cout << "==================================================================================\n";
    std::cout << "Hero status:\n";

    for (Hero* hero : heroes) {
        std::cout << "NAME : " << hero->get_name() << "\n";
        std::cout << "LOCATION :  " << hero->get_location() << "\n";
        std::cout << "HEALTH : " << hero->get_health() << "\n";
        std::cout << "REMAINING ACTIONS : " << hero->get_remainingActions() << "\n";

        const auto& inv = hero->get_inventory();
        std::cout << "ITEMS : ";

        if (inv.empty())
        {
            std::cout << "There are no items...";
        } else {
            for (const auto& item : inv)
            {
                std::cout << item.toString() << " | ";
            }
        }
        std::cout << "\n---------------------------\n";
    }

    std::cout << '\t' << "Items on the map :\n";
    const auto& mapItems = map.get_getAllItems();
    if (mapItems.empty())
    {
        std::cout << "no items currently on the map.\n";
    }else{
        for (const auto& item : mapItems)
        {
            std::cout << "- " << item.toString() << " at " << item.get_location() << '\n';
        }
    }
    
    std::cout << "\n---------------------------\n";
    map.displayAvailableVillagers();
}

void GameController::printActionHelp() const
{
    std::cout << "\nAction Help Menu:\n";
    std::cout << "0. Exit Game: Quit the game.\n";
    std::cout << "1. Move: Travel to an adjacent connected location. Costs 1 action.\n";
    std::cout << "2. Guide: Escort a villager from your current location to another.\n";
    std::cout << "3. Pickup: Pick up an item available at your current location.\n";
    std::cout << "4. Special Ability: Use your hero's unique power.\n";
    std::cout << "5. End Turn: Finish your turn, even if actions remain.\n";
}

void GameController::printSingleActionHelp(int n) const
{
    switch (n) {
        case 1:
            std::cout << "1. Move:\n";
            std::cout << "- Allows your hero to travel to a connected adjacent location.\n";
            std::cout << "- Each move consumes 1 action point.\n";
            break;

        case 2:
            std::cout << "2. Pickup:\n";
            std::cout << "- Picks up one or more items at your current location.\n";
            std::cout << "- Items help you defeat monsters or activate special actions.\n";
            break;

        case 3:
            std::cout << "3. Guide:\n";
            std::cout << "- Allows you to move a villager from your current location along with you.\n";
            std::cout << "- You must be in the same location as the villager.\n";
            break;

        case 4:
            std::cout << "4. Special Ability:\n";
            std::cout << "- Each hero has a unique ability that can help in different ways.\n";
            std::cout << "- For example, the Archaeologist can pick up neighboring items.\n";
            break;

        case 5:
            std::cout << "5. Use Perk Card:\n";
            std::cout << "- Uses the Perk card assigned to your hero if you haven’t used it yet.\n";
            std::cout << "- Perk cards have powerful effects and are usually used once.\n";
            break;
        
        case 6:
            std::cout << "5. End Turn:\n";
            std::cout << "- Skips the rest of your actions and ends your turn immediately.\n";
            break;

        default:
            std::cout << "Invalid action number. Please enter a number between 1 and 5.\n";
    }
}

void GameController::heroPhase(Hero* currentHero)
{
    bool turnEnded = false;

    while (!turnEnded && currentHero->get_remainingActions() > 0)
    {
        std::cout << "\n--- " << currentHero->get_name() << "'s Turn ---\n";
        std::cout << "Location: " << currentHero->get_location() << "\n";
        std::cout << "Health: " << currentHero->get_health() << "\n";
        std::cout << "Remaining Actions: " << currentHero->get_remainingActions() << "\n";

        std::cout << "\n=== Hero Actions ===\n";
        std::cout << "1. Move\n";
        std::cout << "2. Pickup\n";
        std::cout << "3. Guide\n";
        std::cout << "4. Special Ability\n";
        std::cout << "5. Use Perk Card\n";
        std::cout << "6. End Turn\n";
        std::cout << "Enter your choice (or 'help <number>'): \n";
        std::cout << "or enter 0 to exit the game :)";

        std::string input;
        std::getline(std::cin, input);

        if (input.rfind("help", 0) == 0)
        {
            int num = std::stoi(input.substr(5));
            printSingleActionHelp(num);
            continue;
        }

        int choice = std::stoi(input);
        switch (choice)
        {
            case 0:
                std::cout << "Exiting game. Goodbye!\n";
                exit(0);
                break;
            case 1: {
                std::cout << "Enter destination location: ";
                std::string newLoc;
                std::getline(std::cin, newLoc);
                currentHero->move(newLoc);
                map.placeHero(currentHero, newLoc);
                break;
            }
            case 2:
                currentHero->pickup(itemBag);
                break;
            case 3:
                currentHero->guide(map);
                break;
            case 4:
                currentHero->specialAbility();
                break;
            case 5:
                currentHero->usePerk(map, heroes, monsters, itemBag, skipMonsterPhase);
                break;
            case 6:
                turnEnded = true;
                break;
            default:
                std::cout << "Invalid choice.\n";
        }
    }

    std::cout << "--- " << currentHero->get_name() << "'s turn ended ---\n";
    currentHero->resetActions();
}

void GameController::monsterPhase()
{
    if (skipMonsterPhase)
    {
        std::cout << "Monster Phase was skipped due to perk card.\n";
        skipMonsterPhase = false;
        return;
    }

    if (monsterDeck.empty())
    {
        std::cout << "No monster cards left!\n";
        return;
    }

    auto& card = monsterDeck.back();
    std::cout << "\n--- Monster Phase ---\n";
    std::cout << "Card: " << card->get_name() << "\n";
    try{

    card->apply(map, monsters, heroes, dice , *this);
    } catch(const std::exception& e) {
        std::cerr << "Error applying monster card: " << e.what() << "\n";
    }

    monsterDeck.pop_back();

    for (Monster* m : monsters)
    {
        std::string location = m->get_currentLocation();
        std::vector<Villager*> victims = map.getVillagersAt(location);

        for (Villager* v : victims)
        {
            std::cout << "Villager " << v->get_name() << " was killed by " << m->get_name() << "!\n";
            map.removeVillager(v);
            increaseTerrorLevel();
        }
    }
}

void GameController::increaseTerrorLevel()
{
    terrorLevel++;
}

void GameController::checkDefeat(Hero* hero)
{
    if (!hero->isAlive())
    {
        increaseTerrorLevel();
        hero->dropAllItems(itemBag);
        // optional: teleport hero to safe location
        hero->set_location("Hospital");
        hero->receiveDamage(-4);
    }
}

void GameController::setupPerkCards()
{
    for (int i = 0 ; i < 4 ; i++)
    {
        perkDeck.push_back(std::make_unique<LateIntoNightCard>());
    }
    for (int i = 0 ; i < 3 ; i++)
    {
        perkDeck.push_back(std::make_unique<HurryCard>());
    }
    for (int i = 0 ; i < 3 ; i++)
    {
        perkDeck.push_back(std::make_unique<VisitDetectiveCard>());
    }
    for (int i = 0 ; i < 4 ; i++)
    {
        perkDeck.push_back(std::make_unique<OverstockCard>());
    }
    for (int i = 0 ; i < 3 ; i++)
    {
        perkDeck.push_back(std::make_unique<RepelCard>());
    }
    for (int i = 0 ; i < 3 ; i++)
    {
        perkDeck.push_back(std::make_unique<BreakOfDawnCard>());
    }

    std::shuffle(perkDeck.begin(), perkDeck.end(), std::mt19937(std::random_device{}()));

    for (Hero* h : heroes)
    {
        if (!perkDeck.empty())
        {
            std::unique_ptr<PerkCard> card = std::move(perkDeck.back());
            std::cout << h->get_name() << " received perk card: " << card->get_name() << "\n";
            h->givePerk(std::move(card));
            perkDeck.pop_back();
        }
    }
}

void GameController::setUpGame()
{
    std::vector<Item> drawnItems = itemBag.drawRandomItems(12);

    for (const Item& item : drawnItems)
    {
        map.placeItem(item);
    }

    std::cout << "\nInitial Items placed on the Map:\n";
    std::cout << "----------------------------------------\n";

    for (const Item& item : drawnItems)
    {
        std::string typeStr;
        switch (item.get_type())
        {
            case Item::Type::RED:    typeStr = "RED"; break;
            case Item::Type::BLUE:   typeStr = "BLUE"; break;
            case Item::Type::YELLOW: typeStr = "YELLOW"; break;
        }

        std::cout << "- " << typeStr << " Item (Power: " << item.get_power()
                  << ") -> Location: " << item.get_location() << "\n";
    }

    std::cout << "----------------------------------------\n";
}

void GameController::run()
{
    std::cout << "\n=== Welcome to Horrified ===\n";
    std::cout << "^Before you start, take a look at the map^\n";
    map.printMap();
    map.displayAvailableVillagers();
    askPlayersInfo();
    determineStartingPlayer();
    assignHeroesToPlayers();
    setupPerkCards();
    setUpGame();
    std::cout << "Initial state of the game:\n";
    displayGameState();

    while (true)
    {

    skipMonsterPhase = false;
    
    for (Hero* h : heroes)
    {
        if (h->isAlive())
        {
            heroPhase(h);
            monsterPhase();
            displayGameState();
            if (terrorLevel >= 5) return;
        }
    }
}
}