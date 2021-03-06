#pragma once

struct Ray
{
	Vector3 from{ 0.0f, 0.0f, 0.0f };
	Vector3 to{ 0.0f, 0.0f, 0.0f };
};

enum NavAttributeType
{
	NAV_MESH_INVALID = 0,
	NAV_MESH_CROUCH = 0x0000001, // must crouch to use this node/area
	NAV_MESH_JUMP = 0x0000002, // must jump to traverse this area (only used during generation)
	NAV_MESH_PRECISE = 0x0000004, // do not adjust for obstacles, just move along area
	NAV_MESH_NO_JUMP = 0x0000008, // inhibit discontinuity jumping
	NAV_MESH_STOP = 0x0000010, // must stop when entering this area
	NAV_MESH_RUN = 0x0000020, // must run to traverse this area
	NAV_MESH_WALK = 0x0000040, // must walk to traverse this area
	NAV_MESH_AVOID = 0x0000080, // avoid this area unless alternatives are too dangerous
	NAV_MESH_TRANSIENT = 0x0000100, // area may become blocked, and should be periodically checked
	NAV_MESH_DONT_HIDE = 0x0000200, // area should not be considered for hiding spot generation
	NAV_MESH_STAND = 0x0000400, // bots hiding in this area should stand
	NAV_MESH_NO_HOSTAGES = 0x0000800, // hostages shouldn't use this area
	NAV_MESH_STAIRS = 0x0001000, // this area represents stairs, do not attempt to climb or jump them - just walk up
	NAV_MESH_NO_MERGE = 0x0002000, // don't merge this area with adjacent areas
	NAV_MESH_OBSTACLE_TOP = 0x0004000, // this nav area is the climb point on the tip of an obstacle
	NAV_MESH_CLIFF = 0x0008000, // this nav area is adjacent to a drop of at least CliffHeight

	NAV_MESH_FIRST_CUSTOM = 0x00010000, // apps may define custom app-specific bits starting with this value
	NAV_MESH_LAST_CUSTOM = 0x04000000, // apps must not define custom app-specific bits higher than with this value

	NAV_MESH_HAS_ELEVATOR = 0x40000000, // area is in an elevator's path
	NAV_MESH_NAV_BLOCKER = 0x80000000, // area is blocked by nav blocker ( Alas, needed to hijack a bit in the attributes to get within a cache line [7/24/2008 tom])
};

enum NavDirType
{
	NORTH = 0,
	EAST = 1,
	SOUTH = 2,
	WEST = 3,

	NUM_DIRECTIONS
};

enum NavCornerType
{
	NORTH_WEST = 0,
	NORTH_EAST = 1,
	SOUTH_EAST = 2,
	SOUTH_WEST = 3,

	NUM_CORNERS
};
