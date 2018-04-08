#include "UI_Element.h"

iPoint UI_Element::getGlobalPosition()
{
	iPoint ret = local_position;

	if (parent != nullptr)
		ret += parent->getGlobalPosition();

	return ret;
}
