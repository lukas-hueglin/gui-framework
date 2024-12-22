#include "Gui.h"
#include "Application.h"

#include "Core/MainWindow.h"
#include "Widgets/Button.h"
#include "Widgets/LinearLayout.h"
#include "Widgets/Slider.h"
#include "Widgets/TextBox.h"
#include "Widgets/ComboBox.h"
#include "Widgets/Plot.h"
#include "Widgets/PlotSeries1D.h"
#include "Style/Palette.h"

#include <numbers>
#include <string>

App::App(int argc, char** argv) : Application(argc, argv), mp_functional(new Functional()) {

	REGISTER_FUNCTIONAL(mp_functional)
}

void App::initUI() {

	// create new window
	std::wstring s = L"Window";
	MainWindow* window = MainWindow::create(s);
	setMainWindow(window);

	// create a layout
	LinearLayout* l1 = new LinearLayout(window, Orientation::Horizontal);
	window->setLayout(l1);

	// create a widget
	Slider<float>* w1 = new Slider<float>(window, mp_functional->getFreqIncrement(), 0, 1);
	w1->setSuffix(L" Hz");
	w1->setMargin(10);
	w1->setPadding(10);

	connect<Slider<float>, Functional, float>(mp_functional, &Functional::setFreqIncrement, w1->onValueChanged);

	// create a label
	Label* w2 = new Label(window, L"Label");
	w2->setMargin(10);
	w2->setPadding(10);

	// create a layout
	LinearLayout* l2 = new LinearLayout(window, Orientation::Vertical);
	l2->setAlignment(Alignment::Center);
	l2->setFillMode(FillMode::Shrink);

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
	PlotSeries1D* series = new PlotSeries1D(plot, mp_functional->getPlotData(), 0, 2 * std::numbers::pi, mp_functional->getPlotSize(), Palette::Plot(0));
	plot->addPlotSeries(series);

	// create a combobox
	ComboBox* w5 = new ComboBox(window, std::vector<std::wstring>({ L"Number 1", L"Number 2", L"Number 3", L"Number 4" }));
	w5->setMargin(10);
	w5->setPadding(10);

	l2->addFrame(w1);
	l2->addFrame(w2);
	l2->addFrame(w3);
	l2->addFrame(w4);
	l2->addFrame(w5);

	l1->addFrame(plot);
	l1->addFrame(l2);
}

std::wstring App::getApplicationName() {
	return TEXT(PROJECT_NAME);
}
