/*************************************************************************
	> File Name: TongGouShu.c
	> Author: RunRui_Li
	> Mail: 770486267@qq.com 
	> Created Time: Tue 12 Nov 2019 10:58:55 PM CST
 ************************************************************************/
/**
 * 请编写一C程序，该程序求出（输出）1-1000以内的所有的同构数。
 *		 所谓同构数是指对于一个N位的自然数，其数的平方值的末尾的N位数等于该数。例如，1位数5就是一个同构数，因为5的平方是25，而25的末尾的1位数为5。2位数25也是一个同构数，因为625的末尾的2位数是25
 */
#include "stdio.h"

void isTGS(int i){
	int p,n,j = i,t=1;	//p为平方，n为i的位数，j代替i执行操作，t为10的j次幂
	p = i*i;
	for(n = 0;j!=0;++n){
		j = j /10;
		t = 10*t;
	}
	if(p%t == i) printf("%d是同构数\n",i);
}

int main(int argc,char **argv){
	int i;
	for(i = 1;i<=1000;i++) isTGS(i);
	return 1;
}