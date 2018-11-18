#include "appcore.hpp"
#include <cmath>
#include <sstream>
#include "lamp.hpp"

std::vector<Lamp*> Lamp::lamps;

AppCore::AppCore()
{
    
};



void AppCore::run()
{
    sf::VideoMode screen(sf::VideoMode::getDesktopMode());

    sf::RenderWindow window(screen, "");
    window.setFramerateLimit(30);

    sf::Vector2u size = window.getSize();

    sf::Clock clock;
    float lastTime = 0;
    float lastPrintTime = 0;

    Model* figure = new Icosahedron();

    float aRot = 0.5f, bRot = 1.0f;

    float radius = 3.0f, height = 2.0f, time = 0.0f;

    sf::Vector3f camPos;
    sf::Vector3f target(0.0f, 0.0f, 0.0f);
    sf::Vector3f camUp (0.0f, 1.0f, 0.0f);

    Matrix4 matView;
    Matrix4 projection; 
    
    Lamp* lamp1 = new Lamp(sf::Vector3f(0.f, 0.0f, 1.5f), 10.f, sf::Color::Red);
    Lamp* lamp2 = new Lamp(sf::Vector3f(-1.5f, 0.f, 0.f), 10.f, sf::Color::Green);
    Lamp* lamp3 = new Lamp(sf::Vector3f(0.f, -1.50f, 0.f), 10.f, sf::Color::Blue);
    
    sf::Texture texture;
    sf::Sprite sprite(texture);
    

    sf::View view = window.getDefaultView();

    bool active = true;
    int lastDist   = 0;
    sf::Vector2i lastPoint1 = sf::Vector2i(0, 0);
    sf::Vector2i curPoint1 = sf::Vector2i(0, 0);
    sf::Vector2i curPoint2 = sf::Vector2i(0, 0);
    sf::Vector2i deltaCam = sf::Vector2i (0, 0);
    Lamp* curLamp;
    bool isResize = false;
    bool mouseActive = false;
    int resize = 0;

    while (window.isOpen())
    {
        sf::Event event;

        while (active ? window.pollEvent(event) : window.waitEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape)
                        window.close();
                    break;
                case sf::Event::Resized:
                    view.setSize(event.size.width, event.size.height);
                    view.setCenter(event.size.width/2, event.size.height/2);
                    window.setView(view);
                    active = true;
                    break;
                case sf::Event::LostFocus:
                    break;
                case sf::Event::GainedFocus:
                    break;
                
                // On Android MouseLeft/MouseEntered are (for now) triggered,
                // whenever the app loses or gains focus.
                case sf::Event::MouseLeft:
                    active = false;
                    mouseActive = false;
                    break;
                case sf::Event::MouseEntered:
                    active = true;
                    break;
                case sf::Event::MouseButtonPressed: {
                    if(!mouseActive) {
                        mouseActive = true;
                        lastPoint1 = sf::Mouse::getPosition(window);
                        curPoint1 = lastPoint1;
                    }
                    curLamp = Lamp::getLampByPoint(curPoint1);
                }
                    break;
                case sf::Event::TouchBegan:
                    if (event.touch.finger == 0 || event.type == sf::Event::MouseButtonPressed)
                    {
                        lastPoint1 = sf::Vector2i(event.touch.x, event.touch.y);
                        curPoint1 = lastPoint1;
                        Lamp* lamp = Lamp::getLampByPoint(curPoint1);
                    }
                    else if(event.touch.finger == 1)
                    {
                        isResize = true;
                        curPoint2 = sf::Vector2i(event.touch.x, event.touch.y);
                        lastDist = pow((curPoint2.x-curPoint1.x), 2) + pow(curPoint2.y-curPoint1.y, 2);
                    }
                    break;
                case sf::Event::MouseMoved:
                    if(mouseActive) {
                        curPoint1 = sf::Mouse::getPosition(window);
                        lastPoint1 = curPoint1;
                        if(curLamp) {
                            curLamp->setPosition(curPoint1);
                        } else {
                            deltaCam = curPoint1 - lastPoint1;
                        }
                    }
                    break;
                case sf::Event::MouseWheelMoved:
                    resize = -event.mouseWheel.delta * 5;
                    break;
                case sf::Event::TouchMoved:
                    if (event.touch.finger == 0)
                    {
                        curPoint1 = sf::Vector2i(event.touch.x, event.touch.y);
                        if(isResize)
                        {
                            int curDist = pow((curPoint2.x-curPoint1.x), 2) + pow(curPoint2.y-curPoint1.y, 2);
                            int resize = sqrt(lastDist) - sqrt(curDist);

                            lastDist = curDist;
                        } else {
                            
                            deltaCam = curPoint1 - lastPoint1;
                            lastPoint1 = curPoint1;

                        }
                    } else if (event.touch.finger == 1)
                    {
                        curPoint2 = sf::Vector2i(event.touch.x, event.touch.y);
                        int curDist = pow((curPoint2.x-curPoint1.x), 2) + pow(curPoint2.y-curPoint1.y, 2);
                        resize = sqrt(lastDist) - sqrt(curDist);

                        lastDist = curDist;
                    }
                    break;
                case sf::Event::TouchEnded:
                    
                    if(event.touch.finger == 0)
                    {

                    }
                    if(event.touch.finger == 1)
                    {
                        isResize = false;
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    mouseActive = false;
                    curLamp = nullptr;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { deltaCam += sf::Vector2i(2, 0); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { deltaCam += sf::Vector2i(-2, 0); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { deltaCam += sf::Vector2i(0, 2); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { deltaCam += sf::Vector2i(0, -2);}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0)) { Lamp::illuminationType = NoIllumination;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) { Lamp::illuminationType = LambertIllumination;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) { Lamp::illuminationType = GuroIllumination;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)) { Lamp::illuminationType = FongIllumination;}

        if (active)
        {
            float newArot = aRot + deltaCam.y / 30.0f;
            if (newArot <= -M_PI_2) {
                aRot = -M_PI_2 + 0.01f;
            } else if(newArot >= M_PI_2 ) {
                aRot = M_PI_2 - 0.01f;
            } else {
                aRot = newArot;
            }
            float newBrot = bRot + deltaCam.x / 30.0f;
            if(newBrot > 2*M_PI) {
                newBrot -= 2*M_PI;
            } else if(newBrot < 0) {
                newBrot += 2*M_PI;
            }
            bRot = newBrot;
            float newRad = radius + 0.02f * resize;
            if(newRad > 0.5f && newRad < 20.f) {
                radius = newRad;
            }
            resize = 0;
            float xCam = radius * cos(aRot) * cos(bRot);
            float yCam = radius * sin(aRot);
            float zCam = -radius * cos(aRot) * sin(bRot);
            camPos = sf::Vector3f(xCam, yCam, zCam);
            Lamp::camPos = camPos;
            //sf::Vector3f camUp (0.0f, 1.0f, 0.0f);
            matView.LookAt(camPos, target, camUp);
            float aspectRatio = static_cast<float>(size.x) / size.y;
            projection.Projection(Norm(camPos-target), aspectRatio);
            deltaCam = sf::Vector2i(0, 0);
            
            Matrix4 vp = projection * matView;
            
            drawImage(vp, figure, sprite, texture, size);

            float currentTime = clock.getElapsedTime().asSeconds();
            float fps = 1.f / (currentTime - lastTime);
            lastTime = currentTime;
            if(currentTime - lastPrintTime > 1.f) {
                printf("%g\n", fps);
                lastPrintTime = currentTime;
            }

            // sf::Text textFPS;
            // drawFPS(fps, textFPS);
            // textFPS.setPosition(size.x -50 , 0);//задаем позицию текста
            // window.draw(textFPS);

            window.draw(sprite);
            // window.draw(image);
            //window.draw(text);
            window.display();
        }
        else {
            sf::sleep(sf::milliseconds(100));
        }
    }
}

void AppCore::drawFPS(float fps, sf::Text& text)
{
    sf::Font font;
    if (!font.loadFromFile("sansation.ttf"))
        printf("no font found\n");
        
    text.setFont(font); // font is a sf::Font
    std::ostringstream ss;
    ss << fps;
    text.setString(ss.str());
    text.setCharacterSize(24); // in pixels, not points!
    text.setFillColor(sf::Color::Red);
    //text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    
}

void AppCore::drawImage(Matrix4& vp, Model* model, sf::Sprite& sprite, sf::Texture& texture, sf::Vector2u size)
{
    sf::Image image;
    image.create(size.x, size.y, sf::Color(15, 15, 15));
    static ZBuffer zbuffer(size.x, size.y);
    zbuffer.clear();
    model->render(vp, image, zbuffer);
    std::vector<Lamp*>::iterator it;
    std::vector<Lamp*>& lamps = Lamp::lamps;
    for(it = lamps.begin(); it != lamps.end(); it++)
        (*it)->render(vp, image, zbuffer);
    texture.loadFromImage(image);
    sprite.setTexture(texture, true);
    sprite.setPosition(size.x / 2, size.y / 2);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}

AppCore::~AppCore() {}