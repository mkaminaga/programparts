  // @file liner_quaternary_tree.h
  // @brief The test of Liner Quaternary Tree implementation.
  // See also the source code of LQT distributed at the following web page:
  //   http://marupeke296.com
  // @author Mamoru Kaminaga
  // @date 2018-04-12 15:43:57
  // Copyright 2017 Mamoru Kaminaga
#include <assert.h>
#include <stdio.h>
#include <wchar.h>
#include <string>
#include "./liner_quaternary_tree.h"

class TestObject : public TreeObject {
 public:
  TestObject() { }
  TestObject(
      const std::basic_string<wchar_t>& name,
      double x,
      double y,
      double width,
      double height) : x_(x), y_(y), width_(width), height_(height), name_() { }
  ~TestObject() { }

  void GetBoundaryBox(
      double* top_left_x,
      double* top_left_y,
      double* bottom_right_x,
      double* bottom_right_y) {
    assert(top_left_x);
    assert(top_left_y);
    assert(bottom_right_x);
    assert(bottom_right_y);
    *top_left_x = x_;
    *top_left_y = y_;
    *bottom_right_x = x_ + width_;
    *bottom_right_y = y_ + height_;
  }
  void Collide(TreeObject* pair_object) {
    assert(pair_object);

    wprintf(L"%ls vs. %ls\n",
        name_.c_str(),
        dynamic_cast<TestObject*>(pair_object)->name_.c_str());
  }

 private:
  double x_;
  double y_;
  double width_;
  double height_;
  std::basic_string<wchar_t> name_;
};

int main(int argc, char* argv[]) {
  const double width = 100.0;
  const double height = 100.0;
  const int level = 3;

  // The liner Quaternary Tree is initialized.
  LinerQuaternaryTree tree;
  if (!tree.Initialize(width, height, level)) {
    wprintf(L"LQT initialization is failed\n");
    return -1;
  }

  // Object registration.
  TestObject object[9];
  object[0] = TestObject(L"object 0", 48, 80, 0.1, 0.1);
  tree.RegisterObject(&object[0]);

  // The collision check.
  std::vector<TreeObject*> collision_list;
  tree.GetCollisionList(&collision_list);

  wprintf(L"==== Collision Pairs ====\n");
  wprintf(L"count of pairs : %d\n", collision_list.size() / 2);
  for (int i = 0; i < static_cast<int>(collision_list.size()) / 2; ++i) {
    collision_list[i * 2]->Collide(collision_list[i * 2 + 1]);
  }

  // The liner Quaternary Tree is finalized.
  tree.Finalize();

  (void) argc;
  (void) argv;
  return 0;
}
