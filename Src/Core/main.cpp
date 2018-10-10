#include <iostream>
#include "Vi.h"

using namespace Vi;

int main()
{
	ViAl* v = new ViAl();
	v->Start();
	delete v;
}