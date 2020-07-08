#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#define MAX 20
#define INFINITY      9999
typedef struct ArCell {
	int adj;//·������
} bianchang[MAX][MAX];
typedef struct node {
	int x,y;
	char name[10];//����
	int number;//���
	char introduce[100];//����
} point;
typedef struct {
	bianchang side;
	point spot[MAX];
	int vexnum;
	int arcnum; //��ͱߵ���Ŀ
} Graph;
int dist[MAX][MAX];  /*������������*/
int path[MAX][MAX];  /*·������*/
int m[MAX]= {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} ;
int p[20];
int count = 0;
int visited[MAX] = { 0 };
int inf[MAX] = { 0 };//ʢ��ǿ
void view(Graph *G) {
	int i;
	for(i=1; i<=G->vexnum; i++) {
		printf(" %d.%s\n",i,G->spot[i].name);
		//if(i%2==0)printf("\n");
	}
}
void rewrite(Graph *p) {
	int i,j;
	FILE *fp=fopen("f:\\daohang.txt","w+");
	fprintf(fp,"%d  %d\n",p->vexnum,p->arcnum);
	for(i=1; i<=p->vexnum; i++) {
		fprintf(fp,"%d %s %s\n",  p->spot[i].number, p->spot[i].name, p->spot[i].introduce);
	}
	for(i=1; i<=p->vexnum; i++)
		for(j=1; j<=i; j++) {
			if(p->side[i][j].adj!=9999)
				fprintf(fp,"%d %d %d\n",i,j,p->side[i][j].adj);
		}
	fclose(fp);
}
int shuru(Graph *G) {
	int flag=1,m;
	scanf("%d",&m);
	if(m>=1&&m<=G->vexnum)
		flag=0;
	while(flag) {
		printf("����ı�Ų��Ϸ���������Ϸ��ľ����ţ�");
		scanf("%d",&m);
		if(m>=1&&m<G->vexnum)
			flag=0;
	}
	return m;
}
void ShortestPath_FLD(Graph *G) {
	/*���������㷨����������һ����̵�·��������������*/
	int i, j, k;
	for(i=1; i<=G->vexnum; i++)    /*��ʼ������������·����������*/
		for(j=1; j<=G->vexnum; j++) {
			dist[i][j]=G->side[i][j].adj;
			if(i!=j&&dist[i][j]<INFINITY) path[i][j]=i;
			else path[i][j]=-1;           /*-1����ǰ���㲻�ɴ�*/
		}
	for(k=1; k<=G->vexnum; k++)    /*�������ÿ����������·��*/
		for(i=1; i<=G->vexnum; i++)
			for(j=1; j<=G->vexnum; j++)    /*����dist[i][j]��ֵ*/
				if(dist[i][j]>(dist[i][k]+dist[k][j])) {
					dist[i][j]=dist[i][k]+dist[k][j];
					path[i][j]=k;   /*path���ڼ�¼���·���ϵĽ��*/
				}

}
void Floyd_Print(Graph *G, int sNum, int eNum) {
	if(path[sNum][eNum]==-1||path[sNum][eNum]==eNum||path[sNum][eNum]==sNum)
		return ;
	else {
		Floyd_Print(G,sNum,path[sNum][eNum] );          /*���м����Ϊ�յ������ӡ·��*/
		printf("%s->->",G->spot[path[sNum][eNum]].name);             /*��ӡ�м侰������*/
		//	m[G->spot[path[sNum][eNum]].number]=0;
		Floyd_Print(G,path[sNum][eNum],eNum);               /*���м����Ϊ��������ӡ·��*/
	}
}
void Bestpath(Graph *G) { ///*�ྰ��������·��*/
	int a,k;
	int vNum[MAX]= {0},j=1;
	int i;              /*��¼�û�����ı����Ϣ*/
	int d=0;                                 /*ͳ��ȫ���ܳ�*/
	printf("����������Ҫһ�������ĸ�����");
	scanf("%d",&a);
	printf("��������Ҫ�����ĵ�%d������ı�ţ����ּ��ûس��ָ�����",j);
	vNum[j-1]=shuru(G);//scanf("%d",&vNum[j-1]);
	while(vNum[j-1]&&j<a) {
		printf("��������Ҫ�����ĵ�%d�������ţ�",++j);
		vNum[j-1]=shuru(G);//scanf("%d", &vNum[j-1]);
	}
	for(i=0; i<a-1; i++) { //vNum[i]>0&&vNum[i+1]>0
		printf("%s->->",G->spot[vNum[i]].name);   /*���·���ϵ����*/
		Floyd_Print(G,vNum[i],vNum[i+1]);        /*���÷��������㷨*/
		d+=dist[vNum[i]][vNum[i+1]];
	}
	printf("%s\n",G->spot[vNum[j-1]].name);  /*���·���ϵ��յ�*/ // G->spot[vNum[i]]
	printf("\nȫ���ܳ�Ϊ��%dm\n",d);
	printf("��ϣ������������!\n");
	getch();
}

void map() {
	printf("               ��           ��            ��           ѧ           У           ԰           ͼ                        \n");
	printf("************************************************************************************************************************************\n");
	printf("*                                            -------------                                                                        *\n");
	printf("*                                            | 9 У ҽ Ժ  |                                                                       *\n");
	printf("*                                             --------------                                                                       *\n");
	printf("*                                                     |                                                                            *\n");
	printf("*                                                     |                                                                            *\n");
	printf("*                                                     |                                                                            *\n");
	printf("*                                                     |                                                                            *\n");
	printf("*                                            ----     |                            ---------------                                 *\n");
	printf("*                                           | 8  |    |                           | 4 ͼ  ��  ��  |                                *\n");
	printf("*                                           | �� |    |                            ----------------                                *\n");
	printf("*                                           | �� |    |                                 |                     ---------------        *\n");
	printf("*                                      -----| ʳ |-----------------------------------------------------------| 5 �� �� ѧ ¥ |     *\n");
	printf("*                                     |     | �� |                                      |                     ---------------      *\n");
	printf("*                                     |     -----                                 ----------------                    |          *\n");
	printf("*                                     |                                            |  7 ��      ��  |                   |          *\n");
	printf("*  ----                               |                                             ----------------                    |          *\n");
	printf("* | �� |                              |                                                    |                       -------------   *\n");
	printf("* |    |                              |                                                    |----------------------|5 �� ֪ �� ��|  *\n");
	printf("* | �� |--------|                     |                                                                           --------------   *\n");
	printf("* |    |        |                     |                                                                                            *\n");
	printf("* | ԰ |        |        ----         |                                                                                            *\n");
	printf("* | 10 |        |       | 3  |        |                                                                                            *\n");
	printf("*  ----         |       | �� |        |                                                                                            *\n");
	printf("*               |       |    |        |                                                                                            *\n");
	printf("*               |-------| �� |--------                                                                                             *\n");
	printf("*               |       |    |                                                                                                     *\n");
	printf("*               |       | ¥ |                                                                                                     *\n");
	printf("*               |        ----                                                                                                      *\n");
	printf("*               |                                                                                                                  *\n");
	printf("*               |                                                                                                                  *\n");
	printf("*               |                                                                                                                  *\n");
	printf("*        ---------------                                                                                                           *\n");
	printf("*       | 2  ��  ��  ¥  |                                                                                                         *\n");
	printf("*         ---------------                                                                                                          *\n");
	printf("*               |                                                                                                                  *\n");
	printf("*               |                                                                                                                  *\n");
	printf("*               |                                                                                                                  *\n");
	printf("*               |                                                                                                                  *\n");
	printf("*                                                                                                                                  *\n");
	printf("*        ---------------                                                                                                           *\n");
	printf("*       | 1  һ  ��  �� |                                                                                                          *\n");
	printf("*        ---------------                                                                                                           *\n");
	printf("*                                                                                                                                  *\n");
	printf("************************************************************************************************************************************\n");
	printf("\n");
}
void menu() {

	printf("*************************************************************************\n");
	printf("                                                                         \n");
	printf("                                                                         \n");
	printf("                         ��ӭʹ���б�У԰������ѯ                        \n");
	printf("                                                                         \n");
	printf("                                                                         \n");
	printf("*************************************************************************\n");
	printf("                   1.������Ϣ��ѯ                                        \n");
	printf("                   2.�鿴У�ڵ�ͼ                                       \n");
	printf("                   3.�鿴��������·��                                 \n");
	printf("                   4.��ѯ�������������·��                             \n");
	printf("                   5.����У�ڶ���������·��(��ʼ��Ϊ�ο͵�ǰλ��)      \n");
	printf("                   6.�޸���Ϣ                                            \n");
	printf("                   0.�˳�ϵͳ                                            \n");
	printf("*************************************************************************\n");
	printf("                   ��ѡ��");

}
int panduan(int b,int s,int a[]) { //�ҳ�
	int i;
	for(i=1; i<=s; i++) {
		if(a[i]==b) {
			return 0;
		}
	}
	return 1;
}
void dfs(Graph *g, int i, int j, int s) { // �ҳ�
	int k;
	if (inf[s] == j) {
		int juli=0;
		count++;
		printf("��%d��·����", count);
		for (k = 1; k <= s - 1; k++)
			printf("%s-->", g->spot[inf[k]].name);
		printf("%s  \n", g->spot[inf[k]].name);
		for(; s>1; s--)
			juli+=g->side[inf[s]][inf[s-1]].adj;
		printf("�ܾ���Ϊ��%d��\n",juli);
	} else
		for (k = 1; k <= g->vexnum; k++) {
			if(panduan(k,s,inf)) {
				if (g->side[i][k].adj!=9999 && visited[k] == 0) {
					visited[k] = 1;
					inf[s+1] = k;
					dfs(g, k, j, s + 1);
					visited[k] = 0;
				}
			}
		}

}
void alldfs(Graph *g, int i, int j) { // �ҳ�
	printf("��%s��%s������·���У�\n", g->spot[i].name, g->spot[j].name);
	inf[1] = i;
	dfs(g, i, j, 1);
}
void odfs(Graph *g) { // �ҳ�
	int i,j;
	int k;
	count=0;
	printf("���������ص�ı��:\n");
	printf("�������һ���ص�ı��:");
	i=shuru(g);
	printf("������ڶ����ص�ı��:");
	j=shuru(g);//scanf("%d%d",&i,&j);
	alldfs(g,i,j);
	printf("��ϣ������������!\n");
	getch();
}
void initgraph(Graph *p) {
	int i,j;
	FILE *fp=fopen("f:\\daohang.txt","r+");
	fscanf(fp,"%d %d\n",  &p->vexnum,&p->arcnum);
	for(i=1; i<=p->vexnum; i++)
		for(j=1; j<=p->vexnum; j++)
			p->side[i][j].adj=p->side[j][i].adj=9999;
//	printf("%d %d\n",p->vexnum,p->arcnum);
	for(i=1; i<=p->vexnum; i++) {
		fscanf(fp,"%d %s %s\n",  &p->spot[i].number, &p->spot[i].name, &p->spot[i].introduce);
//		printf("%d %s %s\n",  p->spot[i].number, p->spot[i].name, p->spot[i].introduce);
	}
	int x,y,m;
	for(i=1; i<=p->arcnum; i++) {
		fscanf(fp,"%d %d %d\n",  &x, &y, &m);
		p->side[x][y].adj=p->side[y][x].adj=m;
//		printf("%d=%d  x=%d  y=%d \n",i,p->side[x][y].adj,x,y);
	}
	fclose(fp);
}

void Wellway(Graph * G) {
	// ����������������֮������·��
	int v,w,w1,i,j,v1,min,x,flag=1,v0;
	int final[20], D[20], p[20][20];
	while(flag) {
		printf("������һ����ʼ������:");
		scanf("%d",&v0);
		if(v0<0||v0>G->vexnum) {
			printf("�����Ų�����!���������뾰����:");
			scanf("%d",&v0);
		} else {

			if(v0>=0&&v0<=G->vexnum)
				flag=0;
		}
	}
	flag=1;
	while(flag) {
		printf("������һ��Ŀ�ĵؾ�����:");
		scanf("%d",&v1);
		if(v1<0||v1>G->vexnum) {
			printf("�����Ų�����!���������뾰����:");
			scanf("%d",&v1);
		} else {
			if(v1>=0&&v1<=G->vexnum)
				flag=0;
		}
	}
	for(v=0; v<G->vexnum; v++) 
	{
		final[v]=0;
		D[v]=G->side[v0][v].adj;
		for(w=0; w<G->vexnum; w++)
			p[v][w]=0;
		if(D[v]<9999) 
		{
			p[v][v0]=1;
			p[v][v]=1;
		}
	}
	D[v0]=0;
	final[v0]=1;
	for(i=1;i<=G->vexnum;i++) 
	{
		min=INFINITY;
		for(w=1; w<=G->vexnum; w++)
			if(!final[w])
				if(D[w]<min) 
				{
					v=w;
					min=D[w];
				}
		final[v]=1;
		for(w=1; w<=G->vexnum; w++)
			if(!final[w]&&(min+G->side[v][w].adj<D[w])) 
			{
				D[w]=min+G->side[v][w].adj;
				for(x=0; x<G->vexnum; x++)
					p[w][x]=p[v][x];
				p[w][w]=1;
			}
	}
	v=v1;
	w1=v0;
	printf("%s",G->spot[v0].name);
	do {
		flag=0;
		min=INFINITY;
		for(w=0; w<G->vexnum; w++) {
			if(p[v][w]&&w!=v0) {
				flag=1;
				if(D[w]<min) {
					j=w;
					min=D[w];
				}
			}
		}
		if(flag) {
//			if(G->spot[w1].x<G->spot[j].x)// int a,b; if(a>b)
//				printf("����%dm",G->side[w1][j].adj);
//			if(G->spot[w1].x>G->spot[j].x)
//				printf("������%dm",G->side[w1][j].adj);
//			if(G->spot[w1].y<G->spot[j].y)
//				printf("����%dm",G->side[w1][j].adj);
//			if(G->spot[w1].y>G->spot[j].y)
//				printf("������%dm",G->side[w1][j].adj);
			printf("-->%s",G->spot[j].name);
			w1=j;
			p[v][j]=0;
		} else break;
	} while(1);
	printf("\n       ��·�߳�%dm\n\n",D[v]);
	printf("��ϣ������������!\n");
	getch();
}

int find(Graph *g,int a) {

	if(a<=g->vexnum&&a>0) {
		printf("��ţ�%d\n",a);
		printf("���ƣ�%s\n",g->spot[a].name);
		printf("��飺%s\n",g->spot[a].introduce);
		return 0;
	} else {
		printf("����������������룡\n");
		return 1;
	}

}
void ofind(Graph *g) {
	view(g);
	int i=1,j;
	int q;
	printf("������ص�ı��:\n");
	while(i) {
		scanf("%d", &q);
		i=find(g,q);
	}
	printf("�Ƿ������ѯ��1.��2.��\n");
	scanf("%d",&j);
	switch(j) {
		case 1:
			ofind(g);
		case 2:
			break;
		default:
			break;
	}
}
void increasepath(Graph *G) {
	int v0,v1,distance,n,i;
	printf("����������·����Ŀ��");
	scanf("%d",&n);
	G->arcnum+=n;
	for(i=1; i<=n; i++) {
		printf("��%d��·��:\n",i);
		printf("����������·������ʼ��ţ� ");
		v0=shuru(G);//scanf("%d",&v0);
		printf("�������յ��ţ� ");
		v1=shuru(G);//scanf("%d",&v1);
		printf("������·�����ȣ� ");
		scanf("%d",&distance);
		G->side[v0][v1].adj=G->side[v1][v0].adj=distance;
	}
	rewrite(G);
}
void newpath(Graph *G,int x) {
	int v0,v1,distance,n,i;
	printf("����������·����Ŀ��");
	scanf("%d",&n);
	G->arcnum+=n;
	for(i=1; i<=n; i++) {
		printf("��%d��·��:\n",i);
		printf("�������յ��ţ� ");
		v1=shuru(G);//scanf("%d",&v1);
		printf("������·�����ȣ� ");
		scanf("%d",&distance);
		G->side[x][v1].adj=G->side[v1][x].adj=distance;
	}
	rewrite(G);
}
void increasesight(Graph *G) {
	int i;
	G->vexnum++;
	printf("������Ҫ��Ӿ������Ϣ: \n");
	printf("�����뾰�����ƣ� \n");
	scanf("%s",&G->spot[G->vexnum].name);//gets(G->spot[G->vexnum].name);//strcpy(G->spot[G->vexnum].name,gets());
	printf("�����뾰����ܣ� ");
	scanf("%s",&G->spot[G->vexnum].introduce);
	G->spot[G->vexnum].number=G->vexnum;
	for(i=1; i<=G->vexnum; i++) {
		G->side[i][G->vexnum].adj=G->side[G->vexnum][i].adj=9999;
	}
	newpath(G,G->vexnum);
}

void deletesight(Graph *G) {
	int i,a;
	int k;
	printf("������Ҫɾ���ľ��㣺");
	a=shuru(G);//scanf("%d",&a);
	if(a<1||a>G->vexnum )
		printf("����������������룡\n");
	else {
		if(a==G->vexnum) {
			G->vexnum--;
			printf("���ҵ��õ㣬ɾ���ɹ���\n");
		} else {

			for(i=1; k<G->vexnum ; k++) {

				G->side [i][a]=G->side [a][i]=G->side[G->vexnum][i]=G->side [i][G->vexnum];
			}
			strcpy(G->spot [a].name,G->spot [G->vexnum].name );
			strcpy(G->spot[a].introduce ,G->spot[G->vexnum].introduce  );
			printf("���ҵ��õ㣬ɾ���ɹ���\n");
			G->vexnum--;
		}
	}
	rewrite(G);
}
void deletepath(Graph *G) {
	int a,b;
	printf("������Ҫɾ���ıߵ���㣺");
	a=shuru(G);
	printf("������Ҫɾ���ıߵ��յ㣺");
	b=shuru(G);
	G->arcnum--;
	G->side[a][b].adj=G->side[b][a].adj=9999;
	rewrite(G);
}
int main() {
	Graph graph;
	initgraph(&graph);
	int choise,schoise,logo=1;
	while(1) {
		menu();
		logo=1;
		printf("���������ѡ��\n");
		scanf("%d",&choise);
		if(choise<0||choise>6) {
			printf("����������������������");
		} else {
			switch(choise) {

				case 1:
					ofind(&graph);
					break;
				case 2:
					map();
					break;
				case 3:
					Wellway(&graph );
					break;
				case 4:
					odfs(&graph);
					break;
				case 5:
					ShortestPath_FLD(&graph);
					Bestpath(&graph);
					break;
				case 6:
					printf("�޸�ͼ��Ϣ���������߽��棩");

					while(1) {
						if(logo==0)break;
						printf("\n1.���ӵ�                       2.���ӱ�\n");
						printf("3.ɾ����                       4.ɾ����\n");
						printf("0.��һ��\n");
						scanf("%d",&schoise);
						if(schoise<0||schoise>4) {
							printf("����������������������");
						} else {


							switch(schoise) {

								case 1:
									increasesight(&graph);
									break;
								case 2:
									increasepath(&graph);
									break;
								case 3:
									deletesight(&graph);
									break;
								case 4:
									deletepath(&graph);
									break;
								case 0:
									logo=0;
									break;
							}


							break;
						case 0:
							exit(0);

						}
					}
			}
		}
	}
	return 0;
}


