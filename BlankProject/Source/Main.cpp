#include "Core/Application.h"
#include "Core/MainWindow.h"
#include "Core/Graphics2D.h"
#include "Widgets/Button.h"
#include "Widgets/LinearLayout.h"
#include "Widgets/Slider.h"

int main(int argc, char** argv) {
	
	// create new application
	Application* app = new Application(argc, argv);

	// create new window
	const wchar_t* s = L"Window";
	MainWindow<Graphics2D>* window = MainWindow<Graphics2D>::create(s);
	app->setMainWindow(window);

	// create a layout
	LinearLayout* l1 = new LinearLayout(window, Orientation::Vertical);
	window->setLayout(l1);

	// create a widget
	Slider<float>* w1 = new Slider<float>(window, 1, 0, 10);
	w1->setMargin(10);
	w1->setPadding(10);

	// create a label
	Label* w2 = new Label(window, L"Label");
	w2->setMargin(10);
	w2->setPadding(10);

	// create a layout
	LinearLayout* l2 = new LinearLayout(window, Orientation::Horizontal);
	l2->setAlignment(Alignment::Center);
	l2->setFillMode(FillMode::Shrink);

	// create a button
	Button* w3 = new Button(window, L"Left Button");
	w3->setMargin(10);
	w3->setPadding(10);

	// create a button
	Button* w4 = new Button(window, L"Right Button");
	w4->setMargin(10);
	w4->setPadding(10);

	l2->addFrame(w3);
	l2->addFrame(w4);

	l1->addFrame(w1);
	l1->addFrame(l2);

	return app->exec();
}