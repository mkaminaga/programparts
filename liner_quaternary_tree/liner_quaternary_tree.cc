  // @file liner_quaternary_tree.h
  // @brief Implementation of Liner Quaternary Tree algorithm.
  // See also the source code of LQT distributed at the following web page:
  //   http://marupeke296.com
  // @author Mamoru Kaminaga
  // @date 2018-04-12 15:43:57
  // Copyright 2017 Mamoru Kaminaga
#include <assert.h>
#include <stdint.h>
#include <vector>
#include <list>
#include "./liner_quaternary_tree.h"

#if defined(DEBUG)
#include <stdio.h>
#include <wchar.h>
#endif

#define TREE_LEVEL_LIMIT        (9)

namespace {
const int kOffserToLevel[TREE_LEVEL_LIMIT] = {
  0, 1, 5, 21, 85, 341, 1365, 5461, 21845,
};
}  // namespace

namespace {
uint32_t SlideBits(uint32_t v) {
  v = v & 0x0000ffff;  // Lower 16 bits are effective.
  v = (v | (v << 8)) & 0x00ff00ff;
  v = (v | (v << 4)) & 0x0f0f0f0f;
  v = (v | (v << 2)) & 0x33333333;
  return (v | (v << 1)) & 0x55555555;
}
int GetMortonNumberForPoint(double x, double y, double w, double h, int level) {
  const double edge_division_count = static_cast<double>(1 << level);
  const double unit_width = w / edge_division_count;
  const double unit_height = h / edge_division_count;
  const int morton_number = static_cast<int>(
      SlideBits(static_cast<uint32_t>(x / unit_width)) |
      (SlideBits(static_cast<uint32_t>(y / unit_height)) << 1));
#if defined(DEBUG)
  wprintf(L"point Morton : %d\n", morton_number);
  fflush(stdout);
#endif

  return morton_number;
}
bool GetMortonNumberForBox(
    double top_left_x,
    double top_left_y,
    double bottom_right_x,
    double bottom_right_y,
    double w,
    double h,
    int level,
    int* cell_level,
    int* morton_number) {
  const int top_left_morton_number = GetMortonNumberForPoint(
      top_left_x,
      top_left_y,
      w,
      h,
      level);
  const int bottom_right_morton_number = GetMortonNumberForPoint(
      bottom_right_x,
      bottom_right_y,
      w,
      h,
      level);

  int shift_count = 0;
  for (int highest_bits = top_left_morton_number ^ bottom_right_morton_number;
      highest_bits != 0; highest_bits = highest_bits >> 2) {
    ++shift_count;
  }
  *cell_level = level - shift_count;

  *morton_number = top_left_morton_number >> (shift_count * 2);
  const int division_count = (1 << level) * (1 << level);
  if (*morton_number > division_count) {
    *cell_level = 0;
    *morton_number = 0;
    return false;
  }
  return true;
}
}  // namespace

  //
  // LQT object class.
  //
TreeObject::TreeObject() : cell_(nullptr), prev_(nullptr), next_(nullptr) { }
TreeObject::~TreeObject() = default;
bool TreeObject::RemoveFromCell() {
  if (cell_ == nullptr) {
    // The object is not belonging to a cell, so there is no need of removal.
    return false;
  }

  // Removed from cell.
  if (cell_->size_ > 0) {
    cell_->UnRegisterObject(this);
  }

  // Removed from link list.
  if (prev_ != nullptr) {
    prev_->next_ = next_;
  }
  if (next_ != nullptr) {
    next_->prev_ = prev_;
  }

  // Cleared for safety.
  cell_ = nullptr;
  prev_ = nullptr;
  next_ = nullptr;
  return true;
}

  //
  // LQT node class.
  //
TreeCell::TreeCell() : size_(0), serial_number_(0), head_(nullptr) { }
bool TreeCell::Push(TreeObject* object) {
  assert(object);

  // Duplicate registration is not allowed.
  if (object->cell_ == this) {
    return false;
  }

  // The new object is inserted to the head.
  if (head_ == nullptr) {
    head_ = object;
  } else {
    object->next_ = head_;
    head_->prev_ = object;
    head_ = object;
  }

  // The owner list is referred form this object.
  object->cell_ = this;

  // The objects in the cell is counted for later use.
  ++size_;
  return true;
}
void TreeCell::UnRegisterObject(TreeObject* object) {
  assert(object);

  // If the object is the head of the list, the head of the list is replaced
  // width the next object.
  if ((object == head_) && (head_ != nullptr)) {
    head_ = head_->next_;
  }

  // The objects in the cell is counted for later use.
  --size_;
}

//
// Liner Quaternary Tree class
//
LinerQuaternaryTree::LinerQuaternaryTree() :
    level_(0),
    serial_number_(1),
    width_(0.0),
    height_(0.0) { }
bool LinerQuaternaryTree::Initialize(double width, double height, int level) {
  width_ = width;
  height_ = height;
  level_ = level;

  // The memory size is limited.
  if ((level <= 0) || (level >= TREE_LEVEL_LIMIT)) {
    return false;
  }

  // The buffer is reserved.
  cells_.resize(kOffserToLevel[level + 1]);

#if defined(DEBUG)
  wprintf(L"==== Initialize ====\n");
  wprintf(L"width : %d\n", width_);
  wprintf(L"height : %d\n", height_);
  wprintf(L"level : %d\n", level_);
  wprintf(L"buffer size : %d\n", cells_.size());
  fflush(stdout);
#endif
  return true;
}
void LinerQuaternaryTree::Finalize() {
  // The buffer is released.
  for (auto it : cells_) {
    if (it != nullptr) {
      delete it;
      it = nullptr;
    }
  }
}
bool LinerQuaternaryTree::RegisterObject(TreeObject* object) {
  assert(object);
#if defined(DEBUG)
  wprintf(L"----\n");
  fflush(stdout);
#endif

  // The previous registration is released.
  object->RemoveFromCell();

  // The object's boundary box is acquired.
  double top_left_x = 0.0;
  double top_left_y = 0.0;
  double bottom_right_x = 0.0;
  double bottom_right_y = 0.0;
  object->GetBoundaryBox(
      &top_left_x,
      &top_left_y,
      &bottom_right_x,
      &bottom_right_y);

  // The Morton number of the boundary box is acquired.
  int cell_level = 0;
  int morton_number = 0;
  bool result = GetMortonNumberForBox(
      top_left_x,
      top_left_y,
      bottom_right_x,
      bottom_right_y,
      width_,
      height_,
      level_,
      &cell_level,
      &morton_number);
  if (result == false) {
    return false;
  }

  // Memories for cells are created recursively when the memory is not
  // allocated yet.
  const int index = morton_number + kOffserToLevel[cell_level];
#if defined(DEBUG)
  wprintf(L"Box Morton : %d\n", morton_number);
  wprintf(L"level: %d, index : %d\n", cell_level, index);
  fflush(stdout);
#endif
  if (cells_[index] == nullptr) {
    for (int i = index; cells_[i] == nullptr;
        i = (i - 1) / 4) {
      cells_[i] = new TreeCell();
#if defined(DEBUG)
      wprintf(L"create index : %d\n", i);
      fflush(stdout);
#endif
    }
  }

  // The serial number is copied for the next tree patrol.
  for (int i = index; cells_[i]->serial_number_ != serial_number_;
      i = (i - 1) / 4) {
    cells_[i]->serial_number_ = serial_number_;
#if defined(DEBUG)
    wprintf(L"update index : %d\n", i);
    fflush(stdout);
#endif

    if (i == 0) {
      // Loop stops at the root cell.
      break;
    }
  }

  return cells_[index]->Push(object);
}
bool LinerQuaternaryTree::GetCollisionList(
    std::vector<TreeObject*>* collision_list) {
  assert(collision_list);
#if defined(DEBUG)
  wprintf(L"==== Patrol the tree ====\n");
  fflush(stdout);
#endif

  // Check if the tree has content.
  if ((cells_[0] == nullptr) || (cells_[0]->serial_number_ != serial_number_)) {
    return false;
  }

  // The last result is not used.
  collision_list->clear();

  // Reclusive tree trailing.
  int index = 0;
  int child_index = 0;
  bool is_descend = true;
  std::list<TreeObject*> stack;

LOOP_HEAD:
  while (true) {
#if defined(DEBUG)
    wprintf(L"---- index %d ---- \n", index);
    fflush(stdout);
#endif
    //
    // Descend the tree.
    //
    if (is_descend == true) {
      const int size = cells_[index]->size_;
      if (size > 0) {
        if (size == 1) {
#if defined(DEBUG)
          wprintf(L"index: %d, size == 1\n", index);
          fflush(stdout);
#endif
          TreeObject* object = cells_[index]->head_;

          // The collision among the object in the cell and stacked objects.
          for (auto it : stack) {
            collision_list->push_back(object);
            collision_list->push_back(it);
          }
        } else {
#if defined(DEBUG)
          wprintf(L"index: %d, size > 1\n", index);
          fflush(stdout);
#endif
          TreeObject* object = cells_[index]->head_;
          TreeObject* pair = object->next_;
          for (int i = 0; i < size; ++i) {
            // The collision among objects in the cell.
            for (int j = i + 1; j < size; ++j) {
              collision_list->push_back(object);
              collision_list->push_back(pair);
              pair = pair->next_;
            }

            // The collision among objects in the cell and stacked objects.
            for (auto it : stack) {
              collision_list->push_back(object);
              collision_list->push_back(it);
            }
            object = object->next_;
          }
        }

        // Objects are stacked.
        TreeObject* object = cells_[index]->head_;
        for (int i = 0; i < cells_[index]->size_; ++i) {
          stack.push_back(object);
          object = object->next_;
        }
      }

      // Check for the first child node.
      if ((index * 4 + 4) < static_cast<int>(cells_.size())) {
        for (int i = 0; i < 4; ++i) {
          child_index = index * 4 + i + 1;
          if ((cells_[child_index] != nullptr) &&
              (cells_[child_index]->serial_number_ == serial_number_)) {
            index = child_index;
            is_descend = true;
#if defined(DEBUG)
            wprintf(L"descend to %d\n", child_index);
            fflush(stdout);
#endif
            goto LOOP_HEAD;
          }
        }
      }
    } else {
      // Check for the next child node.
      const int last_morton_number = index;
      if (index * 4 < static_cast<int>(cells_.size())) {
        if (child_index % 4 != 0) {
          for (int i = child_index % 4; i < 4; ++i) {
            child_index = index * 4 + i + 1;
            if ((cells_[child_index] != nullptr) &&
                (cells_[child_index]->serial_number_ ==
                 serial_number_)) {
              index = child_index;
              is_descend = true;
#if defined(DEBUG)
              wprintf(L"descend to %d\n", child_index);
              fflush(stdout);
#endif
              goto LOOP_HEAD;
            }
          }
        }
      }

      // Exit condition.
      if (last_morton_number == 0) {
        goto LOOP_EXIT;
      }
    }

    //
    // Ascend the tree.
    //

    // Objects are popped out.
    for (int i = 0; i < cells_[index]->size_; ++i) {
      stack.pop_back();
    }

    child_index = index;
    index = (child_index - 1) / 4;
    is_descend = false;
#if defined(DEBUG)
    wprintf(L"ascend to %d\n", index);
    fflush(stdout);
#endif
  }
LOOP_EXIT:

  // The serial number is updated.
  ++serial_number_;

  return true;
}
