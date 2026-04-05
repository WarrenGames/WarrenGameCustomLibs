#ifndef GAME_COMMON_COMPUTER_PLAYER_AFFINE_FUNCTION_H
#define GAME_COMMON_COMPUTER_PLAYER_AFFINE_FUNCTION_H

namespace spriteMove{ class ObjectMoving; }

struct AffineFunction
{
	double dirCoef;
	double originCoord;
	double xCoord;//Only valid if function is ill formed, i.e. equation is 'x = n'
	bool isFunctionValid;//if equal to false, means the function's form is 'x = n' instead of 'y = ax + b'
	
	AffineFunction();
	AffineFunction(const spriteMove::ObjectMoving& object);
	AffineFunction(double newDirCoef, double newOriginCoord);
	~AffineFunction() = default;
	AffineFunction( const AffineFunction& ) = default;
	AffineFunction& operator= ( const AffineFunction& ) = default;
	
	void computeData(const spriteMove::ObjectMoving& object);
	
	bool operator== ( const AffineFunction& toCompare ) const;
};

#endif //GAME_COMMON_COMPUTER_PLAYER_AFFINE_FUNCTION_H