#define _CRT_SECURE_NO_WARNINGS

#ifndef TREE_DED
#define TREE_DED

#include "stdio.h"
#include "assert.h"
#include <stdlib.h>
#include <string.h>

const int TREE_ERROR = -1;
const int MAX_BD_SIZE = 1000;
const int DEFAULT_TRACK_SIZE = 10;
const int MAX_NODEINFO_SIZE = 100;

enum ParseStatus {
	FOUND = 1,
	UNFOUND = 2
};

typedef char* NodeInfo_t;

enum Order {
	POST = 1,
	IN   = 2,
	PRE  = 3
};

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

int ReadNode(char* str, Node** res);
void PrintNode(const Node* node, Order order);

Node* OpNew(NodeInfo_t data);
void  OpDelete(Node* node);

int TreeCtor(Tree* tree, const char* file_name, NodeInfo_t start_data);
int TreeDtor(Tree* tree);
int TreeVerify(Tree* tree);

#endif // !TREE_DED
