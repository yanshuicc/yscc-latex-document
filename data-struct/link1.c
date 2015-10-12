#include<malloc.h>
#include<stdlib.h>


typedef int Item;/*定义数据项类型*/
typedef struct node * PNode;/*定义节点指针*/

typedef struct node/*节点的定义*/
{
	Item item;  /*数据域*/
	PNode next; /*链域*/	
}Node;

typedef  PNode Position;
typedef  PNode List;



/*
	List MakeEmpty(List L)
	参数
	L 要生成的空链表名
	返回值
	返回生成的空链表名
	功能
	生成空链表
*/
List MakeEmpty(List L)
{
	L = (PNode)malloc(sizeof(Node));
	L->item = 0;
	L->next = NULL;
	return L;
}

/*
	int IsEmpty(List L)
	参数
	L 要判定的链表名
	返回值
	若L为空返回1，否则返回0
	功能
	判断链表L是否为空
*/
int IsEmpty(List L)
{
	return L->next == NULL;
}
/*
	int IsLast(Position P)
	参数
	P 要判定的位置
	返回值
	若P为为最后一个节点则返回1，否则返回0
	功能
	判断位置P的节点是否是链表最后一个节点
*/
int IsLast(Position P)
{
	return P->next == NULL;
}

/*
	Position Find(Item X,List L)
	参数
	X 要查找的数据项
	L 要查找的链表
	返回值
	若X在L中存在则返回第一个匹配节点的位置，否则返回NULL
	功能
	判断位置P的节点是否是链表最后一个节点
*/
Position Find(Item X,List L)
{
	Position P;
	P = L->next;
	while( P!=NULL && P->item != X )
	{
		P = P->next;
	}
	return P;
}

/*
	Position FindPrevious(Item X,List L)
	参数
	X 要查找的数据项
	L 要查找的链表
	返回值
	若X在L中存在则返回第一个匹配节点的前驱位置，否则返回NULL
	功能
	返回链表L中数据项为X的节点的前驱节点位置
*/
Position FindPrevious(Item X,List L)
{
	Position P;
	P = L;
	while(P->next!=NULL && P->next->item != X)
		P = P->next;
	return P;
}

/*
	void Delete(Item X,List L)
	参数
	X 要删除的数据项
	L 要删除节点所在的链表
	返回值
	无
	功能
	在链表L中删除查找到的第一个数据项为X的节点
*/
void Delete(Item X,List L)
{
	Position P,temp;	/*读者请思考，temp为什么是必要的？*/
	P = FindPrevious(X,L);
	if(!IsLast(P))
	{
		temp = P->next;
		P->next = temp->next;
		free(temp);
	}
}



/*
	Position FindNext(Item X,List L)
	参数
	X 要查找的数据项
	L 要查找的链表
	返回值
	若X在L中存在则返回第一个匹配节点的后继位置，否则返回NULL
	功能
	返回链表L中数据项为X的节点的后继节点位置
*/
Position FindNext(Item X,List L)
{
	Position P;
	P = L;
	while(P!=NULL && P->item != X)
		P = P->next;
	return P;
}
/*
	void Insert(Item X,List L,Position P)
	参数
	X 要插入的数据项
	L 要插入的链表
	返回值
	无
	功能
	在链表L中P位置之后插入数据项为X的新节点
*/
void Insert(Item X,List L,Position P)
{
	Position temp;
	temp = malloc(sizeof(Node));
	if(temp==NULL)
		exit(0);
	temp->item = X;
	temp->next = P->next;
	P->next = temp;
}
/*
	void DeleteList(List L)
	参数
	L 要删除节点的链表
	返回值
	无
	功能
	删除链表L中除了头节点之外的所有节点
*/
void DeleteList(List L)
{
	Position P,temp;
	P = L->next;
	L->next = NULL;
	while( P!=NULL)
	{
		temp = P->next;
		free(P);
		 P = temp;
	}
}
/*
	Position Header(List L)
	参数
	L 要查找的链表
	返回值
	返回链表L的头节点位置
	功能
	返回头节点
*/
Position Header(List L)
{
	return L;
}
/*
	Position First(List L)
	参数
	L 要查找的链表
	返回值
	若链表非空则返回第一个数据节点，否则返回NULL
	功能
	返回第一个数据节点位置
*/
Position First(List L)
{
	if(L->next!=NULL)
	return L->next;
}
/*
	Position Advance(Position P)
	参数
	P 当前节点位置
	返回值
	若P位置后继节点存在则返回其位置，否则返回NULL
	功能
	获得位置P后继节点位置
*/
Position Advance(Position P)
{
	if(P!=NULL)
	return P->next;
}
/*
	Item Retrieve(Position P)
	参数
	P 当前节点位置
	返回值
	若P非空则返回其数据项的值
	功能
	返回P位置的数据项
*/
Item Retrieve(Position P)
{
	if(P!=NULL)
	return P->item;
}

int main()
{
	List list=NULL;
	Position p; 
	int i;
	list = MakeEmpty(list);
	printf("----------已生成空链表list---------\n");
	if(IsEmpty(list))
	printf("经检验list是个空链表\n");

	p = list;
	for(i=0;i<5;i++)
	{
		Insert(i*i,list,p);		
		p = Advance(p);
		printf("已插入的值为%d新节点\n",Retrieve(p));
	}
	p = FindNext(9,list);
	printf("数据项为9的节点后继的数据项值为%d\n",Retrieve(p));
	
	p = FindPrevious(9,list);
	printf("数据项为9的节点前驱的数据项值为%d\n",Retrieve(p));

	Delete(9,list);
	
	p = list;
	for(i=0;i<4;i++)
	{	
		p = Advance(p);
		printf("删除数据项为9的节点剩下的节点值为%d\n",Retrieve(p));
	}
	
	DeleteList(list);
	printf("已删除链表list的所以数据节点\n");
	if(IsEmpty(list))
	printf("经检验list是个空链表\n");

}
