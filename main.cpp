//#include<iostream>
#include<SFML/Graphics.hpp>
#include<random>
#include<iostream>

int main()
{
	sf::RenderWindow win(sf::VideoMode(200,200),"Game");
	win.setFramerateLimit(60);

	////back
	sf::Texture Background;
	Background.loadFromFile("backg.jpg");
	sf::RectangleShape backRend(sf::Vector2f(200,200));
	backRend.setTexture(&Background);

	///player
	sf::CircleShape player(5);
	player.setFillColor(sf::Color::Green);
	player.setOutlineThickness(2);
	player.setOutlineColor(sf::Color::Blue);

	/////make blocks
	   ///random of blocks
	std::random_device dev;
	std::mt19937 ran(dev());
	std::uniform_int_distribution<std::mt19937::result_type> rang(1,200);


	/////create text
	sf::Font font;
	font.loadFromFile("FreeMonoBoldOblique.ttf");

	sf::Text pWin;
	sf::Text pLoss;
	pWin.setFont(font);
	pWin.setString("you win :)");
	pWin.setPosition(sf::Vector2f(25,25));
	pWin.setFillColor(sf::Color::White);
	pWin.setFillColor(sf::Color::Green);
	pWin.setCharacterSize(25);

	pLoss.setFont(font);
	pLoss.setString("you loss :(");
	pLoss.setPosition(sf::Vector2f(25,25));
	pLoss.setFillColor(sf::Color::White);
	pLoss.setFillColor(sf::Color::Red);
	pLoss.setCharacterSize(25);

	sf::RectangleShape bOf(sf::Vector2f(200,50));
	bOf.setPosition(0,20);

	////
	bool ifLoss=false;

	///make time for end game
	sf::Time time;
	sf::Clock clock;






	int numOfb=20;
	sf::ConvexShape c[numOfb];
	for(int i=0;i<numOfb;i++)
	{
		c[i].setPointCount(4);
		c[i].setFillColor(sf::Color::Red);
		c[i].setPoint(0,sf::Vector2f(20,20));
		c[i].setPoint(1,sf::Vector2f(30,0));
		c[i].setPoint(2,sf::Vector2f(10,10));
		c[i].setPoint(3,sf::Vector2f(20,0));
		c[i].setPosition(rang(ran)+200,rang(ran));


	}



	///loop of window
	while(win.isOpen())
	{
		sf::Event event;///event of window
		while(win.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				win.close();
			///move player by keybord
			if(event.type == sf::Event::KeyPressed)
			{
				if(event.key.code == sf::Keyboard::Up)
					player.move(0,-5);
				if(event.key.code == sf::Keyboard::Down)
									player.move(0,5);

				if(event.key.code == sf::Keyboard::Left)
									player.move(-5,0);

				if(event.key.code == sf::Keyboard::Right)
									player.move(5,0);








			}


			//move by mouse
			else if(event.type ==sf::Event::MouseMoved)
			{
				player.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(win)));

			}

			///if cross over  blocks

	   for(int i=0;i<numOfb;i++)
	 		{
			if(player.getGlobalBounds().intersects(c[i].getGlobalBounds()))
					{
						ifLoss=true;
						player.setOutlineColor(sf::Color::Red);
					}



		   }


		}

		///move blocks
		for(int i=0;i<numOfb;i++)
		{
			if(c[i].getPosition().x>0)
				c[i].move(-1,0);
		}




		time=clock.getElapsedTime();
		std::cout<<time.asSeconds()<<std::endl;
		///clear
		win.clear();

		///draw objects

		win.draw(backRend);
		win.draw(player);
		if( !(time.asSeconds()>10))//wite for 30 sec for win
		{

		if(!ifLoss){
		for(int i=0;i<numOfb;i++)
		{
			if(c[i].getPosition().x>0)
			win.draw(c[i]);
			else
				c[i].setPosition(rang(ran)+200,rang(ran));

		}
		}else{
		win.draw(bOf);
		win.draw(pLoss);
		}
		}else if(!ifLoss){
			win.draw(bOf);
			win.draw(pWin);

		}

		//display objects
		win.display();


	}


	return 0;
}
