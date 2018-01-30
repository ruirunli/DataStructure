/**
 * 循环链表的实现
 * 主要实现与单链表基本一致，但最主要的不同是判断链表结束由p/p->next为空改成了p/p->next是否指向头结点
 */
#include "stdio.h"
#include "/home/C/DataStructure/Unit_1/src/myDefine.c"
#include "stdlib.h"

typedef int ElemType;
typedef struct CLNode{
	//数据域
	ElemType data;
	//指针域
	struct CLNode *next;
	
}CLNode,*CLinkList;

//构造一个空的线性循环链表。
Status InitList_CL(CLinkList *CL){
	(*CL) = (CLinkList)malloc(sizeof(CLNode));
	if(!(*CL)){
		printf("\n构造循环链表失败：申请空间失败\n");
		return ERROR;
	}
	(*CL) -> next = (*CL);		//将头结点的下一跳指向自己
	return OK;
}

//销毁一个线性循环链表
Status DestroyList_CL(CLinkList *CL){
	CLinkList p,q;
	if(!(*CL)){
		return OK;
	}
	p = (*CL) -> next;
	while(p && p != (*CL)){		//释放所有的节点，第一个循环条件只是为了防止发生意外，也可以删掉
		q = p->next;
		free(p);
		p = q;
	}
	if(p == (*CL)){				//释放头结点
		free(p);
		(*CL) = NULL;
		return OK;
	}
	printf("\n销毁循环链表失败：没有释放头结点\n");
	return ERROR;
}
//清空循环链表
Status ClearList_CL(CLinkList *CL){
	CLinkList p,q;
	if(!(*CL)){
		printf("\n清空循环链表失败：该循环链表不存在\n");
		return ERROR;
	}
	p = (*CL) -> next;
	while(p && p != (*CL)){		//释放所有的节点，第一个循环条件只是为了防止发生意外，也可以删掉
		q = p->next;
		free(p);
		p = q;
	}
	if(p == (*CL)){
		p ->next = p;
		return OK;
	}
	printf("\n清空循环链表失败：没有清空所有节点\n");
	return ERROR;
}

//判断循环链表是否为空
Bool ListEmpty_CL(CLinkList CL){
	if(CL && (CL -> next ==CL))		//循环链表为空的条件为该循环链表存在且只有头结点
		return TRUE;
	return FALSE;
}

//得到循环链表的节点的长度
int ListLength_CL(CLinkList CL){
	CLinkList p;
	int i = 0;
	if(ListEmpty_CL(CL))
		return 0;
	p = CL -> next;
	while(p && (p != CL)){
		i++;
		p = p->next;
	}
	if(p == CL)
		return i;
	printf("\n得到循环链表的节点个数错误！\n");
	return -1;
}
//得到循环链表第i个位置的data
Status GetElem_CL(CLinkList CL,int i,ElemType *e){
	CLinkList p = CL -> next;
	int j = 1;
	if(i<1 || i> ListLength_CL(CL)){
		printf("\n不存在第%d个节点\n",i);
		return ERROR;
	}
	while((j!=i)&&(p!=CL)){
		p = p->next;
		j++;
	}
	if(j == i){
		(*e) = p -> data;
		return OK;
	}
	printf("\n查找操作失败！\n");
		return ERROR;
}
//--------------------------------------------------------
//LocateElem_CL 的compare函数
Bool max(ElemType a,ElemType b){
	return a>b?TRUE:FALSE;
}
Bool equals(ElemType a,ElemType b){
	return a == b?TRUE:FALSE;
}

//返回第一个与e满足关系compare函数的L的节点的节点次序
int LocateElem_CL(CLinkList CL,ElemType e,Bool (*compare)(ElemType ,ElemType)){
	int i = 1;
	CLinkList p = CL -> next;
	while( p != CL && !compare(e,p -> data)){
		p = p -> next;
		i++;
	}
	if(p!=CL)	return i;	//找见了
	return 0;
}

//得到数据域是cur_e的前一个数据，赋值给pre_e,若不存在,pre_e = NULL;
//特殊情况，若cur_e为第一个节点的data，那么pre_e为最后一个节点的data
Status PriorElem_CL(CLinkList CL,ElemType cur_e,ElemType *pre_e){
	CLinkList p,q;
	if(!CL || CL == CL -> next){
		printf("\n该循环链表为空表或者不存在，操作失败！\n");
		return ERROR;
	}
	p = CL -> next;
	//特殊情况，cur_e为第一个节点的data
	if(cur_e == p-> data){
		while(p-> next != CL){		//跳到最后一个节点
			p = p -> next;
		}
		if(p -> next == CL){
			(*pre_e) = p -> data;
			return OK;
		}
	}
	q = p -> next;
	while(q != CL && q -> data != cur_e){
		p = q;
		q = q-> next;

	}
	if(q -> data == cur_e){
		(*pre_e) = p -> data;
		return OK;
	}
	printf("\n表中不存在这个数据\n");
	pre_e = NULL;
	return ERROR;
}
//得到数据域是cur_e的前一个数据，赋值给next_e,若不存在,next_e = NULL;
//特殊情况，若cur_e为最后一个节点的data，那么next_e为第一个节点的data
Status NextElem_CL(CLinkList CL,ElemType cur_e,ElemType *next_e){
	CLinkList p;
	if(!CL || CL == CL -> next){
		printf("\n该循环链表为空表或者不存在，操作失败！\n");
		return ERROR;
	}
	p = CL -> next;
	while(p != CL && p -> data != cur_e){
		p = p -> next;

	}
	if(p -> data == cur_e){		//找见了，但是cur_e需要分是不是最后一个节点的data的两种情况讨论
		if(p -> next == CL){		//cur_e是最后一个节点的data
			(*next_e) = CL -> next -> data;
			return OK;
		}
		//不是特殊情况
		(*next_e) = p -> next -> data;
		return OK;
	}
	printf("\n表中不存在这个数据\n");
	next_e = NULL;
	return ERROR;
}
//在第i个节点的位置插入元素e
Status ListInsert_CL(CLinkList CL,int i,ElemType e){
	CLinkList p,q = NULL;
	int j;
	if(i<1 || i>(ListLength_CL(CL)+1)){
		printf("\n插入的位置%d超出了表的范围，插入失败！\n",i);
		return ERROR;
	}
	p = CL;
	j = 0;
	while( j != i-1){		//指向第i-1个节点
		p = p -> next;
		j++;
	}
	
	q =(CLinkList)malloc(sizeof(CLNode));
	if(!q){
		printf("\n申请空间失败！\n");
		return ERROR;
	}
	q -> data = e;
	q -> next = p -> next;
	p -> next = q;

	return OK;
}
//删掉第i个节点，并且将第i个节点的data传给e
Status ListDelete_CL(CLinkList CL,int i,ElemType *e){
	CLinkList p,q;
	int j;
	if(i< 1 || i> ListLength_CL(CL)){
		printf("\n删除位置%d超出表的范围，删除失败！\n");
		return ERROR;
	}
	p = CL;
	j = 0;
	while(j != i -1){		//还是指向第i-1个节点
		p = p -> next;
		j++;
	}
	q = p -> next;		//q指向要删除的节点
	p -> next = q -> next;
	(*e) = q -> data;
	free(q);
	return OK;
}
//-------------------------
//visit()
Bool visit(ElemType e){
	printf("[");
	printf("%d",e);
	printf("]");
	return OK;
}
Status ListTraverse_CL(CLinkList CL,Bool (*visit)(ElemType)){
	CLinkList p = CL;
	if(!p || p->next == CL){
		printf("\n循环链表不存在，Traverse操作失败!\n");
		return ERROR;
	}
	p = p -> next;
	while(p != CL && visit(p -> data)){
		p = p -> next;
	}
	if(p == CL)	return OK;
	return ERROR;
}	

//显示链表
void Print_CL(CLinkList CL){
	CLinkList p;
	if(!CL){
		printf("\n链表不存在\n");
		return;
	}
	printf("\n---------------------------\n");
	printf("头结点的信息：");
	printf("头结点的地址:%d\t\t头结点的next:%d\n",CL,CL->next);
	printf("循环链表的长度为：%d\n",ListLength_CL(CL));
	p = CL -> next;
	if(p != CL){
		printf("当前节点的地址\t当前节点的date\t当前节点的next\n");
		printf("--------------\t--------------\t--------------\n");
		while(p != CL){
			printf("%d\t%d\t\t%d\n",p,p->data,p->next);
			p = p -> next;
		}
		printf("--------------\t--------------\t--------------\n\n");
	}
	else printf("当前该链表为空链表\n");
}

