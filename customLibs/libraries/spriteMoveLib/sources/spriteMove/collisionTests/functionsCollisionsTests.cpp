#include "spriteMove/collisionTests/functionsCollisionsTests.h"
#include "spriteMove/collisionTests/affineFunction.h"
#include <cassert>

double getXCollisionCoords(const AffineFunction& func1, const AffineFunction& func2)
{
	assert( func1.dirCoef != func2.dirCoef );
	return ( func2.originCoord - func1.originCoord ) / ( func1.dirCoef - func2.dirCoef );
}

double getYCollisionCoords(const AffineFunction& func1, const AffineFunction& func2)
{
	return func1.dirCoef * getXCollisionCoords(func1, func2) + func1.originCoord;
}