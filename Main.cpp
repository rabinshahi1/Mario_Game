#include <array>
#include <chrono>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Headers/Animation.hpp"
#include "Headers/Global.hpp"
#include "Headers/MapManager.hpp"
#include "Headers/Mushroom.hpp"
#include "Headers/Mario.hpp"
#include "Headers/Enemy.hpp"
#include "Headers/Goomba.hpp"
#include "Headers/Koopa.hpp"
#include "Headers/ConvertSketch.hpp"
#include "./Headers/AudioManager.h"
#include<iostream>

 
int main() {
	bool  showText = true;
  bool startIntro = true;
   bool gameStarted=false ;
   bool pauseGame=false;
   bool mDead=false;
   bool endPart=false;
   bool startClock=true;
   
  

  
    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(SCREEN_RESIZE * SCREEN_WIDTH, SCREEN_RESIZE * SCREEN_HEIGHT), "Super Mario Bros", sf::Style::Close);

    sf::Clock clk,deathAnimationClock;
    
    
    Mario mario;
    AudioManager audio;
    sf::Font fontOne,roboFont;
    // Load the background image for the loading screen
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("./Resources/Images/loading.jpg")) {
        std::cout << "Error loading image!" << std::endl;
        return -1;
    }
 

    // Create a sprite for the background image
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    // Scale the background image to fit the window
    
    sf::Vector2u imageSize = backgroundTexture.getSize();
    float scaleX = (float)(SCREEN_RESIZE * SCREEN_WIDTH) / imageSize.x;
    float scaleY = (float)(SCREEN_RESIZE * SCREEN_HEIGHT) / imageSize.y;
    backgroundSprite.setScale(scaleX, scaleY);

    // Load  font
 
    if (!fontOne.loadFromFile("./Resources/Fonts/Font.otf")) {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }
    if (!roboFont.loadFromFile("./Resources/Fonts/Robo.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }
    sf::Text endTextOne("Press (Enter) to restart",fontOne,30),endTextTwo("Press (Q) to Quit",fontOne,30),score("SCORE : 0",roboFont,40);
    
     
   

    // Create the text object
    sf::Text startText("Press (P) to Start", fontOne, 50);
  
	 sf::Text myScore("SCORE : 0" ,roboFont,30);
    myScore.setFillColor(sf::Color::Black);
  
    startText.setFillColor(sf::Color::Black);
    startText.setPosition(550, 470); // Position the text where you want

    // Variables for text animation
    sf::Clock tclk;
   
   

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed  || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))  window.close();

            // Start the game if "P" is pressed
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                audio.stopIntroSound();
                startIntro = false;
                gameStarted = true;
				
               
            }
            	
        }

        if (!gameStarted ) {
            // Animate the text: toggle visibility every 0.8 seconds
            if (tclk.getElapsedTime().asSeconds() > 0.8f) {
                showText = !showText;
                tclk.restart();
            }

            // Clear the window
            window.clear();

            // Draw the background image
            window.draw(backgroundSprite);

            // Draw the animated text if it's visible
            if (showText) {
                window.draw(startText);
            }

            // Play the intro sound in a loop until "P" is pressed
            if (startIntro) {
                audio.playIntroSound();
                clk.restart();
                startIntro = false;
            }
            if (clk.getElapsedTime().asSeconds() >= 12.5f) {
                audio.resetIntroSound();
                startIntro = true;
            }

            // Display the contents of the window
            window.display();
        } if(gameStarted ){

            // Game logic starts here after pressing "P"
            // The following is the main game logic
            unsigned char current_level = 0;
            unsigned short level_finish = 0;
           

            std::chrono::microseconds lag(0);
            std::chrono::steady_clock::time_point previous_time;

            std::vector<std::shared_ptr<Enemy>> enemies;
            sf::Color background_color = sf::Color(0, 219, 255);
            sf::View view(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

            MapManager map_manager;
          
          

            convert_sketch(current_level, level_finish, enemies, background_color, map_manager, mario);

            previous_time = std::chrono::steady_clock::now();

            while (1 == window.isOpen()) {
                std::chrono::microseconds delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time);

                lag += delta_time;
                previous_time += delta_time;
                // if(mario.marioStatus())
                // {
                //     endPart=true;
                //     break;
                // }
               

                while (FRAME_DURATION <= lag) {
                    unsigned view_x;

                    lag -= FRAME_DURATION;

                    while (1 == window.pollEvent(event)) {
                        switch (event.type) {
                            case sf::Event::Closed:
                                window.close();
                                break;
                            case sf::Event::KeyPressed:
                                if (event.key.code == sf::Keyboard::Enter) {
                                    if(endPart)
                                    {
                                        endPart=false;
                                      startClock=true;
                                    enemies.clear();
                                    mario.reset();
                                    audio.stopDeathSound();
                                    audio.resetDeathSound();
                                    mDead=false;
                                    mario.updateStatus();
                                    mario.setScore();
                                    convert_sketch(current_level, level_finish, enemies, background_color, map_manager, mario);
                                    }
                                }
                                if(event.key.code ==sf::Keyboard::Space)
                                {
                                  pauseGame=!pauseGame;
                                }
                                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                                {
                                    window.close();
                                }
                               
                                break;
                           
                        }
                    }
                    if(!pauseGame && !endPart)
                    {
                                if (CELL_SIZE * level_finish <= mario.get_x()) {
                        current_level++;
                        enemies.clear();
                        mario.reset();
                        convert_sketch(current_level, level_finish, enemies, background_color, map_manager, mario);
                    }

                    // Keeping Mario at the center of the view
                    view_x = std::clamp<int>(round(mario.get_x()) - 0.5f * (SCREEN_WIDTH - CELL_SIZE), 0, CELL_SIZE * map_manager.get_map_width() - SCREEN_WIDTH);

                    map_manager.update();
                    mario.update(view_x, map_manager);

                    for (unsigned short a = 0; a < enemies.size(); a++) {
                        enemies[a]->update(view_x, enemies, map_manager, mario);
                    }

                    for (unsigned short a = 0; a < enemies.size(); a++) {
                        if (1 == enemies[a]->get_dead(1)) {
                            enemies.erase(a + enemies.begin());
                            a--;
                        }
                    }
                      if(mario.getScore())
                    {
                      
                      myScore.setString("SCORE : "+std::to_string(mario.getScore()));
                    }
                    else{
                        myScore.setString("SCORE : 0");
                    }
                    

                    if (FRAME_DURATION > lag) {
                        view.reset(sf::FloatRect(view_x, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
                        window.setView(view);
                      
                        
                         
                           myScore.setPosition(view_x + 20, 1);
                          
                        window.clear(background_color);

                        map_manager.draw_map(1, sf::Color(0, 0, 85) == background_color, view_x, window);
                        mario.draw_mushrooms(view_x, window);
                        map_manager.draw_map(0, sf::Color(0, 0, 85) == background_color, view_x, window);

                        for (unsigned short a = 0; a < enemies.size(); a++) {
                            enemies[a]->draw(view_x, window);
                        }


                        mario.draw(window);
                        if(current_level==0)
                        {
                                window.draw(myScore);
                                
                        }
                        else{
                            myScore.setFillColor(sf::Color::White);
                          
                            window.draw(myScore);
                            
                        }
                       
                        
                        window.display();
                    }
                    if(mario.marioStatus() && !mDead)
                    
                    { 
                        mDead=true;
                      audio.playDeathSound();
                    }
                    if(mario.marioStatus() && startClock)
                    {
                         deathAnimationClock.restart();
                         startClock=false;
                         
                        
                    }
                    if(!startClock && (deathAnimationClock.getElapsedTime().asSeconds()>=3)) {
                      
                        endPart=true;
                        break;
                    }
                    }
                    if(endPart)
                    {
                        score.setPosition(view_x+40,10.0f);
                        endTextOne.setPosition(view_x+40,60.f);
                        endTextTwo.setPosition(view_x+40,90.f);
                        score.setString("SCORE : "+ std::to_string(mario.getScore()));
                        window.clear();
                        
                        window.draw(score);
                        window.draw(endTextOne);
                        window.draw(endTextTwo);
                        window.display();
                    }
                  

            
                 
                }
            }

        }
       
       
    }

    return 0;
}
