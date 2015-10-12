#include<stdio.h>
#include<malloc.h>

typedef struct BitNode{
	int data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

void init(BiTree *t,int n)
{
	(*t)->data=n;
	(*t)->lchild=NULL;
	(*t)->rchild=NULL;
	n--;
	if(n<=0){
	//	printf("%d\n",n);
		return;
	}
	else{
		BiTNode *lc,*rc; 
		lc=(BiTNode*)malloc(sizeof(BiTNode));
		rc=(BiTNode*)malloc(sizeof(BiTNode));
	//  printf("%d\n",n);
		(*t)->lchild=&lc;
		(*t)->rchild=&rc;
		init(&((*t)->lchild),n);
		init(&((*t)->rchild),n);
	}
}

void eq(BiTNode *t,int d)
{
	t->data=d;
}

void visit(BiTNode *t)
{
	printf("T%d\n",t->data);
	//printf("T%d\n",(*t)->data);
}

void PreOrder(BiTree t)
{
	if(t!=NULL){
		visit(t);
		//printf(t->lchild->datadata);
		PreOrder((BiTree)t->lchild);
		PreOrder((BiTree)t->lchild);
		//PreOrder((BiTree)(*t).lchild);
		//PreOrder((BiTree)(*t).rchild);
	}
}

int main()
{
	BiTree t;
	
	init(&t,3);
	
	PreOrder(t);

	return 0;
}