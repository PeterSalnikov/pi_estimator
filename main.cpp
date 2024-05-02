#include<iostream>
#include<random>
#include<cmath>
#include<SFML/Graphics.hpp>

sf::RectangleShape createDot(sf::Vector2f coords)
{
    sf::RectangleShape shape(sf::Vector2f(1.f,1.f));
    shape.setFillColor(sf::Color::White);
    shape.setPosition(coords);

    return shape;
}

int main()
{
    int num_iterations = 750000;
    int dim = 1000;
    double rad = static_cast<double>(dim)/2.f;
    sf::Color color;

    int count = 0;
    int inside = 0;

    double pi_result;

    sf::RenderWindow window(sf::VideoMode(dim, dim + 150), "Pi Estimator", sf::Style::Default);
    window.setFramerateLimit(144);

    std::vector<sf::RectangleShape> dots;

    sf::Font font;
    if (!font.loadFromFile("/Library/Fonts/Arial Unicode.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        return -1;
    }

    sf::Text pi_result_text;
    pi_result_text.setFont(font);
    pi_result_text.setCharacterSize(50);
    pi_result_text.setPosition(10.f,dim + 50.f);
    pi_result_text.setFillColor(sf::Color::White);

    std::mt19937_64 mtX(0);
    std::uniform_real_distribution<double> distX(0.f,1.f);

    std::mt19937_64 mtY(1);
    std::uniform_real_distribution<double> distY(0.f,1.f);

    sf::CircleShape radius(rad);
    radius.setFillColor(sf::Color(0,0,0,0));
    radius.setOutlineThickness(1);
    radius.setOutlineColor(sf::Color::White);

    sf::RectangleShape temp;

    std::vector<double> pi_intermediates;

    while(count < num_iterations) {
        double x = distX(mtX);
        double y = distY(mtY);

        if(std::hypot(x-0.5f,y-0.5f) < 0.5f) {
            inside++;
            color = sf::Color::Green;
        }
        else
        {
            color = sf::Color::Red;
        }

            temp = createDot(sf::Vector2f(x*dim,y*dim));
            temp.setFillColor(color);

        count++;
        dots.push_back(temp);
        pi_result = (static_cast<double>(4*inside) / static_cast<double>(count));

        pi_intermediates.push_back(pi_result);
    }

    std::cout << "Final result: " << pi_intermediates[num_iterations-1] << std::endl;

    int pi_count = 0;

    while(window.isOpen() && pi_count < num_iterations) {

        sf::Event event;

        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }
        window.clear(sf::Color::Black);

        window.draw(radius);

        for(int i = 0; i < pi_count; i++) {
            window.draw(dots[i]);
        }

            if(pi_count % 50 == 0)
            {
                pi_result_text.setString(std::to_string(pi_intermediates[pi_count]) + " points sampled: " + std::to_string(pi_count));
            }
            window.draw(pi_result_text);

            window.display();
            pi_count++;
    }

    return 0;
}