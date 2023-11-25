#define _CRT_SECURE_NO_WARNINGS
#include "Akinator.h"

void ClearInputBuffer() {
	int c = 0;
	while ((c = getchar()) != '\n' && c != EOF) {}
}

#define GET_CHAR_ANSWER(answer_ptr)           \
		do {                                  \
			printf(">");                      \
		    scanf("%c", answer_ptr);		  \
			ClearInputBuffer();               \
		} while(0)


#define GET_STRING_ANSWER(answer_ptr)     \
		printf(">");                      \
		scanf("%s", answer_ptr);          \
		ClearInputBuffer();

Node* AddNewHero(Node* node) {
	printf("Who is this?\n");
	char hero[MAX_NODEINFO_SIZE] = {};
	GET_STRING_ANSWER(&hero);

	printf("How is %s different from %s ( write question )\n", hero, node->data);
	char question[MAX_NODEINFO_SIZE] = {};
	GET_STRING_ANSWER(&question);

	printf("What is the answer to this question for %s?\n", hero);
	char answer = {};
	GET_CHAR_ANSWER(&answer);

	Node* new_quest = OpNew(question);
	if (answer == 'y') {
		new_quest->left = OpNew(hero);
		new_quest->right = node;
	}
	else {
		new_quest->right = OpNew(hero);
		new_quest->left = node;
	}
	return new_quest;
}

Node* GuessingHero(Node* node) {
	assert(node != nullptr);

	if (node->left == nullptr && node->right == nullptr) {
		printf("It's a %s?\n", node->data);

		char answer = {};
		GET_CHAR_ANSWER(&answer);

		if (answer == 'y') printf("Nice\n");
		if (answer == 'n') {
			Node* new_node = AddNewHero(node);
			return new_node;
		}

		return node;
	}

	printf("%s\n", node->data);
	char answer = {};
	GET_CHAR_ANSWER(&answer);

	if (answer == 'y') {
		node->left = GuessingHero(node->left);
		return node;
	}
	if (answer == 'n') {
		node->right = GuessingHero(node->right);
		return node;
	}
}

bool AkinatorFindHero(Node* root, char* name, Stack* stack) {
	assert(root != nullptr);

	if (root->left == nullptr && root->right == nullptr) {
		return strcmp(name, root->data) == 0;
	}

	if (AkinatorFindHero(root->left, name, stack) == true) {
		StackPush(stack, LEFT_DIR);
		return true;
	}

	if (AkinatorFindHero(root->right, name, stack) == true) {
		StackPush(stack, RIGHT_DIR);
		return true;
	}

	return false;
}

void AkinatorComparation(Node* root) {
	printf("Write first hero\n");
	char first_hero[MAX_NODEINFO_SIZE] = {};
	GET_STRING_ANSWER(&first_hero);

	Stack stack1 = {};
	StackCtor(&stack1, DEFAULT_TRACK_SIZE, "StackDumpAkinator.txt");

	printf("Write second hero\n");
	char second_hero[MAX_NODEINFO_SIZE] = {};
	GET_STRING_ANSWER(&second_hero);

	Stack stack2 = {};
	StackCtor(&stack2, DEFAULT_TRACK_SIZE, "StackDumpAkinator.txt");

}

void AkinatorHeroProperties(Node* root) {

	printf("Whose properties do you want to know?\n");
	char answer[MAX_NODEINFO_SIZE] = {};
	GET_STRING_ANSWER(&answer);

	Stack stack = {};
	StackCtor(&stack, DEFAULT_TRACK_SIZE, "StackDumpAkinator.txt");

	bool is_found = AkinatorFindHero(root, answer, &stack);
	if (!is_found) {
		assert("Unknown hero");
	}

	int way = 0;
	Node* root_var = root;

	while (stack.size != 0) {
		StackPop(&stack, &way);

		if (way == LEFT_DIR) {
			printf("%s - yes\n", root_var->data);
			root_var = root_var->left;
		}
		else if (way == RIGHT_DIR) {
			printf("%s - no\n", root_var->data);
			root_var = root_var->right;
		}
	}

	StackDtor(&stack);
}

void UploadGameBD(Tree* tree, const char* bd_filename) {
	FILE* file = {};
	fopen_s(&file, bd_filename, "r");

	char buffer[MAX_BD_SIZE] = {};
	fgets(buffer, MAX_BD_SIZE, file);

	ReadNode(buffer, &tree->root);

	fclose(file);
}

int AkinatorGame(Tree* tree, const char* filename) {
	printf("-----------------------------------------------------------------------------\n");
	printf("                **    **  ********  **        **            **      \n");
	printf("               **    **  ********  **        **         **     **   \n");
	printf("              ********  **        **        **         **      **  \n");
	printf("             ********  ********  **        **         **      **  \n");
	printf("            **    **  **        **        **         **      **  \n");
	printf("           **    **  ********  ********  ********    **    **   \n");
	printf("          **    **  ********  ********  ********       **      \n");
	printf("-----------------------------------------------------------------------------\n");
	printf(
		"Welcome to the game.To answer the question \"yes\" write \"y\"\n"
		"To answer \"no\", write \"n\"\n"
	);

	printf("Choose game mode: \n"
           "(1) Guesing\n"
		   "(2) Comparison\n"
		   "(3) Hero properties\n");

	char answer = {};
	GET_CHAR_ANSWER(&answer);

	switch (answer) {
	case GUESSING:
		tree->root = GuessingHero(tree->root);
		break;

	case COMPARATION:
		AkinatorComparation(tree->root);
		break;

	case HERO_PROPERTIES:
		AkinatorHeroProperties(tree->root);
		break;
	}
	
	printf("Will you continue the game?\n");
	answer = {};
	GET_CHAR_ANSWER(&answer);

	if (answer == 'y') 
		AkinatorGame(tree, filename);
	else if (answer == 'n') {
		FILE* file = {};
		fopen_s(&file, filename, "w");
		SaveTreeRoot(tree->root, file);
		fclose(file);
	}
	else {
		assert(!"UNDEFINED ANSWER");
	}
	
	return 0;
}