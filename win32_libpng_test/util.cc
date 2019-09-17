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
#include <string.h>

namespace {
void write_row_callback(png_structp png_ptr, png_uint_32 row, int pass) {
  (void)png_ptr;
  (void)row;
  (void)pass;
}
}  // namespace

bool ReadPNGFile(const wchar_t *file_name, PNGData *png_data) {
  assert(file_name);
  assert(png_data);

  FILE *fp = NULL;
  _wfopen_s(&fp, file_name, L"rb");
  if (!fp) {
#ifdef DEBUG
    fwprintf(stderr, L"ERROR... Failed to open file.\n");
#endif
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

  if (setjmp(png_jmpbuf(png_ptr)) != 0) {
#ifdef DEBUG
    fwprintf(stderr, L"WARNING... longjmp() is called by libpng.\n");
#endif
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose(fp);
    return false;
  }

  png_init_io(png_ptr, fp);
  png_set_sig_bytes(png_ptr, sizeof(sig));

  png_read_png(png_ptr, info_ptr,
               PNG_TRANSFORM_PACKING | PNG_TRANSFORM_STRIP_16, NULL);
  png_data->width = png_get_image_width(png_ptr, info_ptr);
  png_data->height = png_get_image_height(png_ptr, info_ptr);
  png_data->color_type = png_get_color_type(png_ptr, info_ptr);
  png_data->bit_depth = png_get_bit_depth(png_ptr, info_ptr);
  png_data->filter_type = png_get_filter_type(png_ptr, info_ptr);
  png_data->compression_type = png_get_compression_type(png_ptr, info_ptr);
  png_data->interlace_type = png_get_color_type(png_ptr, info_ptr);
  png_data->rowbytes = png_get_rowbytes(png_ptr, info_ptr);
  png_data->channels = png_get_channels(png_ptr, info_ptr);

  if (png_data->rowbytes == 0) {
#ifdef DEBUG
    fwprintf(stderr, L"ERROR... Invalid byte count.\n");
#endif
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose(fp);
    return false;
  }

  // Pixels are read from PNG data.
  // This sample only supports RGBA format.
  if (png_data->color_type != PNG_COLOR_TYPE_RGBA) {
#ifdef DEBUG
    fwprintf(stderr, L"color_type is not PNG_COLOR_TYPE_RGBA, exit.\n");
#endif
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose(fp);
    return false;
  }

  png_bytepp rows = png_get_rows(png_ptr, info_ptr);
  if (!rows) {
#ifdef DEBUG
    fwprintf(stderr, L"ERROR... Failed to get rows.\n");
#endif
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose(fp);
    return false;
  }
  png_bytep row = NULL;
  png_data->red_buffer.resize(png_data->height * png_data->width);
  png_data->green_buffer.resize(png_data->height * png_data->width);
  png_data->blue_buffer.resize(png_data->height * png_data->width);
  png_data->alpha_buffer.resize(png_data->height * png_data->width);
  for (int y = 0; y < static_cast<int>(png_data->height); y++) {
    row = rows[y];
    for (int x = 0; x < static_cast<int>(png_data->width); x++) {
      png_data->red_buffer[y * png_data->width + x] = *(row++);
      png_data->green_buffer[y * png_data->width + x] = *(row++);
      png_data->blue_buffer[y * png_data->width + x] = *(row++);
      png_data->alpha_buffer[y * png_data->width + x] = *row;
#ifdef DEBUG
      fwprintf(stderr, L"(%d,%d),%d.\n", x, y, (int)*(row--));
      row++;
#endif
    }
  }

  // Free memories.
  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
  fclose(fp);
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

  if (setjmp(png_jmpbuf(png_ptr))) {
#ifdef DEBUG
    fwprintf(stderr, L"WARNING... longjmp() is called by libpng.\n");
#endif
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
    return false;
  }

  png_init_io(png_ptr, fp);
  png_set_write_status_fn(png_ptr, *write_row_callback);
  png_set_IHDR(png_ptr, info_ptr, png_data.width, png_data.height,
               png_data.bit_depth, png_data.color_type, png_data.interlace_type,
               png_data.compression_type, png_data.filter_type);

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
  png_set_rows(png_ptr, info_ptr, rows);

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
      *row =
          static_cast<png_byte>(png_data.alpha_buffer[y * png_data.width + x]);
    }
  }

  png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

  // Free memories.
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

void PrintPNGData(FILE *fp, const PNGData &png_data) {
  assert(fp);
  fwprintf(fp, L"width = %d\n", png_data.width);
  fwprintf(fp, L"height = %d\n", png_data.height);
  fwprintf(fp, L"bit_depth = %d\n", png_data.bit_depth);
  fwprintf(fp, L"rowbytes = %d\n", png_data.rowbytes);
  fwprintf(fp, L"channels = %d\n", png_data.channels);

  fwprintf(fp, L"color_type = %d (", png_data.color_type);
  switch (png_data.color_type) {
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

  fwprintf(fp, L"interlace_type = %d (", png_data.interlace_type);
  switch (png_data.interlace_type) {
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

  fwprintf(fp, L"compression_type = %d (", png_data.compression_type);
  switch (png_data.compression_type) {
    case PNG_COMPRESSION_TYPE_DEFAULT:
      fwprintf(fp, L"PNG_COMPRESSION_TYPE_DEFAULT");
      break;
    default:
      fwprintf(fp, L"????");
      break;
  }
  fwprintf(fp, L")\n");

  fwprintf(fp, L"filter_type = %d (", png_data.filter_type);
  switch (png_data.filter_type) {
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
