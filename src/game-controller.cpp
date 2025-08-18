#include "../include/game-controller.h"
#include "../include/game.h"
#include "../include/ActionState.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <ctime>
#include <sstream>

GameController::GameController()
{
    if (!gameFont.loadFromFile("../build/ManufacturingConsent-Regular.ttf"))
    {
        std::cerr << "Failed to load font!\n";
        return;
    }

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

    //std::cout << "Please enter the time you last ate garlic (hours and minutes): ";
    //std::cin >> hour >> minute;
    //std::cin.ignore();

    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm local_tm = *std::localtime(&now_c);
    local_tm.tm_hour = hour;
    local_tm.tm_min = minute;
    local_tm.tm_sec = 0;

    return std::chrono::system_clock::from_time_t(std::mktime(&local_tm));
}

std::chrono::system_clock::time_point GameController::convertToTimePoint(const std::string& timeStr)
{
    int hour = 0, minute = 0;
    std::sscanf(timeStr.c_str(), "%d:%d", &hour, &minute);

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
    //std::cout << "First player's name: ";
    //std::getline(std::cin, player1.name);
    //player1.lastGarlicTime = get_timePointFromInput();
    // std::cout << "Second player's name: ";
    // std::getline(std::cin, player2.name);
    // player2.lastGarlicTime = get_timePointFromInput();
}

std::string GameController::getHeroLocation(const std::string& heroName) const
{
    return map.get_characterLocation(heroName);
}

std::set<std::string> GameController::getConnectedLocations(const std::string& location) const
{ 
    return map.getConnections(location);
}

bool GameController::moveHero(const std::string& heroName, const std::string& toLocation)
{
    return map.moveCharacter(heroName, toLocation);
}

const std::vector<Item>& GameController::getItemsAtLocation(const std::string& location) const
{
    return map.get_itemsAt(location);
}

bool GameController::heroPickUpItem(const std::string& heroName, const std::string& location)
{
    Hero* hero = getHero(heroName);
    if (!hero) return false;
    return map.get_itemBag().transferItemToHero(location , *hero);
}

Hero* GameController::getHero(const std::string& heroName)
{
    for (Hero* hero : heroes)
    {
        if (hero->get_name() == heroName)
        {
            return hero;
        }
    }
    return nullptr;
}

const Hero* GameController::getHero(const std::string& heroName) const
{
    for (const Hero* hero : heroes)
    {
        if (hero->get_name() == heroName)
        {
            return hero;
        }
    }
    return nullptr;
}

const std::vector<Monster*>& GameController::getMonsters() const
{
    return monsters;
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

void GameController::setupPlayers(const std::vector<PlayerInfo>& playerInfos)
{
    for (const auto& info : playerInfos)
    {
        std::string startLoc = heroStartLocations[info.heroName];
        Hero* hero = nullptr;

        if (info.heroName == "Archaeologist")
            hero = new Archaeologist(info.name, startLoc);
        else if (info.heroName == "Mayor")
            hero = new Mayor(info.name, startLoc);
        else if (info.heroName == "Courier")
            hero = new Courier(info.name, startLoc);
        else if (info.heroName == "Scientist")
            hero = new Scientist(info.name, startLoc);
        else
        {
            std::cerr << "Unknown hero name: " << info.heroName << "\n";
            continue;
        }
        map.placeHero(hero, startLoc);
        playerToHero[info.name] = hero;
        heroes.push_back(hero);
    }
}

void GameController::displayGameState(sf::RenderWindow& window) const
{
    sf::Font font;
    if (!font.loadFromFile("../build/ManufacturingConsent-Regular.ttf"))
    {
        std::cerr << "Failed to load font!\n";
        return;
    }

    sf::RectangleShape panel(sf::Vector2f(600.f , 400.f));
    panel.setFillColor(sf::Color(50 , 50 , 50 , 200));
    panel.setPosition(100.f , 100.f);
    window.draw(panel);

    sf::Text terrorText("Terror Level: " + std::to_string(terrorLevel) + " /7" , font , 20);
    terrorText.setFillColor(sf::Color::White);
    terrorText.setPosition(120.f , 120.f);
    window.draw(terrorText);

    sf::Text heroTitle("Hero status:" , font , 20);
    heroTitle.setFillColor(sf::Color::White);
    heroTitle.setPosition(120.f , 160.f);
    window.draw(heroTitle);

    float yOffset = 200.f;


    for (Hero* hero : heroes) {
        sf::Text nameText("NAME : " + hero->get_name() , font , 18);
        nameText.setFillColor(sf::Color::White);
        nameText.setPosition(120.f , yOffset); 
        yOffset += 20.f;
        window.draw(nameText);

        sf::Text locText("LOCATION : " + hero->get_location() , font , 18);
        locText.setFillColor(sf::Color::White);
        locText.setPosition(120.f , yOffset);
        yOffset += 20.f;
        window.draw(locText);

        sf::Text healthText("HEALTH : " + std::to_string(hero->get_health()) , font , 18);
        healthText.setFillColor(sf::Color::White);
        healthText.setPosition(120.f , yOffset);
        yOffset += 20.f;
        window.draw(healthText);

        sf::Text actionsText("REMAINING ACTIONS : " + std::to_string(hero->get_remainingActions()) , font , 18);
        actionsText.setFillColor(sf::Color::White);
        actionsText.setPosition(120.f , yOffset);
        yOffset += 20.f;
        window.draw(actionsText);
        
        sf::Text itemsText("ITEMS : " , font , 18);
        itemsText.setFillColor(sf::Color::White);
        itemsText.setPosition(120.f , yOffset);
        yOffset += 20.f;
        window.draw(itemsText);

        const auto& inv = hero->get_inventory();

        if (inv.empty())
        {
            std::string itemStr;
            for (const auto& item : inv)
            {
                itemStr += item.toString() + " | ";
            }
            sf::Text itemDetail(itemStr , font , 18);
            itemDetail.setFillColor(sf::Color::White);
            itemDetail.setPosition(150.f , yOffset - 20.f);

            window.draw(itemDetail);
        }
        yOffset += 20.f;
        sf::Text separatorText("---------------------------" , font , 18);
        separatorText.setFillColor(sf::Color::White);
        separatorText.setPosition(120.f , yOffset);
        yOffset += 20.f;
        window.draw(separatorText);
    }

    sf::Text mapItemsTitle("\tItems on the map : " , font , 20);
    mapItemsTitle.setFillColor(sf::Color::White);
    mapItemsTitle.setPosition(120.f , yOffset);
    yOffset += 30.f;
    window.draw(mapItemsTitle);

    const auto& mapItems = map.get_AllItems();
    if (!mapItems.empty())
    {
        for (const auto& item : mapItems)
        {
            sf::Text itemText("- " + item.toString() + " at " + item.get_location() , font , 18);
            itemText.setFillColor(sf::Color::White);
            itemText.setPosition(120.f , yOffset);
            yOffset += 20.f;
            window.draw(itemText);
        }
    }

    sf::Text villagersTitle("Available Villagers : " , font , 20);
    villagersTitle.setFillColor(sf::Color::White);
    villagersTitle.setPosition(120.f , yOffset);
    yOffset += 30.f;
    window.draw(villagersTitle);
    
    auto villagerTexts = map.displayAvailableVillagers(window);
}

void GameController::printActionHelp(sf::RenderWindow& window) const
{
    sf::Font font;
    if (!font.loadFromFile("../build/ManufacturingConsent-Regular.ttf"))
    {
        std::cerr << "Failed to load font!\n";
        return;
    }
    sf::RectangleShape panel(sf::Vector2f(400.f , 300.f));
    panel.setFillColor(sf::Color(50 , 50 , 50 , 200));
    panel.setPosition(200.f , 150.f);
    window.draw(panel);

    sf::Text titleText("Action Help Menu:" , font , 24);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(220.f , 170.f);
    window.draw(titleText);
    // std::cout << "\nAction Help Menu:\n";

    std::vector<std::pair<std::string , sf::Vector2f>> options = 
    {{"0. Exit Game: Quit the game." , {220.f , 210.f}} , {"1. Move: Travel to an adjacent connected location. Costs 1 action." , {220.f , 240.f}} ,
    {"2. Guide: Escort a villager from your current location to another." , {220.f , 270.f}} , {"3. Pickup: Pick up an item available at your current location." , {220.f , 300.f}} ,
    {"4. Special Ability: Use your hero's unique power." , {220.f , 330.f}} , {"5. End Turn: Finish your turn, even if actions remain." , {220.f , 360.f}}};
}

void GameController::printSingleActionHelp(sf::RenderWindow& window , int n) const
{
    sf::Font font;
    if (!font.loadFromFile("../build/ManufacturingConsent-Regular.ttf"))
    {
        std::cerr << "Failed to load font!\n";
        return;
    }
    sf::RectangleShape panel(sf::Vector2f(500.f , 200.f));
    panel.setFillColor(sf::Color(50 , 50 , 50 , 200));
    panel.setPosition(150.f , 200.f);
    window.draw(panel);

    sf::Text mainText("" , font , 20);
    mainText.setFillColor(sf::Color::White);
    mainText.setPosition(170.f , 220.f);

    sf::Text detailText1("" , font , 18);
    detailText1.setFillColor(sf::Color::White);
    detailText1.setPosition(170.f , 250.f);

    sf::Text detailText2("" , font , 18);
    detailText2.setFillColor(sf::Color::White);
    detailText2.setPosition(170.f , 280.f);

    switch (n) {
        case 1:
            mainText.setString("1. Move:");
            detailText1.setString("- Allows your hero to travel to a connected adjacent location.");
            detailText2.setString("- Each move consumes 1 action point.");
            // std::cout << "1. Move:\n";
            // std::cout << "- Allows your hero to travel to a connected adjacent location.\n";
            // std::cout << "- Each move consumes 1 action point.\n";
            break;

        case 2:
            mainText.setString("2. Pickup:");
            detailText1.setString("- Picks up one or more items at your current location.");
            detailText2.setString("- Items help you defeat monsters or activate special actions.");
            // std::cout << "2. Pickup:\n";
            // std::cout << "- Picks up one or more items at your current location.\n";
            // std::cout << "- Items help you defeat monsters or activate special actions.\n";
            break;

        case 3:
            mainText.setString("3. Guide:");
            detailText1.setString("- Allows you to move a villager from your current location along with you.");
            detailText2.setString("- You must be in the same location as the villager.");
            // std::cout << "3. Guide:\n";
            // std::cout << "- Allows you to move a villager from your current location along with you.\n";
            // std::cout << "- You must be in the same location as the villager.\n";
            break;

        case 4:
            mainText.setString("4. Special Ability:");
            detailText1.setString("- Each hero has a unique ability that can help in different ways.");
            detailText2.setString("- For example, the Archaeologist can pick up neighboring items.");
            // std::cout << "4. Special Ability:\n";
            // std::cout << "- Each hero has a unique ability that can help in different ways.\n";
            // std::cout << "- For example, the Archaeologist can pick up neighboring items.\n";
            break;

        case 5:
            mainText.setString("5. Use Perk Card:");
            detailText1.setString("- Uses the Perk card assigned to your hero if you haven't used it yet.");
            detailText2.setString("- Perk cards have powerful effects and are usually used once.");
            // std::cout << "5. Use Perk Card:\n";
            // std::cout << "- Uses the Perk card assigned to your hero if you haven’t used it yet.\n";
            // std::cout << "- Perk cards have powerful effects and are usually used once.\n";
            break;
        
        case 6:
            mainText.setString("5. End Turn:");
            detailText1.setString("- Skips the rest of your actions and ends your turn immediately.");
            detailText2.setString("");
            // std::cout << "5. End Turn:\n";
            // std::cout << "- Skips the rest of your actions and ends your turn immediately.\n";
            break;

        default:
            mainText.setString("Invalid action number.");
            detailText1.setString("Please enter a number between 1 and 5.");
            detailText2.setString("");
            // std::cout << "Invalid action number. Please enter a number between 1 and 5.\n";
            break;
    }
    window.draw(mainText);
    window.draw(detailText1);
    window.draw(detailText2);
}

void GameController::heroPhase(sf::RenderWindow& window , Hero* currentHero)
{
    bool turnEnded = false;
    ActionState currentAction = ActionState::None;

    sf::Font font;
    if (!font.loadFromFile("../build/ManufacturingConsent-Regular.ttf"))
    {
        std::cerr << "Failed to load font!\n";
        return;
    }

    std::vector<std::pair<sf::RectangleShape , sf::Text>> actionButtons;
    std::vector<std::string> actions = {"Move" , "Pickup" , "Guide" , "Special Ability" , "Use Perk" , "End Turn"};
    float yOffsetStart = 200.f;

    for (const auto& action : actions)
    {
        sf::RectangleShape button(sf::Vector2f(200.f , 40.f));
        button.setFillColor(sf::Color(80 , 150 , 80));
        button.setPosition(220.f , yOffsetStart);

        sf::Text text(action , font , 18);
        text.setFillColor(sf::Color::White);
        text.setPosition(button.getPosition().x + 10 , button.getPosition().y + 5);

        actionButtons.push_back({button , text});
        yOffsetStart += 50.f;
    }

    std::string moveInput;
    bool typingMove = false;

    while (!turnEnded && window.isOpen())
    {
        // sf::RectangleShape panel(sf::Vector2f(400.f , 400.f));
        // panel.setFillColor(sf::Color(50 , 50 , 50 , 200));
        // panel.setPosition(200.f , 100.f);
        // window.draw(panel);
        // sf::Text statusText("--- " + currentHero->get_name() + "'s Turn ---\n" "Location: " + currentHero->get_location() + "\n" "Health:" + std::to_string(currentHero->get_health()) + "Remaining Actions: " + std::to_string(currentHero->get_remainingActions()) , font , 18);
        // // std::cout << "\n--- " << currentHero->get_name() << "'s Turn ---\n";
        // // std::cout << "Location: " << currentHero->get_location() << "\n";
        // // std::cout << "Health: " << currentHero->get_health() << "\n";
        // // std::cout << "Remaining Actions: " << currentHero->get_remainingActions() << "\n";
        // statusText.setFillColor(sf::Color::White);
        // statusText.setPosition(220.f , 120.f);
        // window.draw(statusText);

        // std::vector<std::pair<sf::RectangleShape , sf::Text>> actionButtons =
        // {{sf::RectangleShape(sf::Vector2f(150.f , 40.f)) , sf::Text("1. Move" , font , 18)} , {sf::RectangleShape(sf::Vector2f(150.f , 40.f)) , sf::Text("2. Pickup" , font , 18)} ,
        // {sf::RectangleShape(sf::Vector2f(150.f , 40.f)) , sf::Text("3. Guide" , font , 18)} , {sf::RectangleShape(sf::Vector2f(150.f , 40.f)) , sf::Text("4. Special Ability" , font , 18)} ,
        // {sf::RectangleShape(sf::Vector2f(150.f , 40.f)) , sf::Text("5. Use Perk Card" , font , 18)} , {sf::RectangleShape(sf::Vector2f(150.f , 40.f)) , sf::Text("6. End Turn" , font , 18)} ,
        // {sf::RectangleShape(sf::Vector2f(150.f , 40.f)) , sf::Text("enter 0 to exit the game :)" , font , 18)}};

        // float yOffset = 200.f;
        // for (auto& [button , text] : actionButtons)
        // {
        //     button.setFillColor(sf::Color::Green);
        //     button.setPosition(220.f , yOffset);
        //     text.setFillColor(sf::Color::White);
        //     text.setPosition(230.f , yOffset + 5.f);

        //     window.draw(button);
        //     window.draw(text);

        //     yOffset += 50.f;
        // }
        // sf::RectangleShape inputBox(sf::Vector2f(200.f , 40.f));
        // inputBox.setFillColor(sf::Color(100 , 100 , 100));
        // inputBox.setPosition(220.f , 450.f);
        // window.draw(inputBox);

        // // std::string input;
        // std::string userInput;
        // bool inputActive = false;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) 
            {
            window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                for (int i = 0 ; i < actionButtons.size() ; i++)
                {
                    if (actionButtons[i].first.getGlobalBounds().contains(mousePos))
                    {
                        switch (i)
                        {
                        case 0:
                        currentAction = ActionState::Move; break;
                        
                        case 1:
                        currentAction = ActionState::Pickup; break;

                        case 2:
                        currentAction = ActionState::Guide; break;

                        case 3:
                        /* Special Ability */ break;

                        case 4:
                        currentAction = ActionState::UsePerk; break;

                        case 5:
                        currentAction = ActionState::EndTurn; turnEnded = true; break;
                        }
                    }
                }
            }
            if (sf::Event::TextEntered && typingMove)
            {
                char c = static_cast<char>(event.text.unicode);
                if (std::isprint(c))
                { 
                moveInput += c;
                }
                if (c == '\r' || c == '\n') 
                {
                typingMove = false;
                }
            }
        }
                    
            window.clear(sf::Color(30 , 30 , 30));

            sf::RectangleShape panel(sf::Vector2f(400.f , 400.f));
            panel.setFillColor(sf::Color(50 , 50 , 50 , 200));
            panel.setPosition(200.f , 100.f);
            window.draw(panel);

            sf::Text statusText("--- " + currentHero->get_name() + "'s Turn ---\n" + std::string("Location: ") + currentHero->get_location() + "\n" + "Health: " + std::to_string(currentHero->get_health()) + "\n" + "Remaining Actions: " + std::to_string(currentHero->get_remainingActions()) , font , 18);
            statusText.setFillColor(sf::Color::White);
            statusText.setPosition(220.f , 120.f);
            window.draw(statusText);

            for (auto& [button, text] : actionButtons)
            {
                window.draw(button);
                window.draw(text);
            }

            if (currentAction == ActionState::Move)
            {
                 sf::Text movePrompt("Enter destination:" , font , 18);
                movePrompt.setPosition(220.f , 480.f);
                movePrompt.setFillColor(sf::Color::Yellow);
                window.draw(movePrompt);

                sf::Text inputText(moveInput , font , 18);
                inputText.setPosition(220.f , 510.f);
                inputText.setFillColor(sf::Color::White);
                window.draw(inputText);

                typingMove = true;
            }else if (currentAction == ActionState::Pickup)
            {
                currentHero->pickup(itemBag);
                currentAction = ActionState::None;
            }else if (currentAction == ActionState::Guide)
            {
                currentHero->guide(map);
                currentAction = ActionState::None;
            }else if (currentAction == ActionState::UsePerk)
            {
                auto& perks = currentHero->getPerks();
                if (!perks.empty())
                {
                    auto card = std::move(perks.back());
                    perks.pop_back();

                    sf::Texture cardTexture;
                    if (!cardTexture.loadFromFile(card->getImagePath()))
                    {
                        std::cerr << "Failed to load perk card image!\n";
                    } else {
                        sf::Sprite cardSprite(cardTexture);
                        cardSprite.setPosition(250.f, 260.f);
                        window.draw(cardSprite);
                        window.display();
                        sf::sleep(sf::seconds(2));
                    }

                    card->apply(*currentHero, heroes, monsters, itemBag, map, skipMonsterPhase);
                }
                currentAction = ActionState::None;
            }
            
            window.display();

            if (!typingMove && !moveInput.empty())
            {
                currentHero->move(moveInput);
                map.placeHero(currentHero , moveInput);
                moveInput.clear();
                currentAction = ActionState::None;
            }
        }

    currentHero->resetActions();
}


std::map<std::string, std::string> GameController::getHeroLocations() const
{
    std::map<std::string, std::string> locations;
    for (const Hero* hero : heroes)
    {
        locations[hero->get_name()] = hero->get_location();
    }
    return locations;
}

void GameController::monsterPhase(sf::RenderWindow& window)
{
    sf::Font font;
    if (!font.loadFromFile("../build/ManufacturingConsent-Regular.ttf"))
    {
        std::cerr << "Failed to load font!\n";
        return;
    }

    if (skipMonsterPhase)
    {
        sf::RectangleShape panel(sf::Vector2f(400.f , 100.f));
        panel.setFillColor(sf::Color(50 , 50 , 50 , 200));
        panel.setPosition(200.f , 250.f);
        window.draw(panel);
        
        sf::Text message("Monster Phase was skipped due to perk card." , font , 20);
        message.setFillColor(sf::Color::White);
        message.setPosition(220.f , 270.f);
        window.draw(message);
        // std::cout << "Monster Phase was skipped due to perk card.\n";
        skipMonsterPhase = false;
        window.display();
        sf::sleep(sf::seconds(2));
        return;
    }

    if (monsterDeck.empty())
    {
        sf::RectangleShape panel(sf::Vector2f(400.f , 100.f));
        panel.setFillColor(sf::Color(50 , 50 , 50 , 200));
        panel.setPosition(200.f , 250.f);
        window.draw(panel);

        sf::Text messsage("No monster cards left!" , font , 20);
        // std::cout << "No monster cards left!\n";
        messsage.setFillColor(sf::Color::White);
        messsage.setPosition(220.f , 270.f);
        window.draw(messsage);

        window.display();
        sf::sleep(sf::seconds(2));

        return;
    }

    auto& card = monsterDeck.back();
    sf::RectangleShape panel(sf::Vector2f(400.f , 150.f));
    panel.setFillColor(sf::Color(50 , 50 , 50 , 200));
    panel.setPosition(200.f , 225.f);
    window.draw(panel);

    sf::Text phaseText("--- Monster Phase ---" , font , 20);
    // std::cout << "\n--- Monster Phase ---\n";
    phaseText.setFillColor(sf::Color::White);
    phaseText.setPosition(220.f , 235.f);
    window.draw(phaseText);

    sf::Text cardText("Card: " + card->get_name() , font , 20);
    // std::cout << "Card: " << card->get_name() << "\n";
    cardText.setFillColor(sf::Color::White);
    cardText.setPosition(220.f , 265.f);
    window.draw(cardText);

    window.display();
    sf::sleep(sf::seconds(1));

    try{

    card->apply(map, monsters, heroes, dice , *this);
    } catch(const std::exception& e) {
        sf::Text errorText("Error applying monster card: " + std::string(e.what()) , font , 18);
        // std::cerr << "Error applying monster card: " << e.what() << "\n";
        errorText.setFillColor(sf::Color::Red);
        errorText.setPosition(220.f , 295.f);
        window.draw(errorText);
        window.display();
        sf::sleep(sf::seconds(2));
    }

    monsterDeck.pop_back();

    for (Monster* m : monsters)
    {
        std::string location = m->get_currentLocation();
        std::vector<Villager*> victims = map.getVillagersAt(location);

        for (Villager* v : victims)
        {
            sf::RectangleShape victimPanel(sf::Vector2f(400.f , 100.f));
            victimPanel.setFillColor(sf::Color(50 , 50 , 50 , 200));
            victimPanel.setPosition(200.f , 250.f);
            window.draw(victimPanel);

            sf::Text victimText("Villager " + v->get_name() + " was killed by " + m->get_name() , font , 20);
            // std::cout << "Villager " << v->get_name() << " was killed by " << m->get_name() << "!\n";
            victimText.setFillColor(sf::Color::Red);
            victimText.setPosition(220.f , 270.f);
            window.draw(victimText);

            window.display();
            sf::sleep(sf::seconds(2));

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

void GameController::setupPerkCards(sf::RenderWindow& window)
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

    sf::RectangleShape setupPanel(sf::Vector2f(400.f , 100.f));
    setupPanel.setFillColor(sf::Color(50 , 50 , 50 , 200));
    setupPanel.setPosition(200.f , 250.f);
    window.draw(setupPanel);

    sf::Text setupText("setup perk cards..." , gameFont , 20);
    setupText.setFillColor(sf::Color::White);
    setupText.setPosition(220.f , 270.f);
    window.draw(setupText);
    window.display();
    sf::sleep(sf::seconds(1));

    std::shuffle(perkDeck.begin(), perkDeck.end(), std::mt19937(std::random_device{}()));

    for (Hero* h : heroes)
    {
        if (!perkDeck.empty())
        {
            std::unique_ptr<PerkCard> card = std::move(perkDeck.back());
            sf::RectangleShape assignPanel(sf::Vector2f(400.f , 100.f));
            assignPanel.setFillColor(sf::Color(50 , 50 , 50 , 200));
            assignPanel.setPosition(200.f , 250.f);
            window.draw(assignPanel);

            sf::Text assignText(h->get_name() + " received perk card: " + card->get_name() , gameFont , 20);
            // std::cout << h->get_name() << " received perk card: " << card->get_name() << "\n";
            assignText.setFillColor(sf::Color::White);
            assignText.setPosition(220.f , 270.f);
            window.draw(assignText);
            window.display();
            sf::sleep(sf::seconds(1));

            h->givePerk(std::move(card));
            perkDeck.pop_back();
        }
    }
}

void GameController::setUpGame(sf::RenderWindow& window)
{
    
    sf::Texture redTexture , blueTexture , yellowTexture;
    if (!redTexture.loadFromFile("../build/Items/Red/Dart.png"))
    {
        std::cerr << "Failed to load red item image!\n";
        return;
    }

    if (!blueTexture.loadFromFile("../build/Items/Blue/Kite.png"))
    {
        std::cerr << "Failed to load blue item image!\n";
        return;
    }

    if (!yellowTexture.loadFromFile("../build/Items/Yellow/Flower.png"))
    {
        std::cerr << "Failed to load yellow item image!\n";
        return;
    }

    std::vector<Item> drawnItems = itemBag.drawRandomItems(12);

    for (const Item& item : drawnItems)
    {
        map.placeItem(item);
    }

    sf::RectangleShape setupPanel(sf::Vector2f(400.f , 100.f));
    setupPanel.setFillColor(sf::Color(50 , 50 , 50 , 200));
    setupPanel.setPosition(200.f , 250.f);
    window.draw(setupPanel);

    sf::Text setupText("Setting up initial items on the map..." , gameFont , 20);
    setupText.setFillColor(sf::Color::White);
    setupText.setPosition(220.f , 270.f);
    window.draw(setupText);
    window.display();
    sf::sleep(sf::seconds(1));

    sf::RectangleShape itemPanel(sf::Vector2f(600.f , 400.f));
    itemPanel.setFillColor(sf::Color(50 , 50 , 50 , 200));
    itemPanel.setPosition(150.f , 100.f);
    window.draw(itemPanel);

    sf::Text titleText("Initial Items placed on the Map:" , gameFont , 20);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(170.f , 120.f);
    window.draw(titleText);

    sf::Text separatorText("----------------------------------------" , gameFont , 18);
    separatorText.setFillColor(sf::Color::White);
    separatorText.setPosition(170.f , 150.f);
    window.draw(separatorText);

    float yOffset = 180.f;
    for (const Item& item : drawnItems)
    {
        sf::Sprite itemSprite;
        std::string typeStr;
        switch (item.get_type())
        {
            case Item::Type::RED:
            itemSprite.setTexture(redTexture);
            typeStr = "RED"; break;

            case Item::Type::BLUE:
            itemSprite.setTexture(blueTexture);
            typeStr = "BLUE"; break;

            case Item::Type::YELLOW:
            itemSprite.setTexture(yellowTexture);
            typeStr = "YELLOW"; break;
        }
        itemSprite.setScale(0.2f , 0.2f);
        itemSprite.setPosition(170.f , yOffset);

        std::string itemInfo = typeStr + " Item (Power: " + std::to_string(item.get_power()) + ") -> Location: " + item.get_location();

        sf::Text itemText(itemInfo , gameFont , 18);
        itemText.setFillColor(sf::Color::White);
        itemText.setPosition(220.f , yOffset + 10.f);
        window.draw(itemSprite);
        window.draw(itemText);
        yOffset += 60.f;
    }
    sf::Text endSeparator("----------------------------------------" , gameFont , 18);
    endSeparator.setFillColor(sf::Color::White);
    endSeparator.setPosition(170.f , yOffset);
    window.draw(endSeparator);
    window.display();
    sf::sleep(sf::seconds(2));
}

void GameController::run()
{
    sf::RectangleShape welcomePanel(sf::Vector2f(400.f , 100.f));
    welcomePanel.setFillColor(sf::Color(50 , 50 , 50 , 200));
    welcomePanel.setPosition(200.f , 250.f);
    window.draw(welcomePanel);

    sf::Text welcomeText("=== Welcome to Horrified ===" , gameFont , 20);
    welcomeText.setFillColor(sf::Color::White);
    welcomeText.setPosition(220.f , 270.f);
    window.draw(welcomeText);


    //map.printMap();
    map.displayAvailableVillagers(window);
    askPlayersInfo();
    determineStartingPlayer();
    setupPerkCards(window);
    setUpGame(window);
    std::cout << "Initial state of the game:\n";
    displayGameState(window);

    while (true)
    {

    skipMonsterPhase = false;
    
    for (Hero* h : heroes)
    {
        if (h->isAlive())
        {
            heroPhase(window , h);
            monsterPhase(window);
            displayGameState(window);
            if (terrorLevel >= 5) return;
        }
    }
}
}