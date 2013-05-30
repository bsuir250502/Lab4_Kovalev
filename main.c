#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define max_length 30
#define max_base 20

typedef struct tree
{
	int count;
	int n;
	struct tree *l_branch, *r_branch;
} tree_t;

void tree_fill(tree_t **);
void add_leaf(tree_t *, int);
void tree_output(tree_t *);
void tree_find(tree_t *, int);
int atoi_change();
int num_check();

int main(int argc, char** argv)
{
	tree_t *my_tree;
	int ident = 0 , find;
	my_tree = NULL;
	do
	{
		tree_fill(&my_tree);
		puts("Want to continue?");
		ident = atoi_change();
	} while(ident);
	tree_output(my_tree);
	puts("What you'd like to find?");
	find = num_check();
	tree_find(my_tree, find);

	return 0;
}

void tree_fill(tree_t **my_tree)
{
    int num;
    printf("Enter the value of the new node: ");
    num = num_check();
    if (!(*my_tree)) {
        *my_tree = (tree_t*)calloc(1, sizeof(tree_t));
        (*my_tree)->count = num;
		(*my_tree)->n = 1;
    } else {
        add_leaf(*my_tree, num);
    }
}

void add_leaf(tree_t *leaf, int num)
{
    if (num > leaf->count) {
        if (leaf->r_branch) {
            add_leaf(leaf->r_branch, num);
            return;
        } else {
            leaf->r_branch = (tree_t*)calloc(1, sizeof(tree_t));
            leaf->r_branch->count = num;
			leaf->r_branch->n = (leaf->n*2)+1;
            return;
        }
    } else if (num < leaf->count) {
        if (leaf->l_branch) {
            add_leaf(leaf->l_branch, num);
            return;
        } else {
            leaf->l_branch = (tree_t*)calloc(1, sizeof(tree_t));
            leaf->l_branch->count = num;
			leaf->l_branch->n = (leaf->n*2);
            return;
        }
    } else if (num == leaf->count) {
        printf("There's already such a leaf. Please, repeat input.\n");
    }
    return;
}


void tree_output(tree_t *my_tree)
{ if(my_tree)
  { printf("Node contains :   %d , count number %d\n", my_tree->count, my_tree->n);
    if (my_tree->l_branch) tree_output(my_tree->l_branch);
    if (my_tree->r_branch) tree_output(my_tree->r_branch);
  }
}

void tree_find(tree_t *my_tree, int find)
{
	if(my_tree->count == find)  printf("Node contains :   %d , count number %d\n", my_tree->count, my_tree->n);
	else if (my_tree->count < find)
		{
			if(my_tree->l_branch) tree_find(my_tree->l_branch, find);
			else puts("There's not such a number!");
		}
	else
		{
			if(my_tree->r_branch) tree_find(my_tree->r_branch, find);
			else puts("There's not such a number!");
		}
}

int atoi_change()
{
    int identifier;
    char string[128];
    while(1)
    {
	printf("(yes - 1/no - 0) ");
	identifier = num_check();
	if(identifier == 1 || identifier == 0) { break; }
	puts("It's not correct. Please, input data again.");
    }
    return identifier;
}

int num_check()
{
    char buffer[max_length], *bufferPointer;
    int num;
    bufferPointer = buffer;
    do {
        fgets(buffer, max_length, stdin);
        num = strtol(buffer, &bufferPointer, 10);
        if (*bufferPointer != '\n') {
            printf("Incorrect value. Try again: ");
            continue;
        }
        break;
    } while (1);
    return num;
}
