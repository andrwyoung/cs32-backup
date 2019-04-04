#include <queue>
#include <iostream>

class Coord
{
  public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
  private:
    int m_r;
    int m_c;
};


bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
{
	std::queue<Coord> coordQueue;

	coordQueue.push(Coord(sr, sc));
	maze[sr][sc] = 'o';
	while(!coordQueue.empty())
	{	
		Coord current = coordQueue.front();
		coordQueue.pop();
		int c = current.c();
		int r = current.r();

		if(r == er && c == ec)
		{
			return true;	
		}

		if(r >= 1 && maze[r - 1][c] == '.') //can move north?
		{
			coordQueue.push(Coord(r - 1, c));
			maze[r - 1][c] = 'o';
		}

		if(c >= 1 && maze[r][c - 1] == '.') //can move west?
		{
			coordQueue.push(Coord(r, c - 1));
			maze[r][c - 1] = 'o';
		}

		if(r <= 8 && maze[r + 1][c] == '.') //can move south?
		{
			coordQueue.push(Coord(r + 1, c));
			maze[r + 1][c] = 'o';
		}

		if(c <= 8 && maze[r][c + 1] == '.') //can move east?
		{
			coordQueue.push(Coord(r, c + 1));
			maze[r][c + 1] = 'o';
		}
	}

	return false;
}