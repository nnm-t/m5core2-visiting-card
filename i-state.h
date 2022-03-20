#pragma once

#include "config.h"
#include "settings.h"

class IState
{
public:
	virtual void begin(Settings* settings) = 0;

	virtual void update() = 0;
};