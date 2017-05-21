#include "pch.h"
#include "Bomber.h"
#include "Simulation.h"

using namespace std;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Numerics;
using namespace Microsoft::Graphics::Canvas::Geometry;

#define BOMBER_RADIUS 80;
#define BOMBER_SPEED 5;
#define BOMBER_COLOR Colors::ForestGreen;

Bomber::Bomber() :Plane()
{
	radius = BOMBER_RADIUS;
	speed = BOMBER_SPEED;
	diff = PI / 32;
	color = BOMBER_COLOR;
}

void Bomber::draw()
{
	Plane::draw();
	CanvasDrawingSession ^session = simulation->render_target->CreateDrawingSession();


	// Motors
	session->FillRectangle(center_x - 0.6*radius, center_y - 0.4*radius, 0.2*radius, 0.6*radius, Colors::DarkSlateGray);
	session->FillRectangle(center_x + 0.6*radius, center_y - 0.4*radius, -0.2*radius, 0.6*radius, Colors::DarkSlateGray);
	
	// Body
	Platform::Array<float2>^ poly = ref new Platform::Array<float2>(14);

	poly[0].x = center_x - 0.1*radius;
	poly[0].y = center_y - radius;

	poly[1].x = center_x - 0.2*radius;
	poly[1].y = center_y - 0.7*radius;

	poly[2].x = center_x - 0.2*radius;
	poly[2].y = center_y - 0.3*radius;

	poly[3].x = center_x - radius;
	poly[3].y = center_y - 0.1*radius;

	poly[4].x = center_x - radius;
	poly[4].y = center_y + 0.1*radius;

	poly[5].x = center_x - 0.2*radius;
	poly[5].y = center_y + 0.1*radius;

	poly[6].x = center_x - 0.1*radius;
	poly[6].y = center_y + radius;

	poly[7].x = center_x + 0.1*radius;
	poly[7].y = center_y + radius;

	poly[8].x = center_x + 0.2*radius;
	poly[8].y = center_y + 0.1*radius;

	poly[9].x = center_x + radius;
	poly[9].y = center_y + 0.1*radius;

	poly[10].x = center_x + radius;
	poly[10].y = center_y - 0.1*radius;

	poly[11].x = center_x + 0.2*radius;
	poly[11].y = center_y - 0.3* radius;

	poly[12].x = center_x + 0.2*radius;
	poly[12].y = center_y - 0.7* radius;

	poly[13].x = center_x + 0.1*radius;
	poly[13].y = center_y - radius;

	session->FillGeometry(CanvasGeometry::CreatePolygon(session, poly), Colors::Olive);

	// Tail 1
	poly = ref new Platform::Array<float2>(6);
	poly[0].x = center_x - 0.1*radius;
	poly[0].y = center_y + 0.6*radius;

	poly[1].x = center_x - 0.5*radius;
	poly[1].y = center_y + 0.8*radius;

	poly[2].x = center_x - 0.5*radius;
	poly[2].y = center_y + radius;

	poly[3].x = center_x + 0.5*radius;
	poly[3].y = center_y + radius;

	poly[4].x = center_x + 0.5*radius;
	poly[4].y = center_y + 0.8*radius;

	poly[5].x = center_x + 0.1*radius;
	poly[5].y = center_y + 0.6*radius;
	session->FillGeometry(CanvasGeometry::CreatePolygon(session, poly), Colors::Olive);

	// Tail 2
	poly = ref new Platform::Array<float2>(3);

	poly[0].x = center_x;
	poly[0].y = center_y + 0.6*radius;

	poly[1].x = center_x - 0.1*radius;
	poly[1].y = center_y + radius;

	poly[2].x = center_x + 0.1*radius;
	poly[2].y = center_y + radius;

	session->FillGeometry(CanvasGeometry::CreatePolygon(session, poly), Colors::DarkOliveGreen);

	// Cockpit
	poly = ref new Platform::Array<float2>(5);
	poly[0].x = center_x;
	poly[0].y = center_y - 0.9*radius;

	poly[1].x = center_x - 0.1*radius;
	poly[1].y = center_y - 0.8*radius;

	poly[2].x = center_x - 0.1*radius;
	poly[2].y = center_y - 0.5*radius;

	poly[3].x = center_x + 0.1*radius;
	poly[3].y = center_y - 0.5*radius;

	poly[4].x = center_x + 0.1*radius;
	poly[4].y = center_y - 0.8*radius;

	session->FillGeometry(CanvasGeometry::CreatePolygon(session, poly), Colors::Cyan);

	// Id
	session->DrawText(id.ToString(), center_x - 10, center_y, Colors::DarkOliveGreen);

}
