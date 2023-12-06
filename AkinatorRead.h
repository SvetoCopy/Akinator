#ifndef AKINATOR_READ_HPP
#define AKINATOR_READ_HPP

#include "Tree.h"

const int MAX_DB_SIZE		 = 1000;
const int DEFAULT_TRACK_SIZE = 10;
const int MAX_NODEINFO_SIZE  = 100;

enum ParseStatus {
	FOUND = 1,
	UNFOUND = 2
};

enum Order {
	POST = 1,
	IN = 2,
	PRE = 3
};

void SaveTreeRoot(Node* root, FILE* file);
int  ReadNode(char* str, Node** res);
void PrintNode(const Node* node, Order order);

#endif // !AKINATOR_READ_HPP
