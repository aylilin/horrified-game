// #include <cstdlib>
// #include <ctime>

// #include "../include/game-controller.h"
// int main()
// {
//     srand(time(nullptr)); 
//     GameController game;
//     game.run();
// }
/*
#include <SFML/Graphics.hpp>
#include "GameView.h"
#include "locations.h"
#include "game-controller.h"

#include <iostream>
#include <sstream>
#include <iomanip>

int main()
{
    //building graphical window
    sf::RenderWindow window(sf::VideoMode(800,800) , "Horrified");

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

    //hero screen
    bool showHeroSelectionScreen = false;
    std::vector<std::string> heroList = {"Archaeologist" , "Mayor" , "Courier" , "Scientist"};
    std::vector<sf::RectangleShape> heroButtons;
    std::vector<sf::Text> heroLabels;
    bool gamePlayStarted = false;

    std::vector<std::string> selectedHeroes(2);
    int currentHeroPlayer;

    //hero selected
    std::map<std::string , sf::Texture> heroTextures;
    std::map<std::string , sf::Sprite> heroSprites;
    std::map<std::string , std::string> heroStartingLocations =
    {{"Archaeologist" , "Docks"} , {"Mayor" , "Theatre"} , {"Courier" , "Shop"} , {"Scientist" , "Institute"}};

    for (const auto& heroName : selectedHeroes)
    {
        if (heroName.empty()) continue;

        sf::Texture texture;
        if (!texture.loadFromFile("../build/Heroes/" + heroName + ".png"))
        {
            std::cerr << "Failed to load hero selected image!\n";
            continue;
        }
        heroTextures[heroName] = texture;

        sf::Sprite sprite;
        sprite.setTexture(heroTextures[heroName]);
        sprite.setScale(0.16f , 0.16f);

        auto it = heroStartingLocations.find(heroName);
        if (it != heroStartingLocations.end())
        {
            const std::string& locationKey = it->second;
            auto posIt = locations.find(locationKey);
            if (posIt != locations.end())
            {
                const Position& pos = posIt->second;
                sprite.setPosition(pos.x , pos.y);
            } else{
                std::cerr << "Location not found for : " << locationKey << "\n";
            }
        } else{
                std::cerr << "No starting location for hero : " << heroName << "\n";
            }

        heroSprites[heroName] = sprite;
    }

    //map screen
    bool showMapScreen = false;

    //display background1
    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("../build/Horrified.jpg"))
    {
        std::cerr << "Failed to load horrified image!\n";
        return -1;
    }

    //input background texture
    sf::Texture inputBgTexture;
    if (!inputBgTexture.loadFromFile("../build/DraculaBackground.jpg"))
    {
        std::cerr << "Failed to load input screen background!\n";
        return -1;
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

    //display font
    sf::Font font;
    if (!font.loadFromFile("../build/ManufacturingConsent-Regular.ttf"))
    {
        std::cerr << "Failed to load font.\n";
        return -1;
    }
    //map
    sf::Texture mapTexture;
    sf::Sprite mapSprite;

    if (!mapTexture.loadFromFile("../build/map.png"))
    {
        std::cerr << "Failed to load map image!\n";
        return -1;
    }
    mapSprite.setTexture(mapTexture);

    float scale2X = 800.f / textSize.x;
    float scale2Y = 800.f / textSize.y;
    float scale2 = std::min(scale2X , scale2Y);
    mapSprite.setScale(scale , scale);


    //load Dracula image
    sf::Texture draculaTexture;
    if (!draculaTexture.loadFromFile("../build/Monsters/Dracula.png"))
    {
        std::cerr << "Failed to load Dracula image!\n";
        return -1;
    }

    sf::Sprite draculaSprite;
    draculaSprite.setTexture(draculaTexture);
    draculaSprite.setScale(0.16f , 0.16f);
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
    invisibleSprite.setScale(0.16f , 0.16f);

    auto it1 = locations.find("Inn");
    if (it != locations.end())
    {
        invisibleSprite.setPosition(sf::Vector2f(it->second.x , it->second.y));
    }

    //load courier image
    sf::Texture courierTexture;
    if (!courierTexture.loadFromFile("../build/Heros/Courier.png"))
    {
        std::cerr << "Failed to load Courier image!\n";
    }

    sf::Sprite courierSprite;
    courierSprite.setTexture(courierTexture);
    courierSprite.setScale(0.16f , 0.16f);

    auto it2 = locations.find("Shop");
    if (it != locations.end())
    {
        courierSprite.setPosition(sf::Vector2f(it->second.x , it->second.y));
    }

    //load scientist image
    sf::Texture scientistTexture;
    if (!scientistTexture.loadFromFile("../build/Heros/Scientist.png"))
    {
        std::cerr << "Failed to load Scientist image!\n";
    }

    sf::Sprite scientistSprite;
    scientistSprite.setTexture(scientistTexture);
    scientistSprite.setScale(0.16f , 0.16f);

    auto it3 = locations.find("Institute");
    if (it != locations.end())
    {
        scientistSprite.setPosition(sf::Vector2f(it->second.x , it->second.y));
    }

    //load archaeologist image
    sf::Texture archaeologistTexture;
    if (!archaeologistTexture.loadFromFile("../build/Heros/Archaeologist.png"))
    {
        std::cerr << "Failed to load Archaeologist image!\n";
    }

    sf::Sprite archaeologistSprite;
    archaeologistSprite.setTexture(archaeologistTexture);
    archaeologistSprite.setScale(0.16f , 0.16f);

    auto it4 = locations.find("Docks");
    if (it != locations.end())
    {
        scientistSprite.setPosition(sf::Vector2f(it->second.x , it->second.y));
    }

    //load mayor image
    sf::Texture mayorTexture;
    if (!mayorTexture.loadFromFile("../build/Heros/Mayor.png"))
    {
        std::cerr << "Failed to load Mayor image!\n";
    }

    sf::Sprite mayorSprite;
    mayorSprite.setTexture(mayorTexture);
    mayorSprite.setScale(0.16f , 0.16f);

    auto it5 = locations.find("Theater");
    if (it != locations.end())
    {
        mayorSprite.setPosition(sf::Vector2f(it->second.x , it->second.y));
    }

    //start button
    sf::RectangleShape startButton(sf::Vector2f(200.f,60.f));
    startButton.setFillColor(sf::Color::Green);
    startButton.setPosition(300.f,500.f);

    //start text
    sf::Text startText("Start" , font , 28);
    startText.setFillColor(sf::Color::White);
    startText.setPosition(startButton.getPosition().x + 40 , startButton.getPosition().y + 10);

    //exit button
    sf::RectangleShape exitButton(sf::Vector2f(200.f,60.f));
    exitButton.setFillColor(sf::Color::Red);
    exitButton.setPosition(300.f,580.f);

    //exit text
    sf::Text exitText("Exit" , font , 28);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(exitButton.getPosition().x + 50 , exitButton.getPosition().y + 10);
    
    sf::RectangleShape nameBox(sf::Vector2f(400.f , 50.f));
    nameBox.setPosition(200.f , 200.f);
    nameBox.setFillColor(sf::Color::White);

    sf::Text nameLabel("enter your name :" , font , 24);
    nameLabel.setPosition(200.f , 160.f);

    sf::Text nameText("" , font , 22);
    nameText.setPosition(210.f , 210.f);
    nameText.setFillColor(sf::Color::Black);

    sf::RectangleShape timeBox(sf::Vector2f(400.f , 50.f));
    timeBox.setPosition(200.f , 300.f);
    timeBox.setFillColor(sf::Color(220 , 220 , 220));

    sf::Text timeLabel("last time you ate garlic :" , font , 24);
    timeLabel.setPosition(200.f , 260.f);

    sf::Text timeText("" , font , 22);
    timeText.setPosition(210.f , 310.f);
    timeText.setFillColor(sf::Color::Black);

    // 'continue' button
    sf::RectangleShape continueButton(sf::Vector2f(150.f , 50.f));
    continueButton.setPosition(320.f , 400.f);
    continueButton.setFillColor(sf::Color::Green);

    sf::Text continueText("continue" , font , 22);
    continueText.setFillColor(sf::Color::White);
    continueText.setPosition(continueButton.getPosition().x + 20 , continueButton.getPosition().y + 10);

    //title text
    sf::Text titleText("" , font , 28);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(250.f , 100.f);


    //main loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            //closing window
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

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

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
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


                // else {
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

                                    sf::Text label(heroList[i] , font , 22);
                                    label.setFillColor(sf::Color::White);
                                    label.setPosition(button.getPosition().x + 20 , button.getPosition().y + 10);
                                    heroLabels.push_back(label);
                                }                              
                            }else{
                                showHeroSelectionScreen = false;
                                gamePlayStarted = true;
                                showMapScreen = true;
                                std::cout << "both players selected their heroes.\n";
                                
                                heroButtons.clear();
                                heroLabels.clear();
                                heroList.clear();
                            }
                            break;
                        }
                    }
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

                sf::Text label(heroList[i] , font , 22);
                label.setFillColor(sf::Color::White);
                label.setPosition(button.getPosition().x + 20 , button.getPosition().y + 10);
                heroLabels.push_back(label);
            }
        }

        //clearing the page with background color
        window.clear();

        if (showMapScreen)
        {
            window.draw(mapSprite);

            window.draw(draculaSprite);
            window.draw(invisibleSprite);
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
        }else if (gamePlayStarted)
        {
            for (const auto& [name , sprite] : heroSprites)
            {
                window.draw(sprite);
            }
        }else{
            
        window.draw(bgSprite);
        window.draw(startButton);
        window.draw(startText);
        window.draw(exitButton);
        window.draw(exitText);

        }
        window.display();
    }
        
    return 0;
}
*/
#include "game.h"
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800,800) , "Horrified");
    
    Game game(window);

    game.startGame();
    
    return 0;
}