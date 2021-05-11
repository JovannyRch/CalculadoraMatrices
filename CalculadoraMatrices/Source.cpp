#include <Windows.h>
#include "resource.h"
BOOL CALLBACK fMenuInicioDialog(HWND, UINT, WPARAM, LPARAM);


void showMenuInicio();

HINSTANCE hGlobalInstance;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrev, PSTR cmdLine, int cShow) {

	hGlobalInstance = hInstance;

	//Primera ventana
	showMenuInicio();
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (GetMessage(&msg, 0, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}

void showMenuInicio() {
	HWND ventana = CreateDialog(hGlobalInstance, MAKEINTRESOURCE(MENU_INICIO), NULL, fMenuInicioDialog);
	ShowWindow(ventana, SW_SHOW);
}


//Callbacks de los dialogos


BOOL CALLBACK fMenuInicioDialog(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg)
	{

	case WM_COMMAND:
	{


		if (HIWORD(wparam) == BN_CLICKED) {
			switch (LOWORD(wparam))
			{
			/*case BTN_LOGIN:
				handleLoginClickButton(hwnd);
				break;
			case BTN_LOGIN_SALIR:
				closeLogin = true;
				cerrarVentana(hwnd);
				break;
			case BTN_REGISTRARSE:
				handleRegisterClickButton(hwnd);
				break;*/
			}
		}

	}
	break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(1);
		break;
	}

	return false;
}