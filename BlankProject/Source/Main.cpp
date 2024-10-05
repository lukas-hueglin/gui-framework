#include "Core/Application.h"
#include "Core/MainWindow.h"
#include "Core/Graphics2D.h"
#include "Widgets/Button.h"
#include "Widgets/LinearLayout.h"

#include "Windows.h"

void func() {
	MessageBox(NULL, L"Hello, World!", L"Important Message", NULL);
}

int main(int argc, char** argv) {
	
	// create new application
	Application* app = new Application(argc, argv);

	// create new window
	const wchar_t* s = L"Window";
	MainWindow<Graphics2D>* window = MainWindow<Graphics2D>::create(s);

	// create a layout
	LinearLayout* l = new LinearLayout(window, Orientation::Vertical);
	l->setFillMode(FillMode::Expand);
	window->setWidget(l);

	// create a widget
	Button* w1 = new Button(window, L"Button 1");
	w1->setMargin(10);
	w1->setPadding(10);
	w1->connect(func);

	// create a label
	Label* w2 = new Label(window, L"Label");
	w2->setMargin(10);
	w2->setPadding(10);

	// create a button
	Button* w3 = new Button(window, L"Button 2");
	w3->setMargin(10);
	w3->setPadding(10);

	l->addWidget(w1);
	l->addWidget(w2);
	l->addWidget(w3);

	return app->exec();
}