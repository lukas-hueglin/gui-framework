#pragma once
#include "Gui.h"
#include "Common/Pimpl.h"

#include <list>

#define REGISTER_FUNCTIONAL(p_functional) mp_functionals.push_back(p_functional); // has to be changed, just use function call


class Object;
class Window;
class MainWindow;
class IFunctional;

class GUI_API IApplication {

	ADD_IMPL_CLASS()

private:
	MainWindow* mp_mainWindow;

protected:
	std::list<Window*> mp_windows;
	std::list<IFunctional*> mp_functionals;

public:
	IApplication(int argc, char** argv);
	~IApplication();

public:
	int exec();

	void registerObject(Window* p_window);
	void registerObject(IFunctional* p_functional);

	void invokeApplicationClose();
	void invokeWindowClose(Window* p_window);

protected:
	template<class T, typename ...Args>
	T& create(Args... args);

private:
	void onTick(float deltaTime);

	void onBegin();
	void onClose();

	virtual void initUI() = 0;
	virtual std::wstring getApplicationName() = 0;
};

#include "Core/IApplication.ipp"