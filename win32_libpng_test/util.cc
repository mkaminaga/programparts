//
// @file util.cc
// @brief Test project for libpng.
// @author Mamoru Kaminaga
// @date 2019-09-17 08:20:12
// Copyright 2019 Mamoru Kaminaga
//
#include "./util.h"
#include <assert.h>
#include <png.h>

bool OpenPNG(const wchar_t* file_name, FILE** fp_out, png_structp* png_ptr_out,
             png_infop* info_ptr_out) {
  assert(file_name);
  assert(fp_out);
  assert(png_ptr_out);
  assert(info_ptr_out);
  (*fp_out) = NULL;
  (*png_ptr_out) = NULL;
  (*info_ptr_out) = NULL;

  FILE* fp = NULL;
  _wfopen_s(&fp, file_name, L"rb");
  if (!fp) {
    return false;
  }

  png_byte sig[8] = {0};
  fread(sig, sizeof(sig), 1, fp);
  if (png_sig_cmp(sig, 0, sizeof(sig)) != 0) {
#ifdef DEBUG
    fwprintf(stderr, L"ERROR... Image is not PNG.\n");
#endif
    fclose(fp);
    return false;
  }

  png_structp png_ptr =
      png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
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
    fwprintf(stderr, L"ERROR... Failed to allocate png_info.\n");
#endif
    png_destroy_read_struct(&png_ptr, NULL, NULL);
    fclose(fp);
    return false;
  }

  png_init_io(png_ptr, fp);
  png_set_sig_bytes(png_ptr, sizeof(sig));  // Tell skipped bytes to libpng.
  png_read_info(png_ptr, info_ptr);

  (*fp_out) = fp;
  (*png_ptr_out) = png_ptr;
  (*info_ptr_out) = info_ptr;
  return true;
}

void ClosePNG(FILE* fp, png_structpp png_ptrptr, png_infopp info_ptrptr) {
  if (png_ptrptr != NULL) {
    png_destroy_read_struct(png_ptrptr, info_ptrptr, NULL);
  }
  if (fp != NULL) {
    fclose(fp);
  }
}

void PrintPNGInfo(FILE* fp, png_uint_32 width, png_uint_32 height,
                  int bit_depth, int color_type, int interlace_method,
                  int compression_method, int filter_method) {
  fwprintf(fp, L"width = %d\n", width);
  fwprintf(fp, L"height = %d\n", height);
  fwprintf(fp, L"bit_depth = %d\n", bit_depth);
  fwprintf(fp, L"color_type = %d\n", color_type);

  fwprintf(fp, L"color_type = %d (", color_type);
  switch (color_type) {
    case PNG_COLOR_TYPE_GRAY:
      fwprintf(fp, L"PNG_COLOR_TYPE_GRAY");
      break;
    case PNG_COLOR_TYPE_PALETTE:
      fwprintf(fp, L"PNG_COLOR_TYPE_PALETTE");
      break;
    case PNG_COLOR_TYPE_RGB:
      fwprintf(fp, L"PNG_COLOR_TYPE_RGB");
      break;
    case PNG_COLOR_TYPE_RGBA:
      fwprintf(fp, L"PNG_COLOR_TYPE_RGBA");
      break;
    case PNG_COLOR_TYPE_GA:
      fwprintf(fp, L"PNG_COLOR_TYPE_GA");
      break;
    default:
      fwprintf(fp, L"????");
      break;
  }
  fwprintf(fp, L")\n");

  fwprintf(fp, L"interlace_method = %d (", interlace_method);
  switch (interlace_method) {
    case PNG_INTERLACE_NONE:
      fwprintf(fp, L"PNG_INTERLACE_NONE");
      break;
    case PNG_INTERLACE_ADAM7:
      fwprintf(fp, L"PNG_INTERLACE_ADAM7");
      break;
    case PNG_INTERLACE_LAST:
      fwprintf(fp, L"PNG_INTERLACE_LAST");
      break;
    default:
      fwprintf(fp, L"????");
      break;
  }
  fwprintf(fp, L")\n");

  fwprintf(fp, L"compression_method = %d (", compression_method);
  switch (compression_method) {
    case PNG_COMPRESSION_TYPE_DEFAULT:
      fwprintf(fp, L"PNG_COMPRESSION_TYPE_DEFAULT");
      break;
    default:
      fwprintf(fp, L"????");
      break;
  }
  fwprintf(fp, L")\n");

  fwprintf(fp, L"filter_method = %d (", filter_method);
  switch (filter_method) {
    case PNG_INTRAPIXEL_DIFFERENCING:
      fwprintf(fp, L"PNG_INTRAPIXEL_DIFFERENCING");
      break;
    case PNG_FILTER_TYPE_DEFAULT:
      fwprintf(fp, L"PNG_FILTER_TYPE_DEFAULT");
      break;
    default:
      fwprintf(fp, L"????");
      break;
  }
  fwprintf(fp, L")\n");
}
