#include "Well.h"
#include "UserInterface.h"

Well::Well(int width, int height, bool specials)
	:m_width(width), m_height(height), m_current(nullptr), m_next(nullptr), m_specials(specials)
{
	if(width < 4 || height < 4 || 
		width > MAX_WELL_WIDTH || height > MAX_WELL_HEIGHT)
    {
        exit(1);
    }
}

Well::~Well()
{
	delete m_current;
	delete m_next;
}

void Well::displayWell(Screen& screen, int x, int y)
{
	for(int i = 0; i < m_height; i++)
		//going down each columns
	{
		screen.gotoXY(x, y + i);
		screen.printChar('@');
		
		screen.gotoXY(x + m_width + 1, y + i);
		screen.printChar('@');
	}

	//printing last row
	screen.gotoXY(x, y + m_height);
	screen.printChar('@');
	for(int i = 0; i < m_width; i++)
	{
		screen.printChar('@');
	}
	screen.printChar('@');

	screen.refresh();
}

void Well::displayInsides(Screen& screen, int x, int y)
{
	for(int i = 0; i < m_height; i++)
		//going down each columns
	{
		screen.gotoXY(x + 1, y + i);
		for(int j = BUFF; j < m_width + BUFF; j++)
			//printing current row
		{
			screen.printChar(m_things[i][j]);
		}
	}

	screen.refresh();
}

bool Well::displayNext(Screen& screen, int x, int y)
{
	if(m_current == nullptr)
	{
		return false;
	}

	std::string str = m_next->feed();

	for(int i = 0; i < 4; i++)
	{
		
		for(int j = 0; j < 4; j++)
		{
			screen.gotoXY(x + j, y + i);
			screen.printChar(' ');
			screen.gotoXY(x + j, y + i);

			if(str[(i * 4) + j] == '1')
			{
				screen.printChar('#');
			}
		}
	}

	return true;
}

bool Well::drop()
{
	if(m_current != nullptr) //should be null for first one
	{
		delete m_current;
	}

	m_x = (m_width / 2) - 2 + BUFF;
	m_y = 0;

	m_current = m_next;
	choose();

	m_str = m_current->feed();

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(m_str[(i * 4) + j] == '1' &&  m_things[m_y + i][m_x + j] != ' ')
			{
					return false;
			}
		}
	}
		
	place(m_str, 0, 0);
	return true;
}

int Well::go(char key)
//depending on key: shifts piece down if nothing.
//changes array. checks if hits anything. displays. returns:
//0 if no input and succesful shift
//1 if input and successful shift
//-1 if no input (only option) and lands (it's done)
//-2 if can't move/shift because of wall or other object
//-3 wrong input
//-4 for quit
{
	if(m_current->getID() == 9)
		//crazy piece
		//will never be created if special is false
	{
		switch(key)
		{
			case '6':
			case 'd':
				key = '4';
				break;
			case '4':
			case 'a':
				key = '6';
				break;
			default:
				break;
		}
	}

	std::string next = m_current->feedNextOrientation();
	switch(key)
	{
		case '8': //rotates
		case 'w':
			if(check(next, 0, 0))
			{
				place(next, 0, 0);
				m_current->changeOrientation();
				m_str = m_current->feed();
				return 1;
			}
			else
			{
				return -2;
			}
			break;

		case '4': //left
		case 'a':
			if(check(m_str, -1, 0))
			{
				place(m_str, -1, 0);
				m_x--;
				return 1;
			}
			else
			{
				return -2;
			}
			break;

		case '6': //right
		case 'd':
			if(check(m_str, 1, 0))
			{
				place(m_str, 1, 0);
				m_x++;
				return 1;
			}
			else
			{
				return -2;
			}
			break;

		case '2':
		case 's':
			if(check(m_str, 0, 1))
			{
				place(m_str, 0, 1);
				m_y++;
				return 0;
			}
			else
			{
				solidify(m_str);
				return -1;
			}
			break;
		case ' ': //slam
			while(go('2') != -1);
			solidify(m_str);
			return -1;
			break;
		default:
			return -3;
	}


	return -3;
}


void Well::choose()
{
	int c = chooseRandomPieceType();

	if(!m_specials)
	{
		while(c > 6)
		{
			c = chooseRandomPieceType();
		}
	}

	switch(c)
	{
		case 0:
			m_next = new iPiece();
			break;
		case 1:
			m_next = new lPiece();
			break;
		case 2:
			m_next = new jPiece();
			break;
		case 3:
			m_next = new tPiece();
			break;
		case 4:
			m_next = new oPiece();
			break;
		case 5:
			m_next = new sPiece();
			break;
		case 6:
			m_next = new zPiece();
			break;
		case 7:
			m_next = new vaporBomb();
			break;
		case 8:
			m_next = new foamBomb();
			break;
		case 9:
			m_next = new crazyShape();
			break;
		default: 
			exit(3);
	}

	
}


bool Well::check(std::string str, int x, int y)
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(str[(i * 4) + j] == '1' && 
				((m_things[m_y + y + i][m_x + x + j] != ' ' && 
				m_str[((i + y) * 4) + j + x] != '1') || 
				m_y + y + i >= m_height || m_x + x + j <= BUFF - 1 || m_x + x + j >= BUFF + m_width))
				//if there is a block
				//and the corresponding space in m_things isn't empty
				//(ignoring the blocks it's currently on)
				//or if its out of bounds
			{
					return false;
			}
		}
	}

	return true;
}

void Well::place(std::string str, int x, int y)
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(m_str[(i * 4) + j] == '1')
			{
				//erase current
				m_things[m_y + i][m_x + j] = ' ';
			}
			
		}
	}

	//wish i could condense both of them
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(str[(i * 4) + j] == '1')
			{
				//place new
				m_things[m_y + y + i][m_x + x + j] = '#';

			}
			
		}
	}
}

void Well::solidify(std::string str)
{
	if(m_current->getID() == 7)
		//vaporBomb
	{
		for(int i = 0; i < 5; i++)
		{
			for(int j = 0; j < 2; j++)
			{
				if(m_y - 2 + i > 0)
				{
					m_things[m_y - 2 + i][m_x + 1 + j] = ' ';
				}
				
			}
		}
	}
	else if(m_current->getID() == 8)
		//foamBomb
	{

		foam(m_x + 1, m_y + 1);
	}
	else
	{
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				if(str[(i * 4) + j] == '1')
				{
					m_things[m_y + i][m_x + j] = '$';
				}
				
			}
		}
	}
		
}

void Well::foam(int x, int y)
{
	if(x > m_x + 3 || x < m_x - 1 || y > m_y + 3 || y < m_y - 1)
	{
		return;
	}
	else
	{
		m_things[y][x] = '*';

		if(m_things[y][x + 1] == ' ')
		{
			foam(x + 1, y);
		}

		if(m_things[y + 1][x] == ' ')
		{
			foam(x, y + 1);
		}

		if(m_things[y][x - 1] == ' ')
		{
			foam(x - 1, y);
		}

		if(m_things[y - 1][x] == ' ')
		{
			foam(x, y - 1);
		}

		return;
	}
}

void Well::clearWell()
{
	for(int i = 0; i < m_height; i++)
    {
    	for(int j = BUFF; j < m_width + BUFF; j++)
    	{
    		m_things[i][j] = ' ';
    	}
    }

    delete m_current;
    m_current = nullptr;
    delete m_next;
    choose();
}

int Well::clearRows()
{
	bool clean = true;
	int counter = 0;
	int tracker = 0;

	for(int i = 0; i < m_height; i++)
	{
		for(int j = BUFF; j < m_width + BUFF; j++)
		{
			if(m_things[i][j] == ' ')
			{
				clean = false;
				break;
			}
			else
			{
				clean = true;
			}
		}

		if(clean)
			//if row is clean. clear the row
		{
			for(int j = BUFF; j < m_width + BUFF; j++)
			{
				m_things[i][j] = ' ';
			}
			tracker = i;
			counter++;
		}
	}

	//shift above rows down;
	if(counter > 0)
	{
		for(int i = tracker - counter; i >= 0; i--)
		{
			for(int j = BUFF; j < m_width + BUFF; j++)
			{
				//don't touch the current piece


				m_things[i + counter][j] = m_things[i][j];
			}
		}
	}
	

	return counter;
}

