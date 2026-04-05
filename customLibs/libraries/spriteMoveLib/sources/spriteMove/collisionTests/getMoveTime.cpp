#include "spriteMove/collisionTests/getMoveTime.h"
#include "customTypes/positionTypes.h"
#include <cassert>
#include <cmath>

long double getMoveIntervalMicrosecTime(int axisStartCoord, int axisEndCoord, long double speed, long int microsecMoveDelay)
{
	assert( microsecMoveDelay > 0 );
	assert( speed > 0 );
	return std::abs( axisEndCoord - axisStartCoord ) * microsecMoveDelay / speed;
}

long double getMoveIntervalMicrosecTime(const Offset& startCoord, const Offset& endCoord, long double speed, long int microsecMoveDelay)
{
	assert( microsecMoveDelay > 0 );
	assert( speed > 0 );
	return std::sqrt( ( endCoord.x - startCoord.x ) * ( endCoord.x - startCoord.x ) 
					+ ( endCoord.y - startCoord.y ) * ( endCoord.y - startCoord.y ) ) 
				 / speed * microsecMoveDelay;
}