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
#include <memory>
#include <string>
#include "./liner_quaternary_tree.h"

class TestObject : public TreeObject {
 public:
  TestObject() { }
  TestObject(
      const wchar_t* name,
      double x,
      double y,
      double width,
      double height) :
    x_(x),
    y_(y),
    width_(width),
    height_(height),
    name_(name) {
      wprintf(L"%ls is created at %.1lf, %.1lf\n", name, x, y);
    }
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

  if (argc < 2) {
    wprintf(L"Argument is required, \'a\', \'b\', \'c\', \'d\' or \'e\'\n");
    return -1;
  } else {
    if ((argv[1][0] != L'a') &&
        (argv[1][0] != L'b') &&
        (argv[1][0] != L'c') &&
        (argv[1][0] != L'd') &&
        (argv[1][0] != L'e')) {
      wprintf(L"Invalid argument : %ls \n", argv[1]);
      return -1;
    }
  }

  // The liner Quaternary Tree is initialized.
  LinerQuaternaryTree tree;
  if (!tree.Initialize(width, height, level)) {
    wprintf(L"LQT initialization is failed\n");
    return -1;
  }

  // The test is done.
  wprintf(L"=~=~=~=~=~= Test case %c =~=~=~=~=~=\n", argv[1][0]);

  std::unique_ptr<TestObject> objects[3];
  std::vector<TreeObject*> collision_list;
  switch (argv[1][0]) {
    case L'a':
      objects[0].reset(new TestObject(L"object A", 50, 0, 40, 40));
      objects[1].reset(new TestObject(L"object B", 50, 50, 20, 20));
      tree.RegisterObject(objects[0].get());
      tree.RegisterObject(objects[1].get());
      break;
    case L'b':
      objects[0].reset(new TestObject(L"object A", 50, 0, 40, 40));
      objects[1].reset(new TestObject(L"object B", 50, 0, 20, 20));
      tree.RegisterObject(objects[0].get());
      tree.RegisterObject(objects[1].get());
      break;
    case L'c':
      objects[0].reset(new TestObject(L"object A", 50, 0, 40, 40));
      objects[1].reset(new TestObject(L"object B", 50, 0, 20, 20));
      tree.RegisterObject(objects[0].get());
      tree.RegisterObject(objects[1].get());

      // The tree is reset.
      tree.GetCollisionList(&collision_list);

      wprintf(L"==========\n");
      objects[2].reset(new TestObject(L"object C", 0, 0, 40, 40));
      tree.RegisterObject(objects[2].get());
      break;
    case L'd':
      objects[0].reset(new TestObject(L"object A", 50, 0, 40, 40));
      objects[1].reset(new TestObject(L"object B", 50, 0, 20, 20));
      tree.RegisterObject(objects[0].get());
      tree.RegisterObject(objects[1].get());

      // The tree is reset.
      tree.GetCollisionList(&collision_list);

      wprintf(L"==========\n");
      objects[2].reset(new TestObject(L"object C", 50, 0, 20, 20));
      tree.RegisterObject(objects[2].get());
      break;
    case L'e':
      objects[0].reset(new TestObject(L"object A", 50, 0, 40, 40));
      objects[1].reset(new TestObject(L"object B", 50, 0, 20, 20));
      tree.RegisterObject(objects[0].get());
      tree.RegisterObject(objects[1].get());

      // The tree is reset.
      tree.GetCollisionList(&collision_list);

      wprintf(L"==========\n");
      objects[2].reset(new TestObject(L"object C", 50, 25, 20, 20));
      tree.RegisterObject(objects[2].get());
    default:
      break;
  }

  // The collision check.
  tree.GetCollisionList(&collision_list);

  wprintf(L"==== Collision Pairs ====\n");
  wprintf(L"count of pairs : %d\n", collision_list.size() / 2);
  for (int i = 0; i < static_cast<int>(collision_list.size()) / 2; ++i) {
    collision_list[i * 2]->Collide(collision_list[i * 2 + 1]);
  }

  // The liner Quaternary Tree is finalized.
  tree.Finalize();

  fflush(stdout);

  (void) argc;
  (void) argv;
  return 0;
}
