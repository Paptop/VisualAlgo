#include <iostream>
#include "Vi.h"

#include "Src/Vi/Math/Vector2.h"
using namespace Vi;

int main()
{
	ViAl* v = new ViAl();
	v->Start();
	delete v;
}