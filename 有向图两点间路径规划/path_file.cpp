#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

#define Maxn_City 1010
#define Maxn_value 0x7fffffff

struct Path
{
    int value;//到当前的距离值
    int before;//该点的直接前驱
};

typedef pair<int,int> Pair;

//重载优先级队列排列比较方式，以车费从小至大排序
struct cmp
{
    bool operator()(Pair X,Pair Y){
        return X.second<Y.second;
    }
};

Path dis[Maxn_City][Maxn_City]; //从A到B的距离
vector<Pair> Cities[Maxn_City]; //Pair存储<到达城市,车费>

/*城市数 路径数*/
int Num_city,Num_path;

void Input_Init(void); //输入初始化
void dijkstra(int Origin_City); //从Origin_City 开始的迪杰斯特拉算法
bool Search_Path(void); //处理之后的路径检索


int main(){

    fstream _file;
	_file.open("path.in",ios::in);
	if(!_file){
        printf("无法找到读入文件path.in，请检查文件路径\n");
        system("pause");
        return 0;
    }
		
    
    freopen("path.in","r",stdin);
    freopen("path.out","w",stdout);
    Input_Init();

    //跑n次迪杰斯特拉算法
    for(int i=1;i<=Num_city;i++)
        dijkstra(i);
    
    printf("查询结果:\n");
    //进行路径检索
    while (Search_Path());

    return 0;
}

void Input_Init(){

    scanf("%d",&Num_city);

    scanf("%d",&Num_path);

    for(int i=1;i<=Num_path;i++){

        int A;
        Pair p;
        scanf("%d %d %d",&A,&p.first,&p.second);
        Cities[A].push_back(p);

    }

    for(int i=1;i<=Num_city;i++){
        for(int j=1;j<=Num_city;j++){
            // if(i!=j) dis[i][j].value = Maxn_value;
            dis[i][j].value = (i==j ? 0:Maxn_value);
            dis[i][j].before = j;
        }
    }

}

/*迪杰斯特拉算法核心，不做描述*/
void dijkstra(int Origin_City){

    priority_queue<Pair,vector<Pair>,cmp> Points;
    Points.push(Pair(Origin_City,dis[Origin_City][Origin_City].value));

    while (!Points.empty())
    {
        Pair Cur_Point = Points.top();
        Points.pop();
        for(int i=0 ; i<(int)Cities[Cur_Point.first].size() ; i++){

            Pair Nxt_Point = Cities[Cur_Point.first][i];
            if(dis[Origin_City][Nxt_Point.first].value > dis[Origin_City][Cur_Point.first].value+Nxt_Point.second){
                
                dis[Origin_City][Nxt_Point.first].value = dis[Origin_City][Cur_Point.first].value+Nxt_Point.second;
                dis[Origin_City][Nxt_Point.first].before = Cur_Point.first;
                Points.push(Pair(Nxt_Point.first,dis[Origin_City][Nxt_Point.first].value));
                
            }

        }
    }
    
}

bool Search_Path(){

    //输入查询的两城
    int A,B;
    scanf("%d %d",&A,&B);

    //检测到输入停止操作
    if(A == 0 || B == 0){
        printf("退出程序\n");
        return 0;
    }

    printf("查询:从%d城 到%d城\n",A,B);

    //输入的城市不存在
    if(A>Num_city || A<=0 || B>Num_city || B<=0){
        printf("非法输入\n");
        return 1;
    }
    
    //A->Bd的路径没有更新过
    if(dis[A][B].value == Maxn_value){
        printf("从%d城到%d城无可达路径\n",A,B);
        return 1;
    } 

    //路径堆，因为存储的是前驱节点，所以反向
    stack<int> Print_Path;
    Print_Path.push(A);

    for(int i=dis[A][B].before;i!=A;i=dis[A][i].before)
        Print_Path.push(i);

    //输出路径
    printf("路径为:");
    while (!Print_Path.empty())
    {
        printf("%d->",Print_Path.top());
        Print_Path.pop();
    }
    printf("%d\n",B);
    printf("共需要车费:%d\n",dis[A][B].value);
    
    return 1;
}