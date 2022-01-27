// Graph_Coloring_Problem.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <queue>
#include <algorithm>
#include <fstream>

const int MAXN = 60; //图中点的最大数目
const int DATA_NUM = 2; //数据组数

struct graph { //图结构体
    double e[MAXN][MAXN]; //邻接矩阵
    int id[MAXN]; //图中每个点的id
    int n; //图的顶点数
};

graph g[DATA_NUM]; //从文件中读入的图

int color[MAXN] = {}; //某个点的颜色，起始为-1
long long tr_tot = 0; //搜索树的节点数

void getData(int num); //从文件读入数据，参数为数据组数
bool dfs(graph* a, int num, int now);//回溯算法，返回值为是否能找到着色方案，参数分别为图、颜色数量、当前搜索到的节点
bool Backtracking(graph* a, int num); //回溯算法，返回值为是否能找到着色方案，参数分别为图、颜色数量，在该函数中cout搜索时间
void ColorClear(); //清空全局变量

void getData(int num) {
    std::fstream data;
    for (int k = 0; k < num; ++k) {
        std::string name = "graph";
        char id = '1' + k;
        name = name + id;
        name = name + ".txt";
        data.open(name);
        data >> g[k].n;
        for (int i = 0; i < g[k].n; ++i) {
            data >> g[k].id[i];
            for (int j = 0; j < g[k].n; ++j) {
                data >> g[k].e[i][j];
                if (g[k].e[i][j] == 99999)g[k].e[i][j] = -1;
            }
        }
        data.close();
    }
}
bool dfs(graph* a, int num, int now) {
    ++tr_tot;
    if (now == (*a).n) {
        return 1;
    }
    for (int i = 0; i < num; ++i) {
        color[now] = i;
        bool flag = 0;
        for (int j = 0; j < now; ++j) {
            if ((*a).e[now][j] > 0 && color[now] == color[j]) { flag = 1; break; }
        }if (flag)continue;
        flag = dfs(a, num, now + 1);
        if (flag)return flag;
    }
    return 0;
}
bool Backtracking(graph* a, int num) {
    int start_time = clock();
    bool flag = dfs(a, num, 0);
    std::cout<<"搜索时间为" << clock()-start_time <<"ms," << "搜索树有" << tr_tot << "个节点,";
    return flag;
}

void ColorClear() {
    for (int i = 0; i < MAXN; ++i)color[i] = -1;
    tr_tot = 0;
}

int main()
{
    std::cout << "开始读入数据\n\n";
    getData(DATA_NUM);
    for (int i = 0; i < DATA_NUM; ++i) {
        std::cout << "开始计算第" << i + 1 << "组数据的顶点着色问题\n";
        std::cout << "图中共" << g[i].n << "个点\n";
        int l = 1, r = g[i].n;
        while (l<r) {
            int m = (l + r) / 2;
            ColorClear();
            std::cout << "颜色种类为" << m << "种，";
            if (Backtracking(&g[i], m)) {
                r = m;
                std::cout << m << "种颜色着色可行\n";
            }
            else {
                l = m + 1;
                std::cout << m << "种颜色着色不可行\n";
            }
        }
        std::cout << "为该图染色至少需要" << r << "种颜色\n";
        std::cout << std::endl;
    }
    return 0;
}
