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
  GetWindowRect(GetDesktopWindow(), &(capture->rect_target));
  capture->width_screen = capture->rect_target.right;
  capture->height_screen = capture->rect_target.bottom;

  // Memory device context is created.
  capture->memDC = CreateCompatibleDC(NULL);

  // DIB section and DDB is created.
  BITMAPINFOHEADER bmiHeader;
  ZeroMemory(&bmiHeader, sizeof(bmiHeader));
  bmiHeader.biSize = sizeof(bmiHeader);
  bmiHeader.biWidth = capture->width_screen;
  bmiHeader.biHeight = capture->height_screen;
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
  const int buffer_size = capture->width_screen * capture->height_screen;
  capture->png_data.red_buffer.resize(buffer_size);
  capture->png_data.green_buffer.resize(buffer_size);
  capture->png_data.blue_buffer.resize(buffer_size);
  capture->png_data.alpha_buffer.resize(buffer_size);

#ifdef DEBUG
  fwprintf(stderr, L"width_screen = %d\n", capture->width_screen);
  fwprintf(stderr, L"height_screen = %d\n", capture->height_screen);
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

bool Capture(CAPTUREMODE capture_mode, CaptureData *capture) {
  assert(capture);

  // RECT of target region is acquired.
  HWND hwnd_desktop = GetDesktopWindow();
  switch (capture_mode) {
    case CAPTUREMODE_SCREEN:
      GetWindowRect(hwnd_desktop, &(capture->rect_target));
#ifdef DEBUG
      fwprintf(stderr, L"CAPTUREMODE_SCREEN\n");
#endif
      break;
    case CAPTUREMODE_WINDOW: {
      GetWindowRect(GetForegroundWindow(), &(capture->rect_target));
    } break;
    default:
      break;
  }
  const int width_target =
      capture->rect_target.right - capture->rect_target.left;
  const int height_target =
      capture->rect_target.bottom - capture->rect_target.top;
#ifdef DEBUG
  fwprintf(stderr, L"width_target = %d\n", width_target);
  fwprintf(stderr, L"height_target = %d\n", height_target);
  fwprintf(stderr, L"\n");
  fwprintf(stderr, L"top = %d\n", capture->rect_target.top);
  fwprintf(stderr, L"left = %d\n", capture->rect_target.left);
  fwprintf(stderr, L"\n");
  fwprintf(stderr, L"bottom = %d\n", capture->rect_target.bottom);
  fwprintf(stderr, L"right = %d\n", capture->rect_target.right);
  fwprintf(stderr, L"\n");
#endif

  // DIB Section is set to memory DC.
  if (BitBlt(capture->memDC, 0, 0, capture->width_screen,
             capture->height_screen, GetWindowDC(hwnd_desktop), 0, 0,
             SRCCOPY) == 0) {
    MessageBox(NULL, L"Bit transfer is failed", L"Error", MB_OK);
    return false;
  }

  // DIB is converted to PNG.
  capture->png_data.width = width_target;
  capture->png_data.height = height_target;
  capture->png_data.bit_depth = 8;
  capture->png_data.rowbytes = width_target * 4;
  capture->png_data.channels = 4;
  capture->png_data.color_type = PNG_COLOR_TYPE_RGBA;
  capture->png_data.interlace_type = PNG_INTERLACE_NONE;
  capture->png_data.compression_type = PNG_COMPRESSION_TYPE_DEFAULT;
  capture->png_data.filter_type = PNG_FILTER_TYPE_DEFAULT;

  int bm_width = capture->width_screen * 3;
  if ((capture->width_screen * 3) % 4) {
    bm_width += (4 - (capture->width_screen * 3) % 4);  // Set padding.
  }

  // Target region of screen is copied to PNG buffer.
  int offset = 0;
  for (int y = 0; y < height_target; y++) {
    for (int x = 0; x < width_target; x++) {
      offset = (capture->height_screen - capture->rect_target.top - y - 1) *
                   bm_width +
               (capture->rect_target.left + x) * 3;
      capture->png_data.blue_buffer[y * width_target + x] =
          ((LPBYTE)capture->memDIB)[offset];
      capture->png_data.green_buffer[y * width_target + x] =
          ((LPBYTE)capture->memDIB)[offset + 1];
      capture->png_data.red_buffer[y * width_target + x] =
          ((LPBYTE)capture->memDIB)[offset + 2];
      capture->png_data.alpha_buffer[y * width_target + x] = 255;
    }
  }
  return true;
}
