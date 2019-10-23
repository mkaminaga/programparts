//
// @file matrix.h
// @brief Matrix class, dynamic tow dimensional array.
// @author Mamoru Kaminaga
// @date 2019-10-22 17:46:56
// Copyright 2019 Mamoru Kaminaga
//
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#ifndef MATRIX_H_
#define MATRIX_H_

namespace mk {

template <class T>
class matrix {
 public:
  matrix() : _pp(nullptr), _i_cap(0), _j_cap(0), _i_siz(0), _j_siz(0) {
    return;
  }

  matrix(size_t i_max, size_t j_max)
      : _pp(nullptr), _i_cap(0), _j_cap(0), _i_siz(0), _j_siz(0) {
    assert(i_max > 0);
    assert(j_max > 0);
    resize(i_max, j_max);
    return;
  }

  ~matrix() {
    for (size_t i = 0; i < _i_cap; i++) {
      if (_pp[i] != nullptr) {
        free(_pp[i]);
        _pp[i] = nullptr;
      }
    }
    if (_pp != nullptr) {
      free(_pp);
      _pp = nullptr;
    }
    return;
  }

  void reserve(size_t new_i_cap, size_t new_j_cap) {
    assert(new_i_cap > 0);
    assert(new_j_cap > 0);
    const size_t old_i_cap = _i_cap;
    const size_t old_j_cap = _j_cap;
    if (new_i_cap <= old_i_cap) {
      if (new_j_cap <= old_j_cap) {
        // There is already enough capacity for both pointer array and data
        // array.
        _i_cap = old_i_cap;
        _j_cap = old_j_cap;
#ifdef DEBUG
        wprintf(L"(%d), _i_cap = %d, _j_cap = %d\n", __LINE__, _i_cap, _j_cap);
#endif
        return;
      }

      // There is already enough capacity for pointer array, but not enough
      // capacity for each data array. Data array capacity is expanded.
      for (size_t i = 0; i < old_i_cap; i++) {
        move_j(i, old_j_cap, new_j_cap);
      }
      _i_cap = old_i_cap;
      _j_cap = new_j_cap;
#ifdef DEBUG
      wprintf(L"(%d), _i_cap = %d, _j_cap = %d\n", __LINE__, _i_cap, _j_cap);
#endif
      return;
    }

    // There is not enough capacity for pointer array. Pointer array capacity
    // is expanded.
    move_i(old_i_cap, new_i_cap);

    // There is already enough capacity for existing data array, so data array
    // which newly allocated for pointer array is expanded.
    if (new_j_cap <= old_j_cap) {
      for (size_t i = old_i_cap; i < new_i_cap; i++) {
        move_j(i, 0, old_j_cap);
      }
      _i_cap = new_i_cap;
      _j_cap = old_j_cap;
#ifdef DEBUG
      wprintf(L"(%d), _i_cap = %d, _j_cap = %d\n", __LINE__, _i_cap, _j_cap);
#endif
      return;
    }

    // There is no enough capacity for existing data array and array
    // which newly allocated for pointer array. All data array is expanded.
    for (size_t i = 0; i < old_i_cap; i++) {
      move_j(i, old_j_cap, new_j_cap);
    }
    for (size_t i = old_i_cap; i < new_i_cap; i++) {
      move_j(i, 0, new_j_cap);
    }
    _i_cap = new_i_cap;
    _j_cap = new_j_cap;
#ifdef DEBUG
    wprintf(L"(%d), _i_cap = %d, _j_cap = %d\n", __LINE__, _i_cap, _j_cap);
#endif
    return;
  }

  void resize(size_t new_i_siz, size_t new_j_siz) {
    assert(new_i_siz > 0);
    assert(new_j_siz > 0);
    const size_t old_i_siz = _i_siz;
    const size_t old_j_siz = _j_siz;
    if (new_i_siz <= old_i_siz) {
      // There is already enough capacity for both pointer array and data
      // array.
      if (new_j_siz <= old_j_siz) {
        _i_siz = new_i_siz;
        _j_siz = new_j_siz;
#ifdef DEBUG
        wprintf(L"(%d), _i_siz = %d, _j_siz = %d\n", __LINE__, _i_siz, _j_siz);
#endif
        return;
      }

      // There is already enough capacity for pointer array but not enough
      // capacity for data array. Data array capacity is expanded.
      reserve(old_i_siz, old_j_siz);
      _i_siz = old_i_siz;
      _j_siz = old_j_siz;
#ifdef DEBUG
      wprintf(L"(%d), _i_siz = %d, _j_siz = %d\n", __LINE__, _i_siz, _j_siz);
#endif
      return;
    }

    if (new_j_siz <= old_j_siz) {
      // There is already enough capacity for data array but not enough size for
      // pointer array. Pointer array capacity is expanded.
      reserve(new_i_siz, old_j_siz);
      _i_siz = new_i_siz;
      _j_siz = old_j_siz;
#ifdef DEBUG
      wprintf(L"(%d), _i_siz = %d, _j_siz = %d\n", __LINE__, _i_siz, _j_siz);
#endif
      return;
    }

    // There is not enough capacity for both data array and pointer array.
    // Capacity of pointer array and data array is expanded.
    reserve(new_i_siz, new_j_siz);
    _i_siz = new_i_siz;
    _j_siz = new_j_siz;
#ifdef DEBUG
    wprintf(L"(%d), _i_siz = %d, _j_siz = %d\n", __LINE__, _i_siz, _j_siz);
#endif
    return;
  }

  void clear() {
    for (size_t i = 0; i < _i_siz; i++) {
      for (size_t j = 0; j < _j_siz; j++) {
        ~_pp[i][j];
        memset(_pp[i][j], 0, sizeof(T));
      }
    }
    return;
  }

  T* operator[](size_t i) {
    assert(_pp);
    assert((i >= 0) && (i < _i_siz));
    return _pp[i];
  }
  T* operator[](size_t i) const {
    assert(_pp);
    assert((i >= 0) && (i < _i_siz));
    return _pp[i];
  }
  T** data() { return _pp; }
  T** data() const { return _pp; }

  size_t size() const { return _i_siz * _j_siz; }
  size_t row() const { return _i_siz; }
  size_t column() const { return _j_siz; }

  size_t capacity() const { return _i_cap * _j_cap; }
  size_t row_capacity() const { return _i_cap; }
  size_t column_capacity() const { return _j_cap; }

 private:
  void move_i(size_t old_i_cap, size_t new_i_cap) {
    assert(new_i_cap > 0);
    T** tmp = (T**)realloc(_pp, new_i_cap * sizeof(T*));
    if (tmp == _pp) {
      // No relocation is occurred.
      return;
    }
    if (_pp == nullptr) {
      // First time memory allocation.
      memset(tmp, 0, new_i_cap * sizeof(T));
      _pp = tmp;
      tmp = nullptr;
      return;
    }
    // Memory relocation is occurred.
    memcpy(tmp, _pp, old_i_cap * sizeof(T));
    free(_pp);
    _pp = tmp;
    tmp = nullptr;
    return;
  }

  void move_j(size_t i, size_t old_j_cap, size_t new_j_cap) {
    assert(new_j_cap > 0);
    T* tmp = (T*)realloc(_pp[i], new_j_cap * sizeof(T));
    if (tmp == _pp[i]) {
      // No relocation is occurred.
      return;
    }
    if (_pp[i] == nullptr) {
      // First time memory allocation.
      memset(tmp, 0, new_j_cap * sizeof(T));
      _pp[i] = tmp;
      tmp = nullptr;
      return;
    }
    // Memory relocation is occurred.
    memcpy(tmp, _pp[i], old_j_cap * sizeof(T));
    free(_pp[i]);
    _pp[i] = tmp;
    tmp = nullptr;
    return;
  }

 private:
  T** _pp;        // pointer array of data array.
  size_t _i_cap;  // Capacity of pointer array.
  size_t _j_cap;  // Capacity of data array.
  size_t _i_siz;  // Size of pointer array.
  size_t _j_siz;  // Size of data array.
};

}  // namespace mk

#endif  // MATRIX_H_
