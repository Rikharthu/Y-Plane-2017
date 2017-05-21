#include "pch.h"
#include "Ufo.h"
#include "Simulation.h"

#define UFO_RADIUS 36;
#define UFO_SPEED 4

Ufo::Ufo() :Plane()
{
	radius = UFO_RADIUS;
	speed = UFO_SPEED;
	diff = PI / 8;
}

void Ufo::draw()
{
	Plane::draw();
	CanvasDrawingSession ^session = simulation->render_target->CreateDrawingSession();
	session->FillCircle(center_x, center_y, radius, Colors::LimeGreen);
	session->FillCircle(center_x, center_y, 0.9*radius, Colors::SlateGray);
	session->FillCircle(center_x, center_y, 0.5*radius, Colors::LightGray);
	session->FillCircle(center_x, center_y, 0.4*radius, Colors::LimeGreen);
	session->DrawText(id.ToString(), center_x - 10, center_y-16, Colors::Lime);
}
