#include <gtest/gtest.h>

extern "C" {
#include "splay.h"
}

void preOrder(SplayNode *root) {
  if (root != NULL) {
    printf("%i (%i, %i)\n", root->key, root->countLeft, root->countRight);
    preOrder(root->left);
    preOrder(root->right);
  }
}

TEST(SplayTree, SplayInsert) {
  SplayNode *root = NewSplayNode(1);
  for(int i = 2; i <= 100; i ++)
    root = SplayInsert(root, i);
  for(int i = 1; i <= 100; i ++) {
    root = SplaySearch(root, i);
    ASSERT_EQ(root->key, i);
    ASSERT_EQ(root->countLeft, i - 1);
    ASSERT_EQ(root->countRight, 100 - i);
  }
}

TEST(SplayTree, SplayRemove) {
  SplayNode *root = NewSplayNode(1);
  for(int i = 2; i <= 100; i ++)
    root = SplayInsert(root, i);
  for(int i = 1; i <= 100; i ++) {
    root = SplayDelete(root, i);
    if (root != NULL) {
      ASSERT_NE(root->key, i);
      root = SplaySearch(root, i);
      ASSERT_EQ(root->key, i + 1);
      ASSERT_EQ(root->countLeft, 0);
      ASSERT_EQ(root->countRight, 99 - i);
    }
  }
  ASSERT_TRUE(root == NULL);
}

TEST(SplayTree, SplayLeftmost) {
  SplayNode *root = NewSplayNode(1);
  for(int i = 3; i <= 200; i += 2)
    root = SplayInsert(root, i);
  for(int i = 1; i <= 200; i += 2) {
    SplayNode *leftMost = SplayLeftmostNode(root);
    ASSERT_EQ(leftMost->key, i);
    root = SplayDelete(root, i);
  }
}

TEST(SplayTree, SplayRightmost) {
  SplayNode *root = NewSplayNode(1);
  for(int i = 3; i <= 200; i += 2)
    root = SplayInsert(root, 202 - i);
  for(int i = 199; i >= 1; i -= 2) {
    SplayNode *rightMost = SplayRightmostNode(root);
    ASSERT_EQ(rightMost->key, i);
    root = SplayDelete(root, i);
  }
}

TEST(SplayTree, SplayMoveNext) {
  SplayNode *root = NewSplayNode(1);
  for(int i = 2; i <= 100; i ++)
    root = SplayInsert(root, i);
  root = SplaySearch(root, 1);
  for(int i = 2; i <= 100; i ++) {
    root = SplayMoveNext(root, root->key);
    ASSERT_EQ(root->key, i);
  }
}

TEST(SplayTree, SplayMovePrevious) {
  SplayNode *root = NewSplayNode(1);
  for(int i = 2; i <= 100; i ++)
    root = SplayInsert(root, i);
  root = SplaySearch(root, 100);
  for(int i = 99; i >= 1; i --) {
    root = SplayMovePrevious(root, root->key);
    ASSERT_EQ(root->key, i);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}