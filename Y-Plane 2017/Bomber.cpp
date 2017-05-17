#include "pch.h"
#include "Bomber.h"
#include "Simulation.h"

#define BOMBER_RADIUS 40;
#define BOMBER_SPEED 5;
#define BOMBER_COLOR Colors::ForestGreen;

Bomber::Bomber():Plane()
{
	radius = BOMBER_RADIUS;
	speed = BOMBER_SPEED;
	color = BOMBER_COLOR;
}

void Bomber::draw()
{
	CanvasDrawingSession ^session = simulation->render_target->CreateDrawingSession();
	session->FillRectangle(center_x-radius, center_y -radius, 2 * radius, 2 * radius, color);
	session->FillCircle(center_x, center_y, 0.85*radius, Colors::Yellow);
	session->FillCircle(center_x, center_y, 0.75*radius, Colors::Blue);
	session->FillCircle(center_x, center_y, 0.55 * radius, Colors::White);
	session->FillCircle(center_x, center_y, 0.3*radius, Colors::Red);
}
