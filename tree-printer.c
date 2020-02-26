#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree-printer.h"

int main ( int argc, char *argv[] )
{
  Node *root = generate_with_leaves(strdup("4321"), strdup("23212"), strdup("3"));
  generate_leaves(root->left, strdup("1344"), strdup("4325"));
  generate_leaves(root->right, strdup("3123"), strdup("71234"));
  print_tree(root);
  free_tree(root);
  return 0;
}

void print_tree(Node *root)
{
  int width = tree_width(root);
  int height = tree_height(root);
  char **screen = malloc(sizeof(char *) * height);
  for(int i = 0; i < height; i++)
  {
    screen[i] = malloc(width + 1);
    for(int j = 0; j < width; j++)
    {
      screen[i][j] = ' ';
    }
    screen[i][width] = '\0';
  }

  print_tree_helper(root, screen, 0, tree_width(root->left));

  printf("width: %d, height: %d\n\n", width, height);
  print_screen(screen, height);
}

void print_tree_helper(Node *root, char **screen, int row, int col)
{
  char *data = (root->data[0] == '\0' || !root->data) ? "|" : root->data;
  int data_len = strlen(data);
  printf("%s, %d\n", data, tree_width(root));
  if(root->left)
  {
    int left_right = tree_width(root->left->right);
    int left_data_len = root->left->data ? strlen(root->left->data) : 1;
    int left_col = col - max(2, left_data_len + left_right);
    print_tree_helper(root->left, screen, row + 2, left_col);
    for(int i = col; screen[row+1][i] != '|'; i--)
    {
      screen[row][i] = '_';
    }
  }

  if(root->right)
  {
    int right_left = tree_width(root->right->left);
    int right_data_len = root->right->data ? strlen(root->right->data) : 1;
    int right_col = col + data_len + right_left;
    if(right_data_len <= 1 && right_left == 0) right_col++;
    print_tree_helper(root->right, screen, row + 2, right_col);
    for(int i = col + data_len; screen[row+1][i] != '|'; i++)
    {
      screen[row][i] = '_';
    }
  }

  for(int i = 0; data[i] != '\0'; i++)
  {
    screen[row][col + i] = data[i];
  }
  if(row > 0)
  {
    screen[row - 1][col + (data_len / 2)] = '|';
  }
}

void print_screen(char **screen, int height)
{
  for(int i = 0; i < height; i++)
  {
    printf("%s\n", screen[i]);
  }
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
  int data_len = root->data ? strlen(root->data) : 1;
  return max(2, data_len + tree_width(root->right) + tree_width(root->left));
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