#include<stdio.h>
int fun(int***);
int main()
{
	int *p,a=10,**k;
	p=&a;
	k=&p;
	printf("%d\n",a);
	printf("%d\n",*p);
	printf("%d\n",**k);
	//printf("%d\n",*k);
	fun(&k);
	printf("%d\n",a);
	printf("%d\n",*p);
	printf("%d\n",**k);
	//printf("%d\n",*k);

}
int fun(int ***k)
{
	int *b,c=9;
	b=&c;
	*k=&b;
	printf("%u\n",k);
	printf("%u\n",*k);
	printf("%d\n",**k);
	//**k=11;
}
