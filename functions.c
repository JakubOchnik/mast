#include "headers.h"

eVertice* emptyToArray(tree* ptr, eVertice* eV) {
	//adding a pointer which points to an empty node to an empty node array
	if (eV->count == eV->tab_size)
	{
		tree** tempTab = (tree**)realloc(eV->tab, eV->tab_size * 2 * sizeof(tree*));
		if (tempTab != NULL) {
			eV->tab = tempTab;
			eV->tab_size *= 2;
		}
	}
	eV->tab[eV->count] = ptr;
	eV->count++;
	return eV;
}

tree* addSon(tree* t, bool ifVal, int val, int* i, eVertice* eV) {
	if (ifVal == false) {
		t->son = (tree*)malloc(sizeof(tree));
		t->son->parent = t;
		t->son->sibling = NULL;
		t->son->son = NULL;
		t->son->value = *i;
		*i = *i - 1;
		emptyToArray(t->son, eV);
	}
	else if (ifVal == true) {
		t->son = (tree*)malloc(sizeof(tree));
		t->son->parent = t;
		t->son->sibling = NULL;
		t->son->son = NULL;
		t->son->value = val;
	}
	tree* ptr = t->son;
	return ptr;
}

tree* addSibling(tree* t, bool ifEmpty, int val, int* i, eVertice* eV) {
	if (ifEmpty == false) {
		t->sibling = (tree*)malloc(sizeof(tree));
		t->sibling->son = NULL;
		t->sibling->value = val;
		t->sibling->parent = t->parent;
		t->sibling->sibling = NULL;
	}
	else {
		t->sibling = (tree*)malloc(sizeof(tree));
		t->sibling->son = NULL;
		t->sibling->value = *i;
		t->sibling->parent = t->parent;
		t->sibling->sibling = NULL;
		*i = *i - 1;
		emptyToArray(t->sibling, eV);
	}
	tree* ptr = t->sibling;
	return ptr;
}

tree* backToParent(tree* t) {
	tree* ptr = t->parent;
	return ptr;
}

tree* moveToEnd(tree* t) {
	//moving at the end of tree
	tree* ptr = t;
	while (ptr->sibling != NULL)
		ptr = ptr->sibling;
	return ptr;
}

int readNumber(char* temp) {
	char temp2;
	if (!((int)(*temp) > 47 && (int)(*temp) < 58))
		printf("ERROR");
	temp2 = getchar();
	if (!((int)temp2 > 47 && (int)temp2 < 58))
	{
		//next char is not a digit
		int x = *temp - '0';
		*temp = temp2;
		return x;
	}
	else {
		*temp = getchar();
		return 10;
	}
}

int** checkArrSpace(int** arr, int leavesCount, int* tabSize) {
	if (leavesCount >= (*tabSize)) {
		int* temp = (int*)realloc(*arr, 2 * sizeof(int) * (*tabSize));
		if (temp != NULL)
			*arr = temp;
	}
	(*tabSize) *= 2;
	return arr;
}

int* readTrees(tree* t, bool first, int* emptyVertices, eVertice* eV, int* leavesCount) {
	//loading a tree
	if (first == true)
		getchar();
	char temp = getchar();
	int tabSize = INIT_TREE_SIZE;
	char prev = ' ';
	int i = 0;
	int j = 0;
	int counter = -1;
	bool backFlag = false;
	int* valueVertices = (int*)malloc(INIT_TREE_SIZE * sizeof(int));
	while (temp != EOF && temp != '\n') {
		/*
		( -> add an empty node, addSon
		digit after ( -> add a node with a value (under an empty node)
		(, -> add a sibling, no empty node
		) -> go back to parent
		*/
		if (i != 0 && prev == '(' && temp == '(') {
			t = addSon(t, false, NULL, &counter, eV);
		}
		else if (i != 0 && prev == '(' && (int)temp > 47 && (int)temp < 58)
		{
			//addSon (empty node)
			int value = readNumber(&temp);
			t = addSon(t, true, value, &counter, eV);
			(*leavesCount)++;
			checkArrSpace(&valueVertices, *leavesCount, &tabSize);
			valueVertices[j] = value;
			j++;
			if (temp == ')')
				backFlag = true;
		}
		else if (prev == ',' && (int)temp > 47 && (int)temp < 58) {
			//add a sibling
			int value = readNumber(&temp);
			t = addSibling(t, false, value, &counter, eV);
			(*leavesCount)++;
			checkArrSpace(&valueVertices, *leavesCount, &tabSize);
			valueVertices[j] = value;
			j++;
			if (temp == ')')
				backFlag = true;
		}
		else if (temp == '(' && prev == ',') {
			//empty node as a sibling
			t = addSibling(t, true, NULL, &counter, eV);
		}
		else if (temp == ')') {
			t = backToParent(t);
			t = moveToEnd(t);
		}
		i++;
		if (backFlag == false)
		{
			prev = temp;
			temp = getchar();
		}
		else
			backFlag = false;
		if (temp != ')' && prev == ')')
		{
			prev = temp;
			temp = getchar();
		}
	}
	*emptyVertices = 0 - counter;
	return valueVertices;
}

int compareValue(int** mainTab, int valX, int valY, int lCount1, int lCount2) {
	//comparing two values in a table (if at least one is larger than 0)
	if (valX > 0 && valY > 0) {
		if (valX == valY)
			return 1;
		else
			return 0;
	}
	else if (valX > 0 && valY <= 0) {
		int x = 1;
		while (mainTab[0][x] != valX) {
			x++;
		}
		int y = lCount2;
		while (mainTab[y][0] != valY) {
			y++;
		}
		if (mainTab[y][x] == 0)
			return 0;
		else
			return 1;
	}
	else if (valX <= 0 && valY > 0) {
		int x = lCount1;
		while (mainTab[0][x] != valX) {
			x++;
		}
		int y = 1;
		while (mainTab[y][0] != valY) {
			y++;
		}
		if (mainTab[y][x] == 0)
			return 0;
		else
			return 1;
	}
	return -1;
}

int check(int* permTab, int n, int* valX, int* valY, int wX, int wY)
{
	//checking if a combination of ones intersects vertically or horizontally
	int* actualInd = (int*)malloc(n * sizeof(int));
	int z = 0;
	for (int i = 0; i < n; i++)
		actualInd[i] = -1;
	for (int i = 0; i < n; i++) {
		if (permTab[i] == 1)
		{
			actualInd[z] = i;
			z++;
		}
	}
	bool fail = false;
	for (int i = 0; i < n; i++) {
		if (permTab[i] == 1)
		{
			//check if it intersects with another element vertically or horizontally
			//starting from X axis
			//from left to right
			//>0, 0 is a legend
			for (int j = 1; j < wX; j++) {
				z = 0;
				//Y = valY[i] X = valX[i]
				while (z < n) {
					if (valY[actualInd[z]] == valY[i] && valX[actualInd[z]] != valX[i])
					{
						fail = true;
						break;
					}
					z++;
				}
				if (fail == true)
					break;
			}
			if (fail == false) {
				for (int j = 1; j < wY; j++) {
					z = 0;
					while (z < n) {
						if (valX[actualInd[z]] == valX[i] && valY[actualInd[z]] != valY[i])
						{
							fail = true;
							break;
						}
						z++;
					}
					if (fail == true)
						break;
				}
			}
			if (fail == true)
				break;
		}
	}
	free(actualInd);
	if (fail == false)
		return 1;
	else
		return 0;
}

void permutations(int* permTab, int* valX, int* valY, int** compareTab, int n, int i, int* out, int wX, int wY)
{
	//recursively generating every possible combination of 0 and 1
	if (i == n)
	{
		if (check(permTab, n, valX, valY, wX, wY) == 1)
		{
			//if it's ok: add a sum of every value
			//then compare it with a previous largest
			int suma = 0;
			for (int x = 0; x < n; x++)
			{
				if (permTab[x] == 1)
					suma += compareTab[valY[x]][valX[x]];
			}
			if (suma > * out)
				*out = suma;
		}
		return;
	}
	permTab[i] = 1;
	permutations(permTab, valX, valY, compareTab, n, i + 1, out, wX, wY);
	permTab[i] = 0;
	permutations(permTab, valX, valY, compareTab, n, i + 1, out, wX, wY);
}

int compareTab(int** tab, eVertice* eV1, eVertice* eV2, int lCount1, int lCount2, int v1, int v2) {
	//create a comparison table - if both vertices <=0 
	//V1 - X V2 - Y
	int ind = -v1;
	int i = 0;
	int x = 1;
	int y = 1;
	tree* curr = eV1->tab[ind]->son;
	while (curr->sibling != NULL) {
		curr = curr->sibling;
		x++;
	}
	ind = -v2;
	curr = eV2->tab[ind]->son;
	while (curr->sibling != NULL) {
		curr = curr->sibling;
		y++;
	}
	int** tempTab = (int**)malloc((y + 1) * sizeof(int*));
	for (int j = 0; j < (y + 1); j++) {
		tempTab[j] = (int*)malloc((x + 1) * sizeof(int));
	}

	//filling the legend of a table
	ind = -v1;
	i = 1;
	curr = eV1->tab[ind]->son;
	while (curr->sibling != NULL) {
		tempTab[0][i] = curr->value;
		curr = curr->sibling;
		i++;
	}
	tempTab[0][i] = curr->value;
	ind = -v2;
	i = 1;
	curr = eV2->tab[ind]->son;
	while (curr->sibling != NULL) {
		tempTab[i][0] = curr->value;
		curr = curr->sibling;
		i++;
	}
	tempTab[i][0] = curr->value;

	int defSize = 5;
	int* valX = (int*)malloc(defSize * sizeof(int));
	int* valY = (int*)malloc(defSize * sizeof(int));
	int count = 0;
	//comparing - filling a table
	for (i = 1; i < y + 1; i++) {
		for (int j = 1; j < x + 1; j++) {
			if (tempTab[i][0] <= 0 && tempTab[0][j] <= 0) {
				if (tab[lCount2 + 1 - tempTab[i][0]][lCount1 + 1 - tempTab[0][j]] == -1)
					tempTab[i][j] = compareTab(tab, eV1, eV2, lCount1, lCount2, tempTab[0][j], tempTab[i][0]);
				else
					tempTab[i][j] = tab[lCount2 + 1 - tempTab[i][0]][lCount1 + 1 - tempTab[0][j]];
				if (tempTab[i][j] != 0) {
					if (count >= defSize)
					{
						defSize *= 2;
						int* tTab = (int*)realloc(valX, defSize * sizeof(int));
						if (tTab != NULL)
							valX = tTab;
						tTab = (int*)realloc(valY, defSize * sizeof(int));
						if (tTab != NULL)
							valY = tTab;
					}
					valX[count] = j;
					valY[count] = i;
					count++;
				}
			}
			else {
				tempTab[i][j] = compareValue(tab, tempTab[0][j], tempTab[i][0], lCount1, lCount2);
				if (tempTab[i][j] != 0) {
					if (count >= defSize)
					{
						defSize *= 2;
						int* tTab = (int*)realloc(valX, defSize * sizeof(int));
						if (tTab != NULL)
							valX = tTab;
						tTab = (int*)realloc(valY, defSize * sizeof(int));
						if (tTab != NULL)
							valY = tTab;
					}
					valX[count] = j;
					valY[count] = i;
					count++;
				}
			}
		}
	}
	//best combination of 0 and 1 in a table
	int out = 0;
	int* permTab = (int*)malloc(count * sizeof(int));
	for (int j = 0; j < count; j++)
		permTab[j] = 0;
	permutations(permTab, valX, valY, tempTab, count, 0, &out, x + 1, y + 1);

	//out = current max

	/*
	  y(v1)
	 \
	x(v2)
	*/

	//comparing Y-axis
	int val;
	for (int j = 1; j < y + 1; j++) {
		if (v1 <= 0 && tempTab[j][0] <= 0) {
			if (tab[lCount2 + 1 - tempTab[j][0]][lCount1 + 1 - v1] == -1)
				val = compareTab(tab, eV1, eV2, lCount1, lCount2, v1, tempTab[j][0]);
			else
				val = tab[lCount2 + 1 - tempTab[j][0]][lCount1 + 1 - v1];
			if (val != 0 && val > out) {
				out = val;
			}
		}
		else {
			val = compareValue(tab, v1, tempTab[j][0], lCount1, lCount2);
			if (val != 0 && val > out) {
				out = val;
			}
		}
	}

	//comparing X-axis
	for (int j = 1; j < x + 1; j++) {
		if (v2 <= 0 && tempTab[0][j] <= 0) {
			if (tab[lCount2 + 1 - v2][1 + lCount1 - tempTab[0][j]] == -1)
				val = compareTab(tab, eV1, eV2, lCount1, lCount2, tempTab[0][j], v2);
			else
				val = tab[lCount2 + 1 - v2][1 + lCount1 - tempTab[0][j]];
			if (val != 0 && val > out) {
				out = val;
			}
		}
		else {
			val = compareValue(tab, tempTab[0][j], v2, lCount1, lCount2);
			if (val != 0 && val > out) {
				out = val;
			}
		}
	}

	free(permTab);
	for (int j = 0; j < (y + 1); j++)
		free(tempTab[j]);
	free(tempTab);
	free(valX);
	free(valY);

	return out;
}

int addExistingV(int** tab, int y, int x, int val, bool ifY, int lTotal) {
	//adding values of existing node's children to a table of current vertice's child
	int existingPos = lTotal - val;
	if (ifY == true) {
		for (int i = 1; i < lTotal + 1; i++) {
			if (tab[i][existingPos] == 1)
				tab[i][x] = 1;
		}
	}
	else if (ifY == false) {
		for (int i = 1; i < lTotal + 1; i++) {
			if (tab[existingPos][i] == 1)
				tab[y][i] = 1;
		}
	}
	return 0;
}

int addToTab(int** tab, int y, int x, int val, bool ifY, int leavesCount) {
	//adding values to a vertice's table
	if (ifY == true) {
		for (int i = 1; i < leavesCount + 2; i++) {
			if (tab[i][0] == val)
				tab[i][x] = 1;
		}
	}
	else if (ifY == false) {
		for (int i = 1; i < leavesCount + 2; i++) {
			if (tab[0][i] == val)
				tab[y][i] = 1;
		}
	}
	return 0;
}

int checkSons(int** tab, eVertice* eV, int eVTabInd, int lC1, int lC2, bool ifY) {
	//filling a table of empty vertice's children
	int currVInd;
	if (ifY)
		currVInd = eVTabInd - lC2;
	else
		currVInd = eVTabInd - lC1;
	tree* curr;
	if (currVInd == 0)
	{
		for (int j = 1; j < (ifY ? lC2 + 1 : lC1 + 1); j++) {
			//iterating y-axis: tab[j][0] -> fits 
			//fitting vertice - eV->tab[currVInd]
			if (ifY == true)
				tab[j][eVTabInd] = 1;
			else
				tab[eVTabInd][j] = 1;

		}
	}
	else {
		//searching for sons
		curr = eV->tab[currVInd]->son;
		if (curr->value > 0) {
			//add to an array and keep searching
			if (ifY == true)
				addToTab(tab, NULL, eVTabInd, curr->value, true, lC2);
			else
				addToTab(tab, eVTabInd, NULL, curr->value, false, lC1);
			while (curr->sibling != NULL) {
				curr = curr->sibling;
				if (curr->value > 0) {
					//add to an array
					if (ifY == true)
						addToTab(tab, NULL, eVTabInd, curr->value, true, lC2);
					else
						addToTab(tab, eVTabInd, NULL, curr->value, false, lC1);
				}
				else {
					//add to an existing node's children array
					if (ifY == true)
						addExistingV(tab, NULL, eVTabInd, curr->value, true, lC2);
					else
						addExistingV(tab, eVTabInd, NULL, curr->value, false, lC1);
				}
			}
		}
		else {
			//add to an array of existing node's children
			if (ifY == true)
				addExistingV(tab, NULL, eVTabInd, curr->value, true, lC2);
			else
				addExistingV(tab, eVTabInd, NULL, curr->value, false, lC1);
			while (curr->sibling != NULL) {
				curr = curr->sibling;
				if (curr->value > 0) {
					//add to an array
					if (ifY == true)
						addToTab(tab, NULL, eVTabInd, curr->value, true, lC2);
					else
						addToTab(tab, eVTabInd, NULL, curr->value, false, lC1);
				}
				else {
					//add to an array of existing node's children
					if (ifY == true)
						addExistingV(tab, NULL, eVTabInd, curr->value, true, lC2);
					else
						addExistingV(tab, eVTabInd, NULL, curr->value, false, lC1);
				}
			}
		}
	}
	return 0;
}

int makeTable(int emptyCount1, int emptyCount2, int* leaves1, int* leaves2, eVertice* empty1, eVertice* empty2, int leavesCount1, int leavesCount2) {
	/*
	X->LEGEND 1 + LEAVES 1 + VERTICES 1
	Y->LEGEND 2 + LEAVES 2 + VERTICES 2
	*/
	//TABLE OF LEAVS NO. 1
	int x = 1 + leavesCount1 + emptyCount1;
	int y = 1 + leavesCount2 + emptyCount2;
	int** tab = (int**)malloc(y * sizeof(int*)); //Y
	for (int i = 0; i < y; i++) {
		tab[i] = (int*)malloc(x * sizeof(int));
	}

	for (int i = 0; i < y; i++)
		for (int j = 0; j < x; j++)
			tab[i][j] = 0;
	//filling legends
	//X - SECOND DIMENSION
	//Y - FIRST DIMENSION
	//tab[y][x]

	//Y LEGEND
	for (int i = 1, j = 0; i < y; i++) {
		if (i < leavesCount2 + 1)
			tab[i][0] = leaves2[i - 1];
		else
		{
			tab[i][0] = j;
			j--;
		}
	}

	//X LEGEND
	for (int i = 1, j = 0; i < x; i++) {
		if (i < leavesCount1 + 1)
			tab[0][i] = leaves1[i - 1];
		else
		{
			tab[0][i] = j;
			j--;
		}
	}

	//filling out a first table with ones and zeros

	for (int i = 1; i < leavesCount2 + 1; i++) { //y
		for (int j = 1; j < leavesCount1 + 1; j++) { //x
			if (tab[i][0] == tab[0][j])
				tab[i][j] = 1;
			else
				tab[i][j] = 0;
		}
	}

	//filling out a no. 2 table
	for (int i = y - 1; i > leavesCount2; i--) {
		checkSons(tab, empty2, i, leavesCount1 + 1, leavesCount1 + 1, false);
	}
	for (int i = x - 1; i > leavesCount1; i--) {
		checkSons(tab, empty1, i, leavesCount1 + 1, leavesCount2 + 1, true);
	}
	//filling out a 4th table with '-1'
	for (int i = leavesCount2 + 1; i < y; i++) {
		for (int j = leavesCount1 + 1; j < x; j++)
			tab[i][j] = -1;
	}
	//printing out 1,2,3 tables
	/*for (int i = 0; i < y; i++) {
			for (int j = 0; j < x; j++)
					printf("%d ", tab[i][j]);
			printf("\n");
	}*/
	int max = 0;
	int a = emptyCount2 - 1; //y
	int b = emptyCount1 - 1; //x
	while (a >= 0) {
		while (b >= 0) {
			tab[1 + leavesCount2 + a][1 + leavesCount1 + b] = compareTab(tab, empty1, empty2, leavesCount1, leavesCount2, -b, -a);
			if (tab[1 + leavesCount2 + a][1 + leavesCount1 + b] > max)
				max = tab[1 + leavesCount1 + a][1 + leavesCount2 + b];
			b--;
		}
		b = emptyCount1 - 1;
		a--;
	}
	//printing out a 4th table
	/*for (int i = 11; i < y; i++) {
			for (int j = 11; j < x; j++)
					printf("%d ", tab[i][j]);
			printf("\n");
	}*/
	for (int i = 0; i < y; i++) {
		free(tab[i]);
	}
	free(tab);
	return leavesCount1 - max;
}