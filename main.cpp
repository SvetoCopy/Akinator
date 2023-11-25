#define _CRT_SECURE_NO_WARNINGS

#include "Akinator.h"
#include "GraphicDump.h"

int main() {
    Tree tree = {};
    char first_data[10] = {};
    strcpy(first_data, "xz kto ?");

    TreeCtor(&tree, "tree_graph.gv", first_data);
    UploadGameBD(&tree, "game.txt");
    FILE* file = {};
    AkinatorGame(&tree, "game.txt");

    PrintNode(tree.root, IN);
    printf("\n");
    AkinatorGraphicDump(&tree);

    return 0;
}