#include "Application.h"
#include "Functional.h"

#include "Core/MainWindow.h"
#include "Core/Graphics2D.h"
#include "Widgets/Button.h"
#include "Widgets/LinearLayout.h"
#include "Widgets/Slider.h"
#include "Widgets/TextBox.h"
#include "Widgets/ComboBox.h"
#include "Widgets/Plot.h"
#include "Widgets/PlotSeries1D.h"
#include "Style/Palette.h"

#include <string>
#include <numbers>

int main(int argc, char** argv) {

	// create new application
	App* app = new App(argc, argv);
	Functional* functional = new Functional();
	app->addFunctional(functional);

	// create new window
	std::wstring s = L"Window";
	MainWindow* window = MainWindow::create(s);
	app->setMainWindow(window);

	// create a layout
	LinearLayout* l1 = new LinearLayout(window, Orientation::Vertical);
	window->setLayout(l1);

	// create a widget
	Slider<int>* w1 = new Slider<int>(window, 4, 0, 10);
	w1->setSuffix(L" \u03a9");
	w1->setMargin(10);
	w1->setPadding(10);

	// create a label
	Label* w2 = new Label(window, L"Label");
	w2->setMargin(10);
	w2->setPadding(10);

	// create a layout
	//LinearLayout* l2 = new LinearLayout(window, Orientation::Horizontal);
	//l2->setAlignment(Alignment::Center);
	//l2->setFillMode(FillMode::Shrink);

	// create a button
	Button* w3 = new Button(window, L"Left Button");
	w3->setMargin(10);
	w3->setPadding(10);

	// create a button
	TextBox* w4 = new TextBox(window, L"TextBox");
	w4->setMargin(10);
	w4->setPadding(10);

	// create a plot
	Plot* plot = new Plot(window, L"Time", L"Voltage");
	plot->setFillMode(FillMode::Expand);

	// create a plot series
	float data[100];

	for (int i = 0; i < 100; ++i) {
		data[i] = sin(i / 49.5 * std::numbers::pi);
	}

	PlotSeries1D* series = new PlotSeries1D(plot, data, 0, 2*std::numbers::pi, 100, Palette::Plot(0));

	plot->addPlotSeries(series);

	// create a combobox
	ComboBox* w5 = new ComboBox(window, std::vector<std::wstring>({L"Number 1", L"Number 2", L"Number 3", L"Number 4"}));
	w5->setMargin(10);
	w5->setPadding(10);

	//l2->addFrame(w3);
	//l2->addFrame(w4);

	l1->addFrame(w1);
	l1->addFrame(w2);
	l1->addFrame(w3);
	l1->addFrame(w4);
	l1->addFrame(w5);
	l1->addFrame(plot);

	return app->exec();
}