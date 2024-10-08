#pragma once

// if windows is used
#ifdef WIN32

	// include important headers
	#include<Windows.h>
	#include <windowsx.h>
	#include <d2d1.h>
	#include <dwrite.h>

	// add lib comments
	#pragma comment(lib, "d2d1")
	#pragma comment(lib, "dwrite")

	// define macros
	#define HInstance() GetModuleHandle(NULL)
	#define MAX_STRING_SIZE 64

#endif

// dll import export macro
#ifdef BUILD_DLL
	#define GUI_API __declspec(dllexport)
#else
	#define GUI_API __declspec(dllimport)
#endif