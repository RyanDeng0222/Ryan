#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib> // 包含rand()和srand()
#include <ctime>   // 包含time()
using namespace sf;

unsigned int width = 1200, height = 600;
int score;
bool flag2 = true;

class Num {
public:
    Num() : x_(0), y_(0), tx_(0), ty_(0), val_(0), isCombined(false) {}
    Num(double x, double y, double tx, double ty,int val, bool flag)
        : x_(x), y_(y), tx_(tx), ty_(ty), val_(val), isCombined(flag) {}

    void Show(RenderWindow* window)
    {
        if (val_ == 0)
            return;
        RectangleShape shape({ 140, 140 });
        shape.setOutlineThickness(0);
        shape.setFillColor(Color(250 - log2(val_) * 30, 0, log2(val_) * 30));
        shape.setPosition({ (float)(8 + 148 * x_), (float)(8 + 148 * y_ )});
        window->draw(shape);
        
        Font font("cnr.otf");

        Text text1(font);
        std::string str = std::to_string(val_);
        str.erase(str.length() - 7, 7);
        text1.setString(str);
        text1.setCharacterSize(20);
        text1.setFillColor(Color::White);
        text1.setPosition({ (float)(8 + 148 * x_ + 70 - str.length() * 7), (float)(8 + 148 * y_ + 55) });
        window->draw(text1);  // 绘制文字
    }

    void Move(RenderWindow* window) 
    {
        x_ += (tx_ - x_) * 0.7;
        y_ += (ty_ - y_) * 0.7;
        Show(window);
    }
    bool isCombined;
    double x_, y_, tx_, ty_, val_;
};
void PlaySound()
{
    SoundBuffer buffer("1766_button-click-08.wav");
    Sound sound(buffer);
    sound.setVolume(100);
    sound.play();
    sleep(milliseconds(500));
}
void Welcome(RenderWindow* window) {
    bool flag = false;//是否在区域内
    bool flag1 = false;//是否在区域内
    Vector2i localPosition = sf::Mouse::getPosition(*window);
    if ((localPosition.x >= 500 && localPosition.x <= 700) && (localPosition.y >= 450 && localPosition.y <= 500))
    {
        flag = true;
    }

    if ((localPosition.x >= 500 && localPosition.x <= 700) && (localPosition.y >= 300 && localPosition.y <= 350))
    {
        flag1 = true;
    }
    Font font("cnr.otf");

    Text text1(font);
    text1.setString("2048Game");
    text1.setCharacterSize(100);
    text1.setFillColor(Color::White);
    text1.setStyle(Text::Bold);
    text1.setPosition({ 370, 100 });
    window->draw(text1);  // 绘制文字

    Text text2(font);
    text2.setString("Producer: Ryan");
    text2.setCharacterSize(50);
    text2.setFillColor(Color::White);
    text2.setPosition({ 400, 200 });
    window->draw(text2);  // 绘制文字

    RectangleShape shape({ 200, 50 });
    if (flag)
    {
        shape.setOutlineThickness(6);
        shape.setOutlineColor(Color::Green);
    }
    else
    {
        shape.setOutlineColor(Color::White);
        shape.setOutlineThickness(3);
    }
    shape.setFillColor(Color::Black);
    shape.setPosition({ 500, 450 });
    window->draw(shape);
    
    Text text3(font);
    text3.setString("Play");
    if (flag)
    {
        text3.setFillColor(Color::Green);
        text3.setCharacterSize(50);
        text3.setStyle(Text::Bold);
    }
    else
    {
        text3.setFillColor(Color::White);
        text3.setCharacterSize(50);
    }
    text3.setPosition({ 540, 440 });
    window->draw(text3);  // 绘制文字

    if (flag1)
    {
        shape.setOutlineThickness(6);
        shape.setOutlineColor(Color::Green);
    }
    else
    {
        shape.setOutlineColor(Color::White);
        shape.setOutlineThickness(3);
    }
    shape.setFillColor(Color::Black);
    shape.setPosition({ 500, 300 });
    window->draw(shape);

    text3.setString("Rules");
    if (flag1)
    {
        text3.setFillColor(Color::Green);
        text3.setCharacterSize(50);
        text3.setStyle(Text::Bold);
    }
    else
    {
        text3.setFillColor(Color::White);
        text3.setCharacterSize(50);
        text3.setStyle(Text::Regular);
    }
    text3.setPosition({ 535, 290 });
    window->draw(text3);  // 绘制文字
}
int Sense(RenderWindow* window)
{
    Vector2i localPosition = sf::Mouse::getPosition(*window);

    if ((localPosition.x >= 735 && localPosition.x <= 835) && (localPosition.y >= 370 && localPosition.y <= 470))
    {
        return 1;//左
    }
    if ((localPosition.x >= 965 && localPosition.x <= 1065) && (localPosition.y >= 370 && localPosition.y <= 470))
    {
        return 2;//右
    }
    if ((localPosition.x >= 850 && localPosition.x <= 950) && (localPosition.y >= 255 && localPosition.y <= 355))
    {
        return 3;//上
    }
    if ((localPosition.x >= 850 && localPosition.x <= 950) && (localPosition.y >= 485 && localPosition.y <= 585))
    {
        return 4;//右
    }
    return 0;
}
void Background(RenderWindow* window)
{
    int state = Sense(window);

    RectangleShape shape1({ 585, 585 });
    shape1.setOutlineThickness(8);
    shape1.setOutlineColor(Color::Black);
    shape1.setFillColor(Color(150, 150, 150));
    shape1.setPosition({ 8, 8 });
    window->draw(shape1);

    RectangleShape shape2({ 140, 140 });
    shape2.setOutlineThickness(8);
    shape2.setOutlineColor(Color::Black);
    shape2.setFillColor(Color(150, 150, 150));
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            shape2.setPosition({ (float)8 + i * 148, (float)8 + j * 148 });
            window->draw(shape2);
        }
    
    std::string s = "score: ";
    std::string str = std::to_string(score);
    s += str;

    Font font("cnr.otf");

    Text text1(font);
    text1.setString(s);
    text1.setCharacterSize(70);
    text1.setFillColor(Color::Green);
    text1.setPosition({ 735, 35 });
    window->draw(text1);  // 绘制文字

    RectangleShape shape3({ 100, 100 });
    if (state == 1)
    {
        shape3.setOutlineThickness(13);
        shape3.setOutlineColor(Color::Green);
    }
    else
    {
        shape3.setOutlineThickness(8);
        shape3.setOutlineColor(Color::Black);
    }
    shape3.setFillColor(Color(150, 150, 150));
    shape3.setPosition({ 735, 370 });
    window->draw(shape3);
    text1.setString("<-");
    if (state == 1)
    {
        text1.setCharacterSize(70);
        text1.setFillColor(Color::Green);
    }
    else
    {
        text1.setCharacterSize(70);
        text1.setFillColor(Color::Black);
    }
    text1.setStyle(Text::Bold);
    text1.setPosition({ 745, 365 });
    window->draw(text1);  // 左

    shape3.setPosition({ 965, 370 });
    if (state == 2)
    {
        shape3.setOutlineThickness(13);
        shape3.setOutlineColor(Color::Green);
    }
    else
    {
        shape3.setOutlineThickness(8);
        shape3.setOutlineColor(Color::Black);
    }
    window->draw(shape3);
    text1.setPosition({ 1050, 465 });
    text1.setRotation(sf::degrees(180));
    if (state == 2)
    {
        text1.setCharacterSize(70);
        text1.setFillColor(Color::Green);
    }
    else
    {
        text1.setCharacterSize(70);
        text1.setFillColor(Color::Black);
    }
    window->draw(text1);  // 右

    shape3.setPosition({ 850, 255 });
    if (state == 3)
    {
        shape3.setOutlineThickness(13);
        shape3.setOutlineColor(Color::Green);
    }
    else
    {
        shape3.setOutlineThickness(8);
        shape3.setOutlineColor(Color::Black);
    }
    window->draw(shape3);
    text1.setPosition({ 950, 265 });
    text1.setRotation(sf::degrees(90));
    if (state == 3)
    {
        text1.setCharacterSize(70);
        text1.setFillColor(Color::Green);
    }
    else
    {
        text1.setCharacterSize(70);
        text1.setFillColor(Color::Black);
    }
    window->draw(text1);  // 上

    shape3.setPosition({ 850, 485 });
    if (state == 4)
    {
        shape3.setOutlineThickness(13);
        shape3.setOutlineColor(Color::Green);
    }
    else
    {
        shape3.setOutlineThickness(8);
        shape3.setOutlineColor(Color::Black);
    }
    window->draw(shape3);
    text1.setPosition({ 850, 575 });
    text1.setRotation(sf::degrees(270));
    if (state == 4)
    {
        text1.setCharacterSize(70);
        text1.setFillColor(Color::Green);
    }
    else
    {
        text1.setCharacterSize(70);
        text1.setFillColor(Color::Black);
    }
    window->draw(text1);  // 下
}
class Board
{
public:
    Board(RenderWindow* window)
        : window_(window), a(), b()
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
            {
                a[i][j] = Num((double)i, (double)j, (double)i, (double)j, 0, false);
                b[i][j] = Num((double)i, (double)j, (double)i, (double)j, 0, false);
            }
    }
    void AddRandNum()
    {
        int cnt = 0;
        while (a[cnt / 4][cnt % 4].val_ != 0)
            cnt = (cnt + 1) % 16;
        std::srand(static_cast<unsigned int>(std::time(0)));
        int randnum = std::rand() % 16;
        while (randnum--)
        {
            cnt = (cnt + 1) % 16;
            while (a[cnt / 4][cnt % 4].val_ != 0)
                cnt = (cnt + 1) % 16;
        }
        randnum = std::rand() % 10;
        if(randnum >= 0 && randnum <= 8)
            a[cnt / 4][cnt % 4].val_ = 2;
        else
            a[cnt / 4][cnt % 4].val_ = 4;
    }
    void Show()
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                a[i][j].Show(window_);
    }
    void Move(int state)
    {
        if (!state)
            return;
        PlaySound();
        flag2 = true;
        if (state == 1)
        {
            for (int j = 0; j < 4; j++)
                for (int i = 0; i < 4; i++)
                {
                    int x = i, y = j;
                    while (x != 0 && b[x - 1][y].val_ == 0)
                        x--;
                    if (x != 0 && b[x - 1][y].val_ == a[i][j].val_ && b[x - 1][y].isCombined == false)
                    {
                        x--;
                        b[x][y].isCombined = true;
                        score += a[i][j].val_ + b[x][y].val_;
                    }
                    b[x][y].val_ += a[i][j].val_;
                    a[i][j].tx_ = x;
                    a[i][j].ty_ = y;
                }
        }
        else if (state == 2)
        {
            for (int j = 0; j < 4; j++)
                for (int i = 3; i >= 0; i--)
                {
                    int x = i, y = j;
                    while (x != 3 && b[x + 1][y].val_ == 0)
                        x++;
                    if (x != 3 && b[x + 1][y].val_ == a[i][j].val_ && b[x + 1][y].isCombined == false)
                    {
                        x++;
                        b[x][y].isCombined = true;
                        score += a[i][j].val_ + b[x][y].val_;
                    }
                    b[x][y].val_ += a[i][j].val_;
                    a[i][j].tx_ = x;
                    a[i][j].ty_ = y;
                }
        }
        else if (state == 3)
        {
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                {
                    int x = i, y = j;
                    while (y != 0 && b[x][y - 1].val_ == 0)
                        y--;
                    if (y != 0 && b[x][y - 1].val_ == a[i][j].val_ && b[x][y - 1].isCombined == false)
                    {
                        y--;
                        b[x][y].isCombined = true;
                        score += a[i][j].val_ + b[x][y].val_;
                    }
                    b[x][y].val_ += a[i][j].val_;
                    a[i][j].tx_ = x;
                    a[i][j].ty_ = y;
                }
        }
        else if (state == 4)
        {
            for (int i = 0; i < 4; i++)
                for (int j = 3; j >= 0; j--)
                {
                    int x = i, y = j;
                    while (y != 3 && b[x][y + 1].val_ == 0)
                        y++;
                    if (y != 3 && b[x][y + 1].val_ == a[i][j].val_ && b[x][y + 1].isCombined == false)
                    {
                        y++;
                        b[x][y].isCombined = true;
                        score += a[i][j].val_ + b[x][y].val_;
                    }
                    b[x][y].val_ += a[i][j].val_;
                    a[i][j].tx_ = x;
                    a[i][j].ty_ = y;
                }
        }
        for (int i = 1; i <= 10; i++)
        {
            window_->clear(Color(150, 150, 150));
            Background(window_);
            //每个单元的Move()函数
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    a[i][j].Move(window_);
            sleep(milliseconds(100));
            window_->display();
        }
        //把b赋值给a, 再初始化b
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
            {
                a[i][j]=b[i][j];
                b[i][j] = Num(i, j, i, j, 0, false);
            }
        Show();
    }
    bool isGameOver()
    {

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (a[i][j].val_ == 0)
                    return false;
                if (i != 3 && a[i + 1][j].val_ == a[i][j].val_)
                    return false;
                if (j != 3 && a[i][j + 1].val_ == a[i][j].val_)
                    return false;
            }
        } 
        return true;
    }
private:
    RenderWindow* window_;
    Num a[4][4], b[4][4];
};
int main() 
{
    RenderWindow window(VideoMode({width, height}), "2048", Style::Close, sf::State::Windowed);
    int state = 1;//时态，1欢迎，2游戏， 3结束，4规则
    Board board(&window);
    board.AddRandNum();
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
            {
                PlaySound();
                window.close();
            }
        }
        if (state == 1)
        {
            window.clear(Color::Black);
            Welcome(&window);
            window.display();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                Vector2i localPosition = sf::Mouse::getPosition(window);
                if ((localPosition.x >= 500 && localPosition.x <= 700) && (localPosition.y >= 450 && localPosition.y <= 500))
                {
                    PlaySound();
                    state = 2;
                }
                if ((localPosition.x >= 500 && localPosition.x <= 700) && (localPosition.y >= 300 && localPosition.y <= 350))
                {
                    PlaySound();
                    state = 4;
                }
            }
        }
        else if (state == 2)
        {
            window.clear(Color(150,150,150));
            Background(&window);

            board.Show();
            if (flag2)
            {
                board.AddRandNum();
                flag2 = false;
                if (board.isGameOver())
                {
                    state = 3;
                }
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                board.Move(Sense(&window));
            }
            window.display();
        }
        else if (state == 3)
        {
            const Texture texture("无标题.png");
            RectangleShape shape({ 1200, 600 });
            shape.setTexture(&texture);
            window.draw(shape);
            Font font("cnr.otf");
            Text text(font); 
            std::string str = std::to_string(score);
            text.setString(str);
            text.setCharacterSize(80);

            text.setPosition({ 647,392 });
            text.setFillColor(Color::Red);
            window.draw(text);

            text.setPosition({ 653,398 });
            text.setFillColor(Color(0, 168, 243));
            window.draw(text);

            text.setPosition({ 650,395 });
            text.setFillColor(Color::White);
            window.draw(text);

            window.display();
        }
        else if (state == 4)
        {
            Texture texture("无标题2.png");
            RectangleShape shape({ 1200, 600 });
            shape.setTexture(&texture);
            window.draw(shape);
            
            bool isinArea = false;
            Vector2i localPosition = sf::Mouse::getPosition(window);
            if ((localPosition.x >= 20 && localPosition.x <= 70) && (localPosition.y >= 20 && localPosition.y <= 70))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                {
                    state = 1;
                    PlaySound();
                }
                isinArea = true;
            }

            std::string str;
            CircleShape shape1(25);
            shape1.setPosition({ 20,20 });
            if (isinArea) 
            {
                shape1.setOutlineColor(Color::Green);
                shape1.setOutlineThickness(8);
                str = "无标题3.png";
            }
            else
            {
                shape1.setOutlineColor(Color::White);
                shape1.setOutlineThickness(5);
                str = "无标题4.png";
            }
            Texture texture2(str);
            shape1.setTexture(&texture2);
            window.draw(shape1);

            window.display();
        }
    }
    return 0;
}