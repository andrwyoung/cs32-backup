#ifndef WELL_INCLUDED
#define WELL_INCLUDED

#include "UserInterface.h"
#include "Piece.h"

const int MAX_WELL_WIDTH = 20; // - 5
const int MAX_WELL_HEIGHT = 20; // - 2

//buffer is used so check and place can't walk off the m_things array
const int BUFF = 4;

class Screen;

class Well
{
  public:
  	Well(int width, int height, bool specials);
    ~Well();

    //actually displays things
    void displayWell(Screen& screen, int x, int y) const;
    void displayInsides(Screen& screen, int x, int y) const;
    bool displayNext(Screen& screen, int x, int y) const;

    //main functions
    bool drop();
      //solifies current piece. different for special pieces
      //deletes m_current
      //current piece = next piece
      //generate new m_next
      //drops piece down
      //returns false if unsuccessful, indicating end of game
    int go(char key = 's');
      //depending on key. shifts piece down if nothing.
      //changes array. checks if hits anything. displays. returns:
      //0 if no input and succesful shift
      //1 if input and successful shift
      //-1 if no input (only option) and lands (it's done)
      //-2 if can't move/shift because of wall or other object
      //-3 any key other than designated keys

    //helper functions
    void choose();
      //chooses a m_next piece
    bool check(std::string str, int x, int y) const;
      //checks if str works at x and y offset
    void place(std::string str, int x, int y);
      //actually places str in m_things at x and y offset
      //usually works together with check
    void solidify(std::string str);
      //turns the things into $
      //also includes special pieces
    void foam(int x, int y);
      //recursion function for foamBomb solidifying

    //clearing and resetings
    void clearWell();
      //clears everything for new level;
    int clearRows();
      //clears rows and returns how many were cleared


  private:
    bool m_specials; //special feature: turn off/on special pieces

    //height and width of well
  	int m_width;
  	int m_height;

    //actual representation of the well
  	char m_things[MAX_WELL_HEIGHT][MAX_WELL_WIDTH + BUFF];

    //holds current pieces and everything about it
  	Piece* m_current;
  	int m_x;
    int m_y;
    std::string m_str;

    //holds onto next piece
  	Piece* m_next;
};

#endif // WELL_INCLUDED
