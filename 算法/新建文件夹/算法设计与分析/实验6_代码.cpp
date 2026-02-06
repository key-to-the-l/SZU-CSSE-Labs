//为什么最大流能解决该问题？
//我的话是从程序的角度出发
//注意那个CurrentTeam_max_wins，它是该队伍获胜的最大场数
//这就意味着那些赢不了的队伍，他的汇节点到某些队伍的容量可能小于零
//这意味着比赛根本不可能比完，意思就是说想要该队伍赢除非比赛比不完
//但很显然这是不可能的，所以说该队伍一定不能赢

//我个人觉得要深究最大流为什么能解决该问题不能从过程入手
//因为最大流算法的运行过程是没有什么实际意义的，不能跟比赛的过程相等
//比如我们的算法进行了四个区域的划分
//即初始还没比完赛的状态（源节点），比赛节点，队伍节点，比完赛的状态（汇节点）
//对于比赛过程，就是比赛一局有胜有负，所以一个比赛节点的结果会传到两个队伍中去
//如果按照程序来讲就是会在比赛到队伍那里有分支
//但问题是FF的"寻找增广路径",这一步是不可能有分支的，并且不是说只看一把比赛的
//所以我我认为看FF的过程是没有意义的，只能从别的地方下手
#include <stack>
#include <iostream>
#include <string>
#include <queue>
using namespace std;

#define MAX_TEAMS 4         // 球队数量
#define MAX_GAMES 6         // 最大比赛数量
#define SIZE (2 + MAX_TEAMS + MAX_GAMES) // 节点总数: 源节点、汇节点、球队节点和比赛节点

int capacity[SIZE][SIZE];     // 容量矩阵
int residualCapacity[SIZE][SIZE];  // 残余容量矩阵,是FF方法的重点
int map_by_level[SIZE];    //在Dinic算法中要用到的数据结构

//FF方法的一种具体实现，利用的DFS寻找增广路径
bool FF_dfs(int source, int target, int map_by_parent[]) {
    bool visited[SIZE];
    memset(visited, 0, sizeof(visited));

    stack<int> intstack;
    intstack.push(source);
    visited[source] = true;
    map_by_parent[source] = -1;

    //DFS
    while (!intstack.empty()) {
        int u = intstack.top(); intstack.pop();
        for (int v = 0; v < SIZE; v++) {
            if (!visited[v] && residualCapacity[u][v] > 0) {
                intstack.push(v);
                map_by_parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return visited[target];
}
int FordFulkerson(int source, int target) {
    int u, v, max_flow = 0;
    int map_by_parent[SIZE];

    // 初始化残余容量矩阵
    for (u = 0; u < SIZE; u++) {
        for (v = 0; v < SIZE; v++) {
            residualCapacity[u][v] = capacity[u][v];
        }
    }

    // 增广路径寻找
    while (FF_dfs(source, target, map_by_parent)) {
        int path_flow = INT_MAX;

        // 找到最小的残余容量作为增广路径上的流量
        for (v = target; v != source; v = map_by_parent[v]) {
            u = map_by_parent[v];
            path_flow = (path_flow < residualCapacity[u][v]) ? path_flow : residualCapacity[u][v];
        }

        // 更新残余网络
        for (v = target; v != source; v = map_by_parent[v]) {
            u = map_by_parent[v];
            residualCapacity[u][v] -= path_flow;
            residualCapacity[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

//EK算法，本质上就是用BFS寻找增广路径，其他地方是一样的
bool EK_bfs(int source, int target, int map_by_parent[]) {
    bool visited[SIZE];
    memset(visited, 0, sizeof(visited));

    queue<int> q;
    q.push(source);
    visited[source] = true;
    map_by_parent[source] = -1;

    // BFS
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v = 0; v < SIZE; v++) {
            if (!visited[v] && residualCapacity[u][v] > 0) {
                q.push(v);
                map_by_parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return visited[target];
}
int EdmondsKarp(int source, int target) {
    int u, v, max_flow = 0;
    int map_by_parent[SIZE];

    // 初始化残余容量矩阵
    for (u = 0; u < SIZE; u++) {
        for (v = 0; v < SIZE; v++) {
            residualCapacity[u][v] = capacity[u][v];
        }
    }

    // 增广路径寻找
    while (EK_bfs(source, target, map_by_parent)) {
        int path_flow = INT_MAX;

        // 找到最小的残余容量作为增广路径上的流量
        for (v = target; v != source; v = map_by_parent[v]) {
            u = map_by_parent[v];
            if (residualCapacity[u][v] < path_flow) {
                path_flow = residualCapacity[u][v];
            }
        }

        // 更新残余网络
        for (v = target; v != source; v = map_by_parent[v]) {
            u = map_by_parent[v];
            residualCapacity[u][v] -= path_flow;
            residualCapacity[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

//Dinic算法，先使用BFS构建分层网络，然后再使用DFS在分层网络中寻找增广路径
bool Dinic_bfs(int s, int t) {
    memset(map_by_level, -1, sizeof(map_by_level));
    queue<int> q;
    q.push(s);
    map_by_level[s] = 0;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v = 0; v < SIZE; v++) {
            if (map_by_level[v] < 0 && residualCapacity[u][v] > 0) {
                map_by_level[v] = map_by_level[u] + 1;
                q.push(v);
            }
        }
    }
    return map_by_level[t] >= 0;
}
int Dinic_dfs(int u, int t, int flow) {
    if (u == t) return flow;
    for (int v = 0; v < SIZE; v++) {
        if (map_by_level[v] == map_by_level[u] + 1 && residualCapacity[u][v] > 0) {
            int current_flow = (flow < residualCapacity[u][v]) ? flow : residualCapacity[u][v];
            int temp_flow = Dinic_dfs(v, t, current_flow);

            if (temp_flow > 0) {
                residualCapacity[u][v] -= temp_flow;
                residualCapacity[v][u] += temp_flow;
                return temp_flow;
            }
        }
    }
    return 0;
}
int Dinic(int s, int t) {
    int max_flow = 0;

    while (Dinic_bfs(s, t)) {
        while (true) {
            int flow = Dinic_dfs(s, t, INT_MAX);
            if (flow == 0) break;
            max_flow += flow;
        }
    }
    return max_flow;
}

//判断函数
bool canWin(int teamIndex, int wins[], int to_play[], int against[][MAX_TEAMS], int CurrentTeam_max_wins) {
    // 初始化容量矩阵
    memset(capacity, 0, sizeof(capacity));

    int source = MAX_TEAMS + MAX_GAMES; // 源节点
    int target = source + 1; // 汇节点
    int nodeIndex = MAX_TEAMS; // 比赛节点

    // i和j代表两只不同的队伍
    for (int i = 0; i < MAX_TEAMS; i++) {
        if (i == teamIndex) continue; // 跳过被检查的球队
        //已经假定该队伍全赢了，自然比赛肯定是全打了的，那比赛全比了就没必要在看他了

        //从队伍到汇节点,容量为 CurrentTeam_max_wins - wins[i]
        //注意这里的CurrentTeam_max_wins是讨论的那个队伍的比赛的最大胜场
        capacity[i][target] = CurrentTeam_max_wins - wins[i];

        for (int j = i + 1; j < MAX_TEAMS; j++) {
            if (j == teamIndex) continue; // 跳过被检查的球队

            //从源节点到比赛节点
            //从比赛节点到队伍节点设置为最大值
            //因为对于棒球问题，这个边并不参与限制，所以为了方便设置一个最大值
            if (against[i][j] > 0) {
                capacity[source][nodeIndex] = against[i][j];
                capacity[nodeIndex][i] = INT_MAX;
                capacity[nodeIndex][j] = INT_MAX;
                nodeIndex++;
            }
        }
    }

    // 初始化残余容量矩阵
    for (int u = 0; u < SIZE; u++) {
        for (int v = 0; v < SIZE; v++) {
            residualCapacity[u][v] = capacity[u][v];
        }
    }
    
    //计算最大流
    int max_flow = FordFulkerson(source, target);

    // 计算总的比赛场次
    int total_matches = 0;
    for (int i = 0; i < MAX_TEAMS; i++) {
        for (int j = i + 1; j < MAX_TEAMS; j++) {
            if (i == teamIndex || j == teamIndex) continue; //同样记得跳过讨论的队伍
            total_matches += against[i][j];
        }
    }

    return max_flow == total_matches;
}

int main() {
    // 输入数据
    int wins[] = { 83, 80, 78, 77 };
    int to_play[] = { 8, 3, 6, 3 };
    int against[MAX_TEAMS][MAX_TEAMS] = {
        {-1, 1, 6, 1},
        {1, -1, 0, 2},
        {6, 0, -1, 0},
        {1, 2, 0, -1}
    };

    bool can_team_win[MAX_TEAMS];
    for (int i = 0; i < MAX_TEAMS; i++) {
        int CurrentTeam_maxWins = wins[i] + to_play[i];
        can_team_win[i] = canWin(i, wins, to_play, against, CurrentTeam_maxWins);
    }

    const char* teamNames[] = { "Atlanta", "Philly", "New York", "Montreal" };

    for (int i = 0; i < MAX_TEAMS; i++) {
        if (can_team_win[i]) {
            cout << teamNames[i] << "有机会获胜" << endl;
        } else {
            cout << teamNames[i] << "不可能获胜" << endl;
        }
    }

    return 0;
}