//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <winsqlite/winsqlite3.h>
#include "Simulation.h"
#include "Plane.h"
#include "Jet.h"
#include "Bomber.h"
#include <ctime>
#include "Utils.h"
#include <locale>
#include <codecvt>
#include <string>

using namespace Y_Plane_2017;

using namespace std;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;


sqlite3 *db;
Simulation * simulation;
Plane * junkers;

MainPage::MainPage()
{
	InitializeComponent();

	SetupDatabase();

	Plane plane;
	plane.moveTo(300, 300);
	plane.radius = 20;
	bool isInside1 = plane.isInside(300, 300);
	bool isInside2 = plane.isInside(320, 300);
	bool isInside3 = plane.isInside(300, 320);
	bool isInside4 = plane.isInside(321, 300);
	bool isInside5 = plane.isInside(300, 321);
	int xyz = 4;
}

String^ StringFromAscIIChars(char* chars)
{
	size_t newsize = strlen(chars) + 1;
	wchar_t * wcstring = new wchar_t[newsize];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wcstring, newsize, chars, _TRUNCATE);
	String^ str = ref new Platform::String(wcstring);
	delete[] wcstring;
	return str;
}

void MainPage::SetupDatabase()
{
	// 1. setup a sqlite database in memory
	// TODO make it file
	int result = sqlite3_open(":memory:", &db);
	if (result) {
		//LogMessage(ref new Platform::String(strcat("sadasd", sqlite3_errmsg(db)));
	}
	else {
		LogMessage("Database opened successfully!");
	}

	// 2. Create new Table
	/* Create SQL statement */
	char*sql = "CREATE TABLE LUFTWAFFE("  \
		"ID INT PRIMARY KEY     NOT NULL," \
		"CREATED_AT     INT    NOT NULL," \
		"DESTROYED_AT   INT     NOT NULL );";
	char *zErrMsg = 0;
	//- Execute SQL statement
	result = sqlite3_exec(db, sql, nullptr, 0, &zErrMsg);
	if (result != SQLITE_OK) {
		//! TODO doesnt work
		char *s = nullptr;
		sprintf(s, "SQL error: %s\n", zErrMsg);
		LogMessage(StringFromAscIIChars(s));
		sqlite3_free(zErrMsg);
	}
	else {
		LogMessage("Table AIRFIELD created successfully\n");
	}
}

void MainPage::LogMessage(Object ^ parameter)
{
	auto paraString = parameter->ToString();
	auto formattedText = std::wstring(paraString->Data()).append(L"\r\n");
	OutputDebugString(formattedText.c_str());
}



void Y_Plane_2017::MainPage::CanvasAnimated_Draw(Microsoft::Graphics::Canvas::UI::Xaml::ICanvasAnimatedControl^ sender, Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedDrawEventArgs^ args)
{
	// TODO move to simulation.render()
	simulation->render_target->CreateDrawingSession()->Clear(Colors::LightBlue);
	simulation->move_all();
	simulation->draw_all();

	junkers->move();
	junkers->draw();

	args->DrawingSession->DrawImage(simulation->render_target);
}


void Y_Plane_2017::MainPage::CanvasAnimated_PointerPressed(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	int x = e->GetCurrentPoint(CanvasAnimated)->Position.X;
	int y = e->GetCurrentPoint(CanvasAnimated)->Position.Y;

	int a = 4;
	simulation->shoot(x, y);
}


void Y_Plane_2017::MainPage::CanvasAnimated_CreateResources(Microsoft::Graphics::Canvas::UI::Xaml::CanvasAnimatedControl^ sender, Microsoft::Graphics::Canvas::UI::CanvasCreateResourcesEventArgs^ args)
{
	junkers = new Bomber();
	junkers->moveTo(200, 200);
	junkers->direction = 91;
	junkers->speed = 3;
	simulation = new Simulation(CanvasAnimated);
	simulation->render_target= ref new CanvasRenderTarget(CanvasAnimated, CanvasAnimated->Size);
	simulation->generatePlanes();
}


void Y_Plane_2017::MainPage::BtnShowDatabase_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	vector<Plane*> planes = *simulation->database->getData2();
	PlanesListView->Items->Clear();
	for (Plane *p : planes) {
		char buffer[256];

		// Date
		// 1. Created at
		time_t created_at = time_t(p->created_at);
		char date1[20];
		struct tm created_at_struct;
		localtime_s(&created_at_struct,&created_at);
		strftime(date1, sizeof(date1), "%d/%m/%Y %H:%M:%S", &created_at_struct);
		// 2. Destroyed at
		char date2[20];
		if (p->destroyed_at != -1) {
			time_t destroyed_at = time_t(p->destroyed_at);
			struct tm destroyed_at_struct;
			localtime_s(&destroyed_at_struct, &destroyed_at);
			strftime(date2, sizeof(date2), "%d/%m/%Y %H:%M:%S", &destroyed_at_struct);
		}
		else {
			strcpy(date2, "-");
		}

		// ID
		sprintf(buffer, "ID: %d\nCreated at\t%s\nDestroyed at\t%s", p->id, date1, date2);

		// Assemble
		PlanesListView->Items->Append(toPlatformString(buffer));
	}
	ListDrawer->IsPaneOpen = true;
}

Platform::String ^ Y_Plane_2017::MainPage::toPlatformString(std::string inputString)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::wstring intermediateForm = converter.from_bytes(inputString);
	Platform::String^ retVal = ref new Platform::String(intermediateForm.c_str());

	return retVal;
}


void Y_Plane_2017::MainPage::HamburgerButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

	ListDrawer->IsPaneOpen = !ListDrawer->IsPaneOpen;
}
