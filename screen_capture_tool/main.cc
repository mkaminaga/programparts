//
// @file main.cc
// @brief Screen capture tool.
// @author Mamoru Kaminaga
// @date 2019-09-21 18:22:39
// Copyright 2019 Mamoru Kaminaga
//
#include <stdio.h>
#include <strsafe.h>
#include <wchar.h>
#include <windows.h>
#include <windowsx.h>
#include "./capture.h"
#include "./folder_dialog.h"
#include "./key_hook.h"
#include "./png_tool.h"
#include "./resource.h"
#include "./task_tray.h"
#include "./util.h"

namespace {
constexpr wchar_t MODULE_FILE_NAME[] = L"ScreenCaptureTool.exe";
constexpr wchar_t WINDOW_NAME[] = L"ScreenCaptureTool";
constexpr wchar_t CLASS_NAME[] = L"ScreenCaptureTool";
constexpr int TASKTRAY_ICONID = 1;
wchar_t output_dir[256] = {0};
CaptureData capture;
}  // namespace

BOOL Cls_OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct) {
  (void)hwnd;
  (void)lpCreateStruct;

  HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);

  // Output path initialization
  if (GetModuleFileName(hInstance, output_dir, ARRAYSIZE(output_dir)) == 0) {
    MessageBox(hwnd, L"Failed to get module file name", L"Error", MB_OK);
    PostQuitMessage(0);
    return (-1);
  }
  output_dir[wcslen(output_dir) - wcslen(MODULE_FILE_NAME) - 1] =
      L'\0';  // Module file path is converted to directory.
#ifdef DEBUG
  fwprintf(stderr, L"Module file dir:%ls\n", output_dir);
#endif

  // Task tray initialization
  NOTIFYICONDATA nid;
  ZeroMemory(&nid, sizeof(nid));
  nid.cbSize = sizeof(nid);
  nid.hWnd = hwnd;
  nid.uID = TASKTRAY_ICONID;
  nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
  nid.uCallbackMessage = WM_TASKTRAY;
  nid.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
  StringCchCopy(nid.szTip, ARRAYSIZE(nid.szTip), L"Task tray test");

  if (Shell_NotifyIcon(NIM_ADD, &nid) != TRUE) {
    MessageBox(hwnd, L"Failed to add an icon on task tray.\n", L"Error", MB_OK);
    return (-1);
  }

  // Key hook initialization
  if (!SetKeyHook(hwnd)) {
    MessageBox(hwnd, L"Failed to set key hook.\n", L"Error", MB_OK);
    return (-1);
  }

  // Capture data initialization
  if (!InitializeCapture(&capture)) {
    MessageBox(hwnd, L"Failed to initialize capture.\n", L"Error", MB_OK);
    return (-1);
  }
  return TRUE;
}

void Cls_OnDestroy(HWND hwnd) {
  (void)hwnd;

  // Key hook finalization
  if (!RemoveKeyHook()) {
    MessageBox(hwnd, L"Failed to remove key hook.\n", L"Error", MB_OK);
  }

  // Task tray finalization
  NOTIFYICONDATA nid;
  ZeroMemory(&nid, sizeof(nid));
  nid.cbSize = sizeof(nid);
  nid.hWnd = hwnd;
  nid.uID = TASKTRAY_ICONID;
  nid.uFlags = 0;
  Shell_NotifyIcon(NIM_DELETE, &nid);

  // Capture data finalization
  FinalizeCapture(&capture);

  PostQuitMessage(0);
}

void Cls_OnClose(HWND hwnd) { DestroyWindow(hwnd); }

void Cls_OnCommand(HWND hwnd, int id, HWND hWndCtl, UINT codeNotify) {
  (void)hwnd;
  (void)id;
  (void)hWndCtl;
  (void)codeNotify;

  switch (id) {
    case IDM_FOLDER: {
      wchar_t buffer[256] = {0};
      if (!GetDirectoryName(hwnd, L"Folder select", NULL, buffer)) {
        MessageBox(hwnd, L"Invalid directory", L"Error", MB_OK);
      } else {
        wcscpy_s(output_dir, ARRAYSIZE(output_dir), buffer);
      }
#ifdef DEBUG
      fwprintf(stderr, L"%ls\n", output_dir);
#endif
    } break;
    case IDM_QUIT:
      DestroyWindow(hwnd);
      break;
    default:
      break;
  }
}

void Cls_OnTaskTray(HWND hwnd, UINT id, UINT uMsg) {
  (void)hwnd;

  if (id != TASKTRAY_ICONID) {
    return;
  }
  switch (uMsg) {
    case WM_RBUTTONDOWN: {
      // Display menu when right button is clicked on task tray icon.
      POINT point;
      GetCursorPos(&point);
      HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
      HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));
      HMENU hSubMenu = GetSubMenu(hMenu, 0);
      TrackPopupMenu(hSubMenu, TPM_LEFTALIGN | TPM_BOTTOMALIGN, point.x,
                     point.y, 0, hwnd, NULL);
    } break;
    default:
      break;
  }
}

void Cls_OnKeyHook(HWND hwnd, WPARAM wParam, LPARAM lParam) {
  (void)hwnd;
  const UINT vk = (UINT)wParam;
  const BOOL fDown = ((lParam & 0x80000000) == 0) ? TRUE : FALSE;

  if (fDown == TRUE) {
    return;
  }

  // Screen capture is executed.
  if ((vk == VK_SCROLL) || (vk == VK_PAUSE)) {
    // File is named by time.
    wchar_t file_name[256] = {0};
    GetTimeFileName(file_name, ARRAYSIZE(file_name), L".png");

    // File path is created.
    wchar_t path[256] = {0};
    wcscat_s(path, ARRAYSIZE(path), output_dir);
    wcscat_s(path, ARRAYSIZE(path), L"\\");
    wcscat_s(path, ARRAYSIZE(path), file_name);
#ifdef DEBUG
    fwprintf(stderr, L"PNG file name:%ls\n", path);
#endif

    // Screen is captured.
    if (!Capture(&capture)) {
      MessageBox(hwnd, L"Failed to capture screen.", L"Error", MB_OK);
      return;
    }
    if (!WritePNGFile(path, capture.png_data)) {
      MessageBox(hwnd, L"Failed to write PNG file.", L"Error", MB_OK);
      return;
    }
    return;
  }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam,
                         LPARAM lParam) {
  switch (message) {
    HANDLE_MSG(hwnd, WM_CREATE, Cls_OnCreate);
    HANDLE_MSG(hwnd, WM_DESTROY, Cls_OnDestroy);
    HANDLE_MSG(hwnd, WM_COMMAND, Cls_OnCommand);
    HANDLE_MSG(hwnd, WM_CLOSE, Cls_OnClose);
    HANDLE_MSG(hwnd, WM_TASKTRAY, Cls_OnTaskTray);
    HANDLE_MSG(hwnd, WM_KEYHOOK, Cls_OnKeyHook);
    default:
      return DefWindowProc(hwnd, message, wParam, lParam);
  }
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPTSTR lpsCmdLine, int nCmdShow) {
  (void)hPrevInstance;
  (void)lpsCmdLine;
  (void)nCmdShow;

#ifdef DEBUG
  FILE* fp = nullptr;
  AllocConsole();
  _wfreopen_s(&fp, L"CONOUT$", L"w", stdout);
  _wfreopen_s(&fp, L"CONOUT$", L"w", stderr);
  _wfreopen_s(&fp, L"CONIN$", L"r", stdin);
#endif

#ifdef DEBUG
  fwprintf(stdout, L"Hello world to stdout!\n");
  fwprintf(stderr, L"Hello world to stderr!\n");
  fwprintf(stderr, L"\n");
#endif

  WNDCLASS wc;
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = CLASS_NAME;
  if (!RegisterClass(&wc)) {
    return FALSE;
  }

  HWND hWnd = CreateWindow(CLASS_NAME, WINDOW_NAME, WS_DISABLED, CW_USEDEFAULT,
                           CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL,
                           NULL, hInstance, NULL);
  if (hWnd == NULL) {
    return FALSE;
  }
  ShowWindow(hWnd, SW_HIDE);

  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0) > 0) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

#ifdef DEBUG
  FreeConsole();
#endif
  return 0;
}
