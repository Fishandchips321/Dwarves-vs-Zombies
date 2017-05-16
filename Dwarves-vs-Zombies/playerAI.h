#pragma once
#include "AIPackage.h"
class playerAI :
	public AIPackage
{
public:
	playerAI();
	void update();
	void eventUpdate();
	void netUpdate();
	~playerAI();
};

