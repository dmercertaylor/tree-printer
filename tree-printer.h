#ifndef TREE_PRINTER_H
#define TREE_PRINTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum branch_direction
{
  left,
  right
};

typedef struct Node
{
  char *data;
  struct Node *left;
  struct Node *right;
} Node;

/* returns larger int */
int max(int a, int b);

/* gets width of tree */
int tree_width(Node *root);

/* gets height of tree */
int tree_height(Node *root);
void tree_height_helper(Node *root, int height, int *max_height);

/* prints tree */
void print_tree(Node *root);

/* prints every line in multidimensional array */
void print_screen(char ** screen, int height);
void print_tree_helper(Node *root, char **screen, int row, int col, enum branch_direction direction);

/* returns Node with NULL children */
Node *generate_node(char * data);

/* adds children to root, with data left_data and right_data */
void generate_leaves(Node *root, char *left_data, char *right_data);

/* generates Node with children */
Node *generate_with_leaves(char *root_data, char *left_data, char *right_data);

/* randomized things */
Node *generate_random_tree(int depth, int str_len);
char *generate_random_str(int str_len);

/* recursively free nodes. Also frees data */
void free_tree(Node *root);

#endif