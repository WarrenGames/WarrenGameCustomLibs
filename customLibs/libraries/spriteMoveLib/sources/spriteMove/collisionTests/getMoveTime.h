#ifndef GAME_COMMON_GET_MOVE_TIME_H
#define GAME_COMMON_GET_MOVE_TIME_H

struct Offset;

//For a same axis coordinates
long double getMoveIntervalMicrosecTime(int axisStartCoord, int axisEndCoord, long double speed, long int microsecMoveDelay);

//For 2D coordinates
long double getMoveIntervalMicrosecTime(const Offset& startCoord, const Offset& endCoord, long double speed, long int microsecMoveDelay);

#endif //GAME_COMMON_GET_MOVE_TIME_H