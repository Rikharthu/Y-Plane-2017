#pragma once
#include "Plane.h"

#define PI 3.1415926535897932385

int random(int low, int high);

Platform::String ^ toPlatformString(std::string inputString);

double disperse(double direction, double delta);