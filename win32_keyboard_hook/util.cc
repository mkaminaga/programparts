//
// @file util.cc
// @brief Test for keyboard hook.
// @author Mamoru Kaminaga
// @date 2019-07-04 18:49:29
// Copyright 2019 Mamoru Kaminaga
//
#define DLLAPI extern "C" __declspec(dllexport)

#include "./util.h"
#include <stdio.h>
#include <windows.h>

#pragma data_seg(".key_hook")
HHOOK hKeyHook = 0;
HWND hWndDest = 0;
#pragma data_seg()

namespace {
HINSTANCE hInstance;
}  // namespace

DLLAPI LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam) {
  if (code < 0) {
    // The hook procedure must pass the message to the CallNextHookEx
    // without further processing, then should return the return value.
    return CallNextHookEx(hKeyHook, code, wParam, lParam);
  }
  switch (code) {
    case HC_ACTION:
      PostMessage(hWndDest, WM_KEYHOOK, wParam, lParam);
      break;
    case HC_NOREMOVE:
      break;
    default:
      break;
  }
  return CallNextHookEx(hKeyHook, code, wParam, lParam);
}

DLLAPI bool StartKeyboardHook(HWND hwnd) {
  // Set the keyboard hook.
  hKeyHook = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, hInstance, 0);
  if (hKeyHook == NULL) {
    hWndDest = NULL;
    return false;
  }
  // The destination of the hook signal.
  hWndDest = hwnd;
#ifdef DEBUG
  fwprintf(stderr, L"1 StartKeyboardHook is called.\n");
  fwprintf(stdout, L"2 StartKeyboardHook is called.\n");
#endif
  return true;
}

DLLAPI bool StopKeyboardHook() {
  // Reset the keyboard hook.
  if (UnhookWindowsHookEx(hKeyHook) == 0) {
    return false;
  }
  hKeyHook = NULL;
  hWndDest = NULL;
  return true;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpvReserved) {
  (void)lpvReserved;
  switch (dwReason) {
    case DLL_PROCESS_ATTACH:
      hInstance = hinstDLL;
      hKeyHook = NULL;
      hWndDest = NULL;
      break;
    case DLL_THREAD_ATTACH:
      break;
    case DLL_THREAD_DETACH:
      break;
    case DLL_PROCESS_DETACH:
      break;
  }
  return TRUE;
}
