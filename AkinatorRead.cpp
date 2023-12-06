#include "AkinatorRead.h"

void PrintNode(const Node* node, Order order) {
	
	if (!node) {
		printf(" nil ");
		return;
	}

	printf(" ( ");

	if (order == IN) {
		PrintNode(node->left, IN);
		printf(" {%s} ", node->data);
		PrintNode(node->right, IN);
	}
	else if (order == POST) {
		PrintNode(node->left, POST);
		PrintNode(node->right, POST);
		printf(" {%s} ", node->data);
	}
	else if (order == PRE) {
		printf(" {%s} ", node->data);
		PrintNode(node->left, POST);
		PrintNode(node->right, POST);
	}

	printf(" ) ");
}

static int DeleteCloseBracket(char* str) {
	
	char symbol = {};
	int end_read_size = 0;
	sscanf(str, " %c %n", &symbol, &end_read_size);

	if (symbol == ')') {
		return end_read_size;
	}

	return 0;
}

static int SkipNil(char* str) {
	
	char read_str[MAX_NODEINFO_SIZE] = {};
	int read_nil_size = 0;
	sscanf(str, " %s %n", &read_str, &read_nil_size);

	if (strcmp(read_str, "nil") == 0) return read_nil_size;
	
	return 0;
}

int ReadNodeRoot(char* str, Node** res) {

	char root_data[MAX_NODEINFO_SIZE] = {};
	int  read_root_size = 0;
	sscanf(str, "{%[^}]}%n", &root_data, &read_root_size);

	*res = OpNew(root_data);

	return read_root_size;
}

#define MoveStr(num) res_size += num;\
					 str      += num;   

#define ReadChild(child) Node* child = nullptr;                                \
						 int child ## _size = ReadNode(str, &child);           \
						 MoveStr(child ## _size);                              \
                                                                               \
					 	 close_bracket_size = DeleteCloseBracket(str); \
						 MoveStr(close_bracket_size);      

// return read size
int ReadNode(char* str, Node** res) {

	assert(str != nullptr);

	if (strcmp(str, "") == 0) return 0;

	int res_size = 0;
	char symbol = {};
	int first_read_size = 0;
	sscanf(str, " %c %n", &symbol, &first_read_size);

	if (symbol == '(') {
		MoveStr(first_read_size);
	}

	int nil_size = SkipNil(str);
	if (nil_size != 0)
	{
		MoveStr(nil_size);
		*res = nullptr;
		res_size += DeleteCloseBracket(str);

		return res_size;
	}

	int read_root_size = ReadNodeRoot(str, res);
	MoveStr(read_root_size);

	int close_bracket_size = 0;
	ReadChild(left);
	ReadChild(right);

	(*res)->left = left;
	(*res)->right = right;

	return res_size;
}

void SaveTreeRoot(Node* root, FILE* file) {

	assert(file != nullptr);

	if (!root) {
		fprintf(file, " nil ");
		return;
	}
	fprintf(file, " ( ");

	fprintf(file, " {%s} ", root->data);
	SaveTreeRoot(root->left, file);
	SaveTreeRoot(root->right, file);

	fprintf(file, " ) ");
}