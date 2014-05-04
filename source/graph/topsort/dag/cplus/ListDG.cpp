/**
 * C++: 无回路有向图(Directed Acyclic Graph)的拓扑排序
 *      该DAG图是通过邻接表实现的。  
 *
 * @author skywang
 * @date 2014/04/22
 */

#include <iomanip>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define MAX 100
// 邻接表
class ListDG
{
    private: // 内部类
        // 邻接表中表对应的链表的顶点
        class ENode
        {
            int ivex;           // 该边所指向的顶点的位置
            ENode *nextEdge;    // 指向下一条弧的指针
            friend class ListDG;
        };

        // 邻接表中表的顶点
        class VNode
        {
            char data;          // 顶点信息
            ENode *firstEdge;   // 指向第一条依附该顶点的弧
            friend class ListDG;
        };

	private: // 私有成员
        int mVexNum;             // 图的顶点的数目
        int mEdgNum;             // 图的边的数目
        VNode *mVexs;            // 图的顶点数组

    public:
        // 创建邻接表对应的图(自己输入)
		ListDG();
        // 创建邻接表对应的图(用已提供的数据)
        ListDG(char vexs[], int vlen, char edges[][2], int elen);
		~ListDG();

        // 深度优先搜索遍历图
        void DFS();
        // 广度优先搜索（类似于树的层次遍历）
        void BFS();
        // 打印邻接表图
        void print();
        // 拓扑排序
        int topologicalSort();

	private:
        // 读取一个输入字符
        char readChar();
        // 返回ch的位置
        int getPosition(char ch);
        // 深度优先搜索遍历图的递归实现
        void DFS(int i, int *visited);
        // 将node节点链接到list的最后
        void linkLast(ENode *list, ENode *node);
};

/*
 * 创建邻接表对应的图(自己输入)
 */
ListDG::ListDG()
{
    char c1, c2;
    int v, e;
    int i, p1, p2;
    ENode *node1, *node2;

    // 输入"顶点数"和"边数"
    cout << "input vertex number: ";
    cin >> mVexNum;
    cout << "input edge number: ";
    cin >> mEdgNum;
    if ( mVexNum < 1 || mEdgNum < 1 || (mEdgNum > (mVexNum * (mVexNum-1))))
    {
        cout << "input error: invalid parameters!" << endl;
        return ;
    }
 
    // 初始化"邻接表"的顶点
    mVexs = new VNode[mVexNum];
    for(i=0; i<mVexNum; i++)
    {
        cout << "vertex(" << i << "): ";
        mVexs[i].data = readChar();
        mVexs[i].firstEdge = NULL;
    }

    // 初始化"邻接表"的边
    for(i=0; i<mEdgNum; i++)
    {
        // 读取边的起始顶点和结束顶点
        cout << "edge(" << i << "): ";
        c1 = readChar();
        c2 = readChar();

        p1 = getPosition(c1);
        p2 = getPosition(c2);
        // 初始化node1
        node1 = new ENode();
        node1->ivex = p2;
        // 将node1链接到"p1所在链表的末尾"
        if(mVexs[p1].firstEdge == NULL)
          mVexs[p1].firstEdge = node1;
        else
            linkLast(mVexs[p1].firstEdge, node1);
    }
}

/*
 * 创建邻接表对应的图(用已提供的数据)
 */
ListDG::ListDG(char vexs[], int vlen, char edges[][2], int elen)
{
    char c1, c2;
    int i, p1, p2;
    ENode *node1, *node2;

    // 初始化"顶点数"和"边数"
    mVexNum = vlen;
    mEdgNum = elen;
    // 初始化"邻接表"的顶点
    mVexs = new VNode[mVexNum];
    for(i=0; i<mVexNum; i++)
    {
        mVexs[i].data = vexs[i];
        mVexs[i].firstEdge = NULL;
    }

    // 初始化"邻接表"的边
    for(i=0; i<mEdgNum; i++)
    {
        // 读取边的起始顶点和结束顶点
        c1 = edges[i][0];
        c2 = edges[i][1];

        p1 = getPosition(c1);
        p2 = getPosition(c2);
        // 初始化node1
        node1 = new ENode();
        node1->ivex = p2;
        // 将node1链接到"p1所在链表的末尾"
        if(mVexs[p1].firstEdge == NULL)
          mVexs[p1].firstEdge = node1;
        else
            linkLast(mVexs[p1].firstEdge, node1);
    }
}

/* 
 * 析构函数
 */
ListDG::~ListDG() 
{
    ENode *node;

    for(int i=0; i<mEdgNum; i++)
    {
        node = mVexs[i].firstEdge;
        while (node != NULL)
        {
            delete node;
            node = node->nextEdge;
        }
    }

    delete[] mVexs;
}

/*
 * 将node节点链接到list的最后
 */
void ListDG::linkLast(ENode *list, ENode *node)
{
    ENode *p = list;

    while(p->nextEdge)
        p = p->nextEdge;
    p->nextEdge = node;
}


/*
 * 返回ch的位置
 */
int ListDG::getPosition(char ch)
{
    int i;
    for(i=0; i<mVexNum; i++)
        if(mVexs[i].data==ch)
            return i;
    return -1;
}

/*
 * 读取一个输入字符
 */
char ListDG::readChar()
{
    char ch;

    do {
        cin >> ch;
    } while(!((ch>='a'&&ch<='z') || (ch>='A'&&ch<='Z')));

    return ch;
}


/*
 * 深度优先搜索遍历图的递归实现
 */
void ListDG::DFS(int i, int *visited)
{
    ENode *node;

    visited[i] = 1;
    cout << mVexs[i].data << " ";
    node = mVexs[i].firstEdge;
    while (node != NULL)
    {
        if (!visited[node->ivex])
            DFS(node->ivex, visited);
        node = node->nextEdge;
    }
}

/*
 * 深度优先搜索遍历图
 */
void ListDG::DFS()
{
    int i;
    int *visited;       // 顶点访问标记

    visited = new int[mVexNum];
    // 初始化所有顶点都没有被访问
    for (i = 0; i < mVexNum; i++)
        visited[i] = 0;

    cout << "== DFS: ";
    for (i = 0; i < mVexNum; i++)
    {
        if (!visited[i])
            DFS(i, visited);
    }
    cout << endl;

    delete[] visited;
}

/*
 * 广度优先搜索（类似于树的层次遍历）
 */
void ListDG::BFS()
{
    int head = 0;
    int rear = 0;
    int *queue;     // 辅组队列
    int *visited;   // 顶点访问标记
    int i, j, k;
    ENode *node;

    queue = new int[mVexNum];
    visited = new int[mVexNum];
    for (i = 0; i < mVexNum; i++)
        visited[i] = 0;

    cout << "== BFS: ";
    for (i = 0; i < mVexNum; i++)
    {
        if (!visited[i])
        {
            visited[i] = 1;
            cout << mVexs[i].data << " ";
            queue[rear++] = i;  // 入队列
        }
        while (head != rear) 
        {
            j = queue[head++];  // 出队列
            node = mVexs[j].firstEdge;
            while (node != NULL)
            {
                k = node->ivex;
                if (!visited[k])
                {
                    visited[k] = 1;
                    cout << mVexs[k].data << " ";
                    queue[rear++] = k;
                }
                node = node->nextEdge;
            }
        }
    }
    cout << endl;

    delete[] visited;
    delete[] queue;
}

/*
 * 打印邻接表图
 */
void ListDG::print()
{
    int i,j;
    ENode *node;

    cout << "== List Graph:" << endl;
    for (i = 0; i < mVexNum; i++)
    {
        cout << i << "(" << mVexs[i].data << "): ";
        node = mVexs[i].firstEdge;
        while (node != NULL)
        {
            cout << node->ivex << "(" << mVexs[node->ivex].data << ") ";
            node = node->nextEdge;
        }
        cout << endl;
    }
}

/*
 * 拓扑排序
 *
 * 返回值：
 *     -1 -- 失败(由于内存不足等原因导致)
 *      0 -- 成功排序，并输入结果
 *      1 -- 失败(该有向图是有环的)
 */
int ListDG::topologicalSort()
{
    int i,j;
    int index = 0;
    int head = 0;           // 辅助队列的头
    int rear = 0;           // 辅助队列的尾
    int *queue;             // 辅组队列
    int *ins;               // 入度数组
    char *tops;             // 拓扑排序结果数组，记录每个节点的排序后的序号。
    ENode *node;

    ins   = new int[mVexNum];
    queue = new int[mVexNum];
    tops  = new char[mVexNum];
    memset(ins, 0, mVexNum*sizeof(int));
    memset(queue, 0, mVexNum*sizeof(int));
    memset(tops, 0, mVexNum*sizeof(char));

    // 统计每个顶点的入度数
    for(i = 0; i < mVexNum; i++)
    {
        node = mVexs[i].firstEdge;
        while (node != NULL)
        {
            ins[node->ivex]++;
            node = node->nextEdge;
        }
    }

    // 将所有入度为0的顶点入队列
    for(i = 0; i < mVexNum; i ++)
        if(ins[i] == 0)
            queue[rear++] = i;          // 入队列

    while (head != rear)                // 队列非空
    {
        j = queue[head++];              // 出队列。j是顶点的序号
        tops[index++] = mVexs[j].data;  // 将该顶点添加到tops中，tops是排序结果
        node = mVexs[j].firstEdge;      // 获取以该顶点为起点的出边队列

        // 将与"node"关联的节点的入度减1；
        // 若减1之后，该节点的入度为0；则将该节点添加到队列中。
        while(node != NULL)
        {
            // 将节点(序号为node->ivex)的入度减1。
            ins[node->ivex]--;
            // 若节点的入度为0，则将其"入队列"
            if( ins[node->ivex] == 0)
                queue[rear++] = node->ivex;  // 入队列

            node = node->nextEdge;
        }
    }

    if(index != mVexNum)
    {
        cout << "Graph has a cycle" << endl;
        delete queue;
        delete ins;
        delete tops;
        return 1;
    }

    // 打印拓扑排序结果
    cout << "== TopSort: ";
    for(i = 0; i < mVexNum; i ++)
        cout << tops[i] << " ";
    cout << endl;

    delete queue;
    delete ins;
    delete tops;

    return 0;
}

int main()
{
    char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    char edges[][2] = {
        {'A', 'G'}, 
        {'B', 'A'}, 
        {'B', 'D'}, 
        {'C', 'F'}, 
        {'C', 'G'}, 
        {'D', 'E'}, 
        {'D', 'F'}}; 
    int vlen = sizeof(vexs)/sizeof(vexs[0]);
    int elen = sizeof(edges)/sizeof(edges[0]);
    ListDG* pG;

    // 自定义"图"(输入矩阵队列)
    //pG = new ListDG();
    // 采用已有的"图"
    pG = new ListDG(vexs, vlen, edges, elen);

    pG->print();   // 打印图
    //pG->DFS();     // 深度优先遍历
    //pG->BFS();     // 广度优先遍历
    pG->topologicalSort();     // 拓扑排序

    return 0;
}
