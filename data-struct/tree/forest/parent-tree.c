#include<stdio.h>
#include<malloc.h>

/***********************************************************
 *	双亲表示法	parent tree
 *
 * 	_________________
 * 	|		|data|parent|
 *	|	0	|	r	|		-1	|
 *	|	1	|	a	|		0		|
 *	|	2	|	b	|		0		|
 *	|	3	|	c	|		0		|
 *	|	4	|	d	|		1		|
 *	|	5	|	e	|		1		|
 *	|	6	|	f	|		3		|
 *	|	7	|	g	|		6		|
 *	|	8	|	h	|		6		|
 *	|	9	|	k	|		6		|
 *	-----------------
 *
 *				r
 *			/		\
 *			a		b		c
 *		/		\			|
 *		d		e			f
 *						/	|	\
 *						g	h	k
 *
 *
 *
 *
 ***********************************************************/


//typedef int ElemType;
typedef char ElemType;

#define MAX_TREE_SIZE 100 //树中的最多结点
typedef struct{
	ElemType data;
	int parent;
}PTNode;

typedef struct{
	PTNode nodes[MAX_TREE_SIZE];
	int n;
}PTree;

PTree* Create(ElemType e)
{
	PTree *p=(PTree*)malloc(sizeof(PTree));
	int i=1;
	p->nodes[0].data=e;
	p->nodes[0].parent=-1;
	p->n=1;
	for(;i<MAX_TREE_SIZE;i++)
	{
		p->nodes[i].data=-1;
		p->nodes[i].parent=-1;
	}
	return p;
}

int Insert(PTree *r,ElemType e,int p)
{
	int i;
	for(i=1;i<MAX_TREE_SIZE;i++)
	{
		if(r->nodes[i].parent==-1)			//找到第一个空位置赋值数据
		{
			r->nodes[r->n].data=e;
			r->nodes[r->n].parent=p;
			r->n++;
			return 1;
		}
	}
	return -1;
}

void Delete(PTree *r,int pos)
{
	r->nodes[n].data=-1;
	r->nodes[n].parent=-1;
	n--;
}

void Clear(PTree *r)
{
	int i;
	n=1;
	for(i=1;i<MAX_TREE_SIZE;i++)
	{
		r->nodes[i].data=-1;
		r->nodes[i].parent=-1;
	}
}

void SetParent(PTree *r,int pos,int p)
{
	r->nodes[pos].parent=p;
}

int SetData(PTree *r,int pos,ElemType e)
{
	if(r->nodes[pos].parent==-1)
		return -1;
	else
		r->nodes[pos].data=e;
	return 1;
}


void Out(PTree *r)
{
	int m,n;
	int i=0;
	printf("size:%d\n",r->n);
	printf("______________________________________________________________\n");
	printf("	|		|	data	|	parent	|\n");
	printf("	|	0	|	%c	|	-1	|\n",r->nodes[0].data);
	for(m=0;m<r->n;m++){
		for(n=1;n<r->n;n++)
			if(r->nodes[n].parent==m)
 				printf("	|	%d	|	%c	|	%d	|\n",i++,r->nodes[n].data,m);
	}
	printf("--------------------------------------------------------------\n");
}

int main()
{
	PTree *p=Create('r');
	Insert(&(*p),'a',0);
	Insert(&(*p),'b',0);
	Insert(&(*p),'c',0);
	Insert(&(*p),'d',1);
	Insert(&(*p),'e',1);
	Insert(&(*p),'f',3);
	Insert(&(*p),'g',6);
	Insert(&(*p),'h',6);
	Insert(&(*p),'k',6);
	
	Out(p);
	return 0;
}
