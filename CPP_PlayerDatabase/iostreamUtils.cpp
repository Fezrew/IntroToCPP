#include "iostreamUtils.h"
#include <iostream>

using namespace std;

void cinClear()
{
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail()); // Clear pending input
}