//
// @file util.cc
// @brief Test project for screen capture.
// @author Mamoru Kaminaga
// @date 2019-09-20 12:51:16
// Copyright 2019 Mamoru Kaminaga
//
#include "./util.h"
#include <assert.h>
#include <png.h>
#include <setjmp.h>
#include <stdint.h>
#include <string.h>
#include <vector>

namespace {}  // namespace

bool CaptureTest(TESTCASE test_case, PNGData *png_data) {
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
  switch (test_case) {
    case TESTCASE_PAINT_DESKTOP:
#ifdef DEBUG
      fwprintf(stderr, L"Test case 1: PaintDesktop().\n");
#endif
      if (PaintDesktop(memDC) == 0) {
        SelectObject(memDC, prevBM);
        DeleteObject(memBM);
        DeleteDC(memDC);
        return false;
      }
      break;
    case TESTCASE_PAINT_WINDOW:
#ifdef DEBUG
      fwprintf(stderr, L"Test case 2: PaintDesktop() & GetShellWindow().\n");
#endif
      if (PrintWindow(GetShellWindow(), memDC, 0) == 0) {
        SelectObject(memDC, prevBM);
        DeleteObject(memBM);
        DeleteDC(memDC);
        return false;
      }
      break;
    case TESTCASE_BITBLT:
#ifdef DEBUG
      fwprintf(stderr, L"Test case 3: BitBlt() & GetDesktopWindow() .\n");
#endif
      if (BitBlt(memDC, 0, 0, width, height, GetWindowDC(GetDesktopWindow()), 0,
                 0, SRCCOPY) == 0) {
        SelectObject(memDC, prevBM);
        DeleteObject(memBM);
        DeleteDC(memDC);
        return false;
      }
      break;
    default:
      break;
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

bool WritePNGFile(const wchar_t *file_name, const PNGData &png_data) {
  assert(file_name);

  FILE *fp = NULL;
  _wfopen_s(&fp, file_name, L"wb");
  if (!fp) {
#ifdef DEBUG
    fwprintf(stderr, L"ERROR... Failed to open file.\n");
#endif
    return false;
  }

  // Memory initialization.
  png_structp png_ptr =
      png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr) {
#ifdef DEBUG
    fwprintf(stderr, L"ERROR... Failed to allocate png_struct.\n");
#endif
    fclose(fp);
    return false;
  }

  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
#ifdef DEBUG
    fwprintf(stderr, L"ERROR... Failed to allocate info_ptr.\n");
#endif
    png_destroy_read_struct(&png_ptr, NULL, NULL);
    fclose(fp);
    return false;
  }

  // Error handling with setjmp/longjmp.
  if (setjmp(png_jmpbuf(png_ptr))) {
#ifdef DEBUG
    fwprintf(stderr, L"WARNING... longjmp() is called by libpng.\n");
#endif
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
    return false;
  }

  // File pointer is set.
  png_init_io(png_ptr, fp);

  // Get access to some of the IHDR settings.
  png_set_IHDR(png_ptr, info_ptr, png_data.width, png_data.height,
               png_data.bit_depth, png_data.color_type, png_data.interlace_type,
               png_data.compression_type, png_data.filter_type);

  // Image buffer is created.
  png_bytepp rows =
      (png_bytepp)png_malloc(png_ptr, sizeof(png_bytep) * png_data.height);
  if (!rows) {
#ifdef DEBUG
    fwprintf(stderr, L"ERROR... Failed to allocate rows.\n");
#endif
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
    return false;
  }

  memset(rows, 0, sizeof(png_bytep) * png_data.height);
  bool alloc_is_ok = true;
  for (int y = 0; y < static_cast<int>(png_data.height); y++) {
    rows[y] = (png_byte *)png_malloc(png_ptr, png_data.rowbytes);
    if (!rows[y]) {
#ifdef DEBUG
      fwprintf(stderr, L"ERROR... Failed to allocate rows[%d].\n", y);
#endif
      alloc_is_ok = false;
      break;
    }
  }
  if (!alloc_is_ok) {
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
    return false;
  }

  // Pixels are written to PNG format.
  // This sample only supports RGBA format.
  if (png_data.color_type != PNG_COLOR_TYPE_RGBA) {
#ifdef DEBUG
    fwprintf(stderr, L"color_type is not PNG_COLOR_TYPE_RGBA, exit.\n");
#endif
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
    return false;
  }

  png_bytep row = NULL;
  for (int y = 0; y < static_cast<int>(png_data.height); y++) {
    row = rows[y];
    for (int x = 0; x < static_cast<int>(png_data.width); x++) {
      *(row++) =
          static_cast<png_byte>(png_data.red_buffer[y * png_data.width + x]);
      *(row++) =
          static_cast<png_byte>(png_data.green_buffer[y * png_data.width + x]);
      *(row++) =
          static_cast<png_byte>(png_data.blue_buffer[y * png_data.width + x]);
      *(row++) =
          static_cast<png_byte>(png_data.alpha_buffer[y * png_data.width + x]);
    }
  }

  // Reflect buffered image to info structure.
  png_set_rows(png_ptr, info_ptr, rows);

  // Data access by high-level write interface.
  png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

  // Memory finalization.
  if (!rows) {
    for (int y = 0; y < static_cast<int>(png_data.height); y++) {
      if (!rows[y]) {
        png_free(png_ptr, rows[y]);
      }
    }
    png_free(png_ptr, rows);
  }

  png_destroy_write_struct(&png_ptr, &info_ptr);
  fclose(fp);
  return true;
}
