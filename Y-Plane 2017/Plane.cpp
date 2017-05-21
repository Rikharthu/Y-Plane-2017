#include "pch.h"
#include "Plane.h"
#include <ctime>
#include "Simulation.h"
#include <math.h>
#include "Utils.h"

using namespace Microsoft::Graphics::Canvas::UI::Xaml;
using namespace Microsoft::Graphics::Canvas;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI;

long Plane::next_id = 0;

Plane::~Plane()
{
	// TODO set smth
	int xyz = 0;
}

void Plane::draw() {
	if (is_selected) {
		CanvasDrawingSession ^session = simulation->render_target->CreateDrawingSession();
		session->DrawCircle(center_x, center_y, 1.2*radius, Colors::Red);
	}
}

void Plane::move()
{
	Rect & f = simulation->field;
	bool is_in = f.Contains(Point(center_x, center_y));
	int tmp_x = center_x + speed*cos(direction);
	int tmp_y = center_y - speed*sin(direction);
	center_x = tmp_x;
	center_y = tmp_y;
	bool will_be_in = f.Contains(Point(center_x, center_y));

	// for debug
	if (!is_in) {
		out_of_bounds_counter++;
	}
	else {
		out_of_bounds_counter = 0;
	}
	if (out_of_bounds_counter == 10) {
		// for debug, however should not happen as of 5/16/2017
		int xyz = 4;
		center_x = f.Right / 2;
		center_y = f.Height / 2;
	}
	if (is_in && !will_be_in) {
		if (center_x<f.Left || center_x>f.Right) {
			// out horizontally
			direction = PI - direction;
			if (center_x < f.Left) {
				center_x = f.Left;
			}
			else {
				center_x = f.Right;
			}
		}
		if(center_y<0|| center_y>f.Height) {
			// out vertically
			direction = 2 * PI - direction;
			if (center_y < 0) {
				center_y = 0;
			}
			else {
				center_y = f.Height;
			}
		}
	}

}
