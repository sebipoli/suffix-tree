#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct node
{
	char sir[256];
	char letter;
	struct node *parrent;
	struct node *children[27];
} node, *Tree;

typedef struct tree
{
	struct node *head;
} tree;

node *createNode()
{
	node *newNode = (node *)malloc(sizeof(node));
	int i;
	for (i = 0; i < 27; i++)
	{
		newNode->children[i] = NULL;
	}
	newNode->parrent = NULL;
	return newNode;
}

tree *init(tree *myTree)
{
	myTree = (tree *)malloc(sizeof(tree));
	myTree->head = (node *)malloc(sizeof(node));
	myTree->head->parrent = NULL;
	int i;
	for (i = 0; i < 27; i++)
		myTree->head->children[i] = NULL;
	return myTree;
}

void printLevel(node *elem, int depth, int *ok, FILE *g)
{
	int i;

	if (depth == 0)
	{
		fprintf(g, "%c ", elem->letter);
		(*ok) = 1;
	}
	for (i = 0; i < 27; i++)
	{
		if (elem->children[i] != NULL)
		{
			printLevel(elem->children[i], depth - 1, ok, g);
		}
	}
}

void printLevelString(node *elem, int depth, int *ok, FILE *g)
{
	int i;

	if (depth == 0)
	{
		fprintf(g, "%s ", elem->sir);
		*ok = 1;
	}

	for (i = 0; i < 27; i++)
	{
		if (elem->children[i] != NULL)
		{
			printLevelString(elem->children[i], depth - 1, ok, g);
		}
	}
}

void printTree(node *root, FILE *g)
{
	int depth = 1;
	int ok;

	while (1)
	{
		ok = 0;
		printLevel(root, depth, &ok, g);
		if (!ok)
		{
			break;
		}
		fprintf(g, "\n");
		depth++;
	}
}

void printTreeString(node *root, FILE *g)
{
	int depth = 1;
	int ok;

	while (1)
	{
		ok = 0;
		printLevelString(root, depth, &ok, g);
		if (!ok)
		{
			break;
		}
		fprintf(g, "\n");
		depth++;
	}
}

void insertNode(tree *myTree, char sir[256])
{
	int i;
	node *current = myTree->head;
	int len = strlen(sir);
	for (i = 0; i < len; i++)
	{
		int k = sir[i] - 'a' + 1;
		if (sir[i] == '$')
			k = 0;
		if (current->children[k] == NULL)
		{
			current->children[k] = createNode();
			if (current->children[k] == NULL)
			{
				return;
			}
			current->children[k]->parrent = current;
			current->children[k]->letter = sir[i];
			current->children[k]->sir[0] = sir[i];
			current->children[k]->sir[1] = '\0';
		}
		current = current->children[k];
	}
}

void search(tree *myTree, char sir[256], FILE *g)
{
	node *current = myTree->head;
	int i, k;
	int len = strlen(sir);
	for (i = 0; i < len; i++)
	{
		k = sir[i] - 'a' + 1;
		if (current->children[k] == NULL || current->children[k]->letter != sir[i])
		{
			fprintf(g, "%d\n", 0);
			return;
		}
		current = current->children[k];
	}
	if (current->children[0] != NULL && current->children[0]->letter == '$')
	{
		fprintf(g, "%d\n", 1);
	}
	else
	{
		fprintf(g, "%d\n", 0);
	}
}

int count_leaf_nodes(node *root)
{
	int i;
	if (root == NULL)
		return 0;
	int count = 0;
	for (i = 0; i < 27; i++)
	{
		if (root->children[i] != NULL)
		{
			// verific daca nodul curent este frunza
			if (root->children[i]->letter == '$')
				count++;
			else
				count += count_leaf_nodes(root->children[i]);
		}
	}
	return count;
}

int count_suffixes_of_length(node *root, int K)
{
	int i;
	if (root == NULL)
		return 0;
	if (K == 0)
	{
		// daca nodul este funza
		if (root->letter == '$')
			return 1;
		else
			return 0;
	}

	int count = 0;
	// se parcurg copiii nodului curent
	for (i = 0; i < 27; i++)
	{
		count += count_suffixes_of_length(root->children[i], K - 1);
	}
	return count;
}

int max_direct_descendants(node *root)
{
	if (root == NULL)
		return 0;
	int i, max = 0;
	for (i = 0; i < 27; i++)
		if (root->children[i] != NULL)
			max++;
	for (i = 0; i < 27; i++)
	{
		int aux = max_direct_descendants(root->children[i]);
		if (aux > max)
			max = aux;
	}
	return max;
}

void compress(node *root)
{
	node *aux = root;
	int i, k = 0, index, j;
	while (1)
	{
		k = 0;
		for (i = 1; i < 27; i++)
		{
			if (root->children[i] != NULL)
			{
				// daca are doar un copil asta inseamna ca nu s-a terminat inca de compresat
				k++;
				// un aux
				index = i;
			}
		}
		if (k == 1 && root->children[0] == NULL)
		{
			// aux coboara in singurul nod existent
			aux = aux->children[index];
			strcat(root->sir, aux->sir);
			for (j = 0; j < 27; j++)
			{
				if (aux->children[j] != NULL)
					root->children[j] = aux->children[j];
				else
					root->children[j] = NULL;
			}
		}
		else
			break;
	}
	for (i = 0; i < 27; i++)
		if (root->children[i] != NULL)
			compress(root->children[i]);
}

int main(int argc, char *argv[])
{
	tree *myTree = NULL;
	myTree = init(myTree);
	int k, i, N = argc; // unused parameter

	char word[256];
	if (strcmp(argv[1], "-c1") == 0)
	{
		FILE *f = fopen(argv[2], "r");
		FILE *g = fopen(argv[3], "w");
		fscanf(f, "%d", &N);
		fgetc(f);
		for (i = 0; i < N; i++)
		{
			fgets(word, sizeof(word), f);
			int len = strlen(word);
			word[len - 1] = '$';
			len = strlen(word);
			for (k = 0; k < len; k++)
			{
				insertNode(myTree, word + k);
			}
		}
		printTree(myTree->head, g);
		fclose(f);
		fclose(g);
	}
	else if (strcmp(argv[1], "-c3") == 0)
	{
		FILE *f = fopen(argv[2], "r");
		FILE *g = fopen(argv[3], "w");
		fscanf(f, "%d", &N);
		fgetc(f);
		int M, k;
		fscanf(f, "%d", &M);
		fgetc(f);
		for (i = 0; i < N; i++)
		{
			fgets(word, sizeof(word), f);
			int len = strlen(word);
			word[len - 1] = '$';
			len = strlen(word);
			for (k = 0; k < len; k++)
			{
				insertNode(myTree, word + k);
			}
		}
		for (i = 0; i < M; i++)
		{
			fgets(word, sizeof(word), f);
			int len = strlen(word);
			word[len - 1] = '\0';
			search(myTree, word, g);
		}
		fclose(f);
		fclose(g);
	}
	else if (strcmp(argv[1], "-c2") == 0)
	{
		int contor;
		int k = atoi(argv[2]);
		FILE *f = fopen(argv[3], "r");
		FILE *g = fopen(argv[4], "w");
		fscanf(f, "%d", &N);
		fgetc(f);
		for (i = 0; i < N; i++)
		{
			fgets(word, sizeof(word), f);
			int len = strlen(word);
			word[len - 1] = '$';
			len = strlen(word);
			printf("%s\n", word);
			for (contor = 0; contor < len; contor++)
			{
				insertNode(myTree, word + contor);
			}
		}
		fprintf(g, "%d\n", count_leaf_nodes(myTree->head));
		fprintf(g, "%d\n", count_suffixes_of_length(myTree->head, k + 1));
		fprintf(g, "%d\n", max_direct_descendants(myTree->head));
		fclose(f);
		fclose(g);
	}
	else if (strcmp(argv[1], "-c4") == 0)
	{
		FILE *f = fopen(argv[2], "r");
		FILE *g = fopen(argv[3], "w");
		fscanf(f, "%d", &N);
		fgetc(f);
		int k;
		for (i = 0; i < N; i++)
		{
			fgets(word, sizeof(word), f);
			int len = strlen(word);
			word[len - 1] = '$';
			len = strlen(word);
			for (k = 0; k < len; k++)
			{
				insertNode(myTree, word + k);
			}
		}
		compress(myTree->head);
		printTreeString(myTree->head, g);
		fclose(f);
		fclose(g);
	}
	return 0;
}