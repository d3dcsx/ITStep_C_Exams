#pragma once

#include "General.h"
#include "Date.h"

struct Task
{
	string name;
	bool priority;
	string description;
	Date dueDate;

	int initialIndex;
};
