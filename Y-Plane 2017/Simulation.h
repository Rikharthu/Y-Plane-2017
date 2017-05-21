#pragma once
#include <list>
#include <vector>
#include "LuftwaffeDatabase.h"

using namespace std;

using namespace Microsoft::Graphics::Canvas::UI::Xaml;
using namespace Microsoft::Graphics::Canvas;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::Foundation;

class Simulation {
public:
	CanvasAnimatedControl ^ canvas; 
	CanvasRenderTarget ^ render_target;
	Rect field;
	LuftwaffeDatabase * database;

	vector<Plane*> luftwaffe;

	void generatePlanes();

	Simulation(CanvasAnimatedControl^ canvas);

	void shoot(int x, int y);
	void draw_all();
	void move_all();
	void set_selected(int index);
}; 

extern Simulation * simulation;