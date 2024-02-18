#include <SFML/Graphics.hpp>

const int WIDTH = 800;
const int HEIGHT = 450;

int main()
{

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "cocka", sf::Style::Default, settings);


    sf::CircleShape circle1(100.f);
    circle1.setFillColor(sf::Color::Green);
    circle1.setOutlineColor(sf::Color::Red);
    circle1.setOutlineThickness(5);
    circle1.setPosition(sf::Vector2f(WIDTH/2 - 100, HEIGHT/2 - 100));

    sf::RectangleShape rectangle1(sf::Vector2f(100.f, 200.f));
    rectangle1.setOrigin(50, 100);//aa
    rectangle1.setFillColor(sf::Color::Blue);
    rectangle1.setOutlineColor(sf::Color::Magenta);
    rectangle1.setOutlineThickness(2);
    rectangle1.setPosition(sf::Vector2f(200, 150));
    rectangle1.setRotation(45.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                window.close();
        }

        sf::Vertex vertex(sf::Vector2f(10.f, 50.f), sf::Color::Red, sf::Vector2f(100.f, 100.f));

        // create an array of 3 vertices that define a triangle primitive
        sf::VertexArray triangle(sf::Triangles, 3);

        // define the position of the triangle's points
        triangle[0].position = sf::Vector2f(250.f, 17.f);
        triangle[1].position = sf::Vector2f(500.f, 45.f);
        triangle[2].position = sf::Vector2f(500.f, 500.f);

        // define the color of the triangle's points
        triangle[0].color = sf::Color::Red;
        triangle[1].color = sf::Color::Magenta;
        triangle[2].color = sf::Color::Green;

        // clear the window
        window.clear();

        window.draw(circle1);
        window.draw(rectangle1);
        
        window.display();
    }

    return 0;
}