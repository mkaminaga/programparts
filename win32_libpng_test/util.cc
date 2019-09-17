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

void ClosePNG(FILE* fp, png_structp png_ptr, png_infop info_ptr) {
  if (png_ptr != NULL) {
    png_destroy_read_struct(&png_ptr, NULL, NULL);
  }
  if (fp != NULL) {
    fclose(fp);
  }
}
