# tree-printer
Prints out randomly generated binary trees. A shockingly difficult logical exercise. Targets standard C99.

Usage: `tree-printer [max-depth]`
Randomly generates a binary tree with at most a depth of `max-depth`. If `max-depth` is unspecified, a random value between 1 and 5 is used. On normal consoles, depths above 7 or so may begin to wrap due to their width.

To compile, run `cc tree-printer.c -o tree-printer`.
