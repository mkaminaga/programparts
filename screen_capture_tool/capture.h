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
  int width;
  int height;
  HDC memDC;
  LPVOID memDIB;
  HBITMAP memBM;
  HBITMAP prevBM;
  PNGData png_data;
};

bool InitializeCapture(CaptureData *capture);
void FinalizeCapture(CaptureData *capture);
bool Capture(CaptureData *capture);

#endif  // _CAPTURE_H_
