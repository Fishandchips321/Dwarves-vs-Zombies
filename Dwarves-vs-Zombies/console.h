#pragma once
#include "UIWindow.h"
#include "consoleController.h"
#include "imageService.h"

class console : public UIWindow
{
public:
	console();
	void update();
	void eventUpdate();
	void draw();
	~console();
private:
	std::ostringstream* Rcout;
	std::ostringstream* Rcerr;
	std::ostringstream* Rclog;
};

