/**
 * C: 无回路有向图(Directed Acyclic Graph)的拓扑排序
 *    该DAG图是通过邻接表实现的。  
 *
 * @author skywang
 * @date 2014/04/22
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

#define isLetter(a)     ((((a)>='a')&&((a)<='z')) || (((a)>='A')&&((a)<='Z')))
#define LENGTH(a)       (sizeof(a)/sizeof(a[0]))

// 邻接表中表对应的链表的顶点
typedef struct _ENode
{
    int ivex;                   // 该边所指向的顶点的位置
    struct _ENode *next_edge;   // 指向下一条弧的指针
}ENode, *PENode;

// 邻接表中表的顶点
typedef struct _VNode
{
    char data;              // 顶点数据
    ENode *first_edge;      // 指向第一条依附该顶点的弧
}VNode;

// 邻接表
typedef struct _LGraph
{
    int vexnum;             // 图的顶点的数目
    int edgnum;             // 图的边的数目
    VNode *vexs;            // 图的顶点数组
}LGraph;

/*
 * 返回ch在matrix矩阵中的位置
 */
static int get_position(LGraph g, char ch)
{
    int i;
    for(i=0; i<g.vexnum; i++)
        if(g.vexs[i].data==ch)
            return i;
    return -1;
}

/*
 * 读取一个输入字符
 */
static char read_char()
{
    char ch;

    do {
        ch = getchar();
    } while(!isLetter(ch));

    return ch;
}

/*
 * 将node链接到list的末尾
 */
static void link_last(ENode *list, ENode *node)
{
    ENode *p = list;

    while(p->next_edge)
        p = p->next_edge;
    p->next_edge = node;
}

/*
 * 创建邻接表对应的图(自己输入)
 */
LGraph* create_lgraph()
{
    char c1, c2;
    int v, e;
    int i, p1, p2;
    ENode *node1, *node2;
    LGraph* pG;

    // 输入"顶点数"和"边数"
    printf("input vertex number: ");
    scanf("%d", &v);
    printf("input edge number: ");
    scanf("%d", &e);
    if ( v < 1 || e < 1 || (e > (v * (v-1))))
    {
        printf("input error: invalid parameters!\n");
        return NULL;
    }
 
    pG = (LGraph*)malloc(sizeof(LGraph));
    assert(pG!=NULL);

    // 初始化"顶点数"和"边数"
    pG->vexnum = v;
    pG->edgnum = e;
    pG->vexs = (VNode *)malloc(pG->vexnum * sizeof(VNode));
    assert(pG->vexs != NULL);
    // 初始化"邻接表"的顶点
    for(i=0; i<pG->vexnum; i++)
    {
        printf("vertex(%d): ", i);
        pG->vexs[i].data = read_char();
        pG->vexs[i].first_edge = NULL;
    }

    // 初始化"邻接表"的边
    for(i=0; i<pG->edgnum; i++)
    {
        // 读取边的起始顶点和结束顶点
        printf("edge(%d): ", i);
        c1 = read_char();
        c2 = read_char();

        p1 = get_position(*pG, c1);
        p2 = get_position(*pG, c2);
        // 初始化node1
        node1 = (ENode*)malloc(sizeof(ENode));
        node1->ivex             = p2;
        // 将node1链接到"p1所在链表的末尾"
        if(pG->vexs[p1].first_edge == NULL)
          pG->vexs[p1].first_edge = node1;
        else
            link_last(pG->vexs[p1].first_edge, node1);
    }

    return pG;
}

/*
 * 创建邻接表对应的图(用已提供的数据)
 */
LGraph* create_example_lgraph()
{
    char c1, c2;
    char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    char edges[][2] = {
        {'A', 'G'}, 
        {'B', 'A'}, 
        {'B', 'D'}, 
        {'C', 'F'}, 
        {'C', 'G'}, 
        {'D', 'E'}, 
        {'D', 'F'}}; 
    int vlen = LENGTH(vexs);
    int elen = LENGTH(edges);
    int i, p1, p2;
    ENode *node1, *node2;
    LGraph* pG;

    if ((pG=(LGraph*)malloc(sizeof(LGraph))) == NULL )
    assert(pG != NULL);
    memset(pG, 0, sizeof(LGraph));

    // 初始化"顶点数"和"边数"
    pG->vexnum = vlen;
    pG->edgnum = elen;
    pG->vexs = (VNode *)malloc(pG->vexnum * sizeof(VNode));
    assert(pG->vexs != NULL);
    // 初始化"邻接表"的顶点
    for(i=0; i<pG->vexnum; i++)
    {
        pG->vexs[i].data = vexs[i];
        pG->vexs[i].first_edge = NULL;
    }

    // 初始化"邻接表"的边
    for(i=0; i<pG->edgnum; i++)
    {
        // 读取边的起始顶点和结束顶点
        c1 = edges[i][0];
        c2 = edges[i][1];

        p1 = get_position(*pG, c1);
        p2 = get_position(*pG, c2);
        // 初始化node1
        node1 = (ENode*)malloc(sizeof(ENode));
        node1->ivex = p2;
        // 将node1链接到"p1所在链表的末尾"
        if(pG->vexs[p1].first_edge == NULL)
          pG->vexs[p1].first_edge = node1;
        else
            link_last(pG->vexs[p1].first_edge, node1);
    }

    return pG;
}

/*
 * 深度优先搜索遍历图的递归实现
 */
static void DFS(LGraph G, int i, int *visited)
{
    int w;
    ENode *node;

    visited[i] = 1;
    printf("%c ", G.vexs[i].data);
    node = G.vexs[i].first_edge;
    while (node != NULL)
    {
        if (!visited[node->ivex])
            DFS(G, node->ivex, visited);
        node = node->next_edge;
    }
}

/*
 * 深度优先搜索遍历图
 */
void DFS_traverse(LGraph G)
{
    int i;
    int *visited;       // 顶点访问标记

    visited = (int *)malloc(G.vexnum * sizeof(int));
    assert(visited != NULL);

    // 初始化所有顶点都没有被访问
    memset(visited, 0, G.vexnum * sizeof(int));

    printf("== DFS: ");
    for (i = 0; i < G.vexnum; i++)
    {
        if (!visited[i])
            DFS(G, i, visited);
    }
    printf("\n");

    free(visited);
}

/*
 * 广度优先搜索（类似于树的层次遍历）
 */
void BFS(LGraph G)
{
    int head = 0;
    int rear = 0;
    int *queue;     // 辅组队列
    int *visited;   // 顶点访问标记
    int i, j, k;
    ENode *node;


    queue   = (int *)malloc(G.vexnum * sizeof(int));
    visited = (int *)malloc(G.vexnum * sizeof(int));
    assert(queue!=NULL && visited!=NULL);

    memset(queue, 0, G.vexnum * sizeof(int));
    memset(visited, 0, G.vexnum * sizeof(int));

    printf("== BFS: ");
    for (i = 0; i < G.vexnum; i++)
    {
        if (!visited[i])
        {
            visited[i] = 1;
            printf("%c ", G.vexs[i].data);
            queue[rear++] = i;  // 入队列
        }
        while (head != rear) 
        {
            j = queue[head++];  // 出队列
            node = G.vexs[j].first_edge;
            while (node != NULL)
            {
                k = node->ivex;
                if (!visited[k])
                {
                    visited[k] = 1;
                    printf("%c ", G.vexs[k].data);
                    queue[rear++] = k;
                }
                node = node->next_edge;
            }
        }
    }
    printf("\n");

    free(visited);
    free(queue);
}

/*
 * 拓扑排序
 *
 * 参数说明：
 *     G -- 邻接表表示的有向图
 * 返回值：
 *     -1 -- 失败(由于内存不足等原因导致)
 *      0 -- 成功排序，并输入结果
 *      1 -- 失败(该有向图是有环的)
 */
int topological_sort(LGraph G)
{
    int i,j;
    int index = 0;
    int head = 0;           // 辅助队列的头
    int rear = 0;           // 辅助队列的尾
    int *queue;             // 辅组队列
    int *ins;               // 入度数组
    char *tops;             // 拓扑排序结果数组，记录每个节点的排序后的序号。
    int num = G.vexnum;
    ENode *node;

    ins  = (int *)malloc(num*sizeof(int));  // 入度数组
    tops = (char *)malloc(num*sizeof(char));// 拓扑排序结果数组
    queue = (int *)malloc(num*sizeof(int)); // 辅助队列
    assert(ins!=NULL && tops!=NULL && queue!=NULL);
    memset(ins, 0, num*sizeof(int));
    memset(tops, 0, num*sizeof(char));
    memset(queue, 0, num*sizeof(int));

    // 统计每个顶点的入度数
    for(i = 0; i < num; i++)
    {
        node = G.vexs[i].first_edge;
        while (node != NULL)
        {
            ins[node->ivex]++;
            node = node->next_edge;
        }
    }

    // 将所有入度为0的顶点入队列
    for(i = 0; i < num; i ++)
        if(ins[i] == 0)
            queue[rear++] = i;          // 入队列

    while (head != rear)                // 队列非空
    {
        j = queue[head++];              // 出队列。j是顶点的序号
        tops[index++] = G.vexs[j].data; // 将该顶点添加到tops中，tops是排序结果
        node = G.vexs[j].first_edge;    // 获取以该顶点为起点的出边队列

        // 将与"node"关联的节点的入度减1；
        // 若减1之后，该节点的入度为0；则将该节点添加到队列中。
        while(node != NULL)
        {
            // 将节点(序号为node->ivex)的入度减1。
            ins[node->ivex]--;
            // 若节点的入度为0，则将其"入队列"
            if( ins[node->ivex] == 0)
                queue[rear++] = node->ivex;  // 入队列

            node = node->next_edge;
        }
    }

    if(index != G.vexnum)
    {
        printf("Graph has a cycle\n");
        free(queue);
        free(ins);
        free(tops);
        return 1;
    }

    // 打印拓扑排序结果
    printf("== TopSort: ");
    for(i = 0; i < num; i ++)
        printf("%c ", tops[i]);
    printf("\n");

    free(queue);
    free(ins);
    free(tops);
    return 0;
}

/*
 * 打印邻接表图
 */
void print_lgraph(LGraph G)
{
    int i;
    ENode *node;

    printf("== List Graph:\n");
    for (i = 0; i < G.vexnum; i++)
    {
        printf("%d(%c): ", i, G.vexs[i].data);
        node = G.vexs[i].first_edge;
        while (node != NULL)
        {
            printf("%d(%c) ", node->ivex, G.vexs[node->ivex].data);
            node = node->next_edge;
        }
        printf("\n");
    }
}

void main()
{
    LGraph* pG;

    // 自定义"图"(自己输入数据)
    //pG = create_lgraph();
    // 采用已有的"图"
    pG = create_example_lgraph();

    // 打印图
    print_lgraph(*pG);      // 打印图
    //DFS_traverse(*pG);    // 深度优先搜索
    //BFS(*pG);             // 广度优先搜索
    topological_sort(*pG);  // 拓扑排序
}
