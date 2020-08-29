/*****************************************************************************************************************************************
Student Name:				Yucong Yin
Student Number:				040792791
Assignment number:			Final Project
Course:						20S_CST8219 C++Programming
Lab section:				303
Professor:					Eric Torunski, Mariusz Makos
Due date:					2020-AUG-7th
Purpose:					you will create a memory game using various shapes. The user interface should show 20 cards, in 5 rows and 4 columns. 
The user can click on a card and see what is on the other side.
*****************************************************************************************************************************************/




#include "FinalProject.hpp"
#include <SFML/Graphics.hpp>
#include "SFML/Window.hpp"
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;
using namespace FinalProject;

Event event;
SoundBuffer buffer;
Sound sound;


/***************************************************************************************************************************************
Function name:				main();
Purpose:					make instance of the classes, call functions to make the window and perform the game
In parameters:				Command Line arguments
Out parameters:				return 0 if exit successfully.
Version:					1.0
Author:						Yucong Yin
******************************************************************************************************************************************/
int main(int argc, char** argv) {
    int startflag = 0;

    do {
        startflag = 0;
        Game game;
        game.staging();

        while (game.window.isOpen())
        {
            game.window.clear();
            game.draw();
            game.window.display();
            
                if (game.found == 10) {

                    game.window.clear();
                    
                        if (!buffer.loadFromFile("cheer.wav"))
                            printf("Unable to load sound resource!");

                        sound.setBuffer(buffer);

                        sound.play();
                    while (1) {
                        game.congrats();
                        while (game.window.pollEvent(event)) {
                            if (event.type == sf::Event::MouseButtonPressed &&
                                event.mouseButton.button == Mouse::Left){
                                startflag = game.doAgain();
                                if (game.quitG()) {
                                    game.window.close();
                                    startflag = 0;
                                    exit(0);
                                }
                            }
                        }
                        if (startflag == 1)
                            break;
                    }

                }



            while (game.window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    game.window.close();

                else if (event.type == sf::Event::MouseButtonPressed &&
                    event.mouseButton.button == Mouse::Left)
                    game.isClicked();

            }
            if (startflag == 1)
                game.window.close();
        }
        
    } while (startflag == 1);
    return 0;
}
