#pragma once
#include "ErrorLogger.h"

class WindowContainer;

class RenderWindow
{
public:
	bool Initialize(WindowContainer * pWindowContainer, HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height);
	bool ProcessMessage();
	HWND GetHWND() const;
	~RenderWindow();
private:
	void RegisterWindowClass(); //윈도우 만들 때 클래스 이름 부여하고 등록도 해야함.
	HWND handle = NULL; //Handle to this window
	HINSTANCE hInstance = NULL;  //Handle to application Instance
	std::string window_title = "";
	std::wstring window_title_wide = L"";// Wstring 윈도우 제목 repsresentation
	std::string window_class = "";
	std::wstring window_class_wide = L""; // 윈도우 클래스 이름 wstring
	int width = 0;
	int height = 0;
};