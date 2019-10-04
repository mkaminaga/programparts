//
// @file capture.h
// @brief Screen capture functions.
// @author Mamoru Kaminaga
// @date 2019-09-21 18:22:39
// Copyright 2019 Mamoru Kaminaga
//
#ifndef _CAPTURE_H_
#define _CAPTURE_H_

#include <windows.h>
#include "./png_tool.h"

struct CaptureData {
  int width_screen;   // Width of screen.
  int height_screen;  // Height of screen.
  RECT rect_target;   // RECT of target (screen or window).
  HDC memDC;
  LPVOID memDIB;
  HBITMAP memBM;
  HBITMAP prevBM;
  PNGData png_data;
};

enum CAPTUREMODE {
  CAPTUREMODE_SCREEN,
  CAPTUREMODE_WINDOW,
};

bool InitializeCapture(CaptureData *capture);
void FinalizeCapture(CaptureData *capture);
bool Capture(CAPTUREMODE capture_mode, CaptureData *capture);

#endif  // _CAPTURE_H_
