#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#define maxn 64

typedef struct node
{
	int data;
	struct node *next;
}snode,*slink;
typedef struct Anode
{
	int tail, head;
	struct Anode *hlink, *tlink;
}arcnode;
typedef struct Vnode
{
	char data;
	arcnode *fin, *fout;
}vexnode;

vexnode G[maxn];

void Clearstack(slink s)
{
	s = NULL;
}
int Emptystack(slink s)
{
	if (s == NULL)
	{
		return(1);
	}
	else
	{
		return(0);
	}
}
void Push(slink *top, int e)
{
	slink p;
	p = (slink)malloc(sizeof(snode));
	p->data = e;
	p->next = *top;
	*top = p;
}
int Pop(slink*top)
{
	int e;
	slink p;
	if (Emptystack(*top))
	{
		return(-1);
	}
	else
	{
		e = (*top)->data;
		p = *top;
		*top = (*top)->next;
		free(p);
		return(e);
	}
}

int LocateVex(vexnode G[],char u)
{
	int i;
	for (i = 0; i < maxn; i++)
	{
		if (u == G[i].data)
		{
			return i;
		}
		if (i == maxn)
		{
			return -1;
		}
	}
}

void createorlist(vexnode G[])
{
	int i, j, n,isFromFile;
	arcnode *p;
	char ch, u, v;
	i = n = 0;
	printf("请选择输入方式：1.文件输入；2.键盘输入\n");
	scanf("%d", &isFromFile);
	getchar();
	if (isFromFile == 2)
	{
		printf("请输入节点，以#结束：");
		ch = getchar();
		getchar();
		while (ch != '#')
		{
			n++;
			G[i].data = ch;
			G[i].fin = G[i].fout = NULL;
			i++;
			ch = getchar();
			getchar();
		}
		printf("\n请输入弧，以##结束：");
		scanf("%c%c", &u, &v);
		getchar();
		while (u != '#')
		{
			i = LocateVex(G, u);
			j = LocateVex(G, v);
			p = (arcnode*)malloc(sizeof(arcnode));
			p->tail = i;
			p->head = j;
			p->hlink = G[j].fin;
			G[j].fin = p;
			p->tlink = G[i].fout;
			G[i].fout = p;
			scanf("%c%c", &u, &v);
			getchar();
		}
	}
	else
	{
		FILE *fpRead = fopen("data.txt", "r");
		if (fpRead == NULL)
		{
			printf("文件不存在……");
		}
		fscanf(fpRead, "%c", &ch);
		while (ch != '#')
		{
				n++;
				G[i].data = ch;
				G[i].fin = G[i].fout = NULL;
				i++;
			fscanf(fpRead, "%c", &ch);
		}
		
		fscanf(fpRead,"%c%c", &u, &v);
		while (u != '#')
		{
			i = LocateVex(G, u);
			j = LocateVex(G, v);
			p = (arcnode*)malloc(sizeof(arcnode));
			p->tail = i;
			p->head = j;
			p->hlink = G[j].fin;
			G[j].fin = p;
			p->tlink = G[i].fout;
			G[i].fout = p;
			fscanf(fpRead, "%c%c", &u, &v);
		}

	}
}

void Creatid(vexnode G[], int n, int id[])
{
	int count, i;
	arcnode *p;
	for (i = 0; i < n; i++)
	{
		count = 0;
		p = G[i].fin;
		while (p)
		{
			count++;
			p = p->hlink;
		}
		id[i] = count;
	}
}

void Topsort(vexnode G[], int n)
{
	int i, j, k, count;
	int id[maxn];
	slink s = NULL;
	arcnode *p;
	Creatid(G, n, id);
	Clearstack(s);
	for ( i = 0; i < n; i++)
	{
		if (id[i] == 0)
			Push(&s, i);
	}
	count = 0;
	while (!Emptystack(s))
	{
		j = Pop(&s);
		printf("%c", G[j].data);
		count++;
		p = G[j].fout;
		while (p)
		{
			k = p->head;
			id[k]--;
			if (id[k] == 0)
				Push(&s, k);
			p = p->tlink;
		}
	}
	if (count == n)
	{
		printf("这是有向无环图");
	}
	else
	{
		printf("这不是有向无环图");
	}

}

void main()
{
	int x;
	do
	{
		int id[maxn];
		createorlist(G);
		Creatid(G, maxn,id);
		Topsort(G,maxn);
		printf("\n是否继续？继续：1；退出：0\n");
		scanf("%d", &x);
		getchar();
	} while (x);
	
}