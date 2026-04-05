#ifndef GENERIC_LIB_USUAL_TYPES_H
#define GENERIC_LIB_USUAL_TYPES_H

struct AccurCoords;

struct Offset
{
	int x;
	int y;
	
	Offset();
	Offset(const AccurCoords& coords);
	constexpr Offset(int new_x, int new_y):x{new_x},y{new_y}{}
	Offset& operator*(double multi);
	
	Offset( const Offset& ) = default;
	Offset& operator= ( const Offset& ) = default;
	Offset( Offset&& ) = default;
	Offset& operator= ( Offset&& ) = default;
};

Offset combineOffset(const Offset& offset1, const Offset& offset2);

Offset computeDiff(const Offset& origin, const Offset& direction);

bool areOffsetCoordinatesTheSame(const Offset& coord1, const Offset& coord2);

struct AccurCoords
{
	double x;
	double y;
	
	explicit AccurCoords();
	explicit AccurCoords(double new_x, double new_y);
	AccurCoords& operator= ( const Offset& offset );
	explicit AccurCoords( const Offset& offset);
	
	AccurCoords( const AccurCoords& ) = default;
	AccurCoords& operator= ( const AccurCoords& ) = default;
	AccurCoords( AccurCoords&& ) = default;
	AccurCoords& operator= ( AccurCoords&& ) = default;
};

#endif //GENERIC_LIB_USUAL_TYPES_H