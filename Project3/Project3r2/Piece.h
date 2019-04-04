#ifndef PIECE_INCLUDED
#define PIECE_INCLUDED

#include <string>

enum PieceType {
    PIECE_I, PIECE_L, PIECE_J, PIECE_T, PIECE_O, PIECE_S, PIECE_Z,
    PIECE_VAPOR, PIECE_FOAM, PIECE_CRAZY, NUM_PIECE_TYPES
};

PieceType chooseRandomPieceType();

class Piece
{
  public:
  	Piece();
  	virtual ~Piece();
  	std::string feed();
  		//output's piece's string so that Well can do stuff
  	std::string feedNextOrientation(); 
  		//changes orientation, then
  		//gives next orientation string. so that well can check if that works
  	void changeOrientation();
  		//changes m_orientation and m_str to match orientation
  	virtual std::string orientations(int orientation) = 0;
    virtual int getID() = 0;

  private:
  	int m_orientation;

  protected:
  	std::string m_str;
  	
};

class iPiece : public Piece
{
  public:
  	iPiece();
  	int getID();
  	std::string orientations(int orientation);
  		//returns orientation for this block

  private:
  	int m_id;
};

class lPiece : public Piece
{
  public:
    lPiece();
    int getID();
    std::string orientations(int orientation);
      //returns orientation for this block

  private:
    int m_id;
};

class jPiece : public Piece
{
  public:
    jPiece();
    int getID();
    std::string orientations(int orientation);
      //returns orientation for this block

  private:
    int m_id;
};


class tPiece : public Piece
{
  public:
    tPiece();
    int getID();
    std::string orientations(int orientation);
      //returns orientation for this block

  private:
    int m_id;
};

class oPiece : public Piece
{
  public:
    oPiece();
    int getID();
    std::string orientations(int orientation);
      //returns orientation for this block

  private:
    int m_id;
};


class sPiece : public Piece
{
  public:
    sPiece();
    int getID();
    std::string orientations(int orientation);
      //returns orientation for this block

  private:
    int m_id;
};

class zPiece : public Piece
{
  public:
    zPiece();
    int getID();
    std::string orientations(int orientation);
      //returns orientation for this block

  private:
    int m_id;
};

class vaporBomb : public Piece
{
  public:
    vaporBomb();
    int getID();
    std::string orientations(int orientation);
      //returns orientation for this block

  private:
    int m_id;
};

class foamBomb : public Piece
{
  public:
    foamBomb();
    int getID();
    std::string orientations(int orientation);
      //returns orientation for this block

  private:
    int m_id;
};

class crazyShape : public Piece
{
  public:
    crazyShape();
    int getID();
    std::string orientations(int orientation);
      //returns orientation for this block

  private:
    int m_id;
};

#endif // PIECE_INCLUDED
