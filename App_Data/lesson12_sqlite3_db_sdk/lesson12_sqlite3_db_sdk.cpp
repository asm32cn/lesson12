// lesson12_sqlite3_db_sdk.cpp : Defines the entry point for the application.
//

/*
错误：unexpected end of file while looking for precompiled headerdirective
分析：工程头文件处理的错误。
解决办法如下：
1、右键点工程名,选设置,然后选c/c++属性页,再选catagory选单中选 precompiled header ,将选项置成no use 或者autometic
2、如果使用的是Win32工程，可能就是错误文件没有包含：#include "stdafx.h" ，添加该包含即可。
*/

#include <windows.h>
#include <commctrl.h>
#include <stdio.h>

#include "sqlite3.h"
#include "resource.h"

char szTitle[32]="lesson12-sqlite3-db-sdk";       //窗口的标题
char szWindowClass[32]="lesson12-sqlite3-db-sdk"; //窗口的名称


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
	WNDCLASSEX wc;		//定义一个窗口类，下面赋初值
	HWND hWnd = NULL;

	//hbrBackground = CreateSolidBrush(RGB(0, 0, 0));

	wc.cbSize        = sizeof(WNDCLASSEX);                  //类的字节长度
	wc.style         = CS_HREDRAW | CS_VREDRAW;             //窗口式样
	wc.lpfnWndProc   = (WNDPROC)WndProc;                    //窗口处理函数
	wc.cbClsExtra    = 0;                                   //分配给窗口类结构之后的额外字节数
	wc.cbWndExtra    = 0;                                   //
	wc.hInstance     = hInstance;                           //实例句柄
	//wc.hIcon         = LoadIcon(hInstance, (LPCTSTR)IDI_APPLICATION);
	wc.hIcon         = LoadIcon(hInstance, (LPCTSTR)IDI_LESSON12_SQLITE3_DB_SDK);
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);         //光标
	wc.hbrBackground = (HBRUSH)GetStockObject(COLOR_WINDOWFRAME);//背景
	//wc.hbrBackground = hbrBackground;
	wc.lpszMenuName  = NULL;                                //菜单
	wc.lpszClassName = szWindowClass;                       //窗口名
	//wc.hIconSm       = LoadIcon(wc.hInstance, (LPCTSTR)IDI_APPLICATION);
	wc.hIconSm       = LoadIcon(wc.hInstance, (LPCTSTR)IDI_SMALL);

	if(!RegisterClassEx(&wc)) return FALSE;

	//创建窗口
	hWnd = CreateWindow( szWindowClass,      //窗口名
						 szTitle,            //窗口标题
						 WS_OVERLAPPEDWINDOW,//窗口风格
						 GetSystemMetrics(SM_CXSCREEN)/2-410, //窗口左上角的x坐标
						 GetSystemMetrics(SM_CYSCREEN)/2-225, //窗口左上角的y坐标
						 820/*CW_USEDEFAULT*/,      //窗口的宽度
						 450/*CW_USEDEFAULT*/,      //窗口的高度
						 NULL,               //父窗口句柄
						 NULL,               //菜单句柄
						 hInstance,          //实例句柄
						 NULL);              //创建参数

	if (!hWnd) {
	   return FALSE;
	}

	ghInstance = hInstance;
	ghWnd = hWnd;

	ShowWindow(hWnd, nCmdShow);	          //显示窗口
	UpdateWindow(hWnd);                   //立即显示

	while (GetMessage(&msg, NULL, 0, 0)){ //消息循环
		TranslateMessage(&msg);	          //消息解释
		DispatchMessage(&msg);            //消息发送
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
			// 添加数据
			LV_ITEM lvItem;       // 项
			LV_COLUMN lvColumn;     // 列
			ZeroMemory(&lvItem, sizeof(LV_ITEM));
			ZeroMemory(&lvColumn, sizeof(LV_COLUMN));

			char * A_szColumnName[7] = {"ID", "标题", "日期", "分类ID", "分类", "阅读数", "备注"};
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
	case WM_PAINT:                         //窗口刷新
		{
			HDC hdc;                       //设备文句柄
			PAINTSTRUCT ps;                //客户描画区信息
			hdc = BeginPaint(hWnd, &ps);   //取得设备环境句柄并开始描画
			EndPaint(hWnd, &ps);           //结束描画
		}
		break;
	case WM_DESTROY:                       //关闭窗口
		PA_DoAppFinalize();
		PostQuitMessage(0);                //发送关闭消息
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