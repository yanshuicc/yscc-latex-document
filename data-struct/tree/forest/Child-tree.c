#include<stdio.h>
#include<malloc.h>

#define MAX_TREE_SIZE 100

typedef struct CTNode{
	int child;
	struct CTNode *next;
}*ChildPtr;

typedef struct{
	TElemType data;
	ChildPtr firstchild;						//头结点
}CTBox;

typedef struct{
	CTBox nodes[MAX_TREE_SIZE];
	int n,r;												//结点数，根的位置
}CTree;
