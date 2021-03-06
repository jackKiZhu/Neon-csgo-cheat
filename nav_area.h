#pragma once

#include "INav.h"
#include "nav_ladder.h"
#include "nav_hidingspot.h"

enum { MAX_NAV_TEAMS = 2 };


class CNavArea;

struct NavConnect
{
	union
	{
		unsigned int id{ 0 };
		CNavArea *area;
	};

	mutable float length{ 0.0f };

	bool operator==(const NavConnect &other) const
	{
		return (area == other.area);
	}
};

union NavLadderConnect
{
	unsigned int id{ 0 };
	CNavLadder *ladder;

	bool operator==(const NavLadderConnect &other) const
	{
		return (ladder == other.ladder) ? true : false;
	}
};

struct SpotOrder
{
	float t{ 0.0f }; // parametric distance along ray where this spot first has LOS to our path

	union
	{
		HidingSpot *spot{ nullptr }; // the spot to look at
		unsigned int id; // spot ID for save/load
	};
};

struct SpotEncounter
{
	NavConnect from{};
	NavDirType fromDir{ NavDirType::NUM_DIRECTIONS };
	NavConnect to{};
	NavDirType toDir{ NavDirType::NUM_DIRECTIONS };
	Ray path{}; // the path segment
	std::vector<SpotOrder> spots; // list of spots to look at, in order of occurrence
};

struct AreaBindInfo	// for pointer loading and binding
{
	union
	{
		CNavArea *area{ nullptr };
		unsigned int id;
	};

	unsigned char attributes;				// VisibilityType

	bool operator==(const AreaBindInfo &other) const
	{
		return (area == other.area);
	}
};

class CNavArea
{
	// This should be private but this makes things a whole lot easier
public:

	unsigned int m_id{ 0 };

	Vector3 m_nwCorner{ 0.0f, 0.0f, 0.0f }; // North-west corner
	Vector3 m_seCorner{ 0.0f, 0.0f, 0.0f }; // South-east corner

	float m_invDxCorners{ 0.0f }; // TODO: What is this?
	float m_invDzCorners{ 0.0f }; // TODO: What is this?

	float m_neY{ 0.0f }; // Height of the north-east corner
	float m_swY{ 0.0f }; // Height of the south-west corner

	Vector3 m_center{ 0.0f, 0.0f, 0.0f }; // Center

	int m_attributeFlags{ 0 }; // Flags for this area, see NavAttributeType

	std::vector<NavConnect> m_connect; // Connected areas for each direction
	std::vector<NavLadderConnect> m_ladder[CNavLadder::NUM_LADDER_DIRECTIONS]; // Connected ladders

	unsigned int m_visibleAreaCount{ 0 }; // Areas visible from this area

	float m_lightIntensity[NUM_CORNERS]; // 0.0 -> 1.0

	unsigned int m_uiVisibleAreaCount{ 0 };

	AreaBindInfo m_inheritVisibilityFrom;

	std::vector<AreaBindInfo> m_potentiallyVisibleAreas;

	std::vector<HidingSpot> m_hidingSpots;

	std::vector<SpotEncounter> m_spotEncounters;

	float m_earliestOccupyTime[MAX_NAV_TEAMS]; // Minimum time to reach this area from the teams spawn


public:
	// Calculates the height of the area at the given x, z coordinates
	// @return Height at the given point
	float CNavArea::GetY(const Vector3 &pos)
	{
		if (this->m_invDxCorners == 0.0f || this->m_invDzCorners == 0.0f)
			return m_neY;

		float u = (pos.x - m_nwCorner.x) * m_invDxCorners;
		float v = (pos.z - m_nwCorner.z) * m_invDzCorners;

		// clamp Z values to (x,y) volume

		u = u >= 0 ? u : 0;
		u = u >= 1 ? 1 : u;
		
		v = v >= 0 ? v : 0;
		v = v >= 1 ? 1 : v;

		float northY = m_nwCorner.z + u * (m_neY - m_nwCorner.z);
		float southY = m_swY + u * (m_seCorner.z - m_swY);

		return northY + v * (southY - northY);
	}

	// Calculates the height of the area at the given x, z coordinates
	// @return Height at the given point
	float CNavArea::GetY(const Vector3 &pos) const
	{
		return const_cast<CNavArea *>(this)->GetY(pos);
	}

	// Calculates the distance between the area and the given point
	// @return Non-squared distance
	float GetDistanceSquaredToPoint(const Vector3 &pos) const
	{
		if (pos.x < m_nwCorner.x)
		{
			if (pos.z < m_nwCorner.z)
			{
				// position is north-west of area
				return (m_nwCorner - pos).LengthSqr();
			}
			else if (pos.z > m_seCorner.z)
			{
				// position is south-west of area
				Vector3 d;
				d.x = m_nwCorner.x - pos.x;
				d.z = m_seCorner.y - pos.z;
				d.y = m_swY - pos.y;
				return d.LengthSqr();
			}
			else
			{
				// position is west of area
				float d = m_nwCorner.x - pos.x;
				return d * d;
			}
		}
		else if (pos.x > m_seCorner.x)
		{
			if (pos.z < m_nwCorner.z)
			{
				// position is north-east of area
				Vector3 d;
				d.x = m_seCorner.x - pos.x;
				d.z = m_nwCorner.y - pos.z;
				d.y = m_neY - pos.y;
				return d.LengthSqr();
			}
			else if (pos.z > m_seCorner.z)
			{
				// position is south-east of area
				return (m_seCorner - pos).LengthSqr();
			}
			else
			{
				// position is east of area
				float d = pos.x - m_seCorner.x;
				return d * d;
			}
		}
		else if (pos.z < m_nwCorner.z)
		{
			// position is north of area
			float d = m_nwCorner.z - pos.z;
			return d * d;
		}
		else if (pos.z > m_seCorner.z)
		{
			// position is south of area
			float d = pos.z - m_seCorner.z;
			return d * d;
		}
		else
		{
			// position is inside of 2D extent of area - find delta Z
			float y = this->GetY(pos);
			float d = y - pos.y;
			return d * d;
		}
	}

	// Check if the given point is overlapping the area
	// @return True if 'pos' is within 2D extents of area.
	bool IsOverlapping(const Vector3 &vecPos, float flTolerance) const
	{
		if (vecPos.x + flTolerance < this->m_nwCorner.x)
		{
			return false;
		}

		if (vecPos.x - flTolerance > this->m_seCorner.x)
		{
			return false;
		}

		if (vecPos.z + flTolerance < this->m_nwCorner.z)
		{
			return false;
		}

		if (vecPos.z - flTolerance > this->m_seCorner.z)
		{
			return false;
		}

		return true;
	}

	// Calculates whether or not the given point is inside the area
	// @return True if the point is inside the area
	bool Contains(const Vector3 &vecPoint) const
	{
		if (!this->IsOverlapping(vecPoint, 0))
		{
			return false;
		}


		if ((this->GetY(vecPoint) - 18.0f) > vecPoint.y)
		{
			return false;
		}

		return true;
	}

	// Loads the area from a file stream
	// @return True on success
	bool LoadFromFile(std::ifstream &ifs)
	{
		ifs.read((char *) &this->m_id, sizeof(this->m_id));
		ifs.read((char *) &this->m_attributeFlags, sizeof(this->m_attributeFlags));
		ifs.read((char *) &this->m_nwCorner, sizeof(this->m_nwCorner));
		ifs.read((char *) &this->m_seCorner, sizeof(this->m_seCorner));

		this->m_center[0] = (this->m_nwCorner[0] + this->m_seCorner[0]) / 2.0f;
		this->m_center[1] = (this->m_nwCorner[1] + this->m_seCorner[1]) / 2.0f;
		this->m_center[2] = (this->m_nwCorner[2] + this->m_seCorner[2]) / 2.0f;

		if ((m_seCorner.x - m_nwCorner.x) > 0.0f && (m_seCorner.y - m_nwCorner.y) > 0.0f)
		{
			m_invDxCorners = 1.0f / (m_seCorner.x - m_nwCorner.x);
			m_invDzCorners = 1.0f / (m_seCorner.z - m_nwCorner.z);
		}
		else
		{
			m_invDxCorners = m_invDzCorners = 0.0f;
		}

		ifs.read((char *) &this->m_neY, sizeof(this->m_neY));
		ifs.read((char *) &this->m_swY, sizeof(this->m_swY));

		for (size_t s{ 0 }; s < NavDirType::NUM_DIRECTIONS; ++s)
		{
			// Number of connections in the current direction
			unsigned int uiCount{ 0 };
			ifs.read((char *)&uiCount, sizeof(uiCount));

			for (unsigned int ui{ 0 }; ui < uiCount; ++ui)
			{
				NavConnect nc{};

				ifs.read((char *)&nc.id, sizeof(nc.id));

				if (nc.id == this->m_id)
				{
					continue;
				}

				this->m_connect.push_back(nc);
			}
		}

		unsigned char hidingSpotCount{ (unsigned char)0x00 };
		ifs.read((char *)&hidingSpotCount, sizeof(hidingSpotCount));

		for (unsigned char c{ (unsigned char)0x00 }; c < hidingSpotCount; ++c)
		{
			HidingSpot hs;

			ifs.read((char *)&hs.m_id, sizeof(hs.m_id));
			ifs.read((char *)&hs.m_pos, sizeof(hs.m_pos));
			ifs.read((char *)&hs.m_flags, sizeof(hs.m_flags));

			this->m_hidingSpots.push_back(hs);
		}

		unsigned int uiEncounterSpotCount{ 0 };
		ifs.read((char *)&uiEncounterSpotCount, sizeof(uiEncounterSpotCount));

		for (unsigned int ui{ 0 }; ui < uiEncounterSpotCount; ++ui)
		{
			SpotEncounter se;

			ifs.read((char *)&se.from.id, sizeof(se.from.id));
			ifs.read((char *)&se.fromDir, sizeof(unsigned char));

			ifs.read((char *)&se.to.id, sizeof(se.to.id));
			ifs.read((char *)&se.toDir, sizeof(unsigned char));

			// Spots along this path
			unsigned char spotCount{ (unsigned char)0x00 };
			ifs.read((char *)&spotCount, sizeof(spotCount));

			for (unsigned char c{ (unsigned char)0x00 }; c < spotCount; ++c)
			{
				SpotOrder order{};

				ifs.read((char *)&order.id, sizeof(order.id));
				ifs.read((char *)&order.t, sizeof(unsigned char));

				se.spots.push_back(order);
			}

			this->m_spotEncounters.push_back(se);
		}

		// PlaceDirectory::IndexType entry = fileBuffer.GetUnsignedShort();
		unsigned short entry{ 0 };
		ifs.read((char *)&entry, sizeof(entry));

		for (size_t s{ 0 }; s < CNavLadder::NUM_LADDER_DIRECTIONS; ++s)
		{
			unsigned int uiCount{ 0 };
			ifs.read((char *)&uiCount, sizeof(uiCount));

			for (unsigned int ui{ 0 }; ui < uiCount; ++ui)
			{
				bool bSkip{ false };
				NavLadderConnect connect{};

				ifs.read((char *)&connect.id, sizeof(connect.id));

				for (const NavLadderConnect &ladder : this->m_ladder[s])
				{
					if (ladder.id == connect.id)
					{
						bSkip = true;
						break;
					}
				}

				if (bSkip)
				{
					continue;
				}

				this->m_ladder[s].push_back(connect);
			}
		}

		for (size_t s{ 0 }; s < MAX_NAV_TEAMS; ++s)
		{
			ifs.read((char *) &this->m_earliestOccupyTime[s], sizeof(this->m_earliestOccupyTime[s]));
		}

		for (size_t s{ 0 }; s < NUM_CORNERS; ++s)
		{
			ifs.read((char *) &this->m_lightIntensity[s], sizeof(this->m_lightIntensity[s]));
		}

		ifs.read((char *) &this->m_uiVisibleAreaCount, sizeof(this->m_uiVisibleAreaCount));

		for (unsigned int ui{ 0 }; ui < this->m_uiVisibleAreaCount; ++ui)
		{
			AreaBindInfo info;

			ifs.read((char *)&info.id, sizeof(info.id));
			ifs.read((char *)&info.attributes, sizeof(info.attributes));

			this->m_potentiallyVisibleAreas.push_back(info);
		}

		ifs.read((char *) &this->m_inheritVisibilityFrom.id, sizeof(this->m_inheritVisibilityFrom.id));

		unsigned char unknownCount{ (unsigned char)0x00 };
		ifs.read((char *)&unknownCount, sizeof(unknownCount));

		for (unsigned char c{ (unsigned char)0x00 }; c < unknownCount; ++c)
		{
			unsigned char unknown[0x0E];
			ifs.read((char *)unknown, 0x0E);
		}

		return true;
	}


	// Default constructor
	CNavArea()
	{

	}

	// Constructor
	CNavArea(std::ifstream &ifs)
	{
		this->LoadFromFile(ifs);
	}
};
