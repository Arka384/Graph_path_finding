#include "Visualization.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <list>

constexpr int windowSizeX = 600;
//Visualization vs;
sf::Clock cl;
sf::Time dt;
float mx, my;

//std::list<int> coords;
//std::list<sf::CircleShape> circles;
//sf::Image map;
//sf::Texture mapTex;
//sf::Sprite mapSprite;
//bool mousePressed = false;
//void readCoordsFromFile(void);

Visualization vs;


int main()
{
	sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeX), "Maze Solver", sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	

	float t = 0;
	int state = 0;
	sf::Vector2i mousePos;
	vs.init();


	//for (int i = 0; i < vertex; i++)
	//{
	//	for (int j = 0; j < vertex; j++)
	//		std::cout << adj_matrix[i][j]<<" ";
	//	std::cout << std::endl;
	//}	

	while (window.isOpen())
	{
		//dt = cl.restart();
		//t += dt.asSeconds();

		sf::Event e;
		while (window.pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed:
				window.close();
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					if (state == 0) {
						vs.create_adj_mat();
						state = 1;
					}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
					vs.init();
					state = 0;
				}
				break;
			default:
				break;
			}
		}

		///////////////////////
		mousePos = sf::Mouse::getPosition(window);

		//states updating
		if (state == 0)
			vs.mouse_update(mousePos);
		if (state == 1) {
			vs.bfs();
			//	vs.dfs();
			state = 2;
		}
		if (state == 2) {
			int length = vs.get_path();
			for (int k = 0; k < length; k++)
				for (int i = 0; i < max; i++)
					for (int j = 0; j < max; j++)
						if (vs.matrix[i][j].vertex == vs.path[k] && vs.path[k] != vs.source && vs.path[k] != vs.des)
							vs.matrix[i][j].box.setFillColor(sf::Color::Yellow);
		}

		/////////////////////////

		window.clear();

		for (int i = 0; i < max; i++)
			for (int j = 0; j < max; j++)
				if (vs.matrix[i][j].box.getFillColor() != sf::Color::Yellow)
					window.draw(vs.matrix[i][j].box);

		window.draw(vs.spriteMap);

		for (int i = 0; i < max; i++)
			for (int j = 0; j < max; j++)
				if (vs.matrix[i][j].box.getFillColor() == sf::Color::Yellow)
					window.draw(vs.matrix[i][j].box);

		window.display();
	}

	return 0;
}


//void readCoordsFromFile(void)
//{
//	std::ifstream input("coords.txt");
//	int number = 0;
//	while (input >> number) {
//		coords.push_back(number);
//	}
//
//	/*for (auto i = coords.begin(); i != coords.end(); i++) {
//		std::cout << *i << " ";
//	}*/
//}



///////////////////////////////////////////////////////////////
/*
	readCoordsFromFile();

	//setting up circles
	sf::CircleShape c;
	//auto i = coords.begin();
	std::list<int>::iterator i = coords.begin();
	while(i != coords.end()){
		c.setFillColor(sf::Color::Red);
		c.setRadius(20);
		float x = *i;
		i++;
		float y = *i;
		c.setPosition(x, y);
		circles.push_back(c);
		i++;
	}
	*/

	/*
	//this is an approach where I use the coordinates to chage the color of pixels in the map image. .png file
	//creating the image map
	map.create(windowSizeX, windowSizeX, sf::Color::Black);
	for (auto k = circles.begin(); k != circles.end(); k++) {
		unsigned int nPosX = k->getPosition().x;
		unsigned int nPosY = k->getPosition().y;
		//std::cout << nPosX << " " << nPosY << "\n";

		map.setPixel(nPosX, nPosY, sf::Color::Red);
		map.setPixel(nPosX + 2, nPosY, sf::Color::Red);
		map.setPixel(nPosX - 2, nPosY, sf::Color::Red);
		map.setPixel(nPosX, nPosY + 2, sf::Color::Red);
		map.setPixel(nPosX, nPosY - 2, sf::Color::Red);

	}
	*/

	//there can be one more approach
	//here I draw the circles and then I take a screen shot and save it as map.png image file.



	/*
	while (window.isOpen())
	{
		//dt = cl.restart();
		//t += dt.asSeconds();
		sf::Event e;
		while (window.pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed:
				window.close();
			case sf::Event::MouseButtonPressed:
				mousePressed = true;
				break;
			case sf::Event::MouseButtonReleased:
				mousePressed = false;
				break;
			default:
				break;
			}
		}

		//these are requried for first approach
		//mapTex.loadFromImage(map);
		//mapSprite.setTexture(mapTex);


		//screen shot for second approach
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			sf::Texture texture;
			texture.create(window.getSize().x, window.getSize().y);
			texture.update(window);

			if (texture.copyToImage().saveToFile("Images/ss_map.png")) {
				//std::cout << "Drawing saved in 'Drawings' folder at " << x << " seconds\n\n";
				std::cout << "saved";
			}
		}



		window.clear();
		for (auto k = circles.begin(); k != circles.end(); k++) {
			window.draw(*k);
		}
		if (mousePressed)
			window.draw(mapSprite);
		window.display();

	} */

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////









///////////////////////////////////////////
/////////////////////////////////////////////

/*
	
	*/

