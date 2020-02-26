#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree-printer.h"

int main ( int argc, char *argv[] )
{
  Node *root = generate_with_leaves(strdup("1"), strdup("2"), strdup("3"));
  generate_leaves(root->right, strdup("4"), strdup("5"));
  /*
   *    _1__
   *   |    |
   *   2   _3_
   *      |   |
   *      4   5
  */
  print_tree(root);
  free_tree(root);
  return 0;
}

void print_tree(Node *root)
{
  int width = tree_width(root);
  int height = tree_height(root);
  printf("width: %d, height: %d\n\n", width, height);
}

int tree_height(Node *root)
{
  int max_height = 0;
  tree_height_helper(root, 1, &max_height);
  return max_height;
}

void tree_height_helper(Node *root, int height, int *max_height)
{
  if(root == NULL) return;
  if(height > *max_height)
  {
    *max_height = height;
  }
  tree_height_helper(root->left, height + 2, max_height);
  tree_height_helper(root->right, height + 2, max_height);
}

int tree_width(Node *root)
{
  if(root == NULL) return 0;
  int data_len = strlen(root->data);
  int len_left = root->left ? tree_width(root->left) : 0;
  int len_right = root->right ? tree_width(root->right) : 0;
  return max(2, data_len + len_right + len_left);
}

Node *generate_node(char * data)
{
  Node *out = malloc(sizeof(Node));
  out->left = NULL;
  out->right = NULL;
  out->data = data;
  return out;
}

void generate_leaves(Node *root, char *left_data, char *right_data)
{
  root->left = generate_node(left_data);
  root->right = generate_node(right_data);
}

Node *generate_with_leaves(char *root_data, char *left_data, char *right_data)
{
  Node *root = generate_node(root_data);
  generate_leaves(root, left_data, right_data);
  return root;
}

void free_tree(Node *root)
{
  if(root == NULL) return;
  if(root->left) free_tree(root->left);
  if(root->right) free_tree(root->right);
  if(root->data) free(root->data);
  free(root);
}

int max(int a, int b)
{
  return a > b ? a : b;
}