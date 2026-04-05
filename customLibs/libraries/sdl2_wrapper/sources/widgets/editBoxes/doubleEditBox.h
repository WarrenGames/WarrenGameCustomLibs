#ifndef SDL2_WRAPPER_WIDGETS_DOUBLE_EDIT_BOX_H
#define SDL2_WRAPPER_WIDGETS_DOUBLE_EDIT_BOX_H

#include "widgets/editBoxes/subObjects/boxEvents.h"
#include "widgets/editBoxes/subObjects/boxRectDisplay.h"
#include "widgets/editBoxes/subObjects/cursorDrawing.h"
#include "widgets/editBoxes/subObjects/boxContentDisplay.h"
#include <string>
#include <functional>

struct AppLogFiles;
namespace sdl2{ class RendererWindow; }
struct SDL_Rect;

class DoubleEditBox
{
private:
	BoxEvents events;
	BoxRectDisplaying boxRect;
	BoxCursor cursor;
	BoxContentDisplay content;
	
	unsigned strMaxSize;
	std::string stringOfDouble;
	std::reference_wrapper<double> doubleRef;
	bool hasStringChanged;

public:
	explicit DoubleEditBox(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const SDL_Rect& boxSize, int fontSize, double& refValue, unsigned stringMaxSize);
	~DoubleEditBox() = default;
	DoubleEditBox( const DoubleEditBox& ) = delete;
	DoubleEditBox& operator= ( const DoubleEditBox& ) = delete;
	DoubleEditBox( DoubleEditBox&& ) = default;
	DoubleEditBox& operator= ( DoubleEditBox&& ) = default;
	
	void drawBoxWithoutFocus(sdl2::RendererWindow& rndWnd) const;
	void catchUserFocus(AppLogFiles& logs, sdl2::RendererWindow& rndWnd, const Offset& mousePos, bool mouseButton);
	double getCurrentValue() const;
	void changeReference(AppLogFiles& logs, double& newRef, sdl2::RendererWindow& rndWnd);
	bool isMouseOverBox(const Offset& mousePos) const;
	void updateGraphics(AppLogFiles& logs, sdl2::RendererWindow& rndWnd);

private:
	void addFigure(const std::string& figure);
	void deleteLastFigure();
	void recordEntry(bool& quitEdition);
	void appendNewFigureToDoubleString();
	void appendMinusToDoubleString();
	void appendDotToString();
	void quitDoubleEdition(bool& quitEdition);
	void drawEverything(sdl2::RendererWindow& rndWnd);
	void updateString();
};

#endif //SDL2_WRAPPER_WIDGETS_DOUBLE_EDIT_BOX_H