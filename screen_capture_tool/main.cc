//
// @file main.cc
// @brief Screen capture tool.
// @author Mamoru Kaminaga
// @date 2019-09-21 18:22:39
// Copyright 2019 Mamoru Kaminaga
//
#include <stdio.h>
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
constexpr int TRAY_ICON_ID = 1;
wchar_t save_dir[256] = {0};
CaptureData capture;
HMENU hMenu = NULL;
HMENU hSubMenu = NULL;
CAPTUREMODE capture_mode = CAPTUREMODE_SCREEN;
}  // namespace

void ChangeCaptureMode(CAPTUREMODE mode) {
  capture_mode = mode;
  CheckMenuItem(hSubMenu, IDM_SCREEN, MF_UNCHECKED);
  CheckMenuItem(hSubMenu, IDM_WINDOW, MF_UNCHECKED);
  switch (mode) {
    case CAPTUREMODE_SCREEN:
      CheckMenuItem(hSubMenu, IDM_SCREEN, MF_CHECKED);
      break;
    case CAPTUREMODE_WINDOW:
      CheckMenuItem(hSubMenu, IDM_WINDOW, MF_CHECKED);
      break;
    default:
      break;
  }
}

BOOL Cls_OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct) {
  (void)hwnd;
  (void)lpCreateStruct;

  HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);

  // Initialization of output path
  if (GetModuleFileName(hInstance, save_dir, ARRAYSIZE(save_dir)) == 0) {
    MessageBox(hwnd, L"Failed to get module file name", L"Error", MB_OK);
    PostQuitMessage(0);
    return (-1);
  }
  save_dir[wcslen(save_dir) - wcslen(MODULE_FILE_NAME) - 1] =
      L'\0';  // Module file path is converted to directory.
#ifdef DEBUG
  fwprintf(stderr, L"Module file dir:%ls\n", save_dir);
#endif

  // Initialization of task tray
  if (!SetTaskTrayIcon(hwnd, TRAY_ICON_ID, IDI_ICON1)) {
    MessageBox(hwnd, L"Failed to initialize task tray.\n", L"Error", MB_OK);
    return (-1);
  }

  // Initialization of key hook
  if (!SetKeyHook(hwnd)) {
    MessageBox(hwnd, L"Failed to set key hook.\n", L"Error", MB_OK);
    RemoveTaskTrayIcon(hwnd, TRAY_ICON_ID);
    return (-1);
  }

  // Initialization of menu.
  hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));
  hSubMenu = GetSubMenu(hMenu, 0);
  ChangeCaptureMode(CAPTUREMODE_SCREEN);

  // Initialization of capture data
  if (!InitializeCapture(&capture)) {
    MessageBox(hwnd, L"Failed to initialize capture.\n", L"Error", MB_OK);
    RemoveTaskTrayIcon(hwnd, TRAY_ICON_ID);
    RemoveKeyHook();
    return (-1);
  }
  return TRUE;
}

void Cls_OnDestroy(HWND hwnd) {
  (void)hwnd;

  // Finalization of capture data
  FinalizeCapture(&capture);

  // Finalization of menu.
  DestroyMenu(hMenu);

  // Finalization of key hook
  RemoveKeyHook();

  // Finalization of task tray
  RemoveTaskTrayIcon(hwnd, TRAY_ICON_ID);

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
      // Folder select dialog is called.
      wchar_t buffer[256] = {0};
      if (!GetDirectoryName(hwnd, L"Folder select", NULL, buffer)) {
        if (buffer != NULL) {
          MessageBox(hwnd, L"Invalid directory", L"Error", MB_OK);
        }
      } else {
        wcscpy_s(save_dir, ARRAYSIZE(save_dir), buffer);
      }
#ifdef DEBUG
      fwprintf(stderr, L"%ls\n", save_dir);
#endif
    } break;
    case IDM_SCREEN:
      ChangeCaptureMode(CAPTUREMODE_SCREEN);
#ifdef DEBUG
      fwprintf(stderr, L"CAPTUREMODE_SCREEN\n");
#endif
      break;
    case IDM_WINDOW:
#ifdef DEBUG
      fwprintf(stderr, L"CAPTUREMODE_WINDOW\n");
#endif
      ChangeCaptureMode(CAPTUREMODE_WINDOW);
      break;
    case IDM_QUIT:
      DestroyWindow(hwnd);
      break;
    default:
      break;
  }
}

void Cls_OnTaskTray(HWND hwnd, UINT id, UINT uMsg) {
  (void)hwnd;

  if (id != TRAY_ICON_ID) {
    return;
  }
  switch (uMsg) {
    case WM_RBUTTONDOWN: {
      // Display menu when right button is clicked on task tray icon.
      POINT point;
      GetCursorPos(&point);
      SetForegroundWindow(hwnd);
      TrackPopupMenu(hSubMenu, TPM_LEFTALIGN | TPM_BOTTOMALIGN, point.x,
                     point.y, 0, hwnd, NULL);
      PostMessage(hwnd, WM_NULL, 0, 0);
    } break;
    case WM_LBUTTONDOWN:
      MessageBox(hwnd, L"Screen capture tool.\nCopyright 2019 Mamoru Kaminaga",
                 MODULE_FILE_NAME, MB_OK);
      break;
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

  // Any shutter button is pushed.
  if ((vk == VK_SCROLL) || (vk == VK_PAUSE)) {
    // Screen is captured.
    if (!Capture(capture_mode, &capture)) {
      return;
    }

    // File is named by time.
    wchar_t file[256] = {0};
    GetTimeString(file, ARRAYSIZE(file));
    wcscat_s(file, ARRAYSIZE(file), L".png");

    // File path is created.
    wchar_t path[256] = {0};
    wcscat_s(path, ARRAYSIZE(path), save_dir);
    wcscat_s(path, ARRAYSIZE(path), L"\\");
    wcscat_s(path, ARRAYSIZE(path), file);
#ifdef DEBUG
    fwprintf(stderr, L"PNG file name:%ls\n", path);
#endif

    // PNG file is exported.
    if (!WritePNGFile(path, capture.png_data)) {
      MessageBox(hwnd, L"Failed to write PNG file.", L"Error", MB_OK);
      return;
    }

    SetForegroundWindow(hwnd);
    MessageBox(hwnd, file, MODULE_FILE_NAME, MB_OK | MB_TOPMOST);
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

  // Multi instance check.
  HANDLE hMutex = CreateMutex(NULL, TRUE, L"screen_capture_tool");
  if (GetLastError() == ERROR_ALREADY_EXISTS) {
    MessageBox(NULL, L"The process is already run", MODULE_FILE_NAME, MB_OK);
    ReleaseMutex(hMutex);
    CloseHandle(hMutex);
    return 1;
  }

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

  // Initialization of COM.
  CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

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
    // Release mutex for multi instance check.
    ReleaseMutex(hMutex);
    CloseHandle(hMutex);
    return 1;
  }

  HWND hWnd = CreateWindow(CLASS_NAME, WINDOW_NAME, WS_DISABLED, CW_USEDEFAULT,
                           CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL,
                           NULL, hInstance, NULL);
  if (hWnd == NULL) {
    // Release mutex for multi instance check.
    ReleaseMutex(hMutex);
    CloseHandle(hMutex);
    return 1;
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

  // Finalization of COM.
  CoUninitialize();

  // Release mutex for multi instance check.
  ReleaseMutex(hMutex);
  CloseHandle(hMutex);
  return 0;
}
