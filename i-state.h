#pragma once

#include "config.h"

class IState
{
public:
	virtual void begin() = 0;

	virtual void update() = 0;
};