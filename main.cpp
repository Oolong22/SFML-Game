#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "cocka");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
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

        // draw the triangle
        window.draw(triangle);

        // display the window content
        window.display();
    }

    return 0;
}