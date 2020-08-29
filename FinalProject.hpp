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



#pragma once
#include <iostream>
#include "FinalProject.hpp"
#include <SFML/Graphics.hpp>
#include "SFML/Window.hpp"
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

/***************************************************************************************************************************************
Namespace name:				Final Project;
Purpose:					This namespace contains 2 classes: Cards and Games
In parameters:				N/A
Out parameters:				N/A
Version:					1.0
Author:						Yucong Yin
******************************************************************************************************************************************/
namespace FinalProject {
	const string imageArray[10] = { "1.JPG","2.JPG" ,"3.JPG" ,"4.JPG" ,"5.JPG" ,"6.JPG" ,"7.JPG" ,"8.JPG" ,"9.JPG" ,"10.JPG" };
	

/***************************************************************************************************************************************
Class name:				    Cards;
Purpose:					This class is used to store the hidden image names of each cards
In parameters:				N/A
Out parameters:				N/A
Version:					1.2
Author:						Yucong Yin
******************************************************************************************************************************************/
	
	class Cards {
	public:
		string hidden;
		
		Cards(int i) {
			hidden = imageArray[i];
		}
	};


/***************************************************************************************************************************************
Class name:				    Game;
Purpose:					This class is used to implement all functionality of a card flipping game
In parameters:				N/A
Out parameters:				N/A
Version:					3.8
Author:						Yucong Yin
******************************************************************************************************************************************/

	class Game {



	public:
		typedef struct Coordinates {
			float x, y;
			Coordinates(double px, double py) {
				x = px;
				y = py;

			}

		}Coord;
		
		

		int flips ;
		int clicks;
		int clickflag[20] = {};
		int findflag[20] = {};
		int found;
		Sprite game;
		Texture gameT;
		Sprite quit;
		Texture quitT;
		SoundBuffer buffer;
		Sound sound;
		vector<Coord>coordinates;
		Sprite sprites[20];
		vector<Cards>cardsDeck;
		Sprite sprite;
		RenderWindow window;

		friend bool operator==(const Cards& card1, const Cards& card2);

/***************************************************************************************************************************************
Function name:				Game();
Purpose:					This is the non-parameter constructor of Game class, it reset all the flags and variables to their initial valus
                            and create a new window if a new instance is created.
In parameters:				N/A
Out parameters:				N/A
Version:					4.0
Author:						Yucong Yin
******************************************************************************************************************************************/

		Game() :window(sf::VideoMode(800, 800), "Hello World") {
			flips = 0;
			found = 0;
			clicks = 0;
			for (int i = 0; i < 20; i++) {
				clickflag[i] = 0;
				findflag[i] = 0;

			}
			
		}

/***************************************************************************************************************************************
Function name:				staging();
Purpose:					This function is the prepare function which is used to store all the position coordinates,
							shuffle the cards in random order.
In parameters:				N/A
Out parameters:				N/A
Version:					1.2
Author:						Yucong Yin
******************************************************************************************************************************************/

		void staging()
		{
			float px = 50;
			float py = 0;

			for (int y = 0; y < 2; y++)
				for (int x = 0; x < 10; x++)
					cardsDeck.push_back(Cards(x));
			random_shuffle(cardsDeck.begin(), cardsDeck.end());

			for (int a = 0; a < 5; a++)
			{
				for (int b = 0; b < 4; b++)
				{
					coordinates.push_back(Coordinates(px, py));
					px += 200.0;
				}
				px = 50.0;
				py += 100.0;
			}

		}//set position array,


/***************************************************************************************************************************************
Function name:				draw();
Purpose:					This function draws the window with cards pictures each time it is called. it decides whether to draw 
							the hidden images or not depending on the flags.
In parameters:				N/A
Out parameters:				N/A
Version:					2.0
Author:						Yucong Yin
******************************************************************************************************************************************/


		void draw()
		{

			Texture texture;
			for (int i = 0; i < 20; i++)
			{
				
				sprite.setPosition(coordinates[i].x, coordinates[i].y);
				sprites[i] = sprite;
				if (clickflag[i] == 1 || findflag[i] == 1)
				{
					if (findflag[i] == 1) {
						texture.loadFromFile("blank.JPG");
						sprite.setTexture(texture);
					}
					else {
						texture.loadFromFile(cardsDeck[i].hidden);
						sprite.setTexture(texture);
					}
				}
				else {
					texture.loadFromFile("default.JPG");
					sprite.setTexture(texture);
				}
				window.draw(sprite);

			}//layout all sprites;
			


		}


/***************************************************************************************************************************************
		Function name:				compare();
		Purpose:					This function is called when 2 cards are clicked at the same time, it compares 2 cards by their hidden
									image, and set the flags depending on the compare result.
		In parameters:				N/A
		Out parameters:				N/A
		Version:					1.2
		Author:						Yucong Yin
******************************************************************************************************************************************/
		void compare(int i)
		{
			flips = 0;

			int soundflag = 0;
			for (int a = 0; a < 20; a++)
			{
				// check if the two cards are the same
				if (clickflag[a] == 1 && a != i)
				{
					if (cardsDeck[i] == cardsDeck[a]) {
						findflag[i] = 1;
						findflag[a] = 1;
						found++;
						soundflag = 1;
					}

					else {
						clickflag[i] = 0;
						clickflag[a] = 0;
					}
				}
				else if (clickflag[a] == 1 && a == i) {
					clickflag[i] = 0;
					clickflag[a] = 0;


				}

			}//end of for loop

			if (!soundflag) {
				if (!buffer.loadFromFile("sad.wav"))
					printf("Unable to load sound resource!");

				sound.setBuffer(buffer);

				sound.play();
				

			}
			else
			{
				if (!buffer.loadFromFile("nice.wav"))
					printf("Unable to load sound resource!");

				sound.setBuffer(buffer);

				sound.play();
				
			}



		}//use to set flags;
		
/***************************************************************************************************************************************
Function name:				isClicked();
Purpose:					This function get the position of all cards and decide if the mouse is in the range of each card
							if a card is clicked, the hidden image should be shown
In parameters:				N/A
Out parameters:				N/A
Version:					2.0
Author:						Yucong Yin
******************************************************************************************************************************************/
		void isClicked() {
			Vector2i localPosition = sf::Mouse::getPosition(window);
			Vector2f floatPosition(localPosition.x, localPosition.y);
			Texture texture;
			
			for (int i = 0; i < 20; i++) {
				
				if (sprites[i].getGlobalBounds().contains(floatPosition))
				{
					
					sprite.setPosition(coordinates[i].x, coordinates[i].y);
					texture.loadFromFile(cardsDeck[i].hidden);
					sprite.setTexture(texture);
					clickflag[i] = 1;
					window.draw(sprite);
					flips++;
					clicks++;
					// if 2 cards are selected
					if (flips == 2)
					{
						window.clear();
						draw();
						
						
						window.display();
						//pause for 3 sec
						sleep(milliseconds(3000));
						compare(i);
					}
					
					break;
				}




			}






		}//function to perform after sprite is clicked

/***************************************************************************************************************************************
Function name:				congrats();
Purpose:					This function is used to show the ending stage after all cards are removed, it shows a 
							congratulation sign, a txt label which tells you the score, a re-match button and a quit button
In parameters:				N/A
Out parameters:				N/A
Version:					3.3
Author:						Yucong Yin
******************************************************************************************************************************************/
		void congrats()
		{
			Text clicktxt;
			Sprite win;
			Texture winT;
			string text;
			text = "It takes you " + clicks;
			text += " times to finish the game! ";
			//window.clear();
			//win.setScale(Vector2f(50,50));
			win.setPosition(50,50);
			winT.loadFromFile("congrats.JPG");
			win.setTexture(winT);
			game.setPosition(50, 200);
			gameT.loadFromFile("new.JPG");
			game.setTexture(gameT);
			window.draw(game);
			quit.setPosition(200, 200);
			quitT.loadFromFile("quit.JPG");
			quit.setTexture(quitT);
			window.draw(quit);
			clicktxt.setString(text);
			clicktxt.setFillColor(Color::White);
			clicktxt.setPosition(Vector2f(50, 300));
			window.draw(win);
			window.draw(clicktxt);
			window.display();
			

			
			
		}

/***************************************************************************************************************************************
Function name:				doAgain();
Purpose:					This function is used to check if the re-match button is pressed
In parameters:				N/A
Out parameters:				return 1 if the button is pressed, 0 if not.
Version:					1.2
Author:						Yucong Yin
******************************************************************************************************************************************/
		int doAgain() {
			
			Vector2i localPosition = sf::Mouse::getPosition(window);
			Vector2f floatPosition(localPosition.x, localPosition.y);
			
			
			if (game.getGlobalBounds().contains(floatPosition))
				return 1;
			else
				return 0;

			sleep(milliseconds(5000));
		}
/***************************************************************************************************************************************
Function name:				quitG();
Purpose:					This function is used to check if the quit button is pressed
In parameters:				N/A
Out parameters:				return 1 if the button is pressed, 0 if not.
Version:					1.2
Author:						Yucong Yin
******************************************************************************************************************************************/
		int quitG() {

			Vector2i localPosition = sf::Mouse::getPosition(window);
			Vector2f floatPosition(localPosition.x, localPosition.y);


			if (quit.getGlobalBounds().contains(floatPosition))
				return 1;
			else
				return 0;


			
		}

	};
	/***************************************************************************************************************************************
	Function name:				operator==();
	Purpose:					overloading operator ==
	In parameters:				instance of Cards objects
	Out parameters:				return 1 if the 2 cards are the same, 0 if not.
	Version:					1.0
	Author:						Yucong Yin
	******************************************************************************************************************************************/
	bool operator==(const Cards& card1, const Cards& card2) {

		if (card1.hidden != card2.hidden)
			return 0;
		else
			return 1;
	}


	};




