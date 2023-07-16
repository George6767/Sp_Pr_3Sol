#include <windows.h>
#include <windowsx.h>
#include <tchar.h>

LPCTSTR lpszClass = TEXT("SpPr3_Class");
LPCTSTR lpszAppTitle = TEXT("������� ���� ���������� SpPr3. ���������� ���������");
LPCTSTR lpszDestroyMessage = TEXT("��������� WM_DESTROY");

//-- Prototypes -------------------
LRESULT CALLBACK SpPr3_WndProc(HWND, UINT, WPARAM, LPARAM);

//-- Global Variables ------------
HINSTANCE g_hInst;

// ��������� �������
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPTSTR lpszCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	MSG msg;
	HWND hWnd;
	g_hInst = hInstance;

	memset(&wc, 0, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = lpszClass;
	wc.lpfnWndProc = SpPr3_WndProc;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
	wc.hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, TEXT("������ ����������� ������ ����!"),
			TEXT("������"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	hWnd = CreateWindowEx(NULL, lpszClass, lpszAppTitle,
		WS_OVERLAPPEDWINDOW, 200, 100, 800, 600,
		NULL, NULL, hInstance, NULL);
	if (!hWnd)
	{
		MessageBox(NULL, TEXT("���� �� �������!"),
			TEXT("������"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


// ������� ���������
LRESULT CALLBACK SpPr3_WndProc(HWND hWnd, UINT messageID, WPARAM wParam, LPARAM lParam)
{

	switch (messageID)
	{
	case WM_CREATE:
	{
		MessageBox(hWnd, TEXT("����������� ���������� WM_CREATE"), TEXT("From WM_CREATE"), MB_OK);

		HWND hBTExit;
		hBTExit = CreateWindowEx(0, TEXT("BUtton"), WS_CHILD | WS_VISIBLE,
			50, 50, 100, 30, hWnd, (HMENU)IDCANCEL, g_hInst, NULL);
		if (!hBTExit)return (-1);

	}return0;

	case WM_COMMAND:
	{int id, event;
	id = LOWORD(wParam);
	event = HIWORD(wPARAM);
	switch (id)
	{
	case IDCANCEL:
	{
		DestroyWindow(hWND);
	}break;


	}


	}break;

	case WM_LBUTTONDOWN:
	{
		HDC hdc;
		hdc = GetDC(hWnd);
		int x; // = 50;
		int y; // = 100;
		x = (int)(short)LOWORD(lParam);
		y = GET_Y_LPARAM(lParam);
		LPCTSTR lpszLbuttonDownMessage = TEXT("��������� ��������� WM_LBUTTONDOWN,"
			" ������� ���������� � ���� ��� ������ ����� ������ ����");
		TextOut(hdc, x, y lpszLbuttonDownMessage, lstrlen(lpszLbuttonDownMessage));
		ReleaseDC(hWnd, hdc);


	}break;

	case WM_PAINT: // ����� ��� ���������� ����
	{	HDC hDC;
	PAINTSTRUCT ps;
	hDC = BeginPaint(hWnd, &ps);	// ��������� ��������� ���
	// ���������� ����
	LPCTSTR lpszHelloText = TEXT("Hello, World Win32 App!");
	TextOut(hDC, 10, 10, lpszHelloText, lstrlen(lpszHelloText)); // ����� � ��������
	EndPaint(hWnd, &ps); // ���������� ���������� ����
	}	break;

	case WM_DESTROY: // ���������� ������ ����������
	{
		MessageBox(hWnd, lpszDestroyMessage, TEXT("From WM_DESTROY"), MB_OK);
		PostQuitMessage(5); // ������� WM_QUIT ����������
	}break;

	default: // ����� "����������� �� ���������"
		return(DefWindowProc(hWnd, messageID, wParam, lParam));
	}
	return 0;// ��� ������ � "break"

}
