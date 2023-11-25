#include "GraphicDump.h"


int HashStr(NodeInfo_t info) {
	int res = 0;
	while (*info != '\0') {
		res += *info;
		info++;
	}
	return res;
}

int DefineQuestions(Tree* tree, Node* node) {
	if (node == nullptr) return 0;

	if (node->left != nullptr || node->right != nullptr) {
		fprintf(tree->graph_logfile, 
			   "\"quest%d\" [shape=Mrecord, style=filled, fillcolor=" QUESTNODE_COLOR ", "
			   "label = \"%s\"];\n", 
			   HashStr(node->data), 
			   node->data);
	}

	DefineQuestions(tree, node->left);
	DefineQuestions(tree, node->right);

	return 0;
}

bool isLeaf(Node* node) {
	if (node->left == nullptr && node->right == nullptr) return true;
	return false;
}

int DefineLeafs(Tree* tree, Node* node) {
	if (node == nullptr) return 0;
	if (isLeaf(node)) {
		fprintf(tree->graph_logfile, 
			    "\"leaf%d\" [shape=Mrecord, style=filled, fillcolor=" LEAFNODE_COLOR ", "
			    "label = \"%s\"];\n", 
				HashStr(node->data), 
			    node->data);
	}
	DefineLeafs(tree, node->left);
	DefineLeafs(tree, node->right);
	return 0;
}

int ConnectNodes(Tree* tree, Node* node) {
	if (node == nullptr) return 0;
	if (node->left != nullptr) {
		const char* node_name = isLeaf(node->left) ? "leaf" : "quest";
		fprintf(tree->graph_logfile, 
				"quest%d->%s%d\n", 
				HashStr(node->data), node_name, HashStr(node->left->data));
	}

	if (node->right != nullptr) {
		if (isLeaf(node->right))
			fprintf(tree->graph_logfile, "quest%d->leaf%d\n",
				HashStr(node->data), HashStr(node->right->data));
		else
			fprintf(tree->graph_logfile, "quest%d->quest%d\n",
				HashStr(node->data), HashStr(node->right->data));
	}

	ConnectNodes(tree, node->left);
	ConnectNodes(tree, node->right);
	return 0;
}

int  AkinatorGraphicDump(Tree* tree) {
	fprintf(tree->graph_logfile, 
		    "digraph Akinator \n{ bgcolor=\"" BG_COLOR "\";" 
		    "node[margin = \"0.01\"];\n");
	DefineQuestions(tree, tree->root);
	DefineLeafs(tree, tree->root);
	ConnectNodes(tree, tree->root);
	fprintf(tree->graph_logfile, "}");
	return 0;
}