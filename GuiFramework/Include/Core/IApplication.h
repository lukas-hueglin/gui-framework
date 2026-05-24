#pragma once
#include "Gui.h"

#include <list>

#define REGISTER_FUNCTIONAL(p_functional) mp_functionals.push_back(p_functional); // has to be changed, just use function call


class Object;
class Window;
class IFunctional;

class GUI_API IApplication {

private:
	std::list<Window*> mp_windows;
	std::list<IFunctional*> mp_functionals;
	std::list<Object*> mp_objects;

public:
	IApplication(int argc, char** argv);
	~IApplication();

public:
	int exec();

	void registerObject(Window* p_window);
	void registerObject(IFunctional* p_functional);
	void registerObject(Object* p_object);

	void invokeApplicationClose();
	void invokeWindowClose(Window* p_window);

protected:
	template<class T, typename ...Args>
	T& create(Args... args);

private:
	void onTick(float deltaTime);

	void onBegin();
	void onClose();

	void programLoop();

	std::wstring getIniPath();

	virtual void initUI() = 0;
	virtual std::wstring getApplicationName() = 0;
};

#include "Core/IApplication.ipp"