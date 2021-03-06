typedef float matrix3x4[3][4];
typedef float matrix4x4[4][4];

class CCollisionProperty
{
public:
	Vector3 vecMins;
	Vector3 vecMaxs;
	char SolidType;
	short SolidFlags;
	char triggerBloat;
};