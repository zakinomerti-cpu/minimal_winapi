#define DWORD     unsigned int
#define LPCSTR    const char*
#define HWND      void*
#define HMENU     void*
#define HINSTANCE void*
#define LPVOID    void*
#define UINT      unsigned int
#define BYTE      unsigned char

#define WINAPI __stdcall

__declspec(dllimport) void* WINAPI CreateWindowExA
(
	DWORD,
	LPCSTR,LPCSTR,
	DWORD,
	int,int,int,int,
	HWND,HMENU,HINSTANCE,LPVOID
);
__declspec(dllimport) int GetMessageA(void*,HWND,UINT,UINT);
__declspec(dllimport) WINAPI TranslateMessage(void*);
__declspec(dllimport) WINAPI DispatchMessageA(void*);
__declspec(dllimport) WINAPI ExitProcess(UINT);
__declspec(dllimport) int WINAPI IsWindow(HWND);

void entry(void) {
	BYTE msg[28];

	void* hwnd = CreateWindowExA(
		0, "edit", 0, 
		282001408,
		0x80000000, 0x80000000,
		500, 500,
		0, 0, 0, 0
	);

	while(GetMessageA(&msg, 0, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageA(&msg);

		/* msg.message == WM_KEYDOWN && msg.wParam = VK_ESCAPE */
		if(*(UINT*)(msg+4) == 0x100 && *(UINT*)(msg+8) == 0x1b) {
			break;
		}
		if(!IsWindow(hwnd)) {
			break;
		}
	}
	ExitProcess(0);

}
