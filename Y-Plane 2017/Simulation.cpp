#include "pch.h"
#include "Simulation.h"
#include "Utils.h"
#include "Bomber.h"
#include "Jet.h"
#include <ctime>
#include <mutex>

// multithreading lock
bool locked = false;
mutex luftwaffe_lock; // protects luftwaffe vector

void Simulation::generatePlanes()
{
	lock_guard<mutex> lock(luftwaffe_lock);
	srand(time(NULL));

	/*int bomber_count = random(1, 5);
	int jet_count = random(1, 12);
	int airliner_count = (1, 8);*/
	int bomber_count = 10;
	int jet_count = 10;

	for (int i = 0; i < bomber_count; i++) {
		luftwaffe.push_back(new Bomber());
	}
	for (int i = 0; i < jet_count; i++) {
		luftwaffe.push_back(new Jet());
	}

	for (Plane *p : luftwaffe) {
		p->moveTo(random(1, 500), random(1, 500));
		p->direction = random(0, 360);
		database->add(*p);
	}
}


Simulation::Simulation(CanvasAnimatedControl ^ canvas)
{
	this->canvas = canvas;
	this->field = Rect(0, 0, canvas->ActualWidth, canvas->ActualHeight);
	// TODO add try-catch if program will fail sometime
	this->database = new LuftwaffeDatabase();
	this->database->create();
}

void Simulation::shoot(int x, int y)
{
	lock_guard<mutex> lock(luftwaffe_lock);
	/*luftwaffe.remove_if([&x,&y](Plane * plane) {
		return plane->isInside(x, y);
	});*/
	for (auto it = luftwaffe.begin(); it != luftwaffe.end();) {
		if ((*it)->isInside(x, y)) {
			(*it)->destroyed_at=time(nullptr);
			database->update(**it);
			it = luftwaffe.erase(it);
		}
		else {
			++it;
		}
	}
	int count = luftwaffe.size();
	int xyzz = 4;
}

void Simulation::draw_all()
{
	lock_guard<mutex> lock(luftwaffe_lock);
	locked = true;
	for (Plane *p : luftwaffe) {
		p->draw();
	}
}

void Simulation::move_all()
{
	lock_guard<mutex> lock(luftwaffe_lock);
	for (Plane *p : luftwaffe) {
		p->move();
	}
}

