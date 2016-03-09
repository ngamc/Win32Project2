#include <windows.h>
#include "resource.h"
#include <iostream>
#include<string>
#include <sstream>
#include <gdiplus.h>
using namespace Gdiplus;

BOOL CALLBACK DialogProc2(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK DialogProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	int getCount= SendDlgItemMessageA(hwnd, IDC_LIST1, LB_GETCOUNT, 0, 0);
	SetDlgItemInt(hwnd, IDC_Showitemno, getCount,0);
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
					char* buf=new char[len+1];
					GetDlgItemTextA(hwnd, IDC_EDIT1, buf, len + 1);
					for (int i = 0; i < nTimes; i++) {
						int index = SendDlgItemMessageA(hwnd, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)buf);
						SendDlgItemMessageA(hwnd, IDC_LIST1, LB_SETITEMDATA, index, (LPARAM)nTimes);
					}
					std::string bb = "yes";
					std::string aa = "You have entered ";
					aa.append(buf);
					aa.append(" ");
					aa.append(std::to_string(nTimes));
					aa.append(" times");
					std::ostringstream oss;
					oss << "You have entered \"" << buf <<"\" "<< nTimes << " times.";
					SendDlgItemMessageA(hwnd, IDC_Log, LB_ADDSTRING, 0, (LPARAM)oss.str().c_str());
					delete[] buf;
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
			int count = SendDlgItemMessageA(hwnd, IDC_LIST1, LB_GETSELCOUNT, 0, 0);
			if (count != LB_ERR) {
				if (count > 0) {
					int *buf;
					buf= new int[count+1];
					SendDlgItemMessageA(hwnd, IDC_LIST1, LB_GETSELITEMS, count, (LPARAM)buf);
					for (int i = count; i > 0; i--) {
						if (SendDlgItemMessageA(hwnd, IDC_LIST1, LB_DELETESTRING, buf[i-1], 0) == LB_ERR) {
							MessageBoxA(hwnd, "Error deleting list items", "Error", MB_ICONERROR);
						}
						else {
							std::ostringstream oss;
							oss << "You have deleted message id=" << buf[i-1] ;
							SendDlgItemMessageA(hwnd, IDC_Log, LB_ADDSTRING, 0, (LPARAM)oss.str().c_str());
						}
					}
					delete[] buf;
				}
				else {
					MessageBoxA(hwnd, "You don't have anything selected", "Error", MB_ICONERROR);
				}
			}
			else {
				MessageBoxA(hwnd, "LB_ERROR", "Error", MB_ICONERROR);
			}
		}
	/*	break;*/
		
		case IDC_LIST1: {
			int count = SendDlgItemMessageA(hwnd, IDC_LIST1, LB_GETSELCOUNT, 0, 0);
			if (count != LB_ERR) {
				if (count == 1) {
					int itemNo;
					SendDlgItemMessageA(hwnd, IDC_LIST1, LB_GETSELITEMS, count, (LPARAM)&itemNo);
					int getData= SendDlgItemMessageA(hwnd, IDC_LIST1, LB_GETITEMDATA, itemNo, NULL);
					SetDlgItemInt(hwnd, IDC_Showtimes, getData, 0);

				}
				else
					SetDlgItemTextA(hwnd, IDC_Showtimes, "-");

			}else
				MessageBoxA(hwnd, "LB_ERROR", "Error", MB_ICONERROR);
		}
		break;
		case IDC_Clear: {
			SendDlgItemMessageA(hwnd, IDC_LIST1, LB_RESETCONTENT, 0, 0);
		}
		break;
		case IDC_Opennew: {
			int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hwnd, DialogProc2);

		}
		break;
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		//TextOutW(hdc, 0, 0, L"Hello, Windows!", 10);
		
		//GDI Way:
		HPEN hPen;
		HPEN hPenOld;
		hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		hPenOld = (HPEN)SelectObject(hdc, hPen);
		MoveToEx(hdc, 20, 10, NULL);
		LineTo(hdc, 200, 100);
		SelectObject(hdc, hPenOld);
		DeleteObject(hPen);

		//GDI+ way:
		//Graphics *myGraphics = new Graphics(hdc);
		//Pen *myPen = new Pen(Color(255, 255, 0, 0), 3);
		//hdc = BeginPaint(hwnd, &ps);
		//myGraphics->DrawLine(myPen, 20, 10, 200, 100);
		//delete myGraphics;
		//delete myPen;
		
		EndPaint(hwnd, &ps);
	}
	break;
	default:
		return FALSE;
	}
	return true;
}

BOOL CALLBACK DialogProc2(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch (Message) {
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		break;
	case WM_CLOSE:
		EndDialog(hwnd,0);
		break;
	default:
		return FALSE;
	}
	return true;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc);
}