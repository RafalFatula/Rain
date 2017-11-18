// Rain.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include "SFML\Graphics.hpp"
#include "SFML\OpenGL.hpp"
#include <ctime>

const int ScreenX = 800;
const int ScreenY = 600;

int main()
{
	sf::RenderWindow window(sf::VideoMode(ScreenX, ScreenY), "Rainy it is", sf::Style::Default);
	window.setVerticalSyncEnabled(true);

	window.setActive(true);

	float spd = 5;																			//added speed of "droplets"
	std::vector<float> speed;																//container for speed based on the thickness
	std::vector<sf::RectangleShape> rectangles;												//container for "droplets"
	std::srand(std::time(0));
	for (int i = 0; i < 100; i++) {															//initializing 100 droplets
		rectangles.push_back(sf::RectangleShape(sf::Vector2f((rand()%15)/10.f+1,(rand()%500)/10.f+3)));					//adding new "rain droplet" betwen 1 and 2.5 thickness and 8 and 53 length
		rectangles[i].setPosition(sf::Vector2f(rand()%ScreenX,rand()%ScreenY));											//giving the droplet random coordinates on the screen(canvas), constants representing initial values
		speed.push_back((rectangles[i].getSize().x)*rectangles[i].getSize().x);											//setting the speed of droplet based on its thickness (larger is faster, to maintain perspective)
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {

				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::Resized:
					// adjust the viewport when the window is resized
					glViewport(0, 0, event.size.width, event.size.height);
					break;

				case sf::Event::KeyPressed:													//if any key is pressed
					if (event.key.code == sf::Keyboard::Right) {							//if right arrow is pressed
						rectangles.push_back(sf::RectangleShape(sf::Vector2f((rand() % 15) / 10.f + 1, (rand() % 500) / 10.f + 8)));				//adding new "rain droplet" betwen 1 and 2.5 thickness and 8 and 58 length
						rectangles[rectangles.size()-1].setPosition(sf::Vector2f(rand() % window.getSize().x, rand() % window.getSize().y));		//giving the droplet random coordinates on the screen (canvas)
						speed.push_back(rectangles[rectangles.size() - 1].getSize().x * rectangles[rectangles.size() - 1].getSize().x);				//setting the speed of droplet based on its thickness (larger is faster, to maintain perspective)
					}
					else if (event.key.code == sf::Keyboard::Left) {						//if left arrow is pressed
						if(rectangles.size()>0)												//deleting a droplet if there is any to delete
							rectangles.pop_back();
					}
					else if (event.key.code == sf::Keyboard::Up) {							//if up arrow is pressed
						spd++;																//increasing speed of all droplets
					}
					else if (event.key.code == sf::Keyboard::Down) {						//if down arrow is pressed
						if(spd > 0 )
							spd--;															//decreasing speed of all droplets
					}
					break;
			}
		}
		window.clear(sf::Color::Black);

		for (int i = 0; i < rectangles.size(); i++) {																				//moving droplets
			if (rectangles[i].getPosition().y <= ScreenY)																			//if on the screen
				rectangles[i].setPosition(rectangles[i].getPosition().x, rectangles[i].getPosition().y + speed[i] + spd);			//moving it downward and never to sides
			else {																													//if off the screen
				rectangles[i].setPosition(rectangles[i].getPosition().x, -40);														//moving it a little above the screen (so it doesnt appear out of nowhere)
			}
		}

		for (int i = 0; i < rectangles.size(); i++) {										//drawing droplets
			window.draw(rectangles[i]);
		}

		window.display();
	}


    return 0;
}

