#include <windows.h>
#include "resource.h"

BOOL CALLBACK DialogProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
	case WM_INITDIALOG:
		SetDlgItemText(hwnd, IDC_EDIT1, L"Added by Nelson Cheung");
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_Add: {
			int len = GetWindowTextLength(GetDlgItem(hwnd, IDC_EDIT1));
			if (len > 0) {
				BOOL bSuccess;
				int nTimes = GetDlgItemInt(hwnd, IDC_Number, &bSuccess, FALSE);
				if (nTimes > 0) {
					char* buf;
					buf = (char*)GlobalAlloc(GPTR, len + 1);
					GetDlgItemTextA(hwnd, IDC_EDIT1, buf, len + 1);
					for (int i = 0; i < nTimes; i++) {
						int index = SendDlgItemMessageA(hwnd, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)buf);
						SendDlgItemMessageA(hwnd, IDC_LIST1, LB_SETITEMDATA, index, (LPARAM)nTimes);
					}
					GlobalFree((HANDLE)buf);
				}
				else {
					MessageBoxA(hwnd, "Please input number of times", "Error", MB_ICONERROR);
				}
			}
			else {
				MessageBoxA(hwnd,  "Please input in blank space", "Error", MB_ICONERROR);
			}
		}
		break;
		case IDC_Delete: {

		}
		break;
		case IDC_Clear: {
			SendDlgItemMessageA(hwnd, IDC_LIST1, LB_RESETCONTENT, 0, 0);
		}
		break;
		case IDC_LIST1: {

		}
		break;
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default:
		return FALSE;
	}
	return true;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);
}