#pragma once

#include "Utils.h"

#define DEFAULT_PLANE_RADIUS 4
#define DEFAULT_PLANE_SPEED 1.0f
#define DEFAULT_PLANE_COLOR Colors::Red;

using namespace Microsoft::Graphics::Canvas::UI::Xaml;
using namespace Microsoft::Graphics::Canvas;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI;

class Plane {
public:
	long id;
	long created_at;
	long destroyed_at;
	int radius;
	int center_x, center_y;
	float direction;
	float speed;
	bool is_selected;
	int out_of_bounds_counter;
	double diff;
	Color color;

	Plane();
	Plane(long id, long created_at, long destroyed_at) :Plane() {
		this->id = id;
		this->created_at = created_at;
		this->destroyed_at = destroyed_at;
	}

	~Plane();

	virtual void draw();
	virtual void move();
	void moveTo(int x, int y);
	bool isInside(int x, int y) {
		return x >= center_x - radius && x <= radius + center_x
			&& y >= center_y - radius && y <= center_y + radius;
	}

	static long next_id;
};
