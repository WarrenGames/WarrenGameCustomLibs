#include "widgets/editBoxes/doubleEditBox.h"
#include "logging/logsStruct.h"
#include "texturing/rendererWindow.h"
#include "customTypes/positionTypes.h"
#include "widgets/editBoxes/subObjects/editBoxes_consts.h"
#include <sstream>

DoubleEditBox::DoubleEditBox(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Rect& boxSize, int fontSize, double& refValue, unsigned stringMaxSize):
	events{},
	boxRect{logs, rndWnd, boxSize},
	cursor{logs, rndWnd, boxSize},
	content{logs, rndWnd, fontSize, std::to_string(refValue) },
	strMaxSize{stringMaxSize},
	doubleRef{std::ref(refValue)},
	hasStringChanged{true}
{
	updateGraphics(logs, rndWnd);
}

void DoubleEditBox::drawBoxWithoutFocus(sdl2::RendererWindow& rndWnd) const
{
	boxRect.drawOffWindow(rndWnd);
	content.drawCurrentValueWithoutFocus(rndWnd);
}

void DoubleEditBox::catchUserFocus(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const Offset& mousePos, bool mouseButton)
{
	if( mouseButton && isUserMouseInBox(boxRect.getMainRect(), mousePos ) )
	{
		bool quitEdition{false};
		while( false == quitEdition )
		{
			cursor.blinkCursor();
			events.updateEvents(quitEdition);
			appendNewFigureToDoubleString();
			appendDotToString();
			appendMinusToDoubleString();
			recordEntry(quitEdition);
			deleteLastFigure();
			quitDoubleEdition(quitEdition);
			content.makeTextTextureFromString(logs, rndWnd, stringOfDouble, hasStringChanged);
			drawEverything(rndWnd);
		}
		content.updateContentWhileLosingFocus(boxRect.getMainRect());
		events.resetAllKeys();
		events.setMouseLeftButtonToFalse();
	}
}

double DoubleEditBox::getCurrentValue() const
{
	return doubleRef;
}

void DoubleEditBox::changeReference(AppLogFiles& logs, double& newRef, sdl2::RendererWindow& rndWnd)
{
	doubleRef = std::ref( newRef );
	updateGraphics(logs, rndWnd);
}

bool DoubleEditBox::isMouseOverBox(const Offset& mousePos) const
{
	return boxRect.isOffsetInsideRect(mousePos);
}

void DoubleEditBox::updateGraphics(AppLogFiles& logs, sdl2::RendererWindow& rndWnd)
{
	updateString();
	content.makeTextTextureFromString(logs, rndWnd, stringOfDouble, hasStringChanged);
	content.updateContentWhileLosingFocus(boxRect.getMainRect());
}

void DoubleEditBox::addFigure(const std::string& figure)
{
	stringOfDouble += figure;
	hasStringChanged = true;
}

void DoubleEditBox::deleteLastFigure()
{
	if( events.getSpecificKey(BoxEventBackspace) && false == stringOfDouble.empty() )
	{
		stringOfDouble.pop_back();
		hasStringChanged = true;
		events.setSpecificKeyToFalse(BoxEventBackspace);
	}
}

void DoubleEditBox::recordEntry(bool& quitEdition)
{
	if( events.getSpecificKey(BoxEventReturn) && false == stringOfDouble.empty() && ! isOnlyMinusCharInString(stringOfDouble) )
	{
		quitEdition = true;
		hasStringChanged = true;
		std::istringstream valueStream{stringOfDouble};
		valueStream >> doubleRef;
		events.setSpecificKeyToFalse(BoxEventReturn);
	}
}

void DoubleEditBox::appendNewFigureToDoubleString()
{
	for( unsigned i{0} ; i < BoxEventMax ; ++i )
	{
		if( events.getNumbersState(i) && stringOfDouble.size() < BoxesCharSizeMax )
		{
			addFigure( std::to_string(i) );
			events.setNumberKeyToFalse(i);
		}
	}
}

void DoubleEditBox::appendMinusToDoubleString()
{
	if( stringOfDouble.empty() && events.getSpecificKey(BoxEventMinus) )
	{
		addFigure("-");
		events.setSpecificKeyToFalse(BoxEventMinus);
	}
}

void DoubleEditBox::appendDotToString()
{
	if( false == stringOfDouble.empty() && 
		( 
			( stringOfDouble[0] == '-' && stringOfDouble.size() >= 2 )
			|| ( stringOfDouble[0] >= '0' && stringOfDouble[0] <= '9' && stringOfDouble.size() >= 1 )
		)
		&& stringOfDouble.find('.') == std::string::npos
		&& events.getSpecificKey(BoxEventDot) )
	{
		stringOfDouble += '.';
		hasStringChanged = true;
		events.setSpecificKeyToFalse(BoxEventDot);
	}
}

void DoubleEditBox::quitDoubleEdition(bool& quitEdition)
{
	if( false == isOnlyMinusCharInString(stringOfDouble) && false == isOnlyDotCharInString(stringOfDouble) && false == stringOfDouble.empty() 
		&& ( ( false == isUserMouseInBox(boxRect.getMainRect(), events.getMousePosition() ) && events.getMouseLeftButtonState() ) || events.getSpecificKey(BoxEventEscape) ) )
	{
		quitEdition = true;
		events.setSpecificKeyToFalse(BoxEventEscape);
		events.setMouseLeftButtonToFalse();
	}
}

void DoubleEditBox::drawEverything(sdl2::RendererWindow& rndWnd)
{
	boxRect.drawActiveWindow(rndWnd);
	content.drawCurrentValueWithFocus(rndWnd, boxRect.getMainRect(), stringOfDouble );
	cursor.drawCursor(rndWnd, Offset{content.getContentRect().x + content.getContentRect().w, content.getContentRect().y + content.getContentRect().h / 2} );
	rndWnd.displayRenderer();
	SDL_Delay(10);
}

void DoubleEditBox::updateString()
{
	stringOfDouble = std::to_string(doubleRef);
	hasStringChanged = true;
	std::istringstream stream{stringOfDouble};
	stream >> doubleRef;
}