#include "pch.h"
#include "Jet.h"
#include "Simulation.h"

#define JET_RADIUS 24;
#define JET_SPEED 10
#define JET_COLOR Colors::White

Jet::Jet():Plane()
{
	radius = JET_RADIUS;
	speed = JET_SPEED;
	color = JET_COLOR;
}

void Jet::draw()
{
	CanvasDrawingSession ^session = simulation->render_target->CreateDrawingSession();
	session->FillCircle(center_x, center_y, radius, JET_COLOR);
	session->DrawCircle(center_x, center_y, radius, Colors::Red);
	session->DrawCircle(center_x, center_y, 0.5*radius, Colors::Red);
	session->FillCircle(center_x, center_y, 0.2*radius, Colors::Red);
	session->DrawLine(center_x, center_y - radius, center_x, center_y + radius, Colors::Red);
	session->DrawLine(center_x-radius, center_y, center_x+radius, center_y, Colors::Red);
}
