# Space game using c++/sfml

## idea of works
We have main components are:

 - player 
 - enemy


Player implement as circular shape:
 

    sf::CircleShape player(30);
    player.setFillColor(sf::Color::Green);
    player.setPosition(sf::Vector2f(screen.width/2,screen.height/4));
    player.setOutlineThickness(3);
    player.setOutlineColor(sf::Color::Blue);

  Enemy ship implement as ConvexShape:
  

    int numOfb=20;
    sf::ConvexShape c[numOfb];
    for(int i=0;i<numOfb;i++)
    {
    c[i].setPointCount(4);
    c[i].setFillColor(sf::Color::Red);
    c[i].setPoint(0,sf::Vector2f(100,100));
    c[i].setPoint(1,sf::Vector2f(200,0));
    c[i].setPoint(2,sf::Vector2f(0,0));
    c[i].setPoint(3,sf::Vector2f(100,0));
    c[i].setPosition(rang(ran)+screen.width,rang(ran));
    }

When player collides with enemy ship will lost, else than will win after 30 sec.

    for(int i=0;i<numOfb;i++)
    {
	    if(player.getGlobalBounds().intersects(c[i].getGlobalBounds()))
	    {
	    ifLoss=true;
	    player.setOutlineColor(sf::Color::Red);
	    }
    }

## build

for linux :
 1. `$ sudo apt-get install libsfml-dev`
 2. go to `app/src/main/jni/`
 3.  `$ g++ -c main.cpp`
 4. `$ g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system`
 5. `$ ./sfml-app`

for android:

 1. first should have:
     	 - android SDK [https://developer.android.com/studio]
    	 - android NDK [https://developer.android.com/ndk]
    	 - gradle [https://gradle.org/]
 2. build SFML for android [https://github.com/SFML/SFML/wiki/Tutorial%3A-Building-SFML-for-Android]
 3. go to root of project will see `local.properties` file open it in text editor, and change paths of SDK and NDK
 4. open CLI and type `gradle build` 
 5. plug your android phone using USB.
 6. also on root folder of project open CLI and type `gradle installDebug`
 7. you will see app install on your phone




## Flow of work
1-first run<br>
 <img width=200 src="https://github.com/MohammadTeeU/sfml-game/blob/master/screenshot/1.png"/>
<hr>
2-avoid enemy<br>
<img width=200 src="https://github.com/MohammadTeeU/sfml-game/blob/master/screenshot/2.png"/>
<hr>
3-win after 30 sec<br>
<img width=200 src="https://github.com/MohammadTeeU/sfml-game/blob/master/screenshot/5.png"/>
<hr>
4-collided enemy<br>
<img width=200 src="https://github.com/MohammadTeeU/sfml-game/blob/master/screenshot/3.png"/>
<hr>
5-game over<br>
<img width=200 src="https://github.com/MohammadTeeU/sfml-game/blob/master/screenshot/4.png"/>


