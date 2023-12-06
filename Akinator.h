#ifndef AKINATOR_DED
#define AKINATOR_DED

#include <limits.h>
#include <math.h>
#include "RuzalLib/stack.h"
#include "AkinatorRead.h"

typedef char* NodeInfo_t;

enum GameMode {
	GUESSING        = '1',
	COMPARATION     = '2',
	HERO_PROPERTIES = '3'
};

enum NodeDirection {
	LEFT_DIR  = 0,
	RIGHT_DIR = 1
};

int  AkinatorGame(Tree* tree, const char* filename);
void UploadGameDB(Tree* tree, const char* bd_filename);
#endif // !AKINATOR_DED
