#pragma once

#define INIT_SIZE 5
#define INIT_TREE_SIZE 10

#include "mainStructs.h"
#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>

eVertice* emptyToArray(tree* ptr, eVertice* eV);
tree* addSon(tree* t, bool ifVal, int val, int* i, eVertice* eV);
tree* addSibling(tree* t, bool ifEmpty, int val, int* i, eVertice* eV);
tree* backToParent(tree* t);
tree* moveToEnd(tree* t);
int readNumber(char* temp);
int** checkArrSpace(int** arr, int leavesCount, int* tabSize);
int* readTrees(tree* t, bool first, int* emptyVertices, eVertice* eV, int* leavesCount);
int compareValue(int** mainTab, int valX, int valY, int lCount1, int lCount2);
int check(int* permTab, int n, int* valX, int* valY, int wX, int wY);
void permutations(int* permTab, int* valX, int* valY, int** compareTab, int n, int i, int* out, int wX, int wY);
int compareTab(int** tab, eVertice* eV1, eVertice* eV2, int lCount1, int lCount2, int v1, int v2);
int addExistingV(int** tab, int y, int x, int val, bool ifY, int lTotal);
int addToTab(int** tab, int y, int x, int val, bool ifY, int leavesCount);
int checkSons(int** tab, eVertice* eV, int eVTabInd, int lC1, int lC2, bool ifY);
int makeTable(int emptyCount1, int emptyCount2, int* leaves1, int* leaves2, eVertice* empty1, eVertice* empty2, int leavesCount1, int leavesCount);

