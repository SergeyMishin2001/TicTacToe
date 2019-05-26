#include <SFML/Graphics.hpp>

#include <iostream>
#include <map>
#include <chrono>
#include <thread>

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;

sf::Sprite* sprites[9] = { nullptr };
char matrix[9] = {0};

std::map<int, sf::Vector2f> coord  = 
{
    {0, sf::Vector2f(100.0f, 100.0f)},
    {1, sf::Vector2f(300.0f, 100.0f)},
    {2, sf::Vector2f(500.0f, 100.0f)},
    {3, sf::Vector2f(100.0f, 300.0f)},
    {4, sf::Vector2f(300.0f, 300.0f)},
    {5, sf::Vector2f(500.0f, 300.0f)},
    {6, sf::Vector2f(100.0f, 500.0f)},
    {7, sf::Vector2f(300.0f, 500.0f)},
    {8, sf::Vector2f(500.0f, 500.0f)}
};

class ISide
{
public:
    bool isReady = false;
    virtual std::string getSide() const = 0;
    virtual char getChar() const = 0;
    virtual void makeMove() = 0;
};

class Player : public ISide
{
public:
    sf::Texture playerT;
    sf::Sprite playerS;
    sf::Vector2i pos;

    int index = 0;

    Player(const std::string& path) 
    {
        playerT.loadFromFile(path);
        playerS.setTexture(playerT);
        playerS.setOrigin(85, 85);
    }
    
    std::string getSide() const override { return "Player"; }

    char getChar() const override { return 'x';}

    bool mapCoordinates(const sf::Vector2i& pos)
    {
        int i = 0;
        for(int y = 0; y <= 400; y += 200)
        {
            if(pos.y > y && pos.y < (y + 200))
            {
                for(int x = 0; x <= 400; x += 200)
                {
                    if(pos.x > x && pos.x < (x + 200) && matrix[i] == 0)
                    {
                        this->index = i;
                        return true;
                    }
                    i++;
                }   
            }
            else i += 3;
        }    
        return false;
    }

    void makeMove() override
    {           
        sprites[index] = new sf::Sprite(playerS);
        sprites[index]->setPosition(coord[index]);
        matrix[index] = 'x';
    }   
};

class Bot : public ISide
{
public:
    sf::Texture botT;
    sf::Sprite botS;

    Bot(const std::string& path)
    {
        botT.loadFromFile(path);
        botS.setTexture(botT);
        botS.setOrigin(85,85);
    }

    std::string getSide() const override { return "Bot"; }

    char getChar() const override { return '0'; }
    void makeMove() override
    {
        for(int i = 0; i < 9; i++)
        {
            if(matrix[i] == 0) 
            { 
                std::this_thread::sleep_for(std::chrono::milliseconds(500));

                sprites[i] = new sf::Sprite(botS);
                sprites[i]->setPosition(coord[i]);
                matrix[i] = '0';

                break;
            }
        }
    }

};

bool checkWin();

ISide* side;

int main(int argc, char** argv)
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "TicTacToe", sf::Style::Close | sf::Style::Titlebar);

    window.setPosition(sf::Vector2i(0,0));

    sf::Texture tex_board;
    sf::Sprite sp_board;

    tex_board.loadFromFile("board.png");
    sp_board.setTexture(tex_board);

    sp_board.setScale(static_cast<float>(WINDOW_WIDTH)/400.0f, static_cast<float>(WINDOW_HEIGHT)/400.0f);
   
    Player player("x.png");
    Bot bot("o.png");
    side = &player;

    bool gameFinished = false;
    bot.isReady = true;



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2i coords = sf::Mouse::getPosition(window);

                if (player.mapCoordinates(coords)) player.isReady = true; 
            }
        }        

        if(side->isReady)
        {   
            side->makeMove();

            gameFinished = checkWin();
            if(!gameFinished)
            {   
                if(side->getSide() == "Player") { side->isReady = false; side = &bot; } 
                else side = &player;
            }
        }

        window.clear();
        window.draw(sp_board);

        for(int i = 0; i < 9; i++)
        {
            if(matrix[i] != 0)
            {
                window.draw(*sprites[i]);
            }
        }

        window.display();

        if(gameFinished)
        {
            std::cout << side->getSide() << " has won!" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            for(int i = 0; i < 9; i++)
            {
                if(matrix[i] != 0)
                {
                    delete sprites[i];
                }
            }
            return 0;
        }
    }
    return 0;
}

bool checkWin()
{
    if( (matrix[0] == matrix[1] && matrix[1] == matrix[2] && matrix[2] == side->getChar()) ||
        (matrix[3] == matrix[4] && matrix[4] == matrix[5] && matrix[5] == side->getChar()) ||
        (matrix[6] == matrix[7] && matrix[7] == matrix[8] && matrix[8] == side->getChar()) ||
        (matrix[0] == matrix[3] && matrix[3] == matrix[6] && matrix[6] == side->getChar()) ||
        (matrix[1] == matrix[4] && matrix[4] == matrix[7] && matrix[7] == side->getChar()) ||
        (matrix[2] == matrix[5] && matrix[5] == matrix[8] && matrix[8] == side->getChar()) ||
        (matrix[0] == matrix[4] && matrix[4] == matrix[8] && matrix[8] == side->getChar()) ||
        (matrix[2] == matrix[4] && matrix[4] == matrix[6] && matrix[6] == side->getChar())) return true;
    else return false;
}
