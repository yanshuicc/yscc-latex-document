// 在m阶B树T上查找关键字K，返回结果(pt,i,tag)。若查找成功，则特征值
// tag=1，指针pt所指结点中第i个关键字等于K；否则特征值tag=0，等于K的
#include <stdio.h>
#include <malloc.h>

#define m 3		// B树的阶，暂设为3
#define N 16	// 数据元素个数
#define MAX 5	// 字符串最大长度+1


typedef struct
{
	char info[MAX];
}Others;	// 记录的其它部分

//  B树的结点类型
typedef struct
{
	int key;	// 关键字
	Others others;	// 其它部分(由主程定义)
}Record;	// 记录类型

typedef struct BTNode
{
	int keynum; // 结点中关键字个数，即结点的大小
	struct BTNode *parent; // 指向双亲结点
	struct Node // 结点向量类型
	{
		int key;		// 关键字向量
		struct BTNode *ptr; // 子树指针向量
		Record *recptr;		// 记录指针向量recptr的0号单元未用
	}node[m+1];				// node[0]的key未用
}BTNode,*BTree;				// B树结点和B树的类型

typedef struct
{
	BTNode *pt;	// 指向找到的结点
	int i;		// 1..m，在结点中的关键字序号
	int tag;	// 1:查找成功，O:查找失败
}Result;		// B树的查找结果类型




// 构造一个空的动态查找表DT
int InitDSTable(BTree *DT)
{
	*DT=NULL;
	return 1;
}

// 销毁动态查找表DT
void DestroyDSTable(BTree *DT)
{
	int i;
	if(*DT) // 非空树
	{
		for(i=0;i<=(*DT)->keynum;i++)
			DestroyDSTable(&(*DT)->node[i].ptr); // 依次销毁第i棵子树
		free(*DT); // 释放根结点
		*DT=NULL; // 空指针赋0
	}
}

// 在p->node[1..keynum].key中查找i,使得p->node[i].key≤K＜p->node[i+1].key
int Search(BTree p, int K)
{
	int i=0,j;
	for(j=1;j<=p->keynum;j++)
		if(p->node[j].key <= K)
			i = j;
	return i;
}

// 关键字应插入在指针Pt所指结点中第i和第i+1个关键字之间。
Result SearchBTree(BTree T, int K)
{
	BTree p=T,q=NULL;	// 初始化，p指向待查结点，q指向p的双亲
	int found=0;	//找到标志，1找到，0没找到
	int i=0;
	Result r;

	while( p && !found)
	{
		i=Search(p,K); // p->node[i].key≤K<p->node[i+1].key
		if(i>0 && p->node[i].key == K) // 找到待查关键字
			found=1;
		else
		{
			q=p;
			p=p->node[i].ptr;
		}
	}
	r.i = i;
	if(found) // 查找成功
	{
		r.pt=p;	//记录中元素结点指向p
		r.tag=1;//标志找到
	}
	else //  查找不成功，返回K的插入位置信息
	{
		r.pt=q;
		r.tag=0;
	}
	return r;
}
// 将r->key、r和ap分别插入到q->key[i+1]、q->recptr[i+1]和q->ptr[i+1]中
void Insert(BTree *q,int i,Record *r,BTree ap)
{
	int j;
	for(j=(*q)->keynum;j>i;j--) // 空出q->node[i+1]
		(*q)->node[j+1]=(*q)->node[j];
	(*q)->node[i+1].key=r->key;
	(*q)->node[i+1].ptr=ap;
	(*q)->node[i+1].recptr=r;
	(*q)->keynum++;
}



// 将结点q分裂成两个结点，前一半保留，后一半移入新生结点ap
void split(BTree *q,BTree *ap)
{
	int i,s=(m+1)/2;
	*ap=(BTree)malloc(sizeof(BTNode)); // 生成新结点ap
	(*ap)->node[0].ptr=(*q)->node[s].ptr; // 后一半移入ap
	for(i=s+1;i<=m;i++)
	{
		(*ap)->node[i-s]=(*q)->node[i];
		if((*ap)->node[i-s].ptr)
			(*ap)->node[i-s].ptr->parent=*ap;
	}
	(*ap)->keynum=m-s;
	(*ap)->parent=(*q)->parent;
	(*q)->keynum=s-1; // q的前一半保留，修改keynum
}

// 生成含信息(T,r,ap)的新的根结点*T，原T和ap为子树指针
void NewRoot(BTree *T,Record *r,BTree ap)
{
	BTree p;
	p=(BTree)malloc(sizeof(BTNode));
	p->node[0].ptr=*T;
	*T=p;
	if((*T)->node[0].ptr)
		(*T)->node[0].ptr->parent=*T;
	(*T)->parent=NULL;
	(*T)->keynum=1;
	(*T)->node[1].key=r->key;
	(*T)->node[1].recptr=r;
	(*T)->node[1].ptr=ap;
	if((*T)->node[1].ptr)
		(*T)->node[1].ptr->parent=*T;
}


// 在m阶B树T上结点*q的key[i]与key[i+1]之间插入关键字K的指针r。若引起
// 结点过大,则沿双亲链进行必要的结点分裂调整,使T仍是m阶B树。
void InsertBTree(BTree *T,Record *r,BTree q,int i)
{
	BTree ap=NULL;
	int finished=0;
	int s;
	Record *rx;
	rx = r;
	while(q && !finished)
	{
		Insert(&q,i,rx,ap); // 将r->key、r和ap分别插入到q->key[i+1]、q->recptr[i+1]和q->ptr[i+1]中
		if(q->keynum < m)
			finished=1; // 插入完成
		else
		{ // 分裂结点*q
			s = (m+1)/2;
			rx = q->node[s].recptr;
			split(&q,&ap); // 将q->key[s+1..m],q->ptr[s..m]和q->recptr[s+1..m]移入新结点*ap
			q=q->parent;
			if(q)
				i=Search(q,rx->key); // 在双亲结点*q中查找rx->key的插入位置
		}
	}
	if(!finished) // T是空树(参数q初值为NULL)或根结点已分裂为结点*q和*ap
		// 生成含信息(T,rx,ap)的新的根结点*T，原T和ap为子树指针
		NewRoot(T,rx,ap);
}

// 按关键字的顺序对DT的每个结点调用函数Visit()一次
void TraverseDSTable(BTree DT,void(*Visit)(BTNode,int))
{
	int i;
	if(DT) // 非空树
	{
		if(DT->node[0].ptr) // 有第0棵子树
			TraverseDSTable(DT->node[0].ptr,Visit);
		for(i=1;i<=DT->keynum;i++)
		{
			Visit(*DT,i);
			if(DT->node[i].ptr) // 有第i棵子树
				TraverseDSTable(DT->node[i].ptr,Visit);
		}
	}
}

void print(BTNode c,int i) // TraverseDSTable()调用的函数
{
	printf("(%d,%s) ",c.node[i].key,c.node[i].recptr->others.info);
}
int main()
{
	int i;
	BTree t;
	Result s;

	Record r[N]={{24,"1"},{45,"2"},{53,"3"},{12,"4"},{37,"5"},
				{50,"6"},{61,"7"},{90,"8"},{100,"9"},{70,"10"},
				{3,"11"},{30,"12"},{26,"13"},{85,"14"},{3,"15"},
				{7,"16"}}; // (以教科书中P242图9.16为例)
	//初始化t
	InitDSTable(&t);
	for(i=0;i<N;i++)
	{
		s=SearchBTree(t,r[i].key);
		if(!s.tag)	//查找失败则插入树中
			InsertBTree(&t,&r[i],s.pt,s.i);
	}
	printf("按关键字顺序遍历B_树:\n");
	TraverseDSTable(t,print);
	printf("\n请输入待查找记录的关键字: ");
	scanf("%d",&i);
	s=SearchBTree(t,i);
	if(s.tag)	//找到
		print(*(s.pt),s.i);
	else
		printf("没找到");
	printf("\n");
	DestroyDSTable(&t);

	system("pause");
	return 0;
}
