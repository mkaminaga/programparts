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
#include <vector>
#include "./png_tool.h"

bool Capture(PNGData *png_data) {
  assert(png_data);

  // The size of desktop window is acquired.
  RECT rect;
  GetWindowRect(GetDesktopWindow(), &rect);
  const int width = rect.right;
  const int height = rect.bottom;

  // Memory device context is created.
  HDC memDC = CreateCompatibleDC(NULL);

  // DIB section and DDB is created.
  BITMAPINFOHEADER bmiHeader;
  ZeroMemory(&bmiHeader, sizeof(bmiHeader));
  bmiHeader.biSize = sizeof(bmiHeader);
  bmiHeader.biWidth = width;
  bmiHeader.biHeight = height;
  bmiHeader.biPlanes = 1;
  bmiHeader.biBitCount = 24;  // 24 bit BITMAP.

  BITMAPINFO bmi;
  bmi.bmiHeader = bmiHeader;

  LPVOID memDIB = NULL;
  HBITMAP memBM = CreateDIBSection(NULL, (LPBITMAPINFO)&bmi, DIB_RGB_COLORS,
                                   &memDIB, NULL, 0);

  // Set DDB to memory device context.
  HBITMAP prevBM = (HBITMAP)SelectObject(memDC, memBM);

  // DIB Section is set to memory DC.
  if (BitBlt(memDC, 0, 0, width, height, GetWindowDC(GetDesktopWindow()), 0, 0,
             SRCCOPY) == 0) {
    SelectObject(memDC, prevBM);
    DeleteObject(memBM);
    DeleteDC(memDC);
    return false;
  }

#ifdef DEBUG
  fwprintf(stderr, L"width = %d\n", width);
  fwprintf(stderr, L"height = %d\n", height);
  fwprintf(stderr, L"\n");
#endif

  // DIB is converted to PNG.
  png_data->width = width;
  png_data->height = height;
  png_data->bit_depth = 8;
  png_data->rowbytes = width * 4;
  png_data->channels = 4;
  png_data->color_type = PNG_COLOR_TYPE_RGBA;
  png_data->interlace_type = PNG_INTERLACE_NONE;
  png_data->compression_type = PNG_COMPRESSION_TYPE_DEFAULT;
  png_data->filter_type = PNG_FILTER_TYPE_DEFAULT;

  png_data->red_buffer.resize(width * height);
  png_data->green_buffer.resize(width * height);
  png_data->blue_buffer.resize(width * height);
  png_data->alpha_buffer.resize(width * height);

  int bm_width = width * 3;
  if ((width * 3) % 4) {
    bm_width += (4 - (width * 3) % 4);  // Set padding.
  }

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      png_data->blue_buffer[y * width + x] =
          *((LPBYTE)memDIB + (height - 1 - y) * bm_width + x * 3);
      png_data->green_buffer[y * width + x] =
          *((LPBYTE)memDIB + (height - 1 - y) * bm_width + x * 3 + 1);
      png_data->red_buffer[y * width + x] =
          *((LPBYTE)memDIB + (height - 1 - y) * bm_width + x * 3 + 2);
      png_data->alpha_buffer[y * width + x] = 255;
    }
  }

  // Restore and release.
  SelectObject(memDC, prevBM);
  DeleteObject(memBM);
  DeleteDC(memDC);
  return true;
}
