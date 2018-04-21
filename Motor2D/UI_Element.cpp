#include "UI_Element.h"

iPoint UI_Element::getGlobalPosition()
{
	iPoint ret = { (int)local_position.x, (int)local_position.y };

	if (parent != nullptr)
		ret += parent->getGlobalPosition();

	return ret;
}
