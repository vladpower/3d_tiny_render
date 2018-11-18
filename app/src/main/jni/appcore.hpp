#ifndef appcore_hpp
#define appcore_hpp

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <chrono>
#include "figure.hpp"
#include "tools/matrix.hpp"

class AppCore {
private:    

public:
    AppCore();
    void run();
    void drawImage(Matrix4& vp, Model* model, sf::Sprite& sprite, sf::Texture& texture, sf::Vector2u size);
    void drawFPS(float fps, sf::Text& text);
    ~AppCore();
protected:

};

#endif //appcore_hpp