#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>

#include "headers.h"

int main() {
	printf("MAXIMUM AGREEMENT SUBTREE PROBLEM SOLVER \nAuthor: Jakub Ochnik\n\n");
	int n; //number of problems
	printf("Enter a number of trees:\n");
	scanf("%d", &n);

	//creating an array of nodes
	eVertice* empty = (eVertice*)malloc(n * sizeof(eVertice));
	for (int i = 0; i < n; i++) {
		empty[i].tab = (tree**)malloc(INIT_SIZE * sizeof(tree*));
		if (empty[i].tab != NULL) {
			for (int j = 0; j < INIT_SIZE; j++)
				empty[i].tab[j] = NULL;
		}
		empty[i].count = 0;
		empty[i].tab_size = INIT_SIZE;
	}
	//initialization of the main tree array
	tree* tTab = (tree*)malloc(n * sizeof(tree));
	for (int i = 0; i < n; i++) {
		(tTab + i)->parent = NULL;
		(tTab + i)->son = NULL;
		(tTab + i)->sibling = NULL;
		(tTab + i)->value = 0;
		emptyToArray(tTab + i, empty + i);
	}
	int* emptyCount = (int*)malloc(n * sizeof(int));

	int* leavesCount = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
		leavesCount[i] = 0;

	int** leaves = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
	{
		printf("Enter a %d. tree in a Newick format:\n",i);
		if (i == 0)
			leaves[i] = readTrees(tTab + i, true, emptyCount, empty, leavesCount);
		else
			leaves[i] = readTrees(tTab + i, false, emptyCount + i, empty + i, leavesCount + i);
	}
	printf("\n\t--RESULTS--\n");
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			printf("Trees %d - %d\n", i, j);
			int result = makeTable(emptyCount[i], emptyCount[j], leaves[i], leaves[j], &empty[i], &empty[j], leavesCount[i], leavesCount[j]);
			printf("%d\n", result);
		}
	}

	for (int i = 0; i < n; i++)
		free(empty[i].tab);

	for (int i = 0; i < n; i++)
		free(leaves[i]);
	free(leaves);
	free(emptyCount);
	free(tTab);
	free(leavesCount);

	return 0;
}