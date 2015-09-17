#ifndef BUILD_GEOMETRIES_H_INCLUDED
#define BUILD_GEOMETRIES_H_INCLUDED

class TGeometry;

struct TGearInfo
{
	int m_iTeethCount;
	float m_fTeethDepth;
};

struct TClockInfo
{
	int m_iHours;
	int m_iMinutes;
	int m_iAngleX;
};

struct TChessTowerInfo
{
	int m_iSegments;
	float m_fRadius;
	float m_fHeight;
};

void BuildBox(TGeometry & tGeometry);
void BuildGear(TGeometry & tGeometry, const TGearInfo & tInfo);
void BuildClock(TGeometry & tGeometry, const TClockInfo & tInfo);
void BuildChessTower(TGeometry & tGeometry, const TChessTowerInfo & tInfo);

#endif
