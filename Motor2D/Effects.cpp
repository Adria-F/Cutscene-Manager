#include "Effects.h"
#include "Unit.h"


void DamageBuff::Apply() { unit->attack += buff; }
void DamageBuff::Remove() { unit->attack -= buff; }