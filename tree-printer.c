#include "tree-printer.h"

int main ( int argc, char *argv[] )
{
  srand((unsigned) time(NULL));
  for(int i = 0; i < 4; i++)
  {
    Node *root = generate_random_tree(i + 3, 5);
    print_tree(root);
    free_tree(root);
    printf("\n\n");
  }
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

  print_tree_helper(root, screen, 0, tree_width(root->left), right);

  printf("width: %d, height: %d\n\n", width, height);
  print_screen(screen, height);
}

/*
   _______4L_______
  |                |
34Yh_             _|
     |           |
     f______    _|
            |  |
         _6apL_a
        |    |
      l7xD   x
*/

void print_tree_helper(Node *root, char **screen, int row, int col, enum branch_direction dir)
{
  printf("%s, width: %d, col: %d\n", root->data, tree_width(root), col);
  char *data = (root->data[0] == '\0' || !root->data) ? "|" : root->data;
  int data_len = strlen(data);
  int lim_left = 0, lim_right = 0;

  if(root->left)
  {
    int left_right = tree_width(root->left->right);
    int left_data_len = root->left->data ? max(1, strlen(root->left->data)) : 1;
    int left_col = col - max(2, left_data_len + left_right);
    print_tree_helper(root->left, screen, row + 2, left_col, left);
    for(lim_left = col; screen[row+1][lim_left] != '|'; lim_left--)
    {
      screen[row][lim_left] = '_';
    }
  }

  if(root->right)
  {
    int right_left = tree_width(root->right->left);
    int right_data_len = root->right->data ? max(1, strlen(root->right->data)) : 1;
    int right_col = col + data_len + right_left;
    if(right_data_len <= 1 && right_left == 0) right_col++;
    print_tree_helper(root->right, screen, row + 2, right_col, right);
    for(lim_right = col; screen[row+1][lim_right] != '|'; lim_right++)
    {
      screen[row][lim_right] = '_';
    }
  }

  int offset = data_len / 2;
  if(root->left && root->right)
  {
    int center = (lim_left + lim_right + 1) / 2;
    for(int i = 0; data[i] != '\0'; i++)
    {
      screen[row][center - offset + i] = data[i];
    }
    if(row > 0)
    {
      screen[row - 1][center] = '|';
    }
  }
  else
  {
    if(dir == left && data_len == 2) offset--;
    for(int i = 0; data[i] != '\0'; i++)
    {
      screen[row][col + i] = data[i];
    }
    if(row > 0)
    {
      screen[row - 1][col + offset] = '|';
    }
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
  if(root == NULL) return 1;
  int data_len = root->data ? max(1, strlen(root->data)) : 1;
  return data_len + tree_width(root->right) + tree_width(root->left);
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

Node *generate_random_tree(int depth, int str_len)
{
  if(depth == 0) return NULL;
  char *str = NULL;
  if(depth > 1)
  {
    str = generate_random_str(rand() % str_len);
  }
  else
  {
    str = generate_random_str((rand() % (str_len - 1)) + 1);
  }
  Node *out = generate_node(str);
  if(rand() % 4)
  {
    out->left = generate_random_tree(depth - 1, str_len);
  }
  if(rand() % 4)
  {
    out->right = generate_random_tree(depth - 1, str_len);
  }
  return out;
}

char *generate_random_str(int str_len)
{
  char *out = malloc(str_len + 1);
  out[str_len] = '\0';
  for(int i = 0; i < str_len; i++)
  {
    switch(rand() % 3)
    {
      case 0:
        out[i] = rand() % 10 + '0';
        break;
      case 1:
        out[i] = rand() % 26 + 'A';
        break;
      default:
        out[i] = rand() % 26 + 'a';
    }
  }
  return out;
}