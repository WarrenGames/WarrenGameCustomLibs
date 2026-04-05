#ifndef GENERIC_LIB_HIGH_RESOLUTION_TIME_H
#define GENERIC_LIB_HIGH_RESOLUTION_TIME_H

#include <chrono>

class HighResolutionTimeDelay
{
private:
	std::chrono::high_resolution_clock::time_point precedent;
	
public:
	HighResolutionTimeDelay();
	~HighResolutionTimeDelay() = default;
	HighResolutionTimeDelay( const HighResolutionTimeDelay& ) = default;
	HighResolutionTimeDelay& operator= ( const HighResolutionTimeDelay& ) = default;
	HighResolutionTimeDelay( HighResolutionTimeDelay&& ) = default;
	HighResolutionTimeDelay& operator= ( HighResolutionTimeDelay&& ) = default;
	
	void joinTimePoints();
	bool hasTimeElapsed(std::chrono::microseconds elapsedTime) const;
	std::chrono::duration<long double, std::micro> getCurrentElapsedMicrosecondsTime() const;
	std::chrono::microseconds getIntCurrentElapsedMicrosecondsTime() const;
};

#endif //GENERIC_LIB_HIGH_RESOLUTION_TIME_H