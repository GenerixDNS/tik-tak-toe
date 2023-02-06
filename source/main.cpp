#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>

constexpr unsigned int interface_xy = 600;
constexpr unsigned int map_size = 8;

template<class T>
void print(T msg) { std::cout << msg << std::endl; }

enum class Position
{
    P0_0, P0_1, P0_2,
    P1_0, P1_1, P1_2,
    P2_0, P2_1, P2_2,
};

enum class Party
{
    RECTANGLE,
    CIRCLE,
};

template<class F, class S>
struct FS
{
    F first;
    S second;
};

FS<Party, unsigned int[2]>* map_register = new FS<Party, unsigned int[2]>[map_size];

void handle_boot();

void handle_draw(sf::RenderWindow& window);

class Game
{
private:
    Party m_turn;
    sf::Color m_bg_color;

public:
    Game() : m_bg_color(sf::Color::White)
    {
        std::random_device device;
        std::mt19937 engine(device());
        auto generator = std::uniform_int_distribution<std::mt19937::result_type>(0, 1);
        int r = generator(engine);
        this->m_turn = r == 0 ? Party::CIRCLE : Party::RECTANGLE;
    }

    sf::Color& color()
    {
        return this->m_bg_color;
    }

    void color(sf::Color color)
    {
        this->m_bg_color = color;
    }

    Party& turn()
    {
        return this->m_turn;
    }

    void turn(Party party)
    {
        this->m_turn = party;
    }

};

void handle_event(sf::Event& event, sf::RenderWindow& window, Game& game);

void on_click(int& x, int& y, Game& game);

void on_position_click(Position position, Game& game);

void on_turn(Game& game);

int main()
{

    Game game{};
    switch (game.turn()) {
        case Party::RECTANGLE:
            on_turn(game);
            break;
        case Party::CIRCLE:
            on_turn(game);
            break;
    }
    sf::RenderWindow window(sf::VideoMode(interface_xy, interface_xy), "demo", sf::Style::Close);
    handle_boot();

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            handle_event(event, window, game);
        }

        window.clear(game.color());
        handle_draw(window);
        window.display();
    }

    return 0;
}

void handle_boot()
{
    for (int i = 0; i == map_size; ++i)
    {

    }
}

void handle_event(sf::Event& event, sf::RenderWindow& window, Game& game)
{
    switch (event.type) {
        case sf::Event::Closed:
            window.close();
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Button::Left)
            {
                on_click(event.mouseButton.x, event.mouseButton.y, game);
            }
            break;
        default:
            break;
    }
}

void on_click(int& x, int& y, Game& game)
{
    if (x < interface_xy / 3)
    {
        if (y < interface_xy / 3)
        {
            on_position_click(Position::P0_0, game);
        } else if (y < interface_xy / 2)
        {
            on_position_click(Position::P0_1, game);
        } else if (y < interface_xy / 1)
        {
            on_position_click(Position::P0_2, game);
        }
    } else if (x < interface_xy / 2)
    {
        if (y < interface_xy / 3)
        {
            on_position_click(Position::P1_0, game);
        } else if (y < interface_xy / 2)
        {
            on_position_click(Position::P1_1, game);
        } else if (y < interface_xy / 1)
        {
            on_position_click(Position::P1_2, game);
        }
    } else if (x < interface_xy / 1)
    {
        if (y < interface_xy / 3)
        {
            on_position_click(Position::P2_0, game);
        } else if (y < interface_xy / 2)
        {
            on_position_click(Position::P2_1, game);
        } else if (y < interface_xy / 1)
        {
            on_position_click(Position::P2_2, game);
        }
    }
}

void on_position_click(Position position, Game& game)
{
    switch (position) {

        case Position::P0_0:
            print("P0_0");
            break;
        case Position::P0_1:
            print("P0_1");
            break;
        case Position::P0_2:
            print("P0_2");
            break;
        case Position::P1_0:
            print("P1_0");
            break;
        case Position::P1_1:
            print("P1_1");
            break;
        case Position::P1_2:
            print("P1_2");
            break;
        case Position::P2_0:
            print("P2_0");
            break;
        case Position::P2_1:
            print("P2_1");
            break;
        case Position::P2_2:
            print("P2_2");
            break;
    }
    game.turn(game.turn() == Party::RECTANGLE ? Party::CIRCLE : Party::RECTANGLE);
    on_turn(game);
}

void on_turn(Game& game)
{
    switch (game.turn()) {
        case Party::RECTANGLE:
            game.color(sf::Color::Red);
            break;
        case Party::CIRCLE:
            game.color(sf::Color::Cyan);
            break;
    }
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
void handle_draw(sf::RenderWindow& window)
{
    for (int i = interface_xy / 3; i < interface_xy; i+= interface_xy / 3)
    {
        sf::RectangleShape line_shape;
        line_shape.setSize(sf::Vector2f(5, interface_xy));
        line_shape.setPosition(sf::Vector2f(i, 0));
        line_shape.setFillColor(sf::Color::Black);
        window.draw(line_shape);
        line_shape.setSize(sf::Vector2f(interface_xy, 5));
        line_shape.setPosition(sf::Vector2f(0, i));
        window.draw(line_shape);
    }
}
#pragma clang diagnostic pop