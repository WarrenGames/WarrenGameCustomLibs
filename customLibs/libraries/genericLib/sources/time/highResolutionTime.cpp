#include "time/highResolutionTime.h"

HighResolutionTimeDelay::HighResolutionTimeDelay():
	precedent{ std::chrono::high_resolution_clock::now() }
{
	
}

void HighResolutionTimeDelay::joinTimePoints()
{
	precedent = std::chrono::high_resolution_clock::now();
}

bool HighResolutionTimeDelay::hasTimeElapsed(std::chrono::microseconds elapsedTime) const
{
	return std::chrono::high_resolution_clock::now() - precedent >= elapsedTime;
}

std::chrono::duration<long double, std::micro> HighResolutionTimeDelay::getCurrentElapsedMicrosecondsTime() const
{
	return std::chrono::high_resolution_clock::now() - precedent;
}

std::chrono::microseconds HighResolutionTimeDelay::getIntCurrentElapsedMicrosecondsTime() const
{
	return std::chrono::duration_cast< std::chrono::microseconds >( std::chrono::high_resolution_clock::now() - precedent );
}