#include "texturing/horizontalGradientTexture.h"
#include "logging/logsStruct.h"
#include "texturing/rendererWindow.h"
#include "customTypes/positionTypes.h"

sdl2::HorizontalGradient::HorizontalGradient(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, unsigned startValue, unsigned maxValue, const SDL_Rect& newRect, 
										const SDL_Color& leftColor, const SDL_Color& rightColor, bool fromLeftCount):
	gradient{ logs, rndWnd, newRect, leftColor, rightColor, GradientTextureOnX },
	boundingBox{newRect},
	selectRect{0, 0, newRect.w, newRect.h},
	destRect{newRect},
	counterMaxValue{ static_cast<int>(maxValue) },
	currentValue{ static_cast<int>( startValue ) },
	fromLeftToRightGrad{fromLeftCount},
	isLoadingPerfect{true}
{
	setNewCounterValue(static_cast<int>(startValue) );
}

sdl2::HorizontalGradient::operator bool() const
{
	return wasLoadingPerfect();
}

bool sdl2::HorizontalGradient::wasLoadingPerfect() const
{
	if( gradient )
		return true;
	else
		return false;
}

void sdl2::HorizontalGradient::draw(sdl2::RendererWindow& rndWnd) const
{
	gradient.sprite.drawWithTwoRect(rndWnd, selectRect, destRect);
}

void sdl2::HorizontalGradient::setNewCounterValue(int newValue)
{
	currentValue = newValue;
	
	updateGradient();
}

void sdl2::HorizontalGradient::setMaxValue(int newMaxValue)
{
	counterMaxValue = newMaxValue;
	
	updateGradient();
}

int sdl2::HorizontalGradient::getMaxValue() const
{
	return counterMaxValue;
}

int sdl2::HorizontalGradient::getCurrentValue() const
{
	return currentValue;
}

void sdl2::HorizontalGradient::setWithLeftAsOrigin()
{
	selectRect.w = currentValue * boundingBox.w / counterMaxValue;
	destRect.w = selectRect.w;
}

void sdl2::HorizontalGradient::setWithRightAsOrigin()
{
	selectRect.x = boundingBox.w - currentValue * boundingBox.w / counterMaxValue;
	selectRect.w = currentValue * boundingBox.w / counterMaxValue;
	
	destRect.x = boundingBox.x + boundingBox.w - selectRect.w;
	destRect.w = selectRect.w;
}

void sdl2::HorizontalGradient::updateGradient()
{
	if( fromLeftToRightGrad )
		setWithLeftAsOrigin();
	else
		setWithRightAsOrigin();
}