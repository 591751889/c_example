/*
C或C++，不允许使用STL
试题(共100分，包括4个问题）
MX是世界上第一大传媒娱乐企业，该公司数十年的经营历史中创作了很多经典
影片，此外还经营着很多的规模十分宏大世界级的主题娱乐公园。最近MX公司刚
和C国X城市达成协定，共同投资建设C国国内唯一一家主题娱乐公园。
主题公园的经营管理部门计划布设m个固定的快餐饮品供应点为游客服务。希
望游客游园时，绝对不要受到快餐店补货车工作运行的影响，最好的办法就是绝对
不让游客在园中看到补货车，绝对不让游客听到补货车的声音。让游客觉得在园中
任何一个餐饮点随时都能买到食品和饮品，能得到无穷无尽的食品和饮品。因此设
计团队想把给m个餐饮点供货的通道设置在地下，并在通道内部敷设一定的隔音材
料，可是修造地下供货通道的经济代价与通道总长度成正比（每100米修造代价是
M万元），花费将是非常巨大的，不过游客至上。
现在设计团队手中已经有了m个餐饮点的坐标位置（x，y）信息，你是设计团
队的一员，团队交给你的工作就是规划一个地下通道建设方案，将m个餐饮点都连
接起来且总修造代价尽可能地小。
考试要求：
（1）请详细描述你的设计方案。（20分）
（2）请详细描述你给出设计方案的实现算法（以流程图或伪代码的形式）以
及选用所有相关的数据结构（需要给出相应的理论依据）。（30分）
（3）请用计算机程序设计语言（C或C++，不允许使用STL）编程实现你设计
的求解算法（给出尽可能详尽的注释）。（30分）
（4）随机生成m个坐标信息验证你的算法和程序，如果最终程序求解的通道
规划方案不唯一，则输出其中的任一方案即可（要求m>=30）。（20分）
（5）答题字数不少于2000（不含源代码、表格和图片）。
 
*/ 
#include<stdio.h>
#include<math.h>
int n=6;
double a[100][100];
int biaoji[100];
double b[100][100];
int position[100][2];


void ge_rand(int n) {
	int random;
	int i,j;
	for(i=0; i<n; i++) {
		biaoji[i]=0;
	}
	int x,y;
	srand((unsigned int)time(0));
	for ( i = 0; i < n; i++)

	{
		random = rand();
		position[i][0] = random % (100 - 1+1) + 1;//设置范围  1-100
		Sleep(500);
		random = rand();
		position[i][1]=random % (100 - 1+1) + 1;
		Sleep(500);
		printf("第%d个点的坐标是%d %d\n",i+1,position[i][0],position[i][1]);
	}

	for ( i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			if(i==j) {
				a[i][j]=9999;
				continue;
			}
			x=position[i][0]-position[j][0];
			y=position[i][1]-position[j][1];
			a[i][j]=a[j][i]=sqrt(x*x+y*y);
//			printf("%d %d %d %d %lf\n",position[i][0],position[i][1],position[j][0],position[j][1],a[i][j]);
		}
	}


}

int suanfa(int n) {
	int i,j;
	int xx=0,yy=0;
	int min=9999;
	int the_x,the_y;
	for(i=0; i<n-1; i++)
		for (j=i+1; j<n; j++) {
			if (min>a[i][j]) {
				min=a[i][j];
				the_x=i;
				the_y=j;
			}
		}
	biaoji[the_x]=1;
	biaoji[the_y]=1;

	b[the_x][the_y]=b[the_y][the_x]=a[the_x][the_y];
	int t=2;
	while(t<n) {
		min=9999;
		for(i=0; i<n; i++) {

			if(biaoji[i]) {
//				printf("biaoji[%d]=%d\n",i,biaoji[i]);
				for(j=0; j<n; j++) {

					if(min>a[i][j])
						xx++;

					if(biaoji[j]==0)
						yy++;

					if(min>a[i][j]&&biaoji[j]==0) {

						min=a[i][j];
						the_x=i;
						the_y=j;
					}
				}
			}
		}
		t++;
		biaoji[the_y]=1;
		b[the_x][the_y]=b[the_y][the_x]=a[the_x][the_y];

	}
	for(i=0; i<n-1; i++)
		for (j=i+1; j<n; j++) {
			if(b[i][j]>0)
			printf("在第%d个点和第%d个点修建%.3lf长的管道\n",i+1,j+1,b[i][j]);
		}

	return 0;
}
int main() {


	printf("请输入生成随机点的数目：");
	scanf("%d",&n);
	ge_rand(n);
	suanfa(n);
}
