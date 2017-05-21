#pragma once

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
	Color color;

	Plane() {
		created_at = time(nullptr);
		id = next_id++;

		destroyed_at = -1;
		radius = DEFAULT_PLANE_RADIUS;
		direction = 0;
		center_x = 0;
		center_y = 0;
		color = DEFAULT_PLANE_COLOR;
		speed = DEFAULT_PLANE_SPEED;
		out_of_bounds_counter = 0;
		is_selected = false;
	}
	Plane(long id, long created_at, long destroyed_at) :Plane() {
		this->id = id;
		this->created_at = created_at;
		this->destroyed_at = destroyed_at;
	}

	~Plane();

	virtual void draw();
	virtual void move();
	void moveTo(int x, int y) {
		center_x = x;
		center_y = y;
	}
	bool isInside(int x, int y) {
		return x >= center_x - radius && x <= radius + center_x
			&& y >= center_y - radius && y <= center_y + radius;
	}

	static long next_id;
};
