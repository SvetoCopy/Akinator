#define _CRT_SECURE_NO_WARNINGS

#ifndef TREE_DED
#define TREE_DED

#include "stdio.h"
#include "assert.h"
#include <stdlib.h>
#include <string.h>

const int TREE_ERROR = -1;

typedef char* NodeInfo_t;

struct Node {
	NodeInfo_t data;
	Node* left;
	Node* right;
};

struct Tree {
	Node* root;
	size_t size;
	FILE* graph_logfile;
};


Node* OpNew(NodeInfo_t data);
void  OpDelete(Node* node);

int TreeCtor(Tree* tree, const char* file_name, NodeInfo_t start_data);
int TreeDtor(Tree* tree);

#endif // !TREE_DED
