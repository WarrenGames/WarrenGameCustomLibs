#ifndef GAME_COMMON_COMPUTER_PLAYER_AFFINE_FUNCTION_COLLISION_TESTS_H
#define GAME_COMMON_COMPUTER_PLAYER_AFFINE_FUNCTION_COLLISION_TESTS_H

struct AffineFunction;

double getXCollisionCoords(const AffineFunction& func1, const AffineFunction& func2);

double getYCollisionCoords(const AffineFunction& func1, const AffineFunction& func2);

#endif //GAME_COMMON_COMPUTER_PLAYER_AFFINE_FUNCTION_COLLISION_TESTS_H