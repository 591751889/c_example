#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#define MAX 20
#define INFINITY      9999
typedef struct ArCell {
	int adj;//路径长度
} bianchang[MAX][MAX];
typedef struct node {
	int x,y;
	char name[10];//名称
	int number;//编号
	char introduce[100];//介绍
} point;
typedef struct {
	bianchang side;
	point spot[MAX];
	int vexnum;
	int arcnum; //点和边的数目
} Graph;
int dist[MAX][MAX];  /*距离向量类型*/
int path[MAX][MAX];  /*路径类型*/
int m[MAX]= {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} ;
int p[20];
int count = 0;
int visited[MAX] = { 0 };
int inf[MAX] = { 0 };//盛春强
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
		printf("输入的编号不合法，请输入合法的景点编号：");
		scanf("%d",&m);
		if(m>=1&&m<G->vexnum)
			flag=0;
	}
	return m;
}
void ShortestPath_FLD(Graph *G) {
	/*弗洛伊德算法求两景点间的一条最短的路径并输出所经结点*/
	int i, j, k;
	for(i=1; i<=G->vexnum; i++)    /*初始化距离向量与路径向量矩阵*/
		for(j=1; j<=G->vexnum; j++) {
			dist[i][j]=G->side[i][j].adj;
			if(i!=j&&dist[i][j]<INFINITY) path[i][j]=i;
			else path[i][j]=-1;           /*-1代表当前两点不可达*/
		}
	for(k=1; k<=G->vexnum; k++)    /*递推求解每两景点的最短路径*/
		for(i=1; i<=G->vexnum; i++)
			for(j=1; j<=G->vexnum; j++)    /*更新dist[i][j]的值*/
				if(dist[i][j]>(dist[i][k]+dist[k][j])) {
					dist[i][j]=dist[i][k]+dist[k][j];
					path[i][j]=k;   /*path用于记录最短路径上的结点*/
				}

}
void Floyd_Print(Graph *G, int sNum, int eNum) {
	if(path[sNum][eNum]==-1||path[sNum][eNum]==eNum||path[sNum][eNum]==sNum)
		return ;
	else {
		Floyd_Print(G,sNum,path[sNum][eNum] );          /*将中间点作为终点继续打印路径*/
		printf("%s->->",G->spot[path[sNum][eNum]].name);             /*打印中间景点名字*/
		//	m[G->spot[path[sNum][eNum]].number]=0;
		Floyd_Print(G,path[sNum][eNum],eNum);               /*将中间点作为起点继续打印路径*/
	}
}
void Bestpath(Graph *G) { ///*多景点间求最佳路径*/
	int a,k;
	int vNum[MAX]= {0},j=1;
	int i;              /*记录用户输入的编号信息*/
	int d=0;                                 /*统计全程总长*/
	printf("请输入你需要一起游览的个数：");
	scanf("%d",&a);
	printf("请输入你要游览的第%d个景点的编号（数字间用回车分隔）：",j);
	vNum[j-1]=shuru(G);//scanf("%d",&vNum[j-1]);
	while(vNum[j-1]&&j<a) {
		printf("请输入你要游览的第%d个景点编号：",++j);
		vNum[j-1]=shuru(G);//scanf("%d", &vNum[j-1]);
	}
	for(i=0; i<a-1; i++) { //vNum[i]>0&&vNum[i+1]>0
		printf("%s->->",G->spot[vNum[i]].name);   /*输出路径上的起点*/
		Floyd_Print(G,vNum[i],vNum[i+1]);        /*利用佛洛依德算法*/
		d+=dist[vNum[i]][vNum[i+1]];
	}
	printf("%s\n",G->spot[vNum[j-1]].name);  /*输出路径上的终点*/ // G->spot[vNum[i]]
	printf("\n全程总长为：%dm\n",d);
	printf("完毕，按任意键继续!\n");
	getch();
}

void map() {
	printf("               中           北            大           学           校           园           图                        \n");
	printf("************************************************************************************************************************************\n");
	printf("*                                            -------------                                                                        *\n");
	printf("*                                            | 9 校 医 院  |                                                                       *\n");
	printf("*                                             --------------                                                                       *\n");
	printf("*                                                     |                                                                            *\n");
	printf("*                                                     |                                                                            *\n");
	printf("*                                                     |                                                                            *\n");
	printf("*                                                     |                                                                            *\n");
	printf("*                                            ----     |                            ---------------                                 *\n");
	printf("*                                           | 8  |    |                           | 4 图  书  馆  |                                *\n");
	printf("*                                           | 第 |    |                            ----------------                                *\n");
	printf("*                                           | 四 |    |                                 |                     ---------------        *\n");
	printf("*                                      -----| 食 |-----------------------------------------------------------| 5 主 教 学 楼 |     *\n");
	printf("*                                     |     | 堂 |                                      |                     ---------------      *\n");
	printf("*                                     |     -----                                 ----------------                    |          *\n");
	printf("*                                     |                                            |  7 操      场  |                   |          *\n");
	printf("*  ----                               |                                             ----------------                    |          *\n");
	printf("* | 柏 |                              |                                                    |                       -------------   *\n");
	printf("* |    |                              |                                                    |----------------------|5 行 知 广 场|  *\n");
	printf("* | 林 |--------|                     |                                                                           --------------   *\n");
	printf("* |    |        |                     |                                                                                            *\n");
	printf("* | 园 |        |        ----         |                                                                                            *\n");
	printf("* | 10 |        |       | 3  |        |                                                                                            *\n");
	printf("*  ----         |       | 逸 |        |                                                                                            *\n");
	printf("*               |       |    |        |                                                                                            *\n");
	printf("*               |-------| 夫 |--------                                                                                             *\n");
	printf("*               |       |    |                                                                                                     *\n");
	printf("*               |       | 楼 |                                                                                                     *\n");
	printf("*               |        ----                                                                                                      *\n");
	printf("*               |                                                                                                                  *\n");
	printf("*               |                                                                                                                  *\n");
	printf("*               |                                                                                                                  *\n");
	printf("*        ---------------                                                                                                           *\n");
	printf("*       | 2  德  怀  楼  |                                                                                                         *\n");
	printf("*         ---------------                                                                                                          *\n");
	printf("*               |                                                                                                                  *\n");
	printf("*               |                                                                                                                  *\n");
	printf("*               |                                                                                                                  *\n");
	printf("*               |                                                                                                                  *\n");
	printf("*                                                                                                                                  *\n");
	printf("*        ---------------                                                                                                           *\n");
	printf("*       | 1  一  道  门 |                                                                                                          *\n");
	printf("*        ---------------                                                                                                           *\n");
	printf("*                                                                                                                                  *\n");
	printf("************************************************************************************************************************************\n");
	printf("\n");
}
void menu() {

	printf("*************************************************************************\n");
	printf("                                                                         \n");
	printf("                                                                         \n");
	printf("                         欢迎使用中北校园导游咨询                        \n");
	printf("                                                                         \n");
	printf("                                                                         \n");
	printf("*************************************************************************\n");
	printf("                   1.景点信息查询                                        \n");
	printf("                   2.查看校内地图                                       \n");
	printf("                   3.查看两点间最短路径                                 \n");
	printf("                   4.查询查找两点间所有路径                             \n");
	printf("                   5.查找校内多个景点最短路径(起始点为游客当前位置)      \n");
	printf("                   6.修改信息                                            \n");
	printf("                   0.退出系统                                            \n");
	printf("*************************************************************************\n");
	printf("                   请选择：");

}
int panduan(int b,int s,int a[]) { //室长
	int i;
	for(i=1; i<=s; i++) {
		if(a[i]==b) {
			return 0;
		}
	}
	return 1;
}
void dfs(Graph *g, int i, int j, int s) { // 室长
	int k;
	if (inf[s] == j) {
		int juli=0;
		count++;
		printf("第%d条路径：", count);
		for (k = 1; k <= s - 1; k++)
			printf("%s-->", g->spot[inf[k]].name);
		printf("%s  \n", g->spot[inf[k]].name);
		for(; s>1; s--)
			juli+=g->side[inf[s]][inf[s-1]].adj;
		printf("总距离为：%d米\n",juli);
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
void alldfs(Graph *g, int i, int j) { // 室长
	printf("从%s到%s的所有路径有：\n", g->spot[i].name, g->spot[j].name);
	inf[1] = i;
	dfs(g, i, j, 1);
}
void odfs(Graph *g) { // 室长
	int i,j;
	int k;
	count=0;
	printf("请输入两地点的编号:\n");
	printf("请输入第一个地点的编号:");
	i=shuru(g);
	printf("请输入第二个地点的编号:");
	j=shuru(g);//scanf("%d%d",&i,&j);
	alldfs(g,i,j);
	printf("完毕，按任意键继续!\n");
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
	// 计算任意两个景点之间的最短路径
	int v,w,w1,i,j,v1,min,x,flag=1,v0;
	int final[20], D[20], p[20][20];
	while(flag) {
		printf("请输入一个起始景点编号:");
		scanf("%d",&v0);
		if(v0<0||v0>G->vexnum) {
			printf("景点编号不存在!请重新输入景点编号:");
			scanf("%d",&v0);
		} else {

			if(v0>=0&&v0<=G->vexnum)
				flag=0;
		}
	}
	flag=1;
	while(flag) {
		printf("请输入一个目的地景点编号:");
		scanf("%d",&v1);
		if(v1<0||v1>G->vexnum) {
			printf("景点编号不存在!请重新输入景点编号:");
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
//				printf("向东走%dm",G->side[w1][j].adj);
//			if(G->spot[w1].x>G->spot[j].x)
//				printf("向西走%dm",G->side[w1][j].adj);
//			if(G->spot[w1].y<G->spot[j].y)
//				printf("向北走%dm",G->side[w1][j].adj);
//			if(G->spot[w1].y>G->spot[j].y)
//				printf("向南走%dm",G->side[w1][j].adj);
			printf("-->%s",G->spot[j].name);
			w1=j;
			p[v][j]=0;
		} else break;
	} while(1);
	printf("\n       总路线长%dm\n\n",D[v]);
	printf("完毕，按任意键继续!\n");
	getch();
}

int find(Graph *g,int a) {

	if(a<=g->vexnum&&a>0) {
		printf("编号：%d\n",a);
		printf("名称：%s\n",g->spot[a].name);
		printf("简介：%s\n",g->spot[a].introduce);
		return 0;
	} else {
		printf("输入错误，请重新输入！\n");
		return 1;
	}

}
void ofind(Graph *g) {
	view(g);
	int i=1,j;
	int q;
	printf("请输入地点的编号:\n");
	while(i) {
		scanf("%d", &q);
		i=find(g,q);
	}
	printf("是否继续查询？1.是2.否\n");
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
	printf("请输入增加路径数目：");
	scanf("%d",&n);
	G->arcnum+=n;
	for(i=1; i<=n; i++) {
		printf("第%d条路径:\n",i);
		printf("请输入增加路径的起始编号： ");
		v0=shuru(G);//scanf("%d",&v0);
		printf("请输入终点编号： ");
		v1=shuru(G);//scanf("%d",&v1);
		printf("请输入路径长度： ");
		scanf("%d",&distance);
		G->side[v0][v1].adj=G->side[v1][v0].adj=distance;
	}
	rewrite(G);
}
void newpath(Graph *G,int x) {
	int v0,v1,distance,n,i;
	printf("请输入增加路径数目：");
	scanf("%d",&n);
	G->arcnum+=n;
	for(i=1; i<=n; i++) {
		printf("第%d条路径:\n",i);
		printf("请输入终点编号： ");
		v1=shuru(G);//scanf("%d",&v1);
		printf("请输入路径长度： ");
		scanf("%d",&distance);
		G->side[x][v1].adj=G->side[v1][x].adj=distance;
	}
	rewrite(G);
}
void increasesight(Graph *G) {
	int i;
	G->vexnum++;
	printf("请输入要添加景点的信息: \n");
	printf("请输入景点名称： \n");
	scanf("%s",&G->spot[G->vexnum].name);//gets(G->spot[G->vexnum].name);//strcpy(G->spot[G->vexnum].name,gets());
	printf("请输入景点介绍： ");
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
	printf("输入你要删除的景点：");
	a=shuru(G);//scanf("%d",&a);
	if(a<1||a>G->vexnum )
		printf("输入错误，请重新输入！\n");
	else {
		if(a==G->vexnum) {
			G->vexnum--;
			printf("已找到该点，删除成功！\n");
		} else {

			for(i=1; k<G->vexnum ; k++) {

				G->side [i][a]=G->side [a][i]=G->side[G->vexnum][i]=G->side [i][G->vexnum];
			}
			strcpy(G->spot [a].name,G->spot [G->vexnum].name );
			strcpy(G->spot[a].introduce ,G->spot[G->vexnum].introduce  );
			printf("已找到该点，删除成功！\n");
			G->vexnum--;
		}
	}
	rewrite(G);
}
void deletepath(Graph *G) {
	int a,b;
	printf("输入你要删除的边的起点：");
	a=shuru(G);
	printf("输入你要删除的边的终点：");
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
		printf("请输入你的选择：\n");
		scanf("%d",&choise);
		if(choise<0||choise>6) {
			printf("您的输入有误，请重新输入");
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
					printf("修改图信息！（管理者界面）");

					while(1) {
						if(logo==0)break;
						printf("\n1.增加点                       2.增加边\n");
						printf("3.删除点                       4.删除边\n");
						printf("0.上一步\n");
						scanf("%d",&schoise);
						if(schoise<0||schoise>4) {
							printf("您的输入有误，请重新输入");
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


