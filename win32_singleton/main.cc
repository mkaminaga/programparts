//
// @file main.cc
// @brief Single launch test.
// @author Mamoru Kaminaga
// @date 2019-10-02 17:45:28
// Copyright 2019 Mamoru Kaminaga
//
#include <stdlib.h>
#include <windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPTSTR lpsCmdLine, int nCmdShow) {
  (void)hInstance;
  (void)hPrevInstance;
  (void)lpsCmdLine;
  (void)nCmdShow;

  HANDLE hMutex = CreateMutex(NULL, TRUE, L"original_name");
  if (GetLastError() == ERROR_ALREADY_EXISTS) {
    MessageBox(NULL, L"The process is already run", L"main.exe", MB_OK);
    ReleaseMutex(hMutex);
    CloseHandle(hMutex);
    return 1;
  }
  system("pause");

  ReleaseMutex(hMutex);
  CloseHandle(hMutex);
  return 0;
}
