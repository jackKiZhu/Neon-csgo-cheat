#pragma once

class HidingSpot
{
public:

	enum
	{
		IN_COVER = 0x01,							// in a corner with good hard cover nearby
		GOOD_SNIPER_SPOT = 0x02,							// had at least one decent sniping corridor
		IDEAL_SNIPER_SPOT = 0x04,							// can see either very far, or a large area, or both
		EXPOSED = 0x08							// spot in the open, usually on a ledge or cliff
	};

	Vector3 m_pos{ 0.0f, 0.0f, 0.0f }; // Position
	unsigned int m_id{ 0 }; // Unique id inside this area

	unsigned char m_flags; // Flags are defined above

};
