#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
using namespace std;

#include "globals.h"
#include "History.h"

History::History(int nRows, int nCols)
:m_rows(nRows), m_cols(nCols)
{
    for(int i = 1; i <= nRows; i++)
    {
        for(int j = 1; j <= nCols; j++)
        {
            m_grid[i][j] = 0;
        }
    }
}

bool History::record(int r, int c)
{
    if(r >= 1 && r <=  m_rows && c >= 1 && c <= m_cols)
    {
        m_grid[r][c]++;
        return true;
    }
    return false;
}
void History::display() const
{
    clearScreen();
    for(int i = 1; i <= m_rows; i++)
    {
        for(int j = 1; j <= m_cols; j++)
        {
            if(m_grid[i][j] == 0)
            {
                std::cout << ".";
            }
            else if(m_grid[i][j] < 26)
            {
                char temp = m_grid[i][j] + '@';
                std::cout << temp;
            }
            else
            {
                std::cout << 'Z';
            }
        }
        
        std::cout << '\n';
    }
    std::cout << '\n';
}

