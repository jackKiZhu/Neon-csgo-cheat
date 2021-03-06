#pragma once

class CNavLadder
{
private:

public:

	enum LadderDirectionType
	{
		LADDER_UP = 0,
		LADDER_DOWN,

		NUM_LADDER_DIRECTIONS
	};


	Vector3 m_top;
	Vector3 m_bottom;

	float m_length;
	float m_width;




};
