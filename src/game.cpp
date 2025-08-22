#include <SFML/Graphics.hpp>
#include "GameView.h"
#include "locations.h"
#include "game-controller.h"
#include "game.h"
#include "ActionState.h"

#include <iostream>
#include <sstream>
#include <iomanip>


Game::Game(sf::RenderWindow& window) : window(window) , typingName(true) , currentPlayerIndex(-1) , inputDone(false) , gamePlayStarted(false) , currentHeroPlayer(0)
{
    if (!gameFont.loadFromFile("../build/ManufacturingConsent-Regular.ttf"))
    {
        std::cerr << "Failed to load font!\n";
        return;
    }
}

void Game::renderActionMenu(sf::RenderWindow& window)
{
    sf::RectangleShape actionPanel(sf::Vector2f(300.f , 300.f));
    actionPanel.setPosition(50.f , 100.f);
    actionPanel.setFillColor(sf::Color(30 , 30 , 30 , 200));
    window.draw(actionPanel);

    std::vector<std::string> actions =
    {"Move" , "Pickup" , "Guide" , "Use Perk" , "End Turn"};

    float buttonY = 120.f;
    for (const auto& action : actions)
    {
        sf::RectangleShape button(sf::Vector2f(250.f , 40.f));
        button.setPosition(75.f , buttonY);
        button.setFillColor(sf::Color(100 , 100 , 200));
        window.draw(button);

        sf::Text label(action , gameFont , 20);
        label.setPosition(90.f , buttonY + 5.f);
        label.setFillColor(sf::Color::White);
        window.draw(label);

        buttonY += 50.f;
    }
}

void Game::handleActionMenuClick(const sf::Vector2f& mousePos)
{
    std::vector<std::string> actions =
    {"Move", "Pickup", "Guide", "Use Perk", "End Turn"};

    float buttonY = 120.f;
    for (const auto& action : actions)
    {
        sf::FloatRect buttonRect(75.f , buttonY , 250.f , 40.f);
        if (buttonRect.contains(mousePos))
        {
            std::cout << "Action selected: " << action << "\n";

            if (action == "Move")
            {
                awaitingMoveDestinations = true;
            }
            else if (action == "Pickup")
        {
            std::string heroName = selectedHeroes[currentHeroPlayer];
            std::string loc = controller.getHeroLocation(heroName);
            const auto& items = controller.getItemsAtLocation(loc);

            if (!items.empty())
            {
                bool ok = controller.heroPickUpItem(heroName , loc);
                if (!ok)
                {
                    std::cerr << "Failed to pick up item for " << heroName << " at " << loc << "\n";
                } else {
            //remainingActions-- 
            // controller.heroPhase
                }
            } else
            {
                std::cout << "No items at location: " << loc << '\n';
            }
        }
            else if (action == "Guide")
            {
                // controller.guide(...);
            }
            else if (action == "Use Perk")
            {
                // controller.usePerk(...);
            }
            else if (action == "End Turn")
            {

            }

            break;
        }

        buttonY += 50.f;
    }
}

void Game::initHeroSpritesAfterSelection(const std::vector<std::string>& selectedHeroes , const sf::Sprite& mapSprite , const std::map<std::string, Position>& locations , GameController& controller)
{
    int i = 0;
    heroSprites.clear();
    heroTextures.clear();

    auto heroLocs = controller.getHeroLocations();

    for (const auto& heroName : selectedHeroes)
    {
        if (heroName.empty()) continue;

        auto& texture = heroTextures[heroName];
        if (!texture.loadFromFile("../build/Heros/" + heroName + ".png"))
        {
            std::cerr << "Failed to load hero image for " << heroName << "\n";
            continue;
        }

        sf::Sprite sprite;
        sprite.setTexture(heroTextures[heroName]);
        sprite.setScale(0.1f, 0.1f);

        auto locIt = heroLocs.find(heroName);
        if (locIt != heroLocs.end())
        {
            auto posIt = locations.find(locIt->second);
            if (posIt != locations.end())
            {
                sprite.setPosition(posIt->second.x , posIt->second.y);
            }
        }
        heroSprites[heroName] = sprite;
    }
}

void Game::startGame()
{
    //for frame
    window.setFramerateLimit(60);

    //for second page
    bool showInputScreen = false;
    bool typingName = true; 
    std::string nameInput , timeInput;
    int currentPlayerIndex = 0;
    std::vector<std::string> playerNames(2);
    std::vector<std::string> playerTimes(2);
    bool inputDone = false;

    heroStartingLocations["Archaeologist"] = "Docks";
    heroStartingLocations["Mayor"] = "Theater";
    heroStartingLocations["Courier"] = "Shop";
    heroStartingLocations["Scientist"] = "Institute";

    //hero screen
    bool showHeroSelectionScreen = false;
    std::vector<std::string> heroList = {"Archaeologist" , "Mayor" , "Courier" , "Scientist"};
    std::vector<sf::RectangleShape> heroButtons;
    std::vector<sf::Text> heroLabels;
    bool gamePlayStarted = false;

    std::vector<std::string> selectedHeroes(2);
    int currentHeroPlayer;
    std::map<std::string, sf::RectangleShape> locationHitboxes;

    std::map<Item::Type, sf::Texture> itemTextures;

    sf::Texture redTex, blueTex, yellowTex;

    if (!redTex.loadFromFile("../build/Items/Red/Dart.png"))
    {
        throw std::runtime_error("Failed to load red item");
    }

    if (!blueTex.loadFromFile("../build/Items/Blue/Fossil.png"))
    {
        throw std::runtime_error("Failed to load blue item");
    }

    if (!yellowTex.loadFromFile("../build/Items/Yellow/Garlic.png"))
    {
        throw std::runtime_error("Failed to load yellow item");
    }

    itemTextures[Item::Type::RED] = redTex;
    itemTextures[Item::Type::BLUE] = blueTex;
    itemTextures[Item::Type::YELLOW] = yellowTex;



    //map screen
    bool showMapScreen = false;

    //display background1
    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("../build/Horrified.jpg"))
    {
        std::cerr << "Failed to load horrified image!\n";
        exit(-1);
    }

    //input background texture
    sf::Texture inputBgTexture;
    if (!inputBgTexture.loadFromFile("../build/DraculaBackground.jpg"))
    {
        std::cerr << "Failed to load input screen background!\n";
        exit(-1);
    }

    sf::Sprite inputBgSprite(inputBgTexture);

    sf::Vector2u textSize = inputBgTexture.getSize();
    sf::Vector2u winSize = window.getSize();

    float scaleX = static_cast<float>(winSize.x) / textSize.x;
    float scaleY = static_cast<float>(winSize.y) / textSize.y;
    inputBgSprite.setScale(scaleX , scaleY);


    sf::Sprite bgSprite(bgTexture);
    // bgSprite.setTexture(bgTexture);
    sf::Vector2u textureSize = bgTexture.getSize();
    sf::Vector2u windowSize = window.getSize();
    //sf::Vector2u imageSize = bgTexture.getSize();
    float scaleX1 = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY1 = static_cast<float>(windowSize.y) / textureSize.y;
    float scale = std::min(scaleX1 , scaleY1);

    bgSprite.setScale(scale , scale);
    //bgSprite.setScale(static_cast<float>(window.getSize().x) / bgSprite.getTexture()->getSize().x , static_cast<float>(window.getSize().y) / bgSprite.getTexture()->getSize().y);
    sf::FloatRect spriteBounds = bgSprite.getGlobalBounds();
    float posX = (windowSize.x - spriteBounds.width) / 2.f;
    float posY = (windowSize.y - spriteBounds.height) / 2.f;
    bgSprite.setPosition(posX , posY);

    //map
    sf::Texture mapTexture;
    sf::Sprite mapSprite;

    if (!mapTexture.loadFromFile("../build/map.png"))
    {
        std::cerr << "Failed to load map image!\n";
        exit(-1);
    }
    mapSprite.setTexture(mapTexture);

    float scale2X = 800.f / textSize.x;
    float scale2Y = 800.f / textSize.y;
    float scale2 = std::min(scale2X , scale2Y);
    mapSprite.setScale(scale , scale);

    for (const auto& [locName, pos] : locations)
    {
        sf::RectangleShape hitbox(sf::Vector2f(20.f , 20.f));
        hitbox.setFillColor(sf::Color(255 , 0 , 0 , 150));
        hitbox.setPosition(pos.x , pos.y);
        locationHitboxes[locName] = hitbox;
    }



    //load Dracula image
    sf::Texture draculaTexture;
    if (!draculaTexture.loadFromFile("../build/Monsters/Dracula.png"))
    {
        std::cerr << "Failed to load Dracula image!\n";
        exit(-1);
    }

    sf::Sprite draculaSprite;
    draculaSprite.setTexture(draculaTexture);
    draculaSprite.setScale(0.1f , 0.1f);
    // draculaSprite.setPosition(locations["Crypt"]);
    auto it = locations.find("Crypt");
    if (it != locations.end())
    {
        draculaSprite.setPosition(sf::Vector2f(it->second.x , it->second.y));
    }

    //load Invisible Man image
    sf::Texture invisibleTexture;
    if (!invisibleTexture.loadFromFile("../build/Monsters/InvisibleMan.png"))
    {
        std::cerr << "Failed to load Invisible Man image!\n";
    }

    sf::Sprite invisibleSprite;
    invisibleSprite.setTexture(invisibleTexture);
    invisibleSprite.setScale(0.1f , 0.1f);

    auto it1 = locations.find("Inn");
    if (it1 != locations.end())
    {
        invisibleSprite.setPosition(sf::Vector2f(it1->second.x , it1->second.y));   
    }

    //start button
    sf::RectangleShape startButton(sf::Vector2f(200.f,60.f));
    startButton.setFillColor(sf::Color::Green);
    startButton.setPosition(300.f,500.f);

    //start text
    sf::Text startText("Start" , gameFont , 28);
    startText.setFillColor(sf::Color::White);
    startText.setPosition(startButton.getPosition().x + 40 , startButton.getPosition().y + 10);

    //exit button
    sf::RectangleShape exitButton(sf::Vector2f(200.f,60.f));
    exitButton.setFillColor(sf::Color::Red);
    exitButton.setPosition(300.f,580.f);

    //exit text
    sf::Text exitText("Exit" , gameFont , 28);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(exitButton.getPosition().x + 50 , exitButton.getPosition().y + 10);
    
    sf::RectangleShape nameBox(sf::Vector2f(400.f , 50.f));
    nameBox.setPosition(200.f , 200.f);
    nameBox.setFillColor(sf::Color::White);

    sf::Text nameLabel("enter your name :" , gameFont , 24);
    nameLabel.setPosition(200.f , 160.f);

    sf::Text nameText("" , gameFont , 22);
    nameText.setPosition(210.f , 210.f);
    nameText.setFillColor(sf::Color::Black);

    sf::RectangleShape timeBox(sf::Vector2f(400.f , 50.f));
    timeBox.setPosition(200.f , 300.f);
    timeBox.setFillColor(sf::Color(220 , 220 , 220));

    sf::Text timeLabel("last time you ate garlic :" , gameFont , 24);
    timeLabel.setPosition(200.f , 260.f);

    sf::Text timeText("" , gameFont , 22);
    timeText.setPosition(210.f , 310.f);
    timeText.setFillColor(sf::Color::Black);

    // 'continue' button
    sf::RectangleShape continueButton(sf::Vector2f(150.f , 50.f));
    continueButton.setPosition(320.f , 400.f);
    continueButton.setFillColor(sf::Color::Green);

    sf::Text continueText("continue" , gameFont , 22);
    continueText.setFillColor(sf::Color::White);
    continueText.setPosition(continueButton.getPosition().x + 20 , continueButton.getPosition().y + 10);

    //title text
    sf::Text titleText("" , gameFont , 28);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(250.f , 100.f);


    //main loop
    while (window.isOpen())
    {
        sf::Event event;
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        while (window.pollEvent(event))
        {
            //closing window
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            
            mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            if (event.type == sf::Event::TextEntered && showInputScreen)
            {
                char c = static_cast<char>(event.text.unicode);
                if (std::isprint(c))
                {
                    if (typingName)
                        nameInput += c;
                        else
                        timeInput += c;
                }
            }

            sf::FloatRect moveButtonRect(75.f , 120.f , 250.f , 40.f);
            sf::FloatRect pickUpButtonRect(75.f , 170.f , 250.f , 40.f);

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    sf::FloatRect moveButtonRect(75.f , 120.f , 250.f , 40.f);
                    sf::FloatRect pickUpButtonRect(75.f , 170.f , 250.f , 40.f);
                    if (moveButtonRect.contains(mousePos))
                    {
                        currentAction = ActionState::Move;
                        showLocationHighlights = true;
                    }else if (pickUpButtonRect.contains(mousePos))
                    {
                        currentAction = ActionState::Pickup;
                        std::cout << "PickUp action selected.\n";
                    }

                   if (!showInputScreen && !showHeroSelectionScreen)
                    {
                   if (startButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                   {
                    showInputScreen = true;
                   }
                    if (exitButton.getGlobalBounds().contains(mousePos))
                    {
                        window.close();
                    }
                }


                if (showInputScreen)
                {
                    if (nameBox.getGlobalBounds().contains(mousePos))
                    {
                        typingName = true;
                    }else if (timeBox.getGlobalBounds().contains(mousePos))
                    {
                        typingName = false;
                    }else if (continueButton.getGlobalBounds().contains(mousePos))
                    {
                        playerNames[currentPlayerIndex] = nameInput;
                        playerTimes[currentPlayerIndex] = timeInput;

                        nameInput.clear();
                        timeInput.clear();

                        currentPlayerIndex++;

                        if (currentPlayerIndex >= 2)
                        {
                            showInputScreen = false;
                            showHeroSelectionScreen = true;

                            currentHeroPlayer = 0;

                        }
                    }
                }
                //for hero screen
                if (showHeroSelectionScreen)
                {
                    for (size_t i = 0 ; i < heroButtons.size() ; i++)
                    {
                        if (heroButtons[i].getGlobalBounds().contains(mousePos))
                        {
                            selectedHeroes[currentHeroPlayer] = heroList[i];
                            std::cout << "player " << currentHeroPlayer + 1 << " selected : " << heroList[i] << "\n";

                            heroButtons.erase(heroButtons.begin() + i);
                            heroLabels.erase(heroLabels.begin() + i);
                            heroList.erase(heroList.begin() + i);

                            if (currentHeroPlayer == 0)
                            {
                                currentHeroPlayer = 1;
                                heroButtons.clear();
                                heroLabels.clear();
                            
                                //choose hero buttons
                                float startY = 200.f;
                                for (size_t i = 0 ; i < heroList.size() ; i++)
                                {
                                    sf::RectangleShape button(sf::Vector2f(250.f , 50.f));
                                    button.setFillColor(sf::Color(100,100,250));
                                    button.setPosition(275.f , startY + i * 70.f);
                                    heroButtons.push_back(button);

                                    sf::Text label(heroList[i] , gameFont , 22);
                                    label.setFillColor(sf::Color::White);
                                    label.setPosition(button.getPosition().x + 20 , button.getPosition().y + 10);
                                    heroLabels.push_back(label);
                                }                           
                            }else{
                                showHeroSelectionScreen = false;
                                gamePlayStarted = true;
                                showMapScreen = true;
                                std::cout << "both players selected their heroes.\n";
                                initHeroSpritesAfterSelection(selectedHeroes , mapSprite , locations , controller);

                                std::vector<PlayerInfo> playerInfos;
                                for (int i = 0 ; i < 2 ; i++)
                                {
                                    PlayerInfo info;
                                    info.name = playerNames[i];
                                    info.heroName = selectedHeroes[i];
                                    info.lastGarlicTime = controller.convertToTimePoint(playerTimes[i]);
                                    playerInfos.push_back(info);
                                }

                                controller.setupPlayers(playerInfos);
                                controller.setUpGame(window);
                                std::cout << "for debugging : hero starting locations :\n";
                                for (auto& kv : heroStartingLocations)
                                {
                                    std::cout << kv.first << "-> " << kv.second << "\n";
                                }
                                
                                heroButtons.clear();
                                heroLabels.clear();
                                heroList.clear();
                            }
                            break;
                        }
                    }
                }
               
                if (gamePlayStarted && showMapScreen)
                {
                    for (int i = 0 ; i < selectedHeroes.size() ; i++)
                    {

                        Hero* currentHero = controller.heroes.at(i);

                        controller.heroPhase(window , currentHero);

                        if (!window.isOpen()) break;
                    }
                }
            }

        if (showHeroSelectionScreen && heroButtons.empty())
        {
            float startY = 200.f;
            for (size_t i = 0 ; i < heroList.size() ; i++)
            {
                sf::RectangleShape button(sf::Vector2f(250.f , 50.f));
                button.setFillColor(sf::Color(100,100,250));
                button.setPosition(275.f , startY + i * 70.f);
                heroButtons.push_back(button);

                sf::Text label(heroList[i] , gameFont , 22);
                label.setFillColor(sf::Color::White);
                label.setPosition(button.getPosition().x + 20 , button.getPosition().y + 10);
                heroLabels.push_back(label);
            }
        }
    }
        //clearing the page with background color
        window.clear();

        if (showMapScreen)
        {
            window.draw(mapSprite);

            if (showLocationHighlights)
            {
                for (auto& kv : locationHighlights)
                {
                    window.draw(kv.second);
                }
            }
            map.printItems(window , mapSprite , locations , itemTextures);
            window.draw(draculaSprite);
            window.draw(invisibleSprite);

            auto heroLocs = controller.getHeroLocations();
            int index = 0;
            for (auto& kv : heroSprites)
            {
                const std::string& heroName = kv.first;
                sf::Sprite& sprite = kv.second;
                auto it = heroLocs.find(heroName);
                if (it != heroLocs.end() && locations.count(it->second))
                {
                    Position p = locations.at(it->second);
                    sf::Vector2f mpos = mapSprite.getPosition();
                    sf::Vector2f mscale = mapSprite.getScale();

                    float offsetX = (index % 2) * 25.f;
                    float offsetY = (index / 2) * 25.f;

                    std::cout << heroName << " position raw: " << p.x << "," << p.y << "\n";
                    std::cout << "scale: " << mscale.x << "," << mscale.y << "\n";

                    sprite.setPosition(mpos.x + (p.x * mscale.x) - sprite.getGlobalBounds().width / 2.f + offsetX , mpos.y + (p.y * mscale.y) - sprite.getGlobalBounds().height / 2.f + offsetY);
                    std::cout << heroName << " -> " << sprite.getPosition().x << "," << sprite.getPosition().y << "\n";

                    window.draw(sprite);
                }
                index++;
            }
    if (gamePlayStarted && showMapScreen)
    {
    renderActionMenu(window);

    if (this->typingMove)
    {
        sf::RectangleShape overlay({480.f , 300.f});
        overlay.setFillColor(sf::Color(30 , 30 , 30 , 230));
        overlay.setPosition(400.f , 200.f);
        window.draw(overlay);

        sf::Text title("Choose destination:" , font , 20);
        title.setFillColor(sf::Color::Yellow);
        title.setPosition(420.f , 220.f);
        window.draw(title);

        for (auto& [btn, txt] : moveButtons)
        {
            window.draw(btn);
            window.draw(txt);
        }
    }
    }
}
        else if (showHeroSelectionScreen)
        {
            sf::Text prompt("player " + std::to_string(currentHeroPlayer + 1) + " : Choose your hero" , font , 26);
            prompt.setPosition(200.f , 100.f);
            window.draw(prompt);

            for (auto& btn : heroButtons) window.draw(btn);
            for (auto& label : heroLabels) window.draw(label);
        }

        else if (showInputScreen)
        {
        // }else{
        window.draw(inputBgSprite);
        window.draw(nameBox);
        window.draw(nameLabel);
        nameText.setString(nameInput);
        window.draw(nameText);

        window.draw(timeBox);
        window.draw(timeLabel);
        timeText.setString(timeInput);
        window.draw(timeText);

        window.draw(continueButton);
        window.draw(continueText);
        }
        else if (!gamePlayStarted)
        {
            window.draw(bgSprite);
            window.draw(startButton);
            window.draw(startText);
            window.draw(exitButton);
            window.draw(exitText);

        }
        window.display();
    }
}
