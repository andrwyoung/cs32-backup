#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Well.h"
#include "UserInterface.h"
#include <string>
#include <algorithm> //std::max
#include <cmath>

const bool SPECIAL = true;
const bool LEVELS = true;

class Game
{
  public:
    Game(int width, int height);
    void play();
    bool playOneLevel();
    void displayPrompt(std::string s);
    void displayStatus();

    // void display();

  private:
    Well    m_well;
    Screen  m_screen;
    int     m_level;
    int     m_rowsLeft;
    int     m_score;

    Timer   m_timer;
};

#endif // GAME_INCLUDED
