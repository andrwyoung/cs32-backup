#include "Piece.h"

Piece::Piece()
	:m_str(""), m_orientation(-1) 
	//so that orientation will be 0
{
}

Piece::~Piece()
	//virtual, so needs this
{
}

std::string Piece::feed()
{
	return m_str;
}

std::string Piece::feedNextOrientation()
{
	if(m_orientation >= 3)
	{
		return orientations(0);
	}
	else
	{
		return orientations(m_orientation + 1);
	}
}

void Piece::changeOrientation()
{
	if(m_orientation >= 3)
	{
		m_orientation = 0;
	}
	else
	{
		m_orientation++;
	}

	m_str = orientations(m_orientation);
}


iPiece::iPiece()
	:m_id(0)
{
	changeOrientation();
}

int iPiece::getID()
{
	return m_id;
}

std::string iPiece::orientations(int orientation)
{
	switch(orientation)
	{
		case 0:
		case 2:
			return "0000111100000000";
		case 1:
		case 3:
			return "0100010001000100";
		default:
			exit(2);
	}
}




lPiece::lPiece()
	:m_id(1)
{
	changeOrientation();
}

int lPiece::getID()
{
	return m_id;
}

std::string lPiece::orientations(int orientation)
{
	switch(orientation)
	{
		case 0:
			return "0000111010000000";
		case 1:
			return "0110001000100000";
		case 2:
			return "0000001011100000";
		case 3:
			return "0000010001000110";
		default:
			exit(2);
	}
}





jPiece::jPiece()
	:m_id(2)
{
	changeOrientation();
}

int jPiece::getID()
{
	return m_id;
}

std::string jPiece::orientations(int orientation)
{
	switch(orientation)
	{
		case 0:
			return "0000011100010000";
		case 1:
			return "0000001000100110";
		case 2:
			return "0000010001110000";
		case 3:
			return "0110010001000000";
		default:
			exit(2);
	}
}





tPiece::tPiece()
	:m_id(3)
{
	changeOrientation();
}

int tPiece::getID()
{
	return m_id;
}

std::string tPiece::orientations(int orientation)
{
	switch(orientation)
	{
		case 0:
			return "0100111000000000";
		case 1:
			return "0100011001000000";
		case 2:
			return "0000111001000000";
		case 3:
			return "0100110001000000";
		default:
			exit(2);
	}
}





oPiece::oPiece()
	:m_id(4)
{
	changeOrientation();
}

int oPiece::getID()
{
	return m_id;
}

std::string oPiece::orientations(int orientation)
{
	switch(orientation)
	{
		case 0:
		case 1:
		case 2:
		case 3:
			return "1100110000000000";
		default:
			exit(2);
	}
}

sPiece::sPiece()
	:m_id(5)
{
	changeOrientation();
}





int sPiece::getID()
{
	return m_id;
}

std::string sPiece::orientations(int orientation)
{
	switch(orientation)
	{
		case 0:
		case 2:
			return "0000011011000000";
		case 1:
		case 3:
			return "0100011000100000";
		default:
			exit(2);
	}
}







zPiece::zPiece()
	:m_id(6)
{
	changeOrientation();
}

int zPiece::getID()
{
	return m_id;
}

std::string zPiece::orientations(int orientation)
{
	switch(orientation)
	{
		case 0:
		case 2:
			return "0000110001100000";
		case 1:
		case 3:
			return "0010011001000000";
		default:
			exit(2);
	}
}

vaporBomb::vaporBomb()
	:m_id(7)
{
	changeOrientation();
}

int vaporBomb::getID()
{
	return m_id;
}

std::string vaporBomb::orientations(int orientation)
{
	switch(orientation)
	{
		case 0:
		case 1:
		case 2:
		case 3:
			return "0110000000000000";
		default:
			exit(2);
	}
}

foamBomb::foamBomb()
	:m_id(8)
{
	changeOrientation();
}

int foamBomb::getID()
{
	return m_id;
}

std::string foamBomb::orientations(int orientation)
{
	switch(orientation)
	{
		case 0:
		case 1:
		case 2:
		case 3:
			return "0000010000000000";
		default:
			exit(2);
	}
}

crazyShape::crazyShape()
	:m_id(9)
{
	changeOrientation();
}

int crazyShape::getID()
{
	return m_id;
}

std::string crazyShape::orientations(int orientation)
{
	switch(orientation)
	{
		case 0:
			return "1001011000000000";
		case 1:
			return "0001001000100001";
		case 2:
			return "0000000001101001";
		case 3:
			return "1000010001001000";
		default:
			exit(2);
	}
}



