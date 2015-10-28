#include<stdio.h>
#include<malloc.h>

typedef struct BiTNode{
	int data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
/*
 *创建结点
 * */
BiTree CreateNode(int data,BiTNode *l,BiTNode *r)
{
	BiTNode *pnode =(BiTNode*)malloc(sizeof(BiTNode));
	if(pnode){
		pnode->data=data;
		pnode->lchild=l;
		pnode->rchild=r;
	}
	return pnode;
}

/*
 *设置数据
 * */

void SetData(BiTNode *t,int d)
{
	t->data=d;
}

/*
 *设置左子结点
 * */
BiTree SetlChild(BiTNode *R,BiTNode *l)
{
	R->lchild=l;
	return l;
}

/*
 *设置右子结点
 * */
BiTree SetrChild(BiTNode *R,BiTNode *r)
{
	R->rchild=r;
	return r;
}


/*
 *遍历函数
 * */
void visit(BiTNode *t)
{
	printf("T:%d\n",t->data);
}


/*
 *判断为空，为空返回1，否则返回0
 * */
int IsEmpty(BiTree t)
{
	if(t==NULL)
		return 1;
	return 0;
}

/*
 *先序
 * */
void PreOrder(BiTree t)
{
	if(t!=NULL){
		visit(t);
		PreOrder((BiTree)t->lchild);
		PreOrder((BiTree)t->rchild);
	}
}

/*
 *中序
 * */
void InOrder(BiTree t)
{
	if(t!=NULL){
		PreOrder((BiTree)t->lchild);
		visit(t);
		PreOrder((BiTree)t->rchild);
	}
}

/*
 *后序
 * */
void PostOrder(BiTree t)
{
	if(t!=NULL){
		PreOrder((BiTree)t->lchild);
		PreOrder((BiTree)t->rchild);
		visit(t);
	}
}



int main()
{
	BiTNode *n1=CreateNode(1,NULL,NULL);
	BiTNode *n2=CreateNode(2,NULL,NULL);
	BiTNode *n3=CreateNode(3,n1,n2);
	BiTNode *n4=CreateNode(4,NULL,NULL);
	BiTNode *n5=CreateNode(5,NULL,NULL);
	BiTNode *n6=CreateNode(6,n4,n5);
	BiTree t=CreateNode(0,n3,n6);

	PreOrder(t);
	printf("\n");
	InOrder(t);
	printf("\n");
	PostOrder(t);
	printf("\n");

	return 0;
}
