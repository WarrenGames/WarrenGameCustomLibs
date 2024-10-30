#include "texturing/verticalGradientTexture.h"
#include "logging/logsStruct.h"
#include "texturing/rendererWindow.h"
#include "customTypes/positionTypes.h"

sdl2::VerticalGradient::VerticalGradient(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, unsigned startValue, unsigned maxValue, const SDL_Rect& newRect, const SDL_Color& topCol, 
									const SDL_Color& bottomCol, bool fromBottom):
	gradient{logs, rndWnd, newRect, topCol, bottomCol, GradientTextureOnY},
	boundingBox{newRect},
	selectRect{0, 0, newRect.w, newRect.h},
	destRect{newRect},
	counterMaxValue{ static_cast<int>(maxValue) },
	currentValue{ static_cast<int>( startValue ) },
	fromBottomToTopGrad{fromBottom}
{
	setNewCounterValue(static_cast<int>(startValue) );
}

sdl2::VerticalGradient::operator bool () const
{
	return wasLoadingPerfect();
}

bool sdl2::VerticalGradient::wasLoadingPerfect() const
{
	if( gradient )
		return true;
	else
		return false;
}

void sdl2::VerticalGradient::draw(sdl2::RendererWindow& rndWnd) const
{
	gradient.sprite.drawWithTwoRect(rndWnd, selectRect, destRect);
}

void sdl2::VerticalGradient::setNewCounterValue(int newValue)
{
	currentValue = newValue;
	
	updateGradient();
}

void sdl2::VerticalGradient::setMaxValue(int newMaxValue)
{
	counterMaxValue = newMaxValue;
	
	updateGradient();
}

int sdl2::VerticalGradient::getMaxValue() const
{
	return counterMaxValue;
}

int sdl2::VerticalGradient::getCurrentValue() const
{
	return currentValue;
}

void sdl2::VerticalGradient::setWithBottomAsOrigin()
{
	selectRect.y = boundingBox.h - currentValue * boundingBox.h / counterMaxValue;
	selectRect.h = currentValue * boundingBox.h / counterMaxValue;
	
	destRect.y = boundingBox.y + boundingBox.h - selectRect.h;
	destRect.h = selectRect.h;
}

void sdl2::VerticalGradient::setWithTopAsOrigin()
{
	selectRect.h = currentValue * boundingBox.h / counterMaxValue;
	
	destRect.h = selectRect.h;
}

void sdl2::VerticalGradient::updateGradient()
{
	if( fromBottomToTopGrad )
		setWithBottomAsOrigin();
	else
		setWithTopAsOrigin();
}