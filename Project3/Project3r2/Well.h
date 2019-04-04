#ifndef WELL_INCLUDED
#define WELL_INCLUDED

#include "UserInterface.h"
#include "Piece.h"

const int MAX_WELL_WIDTH = 20;
const int MAX_WELL_HEIGHT = 20;

const int BUFF = 4;

class Screen;

class Well
{
  public:
  	Well(int width, int height, bool specials);
    ~Well();

    void displayWell(Screen& screen, int x, int y);
    void displayInsides(Screen& screen, int x, int y);
    bool displayNext(Screen& screen, int x, int y);

    bool drop();
      //solifies current piece. different for special pieces
      //deletes m_current
      //current piece = next piece
      //generate new m_next. display that on score thing?
      //drops piece down
      //returns false if unsuccessful, indicating end of game
    int go(char key = 's');
      //depending on key: shifts piece down if nothing.
      //changes array. checks if hits anything. displays. returns:
      //0 if no input and succesful shift
      //1 if input and successful shift
      //-1 if no input (only option) and lands (it's done)
      //-2 if can't move/shift because of wall or other object

    //helper functions

    void choose();
      //chooses a piece
    bool check(std::string str, int x, int y);
      //checks if str works at x and y offset
    void place(std::string str, int x, int y);
      //actually places str in m_things at x and y offset
    void solidify(std::string str);
      //turns the things into $
      //x and y are for the recursion
    void foam(int x, int y);

    void clearWell();
      //clears everything for new level;
    int clearRows();
      //clears rows and returns how many were cleared


  private:
    bool m_specials;

  	int m_width;
  	int m_height;
  	char m_things[MAX_WELL_HEIGHT][MAX_WELL_WIDTH + BUFF];

  	Piece* m_current;
  	int m_x;
    int m_y;
    std::string m_str;

  	Piece* m_next;
};

#endif // WELL_INCLUDED
