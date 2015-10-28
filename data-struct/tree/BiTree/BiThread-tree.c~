#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

/*
 * 先序线索二叉树
 *
 *	LTag	0	左结点为左孩子
 *				1	左结点为前驱
 *	RTag	0	右结点为右孩子
 *				1	右结点为后继
 * */


#define ERROR	-1
#define OK		1
#define OVERFLOW -1

typedef int Status;
typedef enum PointerTag{Link,Thread} PointerTag;		//Link指针，Thread线索
typedef char TElemType;

typedef struct BiThrNode{
	TElemType data;
	struct BiThrNode *lchild,*rchild;
	PointerTag LTag,RTag;									//左右标志
}BiThrNode,*BiThrTree;


/*
 *遍历线索二叉树
 ×从头结点开始，先找到树中的最左结点，依次遍历后续结点。
 * */
Status InOrderTraverse_Thr(BiThrTree T,Status (*Visit)(TElemType e)){
	BiThrNode* p=T->lchild;
	while(p!=T){															//后继为T表示遍历完成，回到头结点
		while(p->LTag==Link)										//循环至左结点为前驱的结点
			p=p->lchild;
		if(!Visit(p->data))
			return ERROR;
		while(p->RTag==Thread&&p->rchild!=T)		//依次遍历后继结点，到后继结点为T
		{
			p=p->rchild;
			Visit(p->data);
		}
		p=p->rchild;
	}
	return OK;
}

/*
 *	二叉树线索化中序递归函数
 *	更改空指针
 * */
void InThreading(BiThrTree p){
	BiThrNode *pre;
	if(p)
	{
		InThreading(p->lchild);
		if(!p->lchild)
		{
			p->LTag=Thread;
			p->lchild=pre;
		}
		if(!pre->rchild)
		{
			pre->RTag=Thread;
			pre->rchild=p;
		}
		pre=p;
		InThreading(p->rchild);
	}
}

/*
 *	二叉树线索化
 *	添加头结点
 *	@param	BiThrTree 为空指针，函数中分配空间，做线索二叉树的头结点
 *	@return	failed -1 succeed 1
 * */
Status InOrderThreading(BiThrTree Thrt,BiThrTree T)
{
	BiThrNode *pre;
	if(!(Thrt=(BiThrTree)malloc(sizeof(BiThrNode))))		//添加头结点
		exit(OVERFLOW);
	Thrt->LTag=Link;
	Thrt->RTag=Thread;
	Thrt->rchild=Thrt;


	if(!T)
		Thrt->lchild=Thrt;																
	else
	{
		Thrt->lchild=T;
		pre=Thrt;
		InThreading(T);
		pre->rchild=Thrt;
		pre->RTag=Thread;
		Thrt->lchild=pre;
	}
	return OK;
}



int main()
{
	printf("%d",NULL);
	return 0; 
}
