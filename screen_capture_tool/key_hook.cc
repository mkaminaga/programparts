//
// @file key_hook.cc
// @brief Keyboard hook related functions.
// @author Mamoru Kaminaga
// @date 2019-09-21 18:31:20
// Copyright 2019 Mamoru Kaminaga
//
#define DLLAPI extern "C" __declspec(dllexport)

#include "./key_hook.h"
#include <stdio.h>
#include <windows.h>

#pragma data_seg(".shared")
DLLAPI HWND hWndDest = NULL;
DLLAPI HHOOK hHook = NULL;
#pragma data_seg()
#pragma comment(linker, "/SECTION:.shared,rws")

namespace {
HINSTANCE hInstance;
}  // namespace

DLLAPI LRESULT CALLBACK KeyProc(int code, WPARAM wParam, LPARAM lParam) {
  if (code < 0) {
    // The hook procedure must pass the message to the CallNextHookEx
    // without further processing, then should return the return value.
    return CallNextHookEx(hHook, code, wParam, lParam);
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
  return CallNextHookEx(hHook, code, wParam, lParam);
}

DLLAPI bool SetKeyHook(HWND hwnd) {
  hHook = SetWindowsHookEx(WH_KEYBOARD, KeyProc, hInstance, 0);
  if (hHook == NULL) {
    hWndDest = NULL;
    return false;
  }
  hWndDest = hwnd;
  return true;
}

DLLAPI bool RemoveKeyHook() {
  if (UnhookWindowsHookEx(hHook) == 0) {
    return false;
  }
  hHook = NULL;
  hWndDest = NULL;
  return true;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
  (void)lpvReserved;
  switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
      hInstance = hinstDLL;
      hHook = NULL;
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
