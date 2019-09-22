//
// @file capture.cc
// @brief Screen capture functions.
// @author Mamoru Kaminaga
// @date 2019-09-21 18:22:39
// Copyright 2019 Mamoru Kaminaga
//
#include "./capture.h"
#include <assert.h>
#include <png.h>
#include <windows.h>
#include <vector>
#include "./png_tool.h"

bool InitializeCapture(CaptureData *capture) {
  assert(capture);

  // The size of desktop window is acquired.
  RECT rect;
  GetWindowRect(GetDesktopWindow(), &rect);
  capture->width = rect.right;
  capture->height = rect.bottom;

  // Memory device context is created.
  capture->memDC = CreateCompatibleDC(NULL);

  // DIB section and DDB is created.
  BITMAPINFOHEADER bmiHeader;
  ZeroMemory(&bmiHeader, sizeof(bmiHeader));
  bmiHeader.biSize = sizeof(bmiHeader);
  bmiHeader.biWidth = capture->width;
  bmiHeader.biHeight = capture->height;
  bmiHeader.biPlanes = 1;
  bmiHeader.biBitCount = 24;  // 24 bit BITMAP.

  BITMAPINFO bmi;
  bmi.bmiHeader = bmiHeader;

  capture->memDIB = NULL;
  capture->memBM = CreateDIBSection(NULL, (LPBITMAPINFO)&bmi, DIB_RGB_COLORS,
                                    &(capture->memDIB), NULL, 0);
  if ((!capture->memBM) || (!capture->memDIB)) {
    return false;
  }

  // Set DDB to memory device context.
  capture->prevBM = (HBITMAP)SelectObject(capture->memDC, capture->memBM);

  // Resize PNG data buffer.
  capture->png_data.red_buffer.resize(capture->width * capture->height);
  capture->png_data.green_buffer.resize(capture->width * capture->height);
  capture->png_data.blue_buffer.resize(capture->width * capture->height);
  capture->png_data.alpha_buffer.resize(capture->width * capture->height);

#ifdef DEBUG
  fwprintf(stderr, L"width = %d\n", capture->width);
  fwprintf(stderr, L"height = %d\n", capture->height);
  fwprintf(stderr, L"\n");
#endif
  return true;
}

void FinalizeCapture(CaptureData *capture) {
  assert(capture);

  // Restore and release.
  SelectObject(capture->memDC, capture->prevBM);
  DeleteObject(capture->memBM);
  DeleteDC(capture->memDC);
}

bool Capture(CaptureData *capture) {
  assert(capture);

  // DIB Section is set to memory DC.
  if (BitBlt(capture->memDC, 0, 0, capture->width, capture->height,
             GetWindowDC(GetDesktopWindow()), 0, 0, SRCCOPY) == 0) {
    return false;
  }

  // DIB is converted to PNG.
  capture->png_data.width = capture->width;
  capture->png_data.height = capture->height;
  capture->png_data.bit_depth = 8;
  capture->png_data.rowbytes = capture->width * 4;
  capture->png_data.channels = 4;
  capture->png_data.color_type = PNG_COLOR_TYPE_RGBA;
  capture->png_data.interlace_type = PNG_INTERLACE_NONE;
  capture->png_data.compression_type = PNG_COMPRESSION_TYPE_DEFAULT;
  capture->png_data.filter_type = PNG_FILTER_TYPE_DEFAULT;

  int bm_width = capture->width * 3;
  if ((capture->width * 3) % 4) {
    bm_width += (4 - (capture->width * 3) % 4);  // Set padding.
  }

  for (int y = 0; y < capture->height; y++) {
    for (int x = 0; x < capture->width; x++) {
      capture->png_data.blue_buffer[y * capture->width + x] =
          ((LPBYTE)
               capture->memDIB)[(capture->height - 1 - y) * bm_width + x * 3];
      capture->png_data.green_buffer[y * capture->width + x] =
          ((LPBYTE)capture
               ->memDIB)[(capture->height - 1 - y) * bm_width + x * 3 + 1];
      capture->png_data.red_buffer[y * capture->width + x] =
          ((LPBYTE)capture
               ->memDIB)[(capture->height - 1 - y) * bm_width + x * 3 + 2];
      capture->png_data.alpha_buffer[y * capture->width + x] = 255;
    }
  }
  return true;
}
