#pragma once
class keyBindAction
{
public:
	keyBindAction();
	bool act();
	bool undo();
	~keyBindAction();
};

