  // @file liner_quaternary_tree.h
  // @brief Implementation of Liner Quaternary Tree algorithm.
  // See also the source code of LQT implementation distributed by IKD.
  //   http://marupeke296.com
  // @author Mamoru Kaminaga
  // @date 2018-04-12 15:43:57
  // Copyright 2017 Mamoru Kaminaga
#ifndef LINER_QUATERNARY_TREE_H_
#define LINER_QUATERNARY_TREE_H_

#include <vector>

  // The base class for objects that is handled by LQT.
  // This class behaves like a list, but it also removes itself from the list
  // when the object is expired for reasons. This self-removal feature enables
  // LQT to remove object in O(1).
class TreeCell;
class TreeObject {
 public:
  TreeObject();
  virtual ~TreeObject();

  virtual void GetBoundaryBox(
      double* top_left_x,
      double* top_left_y,
      double* rigth_bottom_x,
      double* right_bottom_y) {
    (void) top_left_x;
    (void) top_left_y;
    (void) rigth_bottom_x;
    (void) right_bottom_y;
  }
  virtual void Collide(TreeObject* object) {
    (void) object;
  }

  friend class TreeCell;
  friend class LinerQuaternaryTree;

 private:
  bool RemoveFromCell();  // No overload.

 private:
  TreeCell* cell_;  // The cell that this object is belonging.
  TreeObject* prev_;  // The previous object in the list.
  TreeObject* next_;  // The next object in the list.
};

  // The object list class.
  // This list class is handled by LQT class to manage objects.
class TreeCell {
 public:
  TreeCell();

  bool Push(TreeObject* object);
  void UnRegisterObject(TreeObject* object);

  friend class TreeObject;
  friend class LinerQuaternaryTree;

 private:
  int size_;
  int serial_number_;
  TreeObject* head_;
};

  // The Liner Quaternary Tree (LQT) class.
  // LQT algorithm can be used for the pre-process of the collision judge.
  // LQT divides client space into cells by Morton number.
class LinerQuaternaryTree {
 public:
  LinerQuaternaryTree();

  bool Initialize(double width, double height, int level);
  void Finalize();
  bool RegisterObject(TreeObject* object);
  bool GetCollisionList(std::vector<TreeObject*>* collision_list);

 private:
  int level_;
  int serial_number_;
  double width_;
  double height_;
  std::vector<TreeCell*> cells_;
};
#endif  // LINER_QUATERNARY_TREE_H_
