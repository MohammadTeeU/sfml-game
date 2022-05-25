#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include<random>
#include<iostream>
#include <SFML/Window/Touch.hpp>
// Do we want to showcase direct JNI/NDK interaction?
// Undefine this to get real cross-platform code.
// Uncomment this to try JNI access; this seems to be broken in latest NDKs
//#define USE_JNI

#if defined(USE_JNI)
// These headers are only needed for direct NDK/JDK interaction
#include <jni.h>
#include <android/native_activity.h>

// Since we want to get the native activity from SFML, we'll have to use an
// extra header here:
#include <SFML/System/NativeActivity.hpp>

// NDK/JNI sub example - call Java code from native code
int vibrate(sf::Time duration)
{
    // First we'll need the native activity handle
    ANativeActivity *activity = sf::getNativeActivity();
    
    // Retrieve the JVM and JNI environment
    JavaVM* vm = activity->vm;
    JNIEnv* env = activity->env;

    // First, attach this thread to the main thread
    JavaVMAttachArgs attachargs;
    attachargs.version = JNI_VERSION_1_6;
    attachargs.name = "NativeThread";
    attachargs.group = NULL;
    jint res = vm->AttachCurrentThread(&env, &attachargs);

    if (res == JNI_ERR)
        return EXIT_FAILURE;

    // Retrieve class information
    jclass natact = env->FindClass("android/app/NativeActivity");
    jclass context = env->FindClass("android/content/Context");
    
    // Get the value of a constant
    jfieldID fid = env->GetStaticFieldID(context, "VIBRATOR_SERVICE", "Ljava/lang/String;");
    jobject svcstr = env->GetStaticObjectField(context, fid);
    
    // Get the method 'getSystemService' and call it
    jmethodID getss = env->GetMethodID(natact, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
    jobject vib_obj = env->CallObjectMethod(activity->clazz, getss, svcstr);
    
    // Get the object's class and retrieve the member name
    jclass vib_cls = env->GetObjectClass(vib_obj);
    jmethodID vibrate = env->GetMethodID(vib_cls, "vibrate", "(J)V"); 
    
    // Determine the timeframe
    jlong length = duration.asMilliseconds();
    
    // Bzzz!
    env->CallVoidMethod(vib_obj, vibrate, length);

    // Free references
    env->DeleteLocalRef(vib_obj);
    env->DeleteLocalRef(vib_cls);
    env->DeleteLocalRef(svcstr);
    env->DeleteLocalRef(context);
    env->DeleteLocalRef(natact);
    
    // Detach thread again
    vm->DetachCurrentThread();
}
#endif

// This is the actual Android example. You don't have to write any platform
// specific code, unless you want to use things not directly exposed.
// ('vibrate()' in this example; undefine 'USE_JNI' above to disable it)
int main(int argc, char *argv[])
{
    sf::VideoMode screen(sf::VideoMode::getDesktopMode());

    sf::RenderWindow win(screen, "");
    win.setFramerateLimit(30);

    ////back
    sf::Texture Background;
    Background.loadFromFile("backg.jpg");
    sf::RectangleShape backRend(sf::Vector2f(screen.width,screen.height));
    backRend.setTexture(&Background);

    ///player
    sf::CircleShape player(30);
    player.setFillColor(sf::Color::Green);
    player.setPosition(sf::Vector2f(screen.width/2,screen.height/4));
    player.setOutlineThickness(3);
    player.setOutlineColor(sf::Color::Blue);

    /////make blocks
       ///random of blocks
    std::random_device dev;
    std::mt19937 ran(dev());
    std::uniform_int_distribution<std::mt19937::result_type> rang(1,screen.height);


    /////create text
    sf::Font font;
    font.loadFromFile("FreeMonoBoldOblique.ttf");

    sf::Text pWin;
    sf::Text pLoss;
    sf::Text counter;
    sf::Text sText;

    sText.setFont(font);
    sText.setString("Try to avoid enemy ships!!");
    sText.setPosition(sf::Vector2f(screen.width/4,screen.height/2));
    sText.setFillColor(sf::Color::Green);
    sText.setCharacterSize(50);

    pWin.setFont(font);
    pWin.setString("you win :)");
    pWin.setPosition(sf::Vector2f(screen.width/4,screen.height/2));
    pWin.setFillColor(sf::Color::White);
    pWin.setFillColor(sf::Color::Green);
    pWin.setCharacterSize(100);

    pLoss.setFont(font);
    pLoss.setString("game over:(");
    pLoss.setPosition(sf::Vector2f(screen.width/4,(screen.height/2)));
    pLoss.setFillColor(sf::Color::White);
    pLoss.setFillColor(sf::Color::Red);
    pLoss.setCharacterSize(100);

    counter.setFont(font);
    counter.setString("0");
    counter.setPosition(sf::Vector2f(0,screen.height-300));
    counter.setFillColor(sf::Color::White);
    counter.setFillColor(sf::Color::Red);
    counter.setCharacterSize(100);


    sf::RectangleShape bOf(sf::Vector2f(screen.width,200));
    bOf.setPosition(0,screen.height/2);

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
        c[i].setPoint(0,sf::Vector2f(100,100));
        c[i].setPoint(1,sf::Vector2f(200,0));
        c[i].setPoint(2,sf::Vector2f(0,0));
        c[i].setPoint(3,sf::Vector2f(100,0));
        c[i].setPosition(rang(ran)+screen.width,rang(ran));


    }



    ///loop of window
    while(win.isOpen())
    {
        int downcount=30;

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
            else if(sf::Touch::isDown(0))
            {

                sf::Vector2f pos  = static_cast<sf::Vector2f>(sf::Touch::getPosition(0, win));
                pos.y-=500.0;
                player.setPosition(pos);

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
                c[i].move(-3,0);
        }




        time=clock.getElapsedTime();
        std::cout<<time.asSeconds()<<std::endl;
        downcount -=int(time.asSeconds());
        counter.setString(std::to_string(downcount));
        ///clear
        win.clear();

        ///draw objects

        win.draw(backRend);
        win.draw(player);
        

        if (time.asSeconds()<2)
        {
            win.draw(sText);
        }
        if( (downcount != 0 and downcount >0))//wite for 30 sec for win
        {
            
        if(!ifLoss){
            win.draw(counter);
        for(int i=0;i<numOfb;i++)
        {
            if(c[i].getPosition().x>0)
            win.draw(c[i]);
            else
                c[i].setPosition(rang(ran)+500,rang(ran));

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
