#include<stdio>
#include<malloc>

typedef char ElemType
typedef struct CSNode{
	ElemType data;
	struct CSNode *firstchild,*nextsibling;
}CSNode,*CSTree;

CSNode* CreateCSNode(ElemType e,CSNode* f,CSNode* n)
{
	CSNode* p=(CSNode*)malloc(sizeof(CSNode));
	p->data=e;
	p->firstchild=f;
	p->nextsibling=n;
	return p;
}



int main()
{
	return 0;
}
