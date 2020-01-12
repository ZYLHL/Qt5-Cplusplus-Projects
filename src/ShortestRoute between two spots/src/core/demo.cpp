#include <sstream>
#include <cstdlib>
using namespace std;

stringstream sout;
#define cout sout

#define MAXV 17		//结点数
#define INF 9999  //∞
typedef float InfoType; //权值类型(目前表示距离)

string getName(int p) {
    static string names[MAXV] = {
        "物流集散中心",
        "大学城",
        "机场航站楼",
        "新世界中心",
        "园区路口",
        "新阳大厦",
        "音乐谷广场",
        "中华社区",
        "丰源路口",
        "滨江别墅带",
        "污水处理厂",
        "石化园区",
        "幻想北客站",
        "中华山脚",
        "人民公园",
        "辛德尔路",
        "汽车总站"
    };
    return names[p];
}

typedef struct {
    int nodeid;
    InfoType nodeinfo;
    bool known;
} VertexType;
//邻接矩阵（弗洛伊德算法）
typedef struct {
    float edges[MAXV][MAXV];
    int vn, en;
    VertexType vexs[MAXV];
} MGraph;
//邻接表（迪科斯彻算法）
//边表
typedef struct ANode {//边表定义
    int adjvex;
    struct ANode *nextarc;
    InfoType weight;
} ArcNode;
typedef int Vertex;
//顶点表结构体
typedef struct Vnode {//顶点表结点
    Vertex data;
    ArcNode *firstarc;
} AdjList[MAXV];
//顶点数组结构体
typedef struct {//顶点数组
    AdjList adjlist;
    int vn, en;
} ALGraph;
//Dijkstra算法记录表
typedef struct {
    bool known = false;
    float dist;
    int path;
} DijkstraNodeStatus[MAXV];
//----------------函数声明--------------
void PrintLink(ALGraph *g, ArcNode *next);
ALGraph *CreateAL(ALGraph *g);
void disp(ALGraph *g);
void add_adjedge(ALGraph *g, int start, int end, float len);

void DispMatrix(MGraph g) {
    int i, j;
    for (i = 0; i < g.vn; i++) {
        for (j = 0; j < g.vn; j++) {
            if (g.edges[i][j] == INF) {
                cout << "∞" << "  ";
            } else {
                cout << g.edges[i][j] << "  ";
            }
        }
        cout << endl;
    }
}
//ppath()和DisPath()用于Floyd最短路径的打印
void ppath(int path[][MAXV], int v, int endv) {
    int k;

    k = path[v][endv];
    if (k == -1) {
        return;
    }
    ppath(path, v, k);
    cout << getName(k) << "->";
    ppath(path, k, endv);
}

void DisPath(float A[][MAXV], int path[][MAXV], int n, int v, int endv) {
    cout << "FROM " << getName(v) << " TO " << getName(endv) << "'s route is:\n";
    cout << getName(v) << "->";
    ppath(path, v, endv);
    cout << getName(endv);
    cout << endl;
    cout << "ROUTE'S LENGTH IS: " << A[v][endv] << "km" << endl;
}
//创建邻接表
ALGraph *CreateAL(ALGraph *g) {
    g->vn = 17;
    g->en = 40;
    for (int i = 0; i < g->vn; i++) {
        g->adjlist[i].data = i;
        g->adjlist[i].firstarc = NULL;
    }
    add_adjedge(g, 0, 1, 10);
    add_adjedge(g, 1, 2, 7.8f);
    add_adjedge(g, 2, 3, 8);
    add_adjedge(g, 3, 4, 1);
    add_adjedge(g, 4, 5, 2);
    add_adjedge(g, 2, 6, 1);
    add_adjedge(g, 6, 7, 2);
    add_adjedge(g, 7, 8, 3);
    add_adjedge(g, 8, 5, 2);
    add_adjedge(g, 5, 9, 5);
    add_adjedge(g, 9, 10, 4);
    add_adjedge(g, 10, 11, 5);
    add_adjedge(g, 11, 12, 8);
    add_adjedge(g, 12, 13, 8);
    add_adjedge(g, 13, 0, 5);
    add_adjedge(g, 12, 14, 7);
    add_adjedge(g, 14, 15, 10);
    add_adjedge(g, 15, 3, 1.5f);
    add_adjedge(g, 3, 7, 2.6f);
    add_adjedge(g, 7, 16, 6);

    add_adjedge(g, 16, 7, 6);
    add_adjedge(g, 7, 3, 2.6f);
    add_adjedge(g, 3, 15, 1.5f);
    add_adjedge(g, 15, 14, 10);
    add_adjedge(g, 14, 12, 7);
    add_adjedge(g, 0, 13, 5);
    add_adjedge(g, 13, 12, 8);
    add_adjedge(g, 12, 11, 8);
    add_adjedge(g, 11, 10, 5);
    add_adjedge(g, 10, 9, 4);
    add_adjedge(g, 9, 5, 5);
    add_adjedge(g, 5, 8, 2);
    add_adjedge(g, 8, 7, 3);
    add_adjedge(g, 7, 6, 2);
    add_adjedge(g, 6, 2, 1);
    add_adjedge(g, 5, 4, 2);
    add_adjedge(g, 4, 3, 1);
    add_adjedge(g, 3, 2, 8);
    add_adjedge(g, 2, 1, 7.8f);
    add_adjedge(g, 1, 0, 10);

    return g;
}
//邻接表添加结点
void add_adjedge(ALGraph *g, int start, int end, float len) {
    ArcNode *node = (ArcNode *)malloc(sizeof(ArcNode));
    node->adjvex = end;
    node->nextarc = g->adjlist[start].firstarc;
    node->weight = len;
    g->adjlist[start].firstarc = node;
}

//显示邻接表
void disp(ALGraph *g) {
    cout << "邻接表为:" << endl;
    for (int i = 0; i < g->vn; i++) {
        cout << g->adjlist[i].data << " ";
        PrintLink(g, g->adjlist[i].firstarc);
    }
}
//PrintLink()和DijkstraPrintPath()用于显示具体路径结果
void PrintLink(ALGraph *g, ArcNode *next) {
    while (next != NULL) {
        cout << g->adjlist[next->adjvex].data << " (Length:" << next->weight << ") ";
        next = next->nextarc;
    }
    cout << endl;
}

void DijkstraPrintPath(DijkstraNodeStatus STATUS, ALGraph *g, int start, int end) {
    int i = 0, j = STATUS[end].path, path[MAXV] = { -1 };
    path[i++] = end;
    while(j != start) {
        path[i++] = j;
        end = STATUS[end].path;
        j = STATUS[end].path;
    }
    path[i++] = j;
    int k = i - 1;
    cout << getName(path[k--]);
    for ( ; k > -1; k--) {
        cout << " -> " << getName(path[k]);
    }
    cout << endl;

    cout << "Node " << " Known " << " Dist " << " Path " << endl;
    for (int i = 0; i < g->vn; ++i) {
        if (STATUS[i].known) {
            cout << getName(i) << "  " << STATUS[i].known << "  " << STATUS[i].dist << "  " << STATUS[i].path << endl;
        }
    }
}

void Dijkstra(DijkstraNodeStatus STATUS, ALGraph *g, int src) {
    for (int i = 0; i < g->vn; i++) {
        STATUS[i].known = false;
        STATUS[i].dist = INF;
        STATUS[i].path = 0;
    }
    STATUS[src].dist = 0;		//开启算法关键步骤
    for (;;) {
        int v = 0;
        float max = INF;
        //寻找known=false并且dist最小的顶点
        for (int i = 0; i < g->vn; ++i) {
            if (!STATUS[i].known && (max > STATUS[i].dist)) {
                max = STATUS[i].dist;
                v = i;
            }
        }
        if (max == INF) {
            break;
        }
        STATUS[v].known = true;
        ArcNode *next = (ArcNode *)malloc(sizeof(ArcNode));
        next = g->adjlist[v].firstarc;
        while (next != NULL) {
            if (!STATUS[next->adjvex].known) {
                if (STATUS[next->adjvex].dist > (next->weight + STATUS[v].dist)) {
                    STATUS[next->adjvex].dist = next->weight + STATUS[v].dist;
                    STATUS[next->adjvex].path = v;
                }
            }
            next = next->nextarc;
        }
    }
}

void Floyd(MGraph g, int v, int endv) {
    float A[MAXV][MAXV];
    int path[MAXV][MAXV];
    int i, j, k, n = g.vn;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            A[i][j] = g.edges[i][j];
            path[i][j] = -1;
        }
    }
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (A[i][j] > (A[i][k] + A[k][j])) {
                    A[i][j] = A[i][k] + A[k][j];
                    path[i][j] = k;
                }
            }
        }
    }
    DisPath(A, path, n, v, endv);
}

ALGraph *adjg;
MGraph g; //AdjMatrix

void init() {
    static bool first = true;
    if (first) {
        adjg = (ALGraph *)malloc(sizeof(ALGraph)); //AdjList
        //					  0   1   2   3   4   5   6   7   8  9   10   11   12  13 14  15   16
        float A[MAXV][MAXV] = {{INF, 10, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 5, INF, INF, INF}, /*0*/
            {10, INF, 7.8f, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF}, /*1*/
            {INF, 7.8f, INF, 8, INF, INF, 1, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF}, /*2*/
            {INF, INF, 8, INF, 1, INF, INF, 2.6f, INF, INF, INF, INF, INF, INF, INF, 1.5f, INF}, /*3*/
            {INF, INF, INF, 1, INF, 2, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF}, /*4*/
            {INF, INF, INF, INF, 2, INF, INF, INF, 2, 5, INF, INF, INF, INF, INF, INF, INF}, /*5*/
            {INF, INF, 1, INF, INF, INF, INF, 2, INF, INF, INF, INF, INF, INF, INF, INF, INF}, /*6*/
            {INF, INF, INF, 2.6f, INF, INF, 2, INF, 3, INF, INF, INF, INF, INF, INF, INF, 6}, /*7*/
            {INF, INF, INF, INF, INF, 2, INF, 3, INF, INF, INF, INF, INF, INF, INF, INF, INF}, /*8*/
            {INF, INF, INF, INF, INF, 5, INF, INF, INF, INF, 4, INF, INF, INF, INF, INF, INF}, /*9*/
            {INF, INF, INF, INF, INF, INF, INF, INF, INF, 4, INF, 5, INF, INF, INF, INF, INF}, /*10*/
            {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 5, INF, 8, INF, INF, INF, INF}, /*11*/
            {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 8, INF, 8, 7, INF, INF}, /*12*/
            {5, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 8, INF, INF, INF, INF}, /*13*/
            {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 7, INF, INF, 10, INF}, /*14*/
            {INF, INF, INF, 1.5f, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 10, INF, INF}, /*15*/
            {INF, INF, INF, INF, INF, INF, INF, 6, INF, INF, INF, INF, INF, INF, INF, INF, INF}, /*16*/
        };
        g.en = 40;
        g.vn = 17;
        adjg = CreateAL(adjg);

        for (int i = 0; i < g.vn; i++) {
            for (int j = 0; j < g.vn; j++) {
                g.edges[i][j] = A[i][j];
            }
        }
        first = false;
    }
}

std::string floyd(int s, int e) {
    sout.str("");

    init();
    Floyd(g, s, e);

    return sout.str();
}

std::string dij(int s, int e) {
    sout.str("");

    init();
    DijkstraNodeStatus S;
    Dijkstra(S, adjg, s);
    cout << "FROM " << getName(s) << " TO " << getName(e) << "'s route is:";
    DijkstraPrintPath(S, adjg, s, e);

    return sout.str();
}
