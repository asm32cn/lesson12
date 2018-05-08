// lesson12_sqlite3_db_sdk.cpp : Defines the entry point for the application.
//

/*
����unexpected end of file while looking for precompiled headerdirective
����������ͷ�ļ�����Ĵ���
����취���£�
1���Ҽ��㹤����,ѡ����,Ȼ��ѡc/c++����ҳ,��ѡcatagoryѡ����ѡ precompiled header ,��ѡ���ó�no use ����autometic
2�����ʹ�õ���Win32���̣����ܾ��Ǵ����ļ�û�а�����#include "stdafx.h" ����Ӹð������ɡ�
*/

#include <windows.h>
#include <commctrl.h>
#include <stdio.h>

#include "sqlite3.h"
#include "resource.h"

char szTitle[32]="lesson12-sqlite3-db-sdk";       //���ڵı���
char szWindowClass[32]="lesson12-sqlite3-db-sdk"; //���ڵ�����


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void PA_DoAppInitialize();
void PA_DoAppFinalize();

int UTF8_GBK(char* szUtf8, char* szGBK, int nLen);

UINT nTimerID = 1;

//HBRUSH hbrBackground;
WORD nClientWidth;
WORD nClientHeight;
RECT rectClient = {0};

HWND ghWnd = NULL;
HINSTANCE ghInstance = NULL;
HWND hListCtrl = NULL;

int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR     lpCmdLine,
					 int       nCmdShow) {
	MSG msg;
	WNDCLASSEX wc;		//����һ�������࣬���渳��ֵ
	HWND hWnd = NULL;

	//hbrBackground = CreateSolidBrush(RGB(0, 0, 0));

	wc.cbSize        = sizeof(WNDCLASSEX);                  //����ֽڳ���
	wc.style         = CS_HREDRAW | CS_VREDRAW;             //����ʽ��
	wc.lpfnWndProc   = (WNDPROC)WndProc;                    //���ڴ�����
	wc.cbClsExtra    = 0;                                   //�����������ṹ֮��Ķ����ֽ���
	wc.cbWndExtra    = 0;                                   //
	wc.hInstance     = hInstance;                           //ʵ�����
	//wc.hIcon         = LoadIcon(hInstance, (LPCTSTR)IDI_APPLICATION);
	wc.hIcon         = LoadIcon(hInstance, (LPCTSTR)IDI_LESSON12_SQLITE3_DB_SDK);
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);         //���
	wc.hbrBackground = (HBRUSH)GetStockObject(COLOR_WINDOWFRAME);//����
	//wc.hbrBackground = hbrBackground;
	wc.lpszMenuName  = NULL;                                //�˵�
	wc.lpszClassName = szWindowClass;                       //������
	//wc.hIconSm       = LoadIcon(wc.hInstance, (LPCTSTR)IDI_APPLICATION);
	wc.hIconSm       = LoadIcon(wc.hInstance, (LPCTSTR)IDI_SMALL);

	if(!RegisterClassEx(&wc)) return FALSE;

	//��������
	hWnd = CreateWindow( szWindowClass,      //������
						 szTitle,            //���ڱ���
						 WS_OVERLAPPEDWINDOW,//���ڷ��
						 GetSystemMetrics(SM_CXSCREEN)/2-410, //�������Ͻǵ�x����
						 GetSystemMetrics(SM_CYSCREEN)/2-225, //�������Ͻǵ�y����
						 820/*CW_USEDEFAULT*/,      //���ڵĿ��
						 450/*CW_USEDEFAULT*/,      //���ڵĸ߶�
						 NULL,               //�����ھ��
						 NULL,               //�˵����
						 hInstance,          //ʵ�����
						 NULL);              //��������

	if (!hWnd) {
	   return FALSE;
	}

	ghInstance = hInstance;
	ghWnd = hWnd;

	ShowWindow(hWnd, nCmdShow);	          //��ʾ����
	UpdateWindow(hWnd);                   //������ʾ

	while (GetMessage(&msg, NULL, 0, 0)){ //��Ϣѭ��
		TranslateMessage(&msg);	          //��Ϣ����
		DispatchMessage(&msg);            //��Ϣ����
	}

	return msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message)
	{
	case WM_CREATE:
		{
			RECT rect;
			INT cx, cy;
			GetClientRect(hWnd, &rect);
			cx = rect.right;
			cy = rect.bottom;

			int rowIndex = 7;
			hListCtrl = CreateWindow("syslistview32", "", WS_VISIBLE|WS_CHILD|WS_BORDER|LVS_REPORT|LVS_SHOWSELALWAYS,
									0, 0, cx, cy, hWnd, NULL, ghInstance, NULL);
			ListView_SetExtendedListViewStyle(hListCtrl, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			// �������
			LV_ITEM lvItem;       // ��
			LV_COLUMN lvColumn;     // ��
			ZeroMemory(&lvItem, sizeof(LV_ITEM));
			ZeroMemory(&lvColumn, sizeof(LV_COLUMN));

			char * A_szColumnName[7] = {"ID", "����", "����", "����ID", "����", "�Ķ���", "��ע"};
			int  A_nColumnWidth[7] = {25, 325, 130, 55, 85, 55, 115};
       
			for(int i=0; i<7; i++){
				lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
				lvColumn.fmt  = (i==3 || i==5 ? LVCFMT_CENTER : LVCFMT_LEFT);
				lvColumn.pszText = A_szColumnName[i];
				lvColumn.cchTextMax = 0;
				lvColumn.cx = A_nColumnWidth[i];
				lvColumn.iSubItem = 0;
				ListView_InsertColumn(hListCtrl, i, &lvColumn);
			}

			char szDisplay[256] = {0};

			sqlite3* db = NULL;
			char* errMsg = NULL;
			sqlite3_stmt* stmt = NULL;
			int rc = 0;

			lvItem.mask = LVIF_PARAM | LVIF_TEXT;
			lvItem.iSubItem  = 0;

			rc = sqlite3_open("..\\lesson12.sqlite3", &db);
			if(rc == SQLITE_OK){
				char szQuery[] = "select id, strTitle, strDate, nTypeID, strTypeName, nCount, strMemo from table_article";
				INT nRow = 0;
				char szText[256] = {0};
				rc = sqlite3_prepare(db, szQuery, -1, &stmt, 0);
				if(rc == SQLITE_OK){
					INT nFields = sqlite3_column_count(stmt);
					while( (sqlite3_step(stmt)) == SQLITE_ROW){
						sprintf(szText, "%s", sqlite3_column_text(stmt, 0));
						lvItem.iItem = nRow;
						lvItem.pszText = szText;
						lvItem.cchTextMax = lstrlen(szText);
						lvItem.lParam = (LPARAM)atoi(szText);
						INT nItemID = ListView_InsertItem(hListCtrl, &lvItem);
						if(nItemID>=0){
							for(int i=1; i<7; i++){
								sprintf(szText, "%s", sqlite3_column_text(stmt, i));
								char szGBK[128] = {0};
								UTF8_GBK(szText, szGBK, sizeof(szGBK));
								ListView_SetItemText(hListCtrl, nItemID, i, szGBK);
							}
						}
						nRow++;
					}
				}else{
					stmt = NULL;
				}
				sqlite3_close(db);
			}else{
				sprintf(szDisplay, "Can't open database: %s", sqlite3_errmsg(db));
			}
		}
		break;
	case WM_SHOWWINDOW:
		PA_DoAppInitialize();
		break;
	case WM_SIZE:
		{
			nClientWidth  = LOWORD(lParam);
			nClientHeight = HIWORD(lParam);
			if(nClientWidth>0 && nClientHeight>0){
				MoveWindow(hListCtrl, 0, 0, nClientWidth, nClientHeight, TRUE);
			}
		}
		break;
	case WM_PAINT:                         //����ˢ��
		{
			HDC hdc;                       //�豸�ľ��
			PAINTSTRUCT ps;                //�ͻ��軭����Ϣ
			hdc = BeginPaint(hWnd, &ps);   //ȡ���豸�����������ʼ�軭
			EndPaint(hWnd, &ps);           //�����軭
		}
		break;
	case WM_DESTROY:                       //�رմ���
		PA_DoAppFinalize();
		PostQuitMessage(0);                //���͹ر���Ϣ
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

void PA_DoAppInitialize(){
}

void PA_DoAppFinalize(){
}

int UTF8_GBK(char* szUtf8, char* szGBK, int nLen){
	int n = MultiByteToWideChar(CP_UTF8, 0, szUtf8, -1, NULL, 0);
	WCHAR* wszGBK = new WCHAR[sizeof(WCHAR) * n];
	memset(wszGBK, 0, sizeof(WCHAR) * n);
	MultiByteToWideChar(CP_UTF8, 0, szUtf8, -1, wszGBK, n);

	n = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	if(n>nLen){
		delete[] wszGBK;
		return -1;
	}
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, n, NULL, NULL);
	delete[] wszGBK;
	wszGBK = NULL;
	return 0;
}