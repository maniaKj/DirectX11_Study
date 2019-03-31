#include "WindowContainer.h"

bool RenderWindow::Initialize(WindowContainer * pWindowContainer, HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height) {
	this->hInstance = hInstance;
	this->width = width;
	this->height = height;
	this->window_title = window_title;
	this->window_title_wide = StringHelper::StringToWide(this->window_title);
	this->window_class = window_class;
	this->window_class_wide = StringHelper::StringToWide(this->window_class);

	//윈도우 창 크기는 위의 타이틀 바까지 포함해서 생성됨. 즉 타이틀 바를 제외한 크기의 윈도우 생성.
	this->RegisterWindowClass();

	int centerScreenX = GetSystemMetrics(SM_CXSCREEN) / 2 - this->width / 2;
	int centerScreenY = GetSystemMetrics(SM_CYSCREEN) / 2 - this->height / 2;

	RECT wr; // Window rectangle
	wr.left = centerScreenX;
	wr.top = centerScreenY;
	wr.right = wr.left + this->width;
	wr.bottom = wr.top + this->height;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE); // 윈도우 크기 조정

	this->handle = CreateWindowEx(0, //Extended Window style -> 0은 디폴트
		this->window_class_wide.c_str(), //클래스 이름
		this->window_title_wide.c_str(), //타이틀 이름
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, //윈도우 스타일
		wr.left, //윈도우 x 위치
		wr.top, //윈도우 y 위치
		wr.right - wr.left, //창 너비
		wr.bottom - wr.top, //창 높이
		NULL, //윈도우 parent, 현재 parent window 없음
		NULL, //chile window 혹은 menu, 현재 child window 없음
		this->hInstance,//윈도우 instance
		pWindowContainer); //param to create window

	if (this->handle == NULL) {
		ErrorLogger::Log(GetLastError(), "CreateWindowEX Failed for window: " + this->window_title);
		return false;
	}

	ShowWindow(this->handle, SW_SHOW);
	SetForegroundWindow(this->handle);
	SetFocus(this->handle);

	return true;
}

RenderWindow::~RenderWindow() {
	if (this->handle != NULL) {
		UnregisterClass(this->window_class_wide.c_str(), this->hInstance);
		DestroyWindow(handle);
	}
}

LRESULT CALLBACK HandleMsgRedirect(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		//all other messages
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;

	default:
	{
		//retrieve ptr to window class
		WindowContainer* const pWindow = reinterpret_cast<WindowContainer*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		//forward message to window class handler
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
	}
	}
}

LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) { //메세지는 종류가 다양해서 스위치 활용. 예를 들면 ->키가 눌려졌을 때
	case WM_NCCREATE: {
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		WindowContainer * pWindow = reinterpret_cast<WindowContainer*>(pCreate->lpCreateParams);
		if (pWindow == nullptr) //Sanity check
		{
			ErrorLogger::Log("Critical Error: Pointer to window container is null during WM_NCCREATE.");
			exit(-1);
		}
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMsgRedirect));
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam); //기본 윈도우 프로세스 셋업
	}
	
}

void RenderWindow::RegisterWindowClass() {
	WNDCLASSEX wc; //윈도우 클래스 확장 버전
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = HandleMessageSetup; //이게 되네?? 파라미터 안 붙였는데
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = this->hInstance;
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = this->window_class_wide.c_str();
	wc.cbSize = sizeof(WNDCLASSEX);
	RegisterClassEx(&wc);
}

bool RenderWindow::ProcessMessage() {
	//Handling the Window Message
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));//메세지 구조 초기화

	while (PeekMessage(&msg,//메세지 저장 장소
		this->handle, //handle to window we are checking messages for
		0, //Minimum Filter Msg Value - We are not filtering messages
		0, //Maximm Filter Msg value
		PM_REMOVE)) //Remove Message after capturing if via peekMessage
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//창이 닫혔는지 확인
	if (msg.message == WM_NULL) {
		if (!IsWindow(this->handle)) {
			this->handle = NULL; //Message Processing loop takes care of destroying this window
			UnregisterClass(this->window_class_wide.c_str(), this->hInstance);
			return false;
		}
	}

	return true;
}

HWND RenderWindow::GetHWND() const
{
	return this->handle;
}
