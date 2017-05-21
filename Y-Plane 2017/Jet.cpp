#include "pch.h"
#include "Jet.h"
#include "Simulation.h"
#include "Utils.h"

using namespace std;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Numerics;
using namespace Microsoft::Graphics::Canvas::Geometry;

#define JET_RADIUS 36;
#define JET_SPEED 10
#define JET_COLOR Colors::White


Jet::Jet() :Plane()
{
	radius = JET_RADIUS;
	speed = JET_SPEED;
	color = JET_COLOR;
}

void Jet::draw()
{
	Plane::draw();
	CanvasDrawingSession ^session = simulation->render_target->CreateDrawingSession();
	/*session->FillCircle(center_x, center_y, radius, JET_COLOR);
	session->DrawCircle(center_x, center_y, radius, Colors::Red);
	session->DrawCircle(center_x, center_y, 0.5*radius, Colors::Red);
	session->FillCircle(center_x, center_y, 0.2*radius, Colors::Red);
	session->DrawLine(center_x, center_y - radius, center_x, center_y + radius, Colors::Red);
	session->DrawLine(center_x-radius, center_y, center_x+radius, center_y, Colors::Red);*/
	Platform::Array<float2>^ poly = ref new Platform::Array<float2>(3);
	// Wings
	poly[0].x = center_x;
	poly[0].y = center_y - 0.5*radius;
	poly[1].x = center_x - radius;
	poly[1].y = center_y + 0.5*radius;
	poly[2].x = center_x + radius;
	poly[2].y = center_y + 0.5*radius;
	session->FillGeometry(CanvasGeometry::CreatePolygon(session, poly), Colors::WhiteSmoke);
	// Body
	// part 1
	poly[0].x = center_x;
	poly[0].y = center_y - radius;
	poly[1].x = center_x - 0.5*radius;
	poly[1].y = center_y + radius;
	poly[2].x = center_x + 0.5*radius;
	poly[2].y = center_y + radius;
	session->FillGeometry(CanvasGeometry::CreatePolygon(session, poly), Colors::White);
	// part 2
	poly[1].y = center_y + 0.5*radius;
	poly[2].y = center_y + 0.5*radius;
	session->FillGeometry(CanvasGeometry::CreatePolygon(session, poly), Colors::AntiqueWhite);
	// Cockpit
	poly[0].x = center_x;
	poly[0].y = center_y - 0.4*radius;
	poly[1].x = center_x + 0.2*radius;
	poly[1].y = center_y + 0.2*radius;
	poly[2].x = center_x - 0.2*radius;
	poly[2].y = center_y + 0.2*radius;
	session->FillGeometry(CanvasGeometry::CreatePolygon(session, poly), Colors::Cyan);
	// number
	session->DrawText(id.ToString(), center_x-10,center_y+radius/3, Colors::Red);
}