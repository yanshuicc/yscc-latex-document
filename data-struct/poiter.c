#include<stdio.h>

int te(int *a)
{
	(*a)++;
	return *a;
}








typedef struct BitNode{
	int data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

void init(BiTree t,int n)
{
	t->data=n;
	t->lchild=NULL;
	t->rchild=NULL;
	n--;
	if(n<=0)
		return;
	else{
		BiTNode *lc,rc;
		t->lchild=&lc;
		t->rchild=&rc;
		init((BiTree)&(t->lchild),n);
		init((BiTree)&(t->rchild),n);
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
//		PreOrder((BiTree)(*t).lchild);
//		PreOrder((BiTree)(*t).rchild);
	}
}




int main()
{
	int a1=123;						//整数a1
	int *a2;							//整数a2指针
	a2=&a1;								//a2指向a1地址

//	printf("a1:%d\n",a1);
//	printf("&a1:%d\n",&a1);
//	printf("&a2:%d\n",&a2);
//	printf("a2:%d\n",a2);
//	printf("*a2:%d\n",*a2);

	printf("\n-----------------------\n\n");
	int b=te(&a1);
	printf("te(a1):%d,a1:%d\n",b,a1);

	printf("\n-----------------------\n\n");

	BiTree t;
	
	init(t,3);
	
	PreOrder(t);
	return 0;
}
