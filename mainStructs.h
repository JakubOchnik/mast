#pragma once

//glowna struktura wierzcholka
typedef struct tNode {
	int value;
	struct tNode* son;
	struct tNode* sibling;
	struct tNode* parent;
}tree;

//struktura z tablica wskaznikow na puste wierzcholki
typedef struct eVertices {
	int count;
	int tab_size;
	tree** tab;
}eVertice;
