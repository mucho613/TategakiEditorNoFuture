#define UNICODE
#define _UNICODE

#define WIDTH 800
#define HEIGHT 600

#include <windows.h>
#include <Richedit.h>

HWND hWnd, hWndRichEdit;
RECT clientRect;

LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch (msg) { 
  case WM_PAINT:
    GetClientRect(hWnd, &clientRect);
    SetWindowPos(hWndRichEdit, NULL, clientRect.left, clientRect.top, clientRect.right, clientRect.bottom, SWP_NOOWNERZORDER);
    return 0;
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  }
  return DefWindowProc(hWnd, msg, wParam, lParam);
}
              
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nShowCmd)
{
  MSG msg;
  WNDCLASS wc;

  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = WinProc;
  wc.cbClsExtra = wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  wc.lpszClassName = TEXT("Test");
  wc.lpszMenuName = NULL;

  if (!RegisterClass(&wc)) {
    MessageBox(hWnd, TEXT("Failed to register class"), TEXT("Error"), MB_OK);
    return -1;
  }

  hWnd = CreateWindow(TEXT("Test"), TEXT("TategakiEditor"),
    WS_VISIBLE | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_POPUP,
    0, 0, WIDTH, HEIGHT, NULL, NULL, hInstance, NULL);

  LoadLibrary(TEXT("Msftedit.dll"));

  GetClientRect(hWnd, &clientRect);

  hWndRichEdit = CreateWindow(MSFTEDIT_CLASS, TEXT("縦書き"),
    ES_VERTICAL | ES_MULTILINE | ES_AUTOVSCROLL | WS_VISIBLE | WS_CHILD | WS_TABSTOP,
    clientRect.left, clientRect.top, clientRect.right, clientRect.bottom, hWnd, NULL, hInstance, NULL);

  if (hWnd == NULL || hWndRichEdit == NULL) {
    MessageBox(hWnd, TEXT("ウィンドウ作成失敗"), TEXT("Error"), MB_OK);
    return -1;
  }

  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }                                                                             

  UnregisterClass(TEXT("Test"), hInstance);

  return 0;
}
