#include <Windows.h>
#include "resource.h"

BOOL CALLBACK fMenuInicioDialog(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK fCalculadoraMatricesDialog(HWND, UINT, WPARAM, LPARAM);

void handleClickCalculadoraMatrices(HWND);


void showMenuInicio();
void showCalculadoraMatricesDialog();
void addComboBoxItems(HWND, int);

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
				case BTN_MENU_CALCULADORA_MATRICES:
					handleClickCalculadoraMatrices(hwnd);
					break;
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


BOOL CALLBACK fCalculadoraMatricesDialog(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg)
	{
		case WM_INITDIALOG:
		{
			addComboBoxItems(hwnd, COLUMNAS_1);
			addComboBoxItems(hwnd, COLUMNAS_2);
			addComboBoxItems(hwnd, FILAS_1);
			addComboBoxItems(hwnd, FILAS_2);
		}
		break;
		case WM_COMMAND:
		{


			if (HIWORD(wparam) == BN_CLICKED) {
				switch (LOWORD(wparam))
				{
					case BTN_MENU_CALCULADORA_MATRICES:
						handleClickCalculadoraMatrices(hwnd);
						break;
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


//Clicks handlers
void handleClickCalculadoraMatrices(HWND hwnd) {
	ShowWindow(hwnd, SW_HIDE);
	showCalculadoraMatricesDialog();
}

void showCalculadoraMatricesDialog() {
	//HMENU menu = LoadMenu(hGlobalInstance, MAKEINTRESOURCE(IDR_MENU1));
	HWND ventana = CreateDialog(hGlobalInstance, MAKEINTRESOURCE(CALCULADORA_MATRICES), NULL, fCalculadoraMatricesDialog);
	//SetMenu(ventana, menu);
	ShowWindow(ventana, SW_SHOW);
}

void addComboBoxItems(HWND hwnd,int id) {
	HWND hComboBoxColumnas = GetDlgItem(hwnd, id);
	SendMessage(hComboBoxColumnas, CB_ADDSTRING, NULL, (LPARAM)"1");
	SendMessage(hComboBoxColumnas, CB_ADDSTRING, NULL, (LPARAM)"2");
	SendMessage(hComboBoxColumnas, CB_ADDSTRING, NULL, (LPARAM)"3");
	SendMessage(hComboBoxColumnas, CB_ADDSTRING, NULL, (LPARAM)"4");
	SendMessage(hComboBoxColumnas, CB_ADDSTRING, NULL, (LPARAM)"5");
	SendMessage(hComboBoxColumnas, CB_ADDSTRING, NULL, (LPARAM)"6");
}