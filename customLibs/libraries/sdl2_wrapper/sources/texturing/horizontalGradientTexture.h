#ifndef HORIZONTAL_GRADIENT_TEXTURE_H
#define HORIZONTAL_GRADIENT_TEXTURE_H

/*
	Caveats when using this class:
		- If you modify the currentValue with the function 'void setNewCounterValue(int newValue);',
			you must ensure the 'counterMaxValue' integer is strictly superior to 0 with the function
			'int getMaxValue() const;' because there is divisions by 'counterMaxValue' in functions 
			that updates the gradient aspect.
		- If you modify the counter max value with the function 'void setMaxValue(int newMaxValue);',
			you must ensure that the only parameter is strictly superior to 0 or that you don't use 
			the class instance afterwards.
		- In general, the max value should never be equal to 0, because that brings too much problems.
		- If you ever want to modify the maxValue with function 'void setMaxValue(int newMaxValue);',
			you must ensure the 'currentValue' integer, through 'int getCurrentValue() const;' function 
			is inferior or equal to the max value.

*/

#include "texturing/texturesCombo.h"

struct AppLogFiles;

namespace sdl2{
	class RendererWindow;

class HorizontalGradient
{
private:
	TextureCombo gradient;
	SDL_Rect boundingBox;
	SDL_Rect selectRect;
	SDL_Rect destRect;
	int counterMaxValue;
	int currentValue;
	bool fromLeftToRightGrad;
	bool isLoadingPerfect;
	
public:
	HorizontalGradient(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, unsigned startValue, unsigned maxValue, const SDL_Rect& newRect, const SDL_Color& leftColor, 
						const SDL_Color& rightColor, bool fromLeftCount);
	~HorizontalGradient() = default;
	HorizontalGradient( const HorizontalGradient& ) = delete;
	HorizontalGradient& operator= ( const HorizontalGradient& ) = delete;
	HorizontalGradient( HorizontalGradient&& ) = default;
	HorizontalGradient& operator= ( HorizontalGradient&& ) = default;
	
	operator bool () const;
	bool wasLoadingPerfect() const;
	void draw(sdl2::RendererWindow& rndWnd) const;
	void setNewCounterValue(int newValue);
	void setMaxValue(int newMaxValue);
	int getMaxValue() const;
	int getCurrentValue() const;
	
private:
	void setWithLeftAsOrigin();
	void setWithRightAsOrigin();
	void updateGradient();
};

}

#endif //HORIZONTAL_GRADIENT_TEXTURE_H