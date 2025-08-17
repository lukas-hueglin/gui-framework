#pragma once
#include "Gui.h"
#include "Common/Reflection/Internal.h"
#include "Core/Object.h"

#include <string>

#define IMPLEMENT_LOADSAVE(class_name) \
public:\
	void loadMembers(std::wstring path) {REFLECTION.load(#class_name, path);} \
	void saveMembers(std::wstring path) {REFLECTION.save(#class_name, path);} \

class GUI_API IFunctional : public Object {

	USE_REFLECTION()

public:
	IFunctional(const Credentials& creds, IApplication* p_app);

public:
	virtual void loadMembers(std::wstring path) = 0;
	virtual void saveMembers(std::wstring path) = 0;

	// make IApplication a friend
	friend class IApplication;
};