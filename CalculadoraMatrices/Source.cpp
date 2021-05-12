#include <Windows.h>
#include "resource.h"
#include <iostream>
#include <string> 
#include <stdlib.h>

#define MAX 10
using namespace std;

BOOL CALLBACK fMenuInicioDialog(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK fCalculadoraMatricesDialog(HWND, UINT, WPARAM, LPARAM);

void handleClickCalculadoraMatrices(HWND);


void showMenuInicio();
void showCalculadoraMatricesDialog();
void addComboBoxItems(HWND, int);
void setMatrizInput(HWND, int, int , int, int);
void handleSumarMatrizClick(HWND);
bool validarSumaResta();


HINSTANCE hGlobalInstance;

HWND editMatriz1[MAX][MAX];
HWND editMatriz2[MAX][MAX];
int columnas1, filas1;
int columnas2, filas2;
float matrizResultado[MAX][MAX];

//Helpers

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
					case BTN_CREAR_MATRIZ_1:
						setMatrizInput(hwnd, MATRIZ_A_CONTAINER, FILAS_1, COLUMNAS_1, 1);
						break;
					case BTN_CREAR_MATRIZ_2:
						setMatrizInput(hwnd, MATRIZ_B_CONTAINER, FILAS_2, COLUMNAS_2, 2);
						break;
					case BTN_SUMAR_MATRIZ:
						handleSumarMatrizClick(hwnd);
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

void handleSumarMatrizClick(HWND hwnd) {
	if (!validarSumaResta()) {
		MessageBox(hwnd, (LPCWSTR)L"Las matrices deben tener el mismo numero de columnas y de filas", (LPCWSTR)L"Mensaje", MB_ICONERROR);
		return;
	}
	float matriz1[MAX][MAX];
	float matriz2[MAX][MAX];

	for (int i = 0; i < filas1; i++) {
		for (int j = 0; j < columnas1; j++) {
			char buffer[256];
			SendMessage(editMatriz1[i][j],
				WM_GETTEXT,
				sizeof(buffer) / sizeof(buffer[0]),
				reinterpret_cast<LPARAM>(buffer));
			matriz1[i][j] = atof(buffer);

			char buffer2[256];
			SendMessage(editMatriz2[i][j],
				WM_GETTEXT,
				sizeof(buffer2) / sizeof(buffer2[0]),
				reinterpret_cast<LPARAM>(buffer2));
			matriz2[i][j] = atof(buffer2);
			
			matrizResultado[i][j] = matriz1[i][j] + matriz2[i][j];
		}
	}

	

}


bool validarSumaResta() {
	if (columnas1 != columnas2) {
		return false;
	}
	if (filas1 != filas2) {
		return false;
	}

	if (columnas1 != filas2) {
		return false;
	}

	if (columnas2 != filas1) {
		return false;
	}
	if (filas1 != columnas1) {
		return false;
	}
	if (filas2 != columnas2) {
		return false;
	}


	return true;
}


void setMatrizInput(HWND hwnd, int container_id, int filas_id, int columnas_id, int matrizNumber) {
	HWND hComboBoxColumnas = GetDlgItem(hwnd, columnas_id);
	int columnas = SendMessage(hComboBoxColumnas, CB_GETCURSEL, 0, 0) + 1;

	HWND hComboBoxFilas = GetDlgItem(hwnd, filas_id);
	int filas = SendMessage(hComboBoxFilas, CB_GETCURSEL, 0, 0) + 1;

	if (matrizNumber == 1) {
		columnas1 = columnas;
		filas1 = filas;
	}
	else {
		columnas2 = columnas;
		filas2 = filas;
	}

	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			HWND hComboBoxColumnas = GetDlgItem(hwnd, container_id);
			HWND editControl = CreateWindowEx(0, L"EDIT",
				NULL,
				WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL,
				20 + j * 30, (20 + (i * 30)) + 10, 30, 30,
				hComboBoxColumnas, (HMENU)8000,
				GetModuleHandle(NULL), 0);
			if (matrizNumber == 1) {
				editMatriz1[i][j] = editControl;
			}
			else if(matrizNumber == 2) {
				editMatriz2[i][j] = editControl;
			}
		}
	}
}





//Init functions
void addComboBoxItems(HWND hwnd,int id) {
	HWND hComboBoxColumnas = GetDlgItem(hwnd, id);
	SendMessage(hComboBoxColumnas, CB_ADDSTRING, NULL, (LPARAM)"1");
	SendMessage(hComboBoxColumnas, CB_ADDSTRING, NULL, (LPARAM)"2");
	SendMessage(hComboBoxColumnas, CB_ADDSTRING, NULL, (LPARAM)"3");
	SendMessage(hComboBoxColumnas, CB_ADDSTRING, NULL, (LPARAM)"4");
	SendMessage(hComboBoxColumnas, CB_ADDSTRING, NULL, (LPARAM)"5");
	SendMessage(hComboBoxColumnas, CB_ADDSTRING, NULL, (LPARAM)"6");
}

string convertToString(char* a, int size)
{
	int i;
	string s = "";
	for (i = 0; i < size; i++) {
		s = s + a[i];
	}
	return s;
}