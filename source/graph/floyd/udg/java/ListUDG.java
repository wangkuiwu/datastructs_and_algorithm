/**
 * Java: Dijkstra算法获取最短路径(邻接表)
 *
 * @author skywang
 * @date 2014/04/24
 */

import java.io.IOException;
import java.util.Scanner;

public class ListUDG {
    private static int INF = Integer.MAX_VALUE;

    // 邻接表中表对应的链表的顶点
    private class ENode {
        int ivex;       // 该边所指向的顶点的位置
        int weight;     // 该边的权
        ENode nextEdge; // 指向下一条弧的指针
    }

    // 邻接表中表的顶点
    private class VNode {
        char data;          // 顶点信息
        ENode firstEdge;    // 指向第一条依附该顶点的弧
    };

    private int mEdgNum;    // 边的数量
    private VNode[] mVexs;  // 顶点数组


    /* 
     * 创建图(自己输入数据)
     */
    public ListUDG() {

        // 输入"顶点数"和"边数"
        System.out.printf("input vertex number: ");
        int vlen = readInt();
        System.out.printf("input edge number: ");
        int elen = readInt();
        if ( vlen < 1 || elen < 1 || (elen > (vlen*(vlen - 1)))) {
            System.out.printf("input error: invalid parameters!\n");
            return ;
        }
        
        // 初始化"顶点"
        mVexs = new VNode[vlen];
        for (int i = 0; i < mVexs.length; i++) {
            System.out.printf("vertex(%d): ", i);
            mVexs[i] = new VNode();
            mVexs[i].data = readChar();
            mVexs[i].firstEdge = null;
        }

        // 初始化"边"
        mEdgNum = elen;
        for (int i = 0; i < elen; i++) {
            // 读取边的起始顶点和结束顶点
            System.out.printf("edge(%d):", i);
            char c1 = readChar();
            char c2 = readChar();
            int weight = readInt();

            int p1 = getPosition(c1);
            int p2 = getPosition(c2);
            // 初始化node1
            ENode node1 = new ENode();
            node1.ivex = p2;
            node1.weight = weight;
            // 将node1链接到"p1所在链表的末尾"
            if(mVexs[p1].firstEdge == null)
              mVexs[p1].firstEdge = node1;
            else
                linkLast(mVexs[p1].firstEdge, node1);
            // 初始化node2
            ENode node2 = new ENode();
            node2.ivex = p1;
            node2.weight = weight;
            // 将node2链接到"p2所在链表的末尾"
            if(mVexs[p2].firstEdge == null)
              mVexs[p2].firstEdge = node2;
            else
                linkLast(mVexs[p2].firstEdge, node2);
        }
    }

    /*
     * 创建图(用已提供的矩阵)
     *
     * 参数说明：
     *     vexs  -- 顶点数组
     *     edges -- 边
     */
    public ListUDG(char[] vexs, EData[] edges) {
        
        // 初始化"顶点数"和"边数"
        int vlen = vexs.length;
        int elen = edges.length;

        // 初始化"顶点"
        mVexs = new VNode[vlen];
        for (int i = 0; i < mVexs.length; i++) {
            mVexs[i] = new VNode();
            mVexs[i].data = vexs[i];
            mVexs[i].firstEdge = null;
        }

        // 初始化"边"
        mEdgNum = elen;
        for (int i = 0; i < elen; i++) {
            // 读取边的起始顶点和结束顶点
            char c1 = edges[i].start;
            char c2 = edges[i].end;
            int weight = edges[i].weight;

            // 读取边的起始顶点和结束顶点
            int p1 = getPosition(c1);
            int p2 = getPosition(c2);
            // 初始化node1
            ENode node1 = new ENode();
            node1.ivex = p2;
            node1.weight = weight;
            // 将node1链接到"p1所在链表的末尾"
            if(mVexs[p1].firstEdge == null)
              mVexs[p1].firstEdge = node1;
            else
                linkLast(mVexs[p1].firstEdge, node1);
            // 初始化node2
            ENode node2 = new ENode();
            node2.ivex = p1;
            node2.weight = weight;
            // 将node2链接到"p2所在链表的末尾"
            if(mVexs[p2].firstEdge == null)
              mVexs[p2].firstEdge = node2;
            else
                linkLast(mVexs[p2].firstEdge, node2);
        }
    }

    /*
     * 将node节点链接到list的最后
     */
    private void linkLast(ENode list, ENode node) {
        ENode p = list;

        while(p.nextEdge!=null)
            p = p.nextEdge;
        p.nextEdge = node;
    }

    /*
     * 返回ch位置
     */
    private int getPosition(char ch) {
        for(int i=0; i<mVexs.length; i++)
            if(mVexs[i].data==ch)
                return i;
        return -1;
    }

    /*
     * 读取一个输入字符
     */
    private char readChar() {
        char ch='0';

        do {
            try {
                ch = (char)System.in.read();
            } catch (IOException e) {
                e.printStackTrace();
            }
        } while(!((ch>='a'&&ch<='z') || (ch>='A'&&ch<='Z')));

        return ch;
    }

    /*
     * 读取一个输入字符
     */
    private int readInt() {
        Scanner scanner = new Scanner(System.in);
        return scanner.nextInt();
    }

    /*
     * 深度优先搜索遍历图的递归实现
     */
    private void DFS(int i, boolean[] visited) {
        ENode node;

        visited[i] = true;
        System.out.printf("%c ", mVexs[i].data);
        node = mVexs[i].firstEdge;
        while (node != null) {
            if (!visited[node.ivex])
                DFS(node.ivex, visited);
            node = node.nextEdge;
        }
    }

    /*
     * 深度优先搜索遍历图
     */
    public void DFS() {
        boolean[] visited = new boolean[mVexs.length];       // 顶点访问标记

        // 初始化所有顶点都没有被访问
        for (int i = 0; i < mVexs.length; i++)
            visited[i] = false;

        System.out.printf("DFS: ");
        for (int i = 0; i < mVexs.length; i++) {
            if (!visited[i])
                DFS(i, visited);
        }
        System.out.printf("\n");
    }

    /*
     * 广度优先搜索（类似于树的层次遍历）
     */
    public void BFS() {
        int head = 0;
        int rear = 0;
        int[] queue = new int[mVexs.length];            // 辅组队列
        boolean[] visited = new boolean[mVexs.length];  // 顶点访问标记

        for (int i = 0; i < mVexs.length; i++)
            visited[i] = false;

        System.out.printf("BFS: ");
        for (int i = 0; i < mVexs.length; i++) {
            if (!visited[i]) {
                visited[i] = true;
                System.out.printf("%c ", mVexs[i].data);
                queue[rear++] = i;  // 入队列
            }

            while (head != rear) {
                int j = queue[head++];  // 出队列
                ENode node = mVexs[j].firstEdge;
                while (node != null) {
                    int k = node.ivex;
                    if (!visited[k])
                    {
                        visited[k] = true;
                        System.out.printf("%c ", mVexs[k].data);
                        queue[rear++] = k;
                    }
                    node = node.nextEdge;
                }
            }
        }
        System.out.printf("\n");
    }

    /*
     * 打印矩阵队列图
     */
    public void print() {
        System.out.printf("List Graph:\n");
        for (int i = 0; i < mVexs.length; i++) {
            System.out.printf("%d(%c): ", i, mVexs[i].data);
            ENode node = mVexs[i].firstEdge;
            while (node != null) {
                System.out.printf("%d(%c) ", node.ivex, mVexs[node.ivex].data);
                node = node.nextEdge;
            }
            System.out.printf("\n");
        }
    }

    /*
     * 获取边<start, end>的权值；若start和end不是连通的，则返回无穷大。
     */
    private int getWeight(int start, int end) {

        if (start==end)
            return 0;

        ENode node = mVexs[start].firstEdge;
        while (node!=null) {
            if (end==node.ivex)
                return node.weight;
            node = node.nextEdge;
        }

        return INF;
    }

    /*
     * prim最小生成树
     *
     * 参数说明：
     *   start -- 从图中的第start个元素开始，生成最小树
     */
    public void prim(int start) {
        int min,i,j,k,m,n,tmp,sum;
        int num = mVexs.length;
        int index=0;                   // prim最小树的索引，即prims数组的索引
        char[] prims = new char[num];  // prim最小树的结果数组
        int[] weights = new int[num];  // 顶点间边的权值

        // prim最小生成树中第一个数是"图中第start个顶点"，因为是从start开始的。
        prims[index++] = mVexs[start].data;

        // 初始化"顶点的权值数组"，
        // 将每个顶点的权值初始化为"第start个顶点"到"该顶点"的权值。
        for (i = 0; i < num; i++ )
            weights[i] = getWeight(start, i);

        for (i = 0; i < num; i++) {
            // 由于从start开始的，因此不需要再对第start个顶点进行处理。
            if(start == i)
                continue;

            j = 0;
            k = 0;
            min = INF;
            // 在未被加入到最小生成树的顶点中，找出权值最小的顶点。
            while (j < num) {
                // 若weights[j]=0，意味着"第j个节点已经被排序过"(或者说已经加入了最小生成树中)。
                if (weights[j] != 0 && weights[j] < min) {
                    min = weights[j];
                    k = j;
                }
                j++;
            }

            // 经过上面的处理后，在未被加入到最小生成树的顶点中，权值最小的顶点是第k个顶点。
            // 将第k个顶点加入到最小生成树的结果数组中
            prims[index++] = mVexs[k].data;
            // 将"第k个顶点的权值"标记为0，意味着第k个顶点已经排序过了(或者说已经加入了最小树结果中)。
            weights[k] = 0;
            // 当第k个顶点被加入到最小生成树的结果数组中之后，更新其它顶点的权值。
            for (j = 0 ; j < num; j++) {
                // 获取第k个顶点到第j个顶点的权值
                tmp = getWeight(k, j);
                // 当第j个节点没有被处理，并且需要更新时才被更新。
                if (weights[j] != 0 && tmp < weights[j])
                    weights[j] = tmp;
            }
        }

        // 计算最小生成树的权值
        sum = 0;
        for (i = 1; i < index; i++) {
            min = INF;
            // 获取prims[i]在矩阵表中的位置
            n = getPosition(prims[i]);
            // 在vexs[0...i]中，找出到j的权值最小的顶点。
            for (j = 0; j < i; j++) {
                m = getPosition(prims[j]);
                tmp = getWeight(m, n);
                if (tmp < min)
                    min = tmp;
            }
            sum += min;
        }
        // 打印最小生成树
        System.out.printf("PRIM(%c)=%d: ", mVexs[start].data, sum);
        for (i = 0; i < index; i++)
            System.out.printf("%c ", prims[i]);
        System.out.printf("\n");
    }

    /*
     * 克鲁斯卡尔（Kruskal)最小生成树
     */
    public void kruskal() {
        int index = 0;                      // rets数组的索引
        int[] vends = new int[mEdgNum];     // 用于保存"已有最小生成树"中每个顶点在该最小树中的终点。
        EData[] rets = new EData[mEdgNum];  // 结果数组，保存kruskal最小生成树的边
        EData[] edges;                      // 图对应的所有边

        // 获取"图中所有的边"
        edges = getEdges();
        // 将边按照"权"的大小进行排序(从小到大)
        sortEdges(edges, mEdgNum);

        for (int i=0; i<mEdgNum; i++) {
            int p1 = getPosition(edges[i].start);      // 获取第i条边的"起点"的序号
            int p2 = getPosition(edges[i].end);        // 获取第i条边的"终点"的序号

            int m = getEnd(vends, p1);                 // 获取p1在"已有的最小生成树"中的终点
            int n = getEnd(vends, p2);                 // 获取p2在"已有的最小生成树"中的终点
            // 如果m!=n，意味着"边i"与"已经添加到最小生成树中的顶点"没有形成环路
            if (m != n) {
                vends[m] = n;                       // 设置m在"已有的最小生成树"中的终点为n
                rets[index++] = edges[i];           // 保存结果
            }
        }

        // 统计并打印"kruskal最小生成树"的信息
        int length = 0;
        for (int i = 0; i < index; i++)
            length += rets[i].weight;
        System.out.printf("Kruskal=%d: ", length);
        for (int i = 0; i < index; i++)
            System.out.printf("(%c,%c) ", rets[i].start, rets[i].end);
        System.out.printf("\n");
    }

    /* 
     * 获取图中的边
     */
    private EData[] getEdges() {
        int index=0;
        EData[] edges;

        edges = new EData[mEdgNum];
        for (int i=0; i < mVexs.length; i++) {

            ENode node = mVexs[i].firstEdge;
            while (node != null) {
                if (node.ivex > i) {
                    edges[index++] = new EData(mVexs[i].data, mVexs[node.ivex].data, node.weight);
                }
                node = node.nextEdge;
            }
        }

        return edges;
    }

    /* 
     * 对边按照权值大小进行排序(由小到大)
     */
    private void sortEdges(EData[] edges, int elen) {

        for (int i=0; i<elen; i++) {
            for (int j=i+1; j<elen; j++) {

                if (edges[i].weight > edges[j].weight) {
                    // 交换"边i"和"边j"
                    EData tmp = edges[i];
                    edges[i] = edges[j];
                    edges[j] = tmp;
                }
            }
        }
    }

    /*
     * 获取i的终点
     */
    private int getEnd(int[] vends, int i) {
        while (vends[i] != 0)
            i = vends[i];
        return i;
    }

    /*
     * Dijkstra最短路径。
     * 即，统计图中"顶点vs"到其它各个顶点的最短路径。
     *
     * 参数说明：
     *       vs -- 起始顶点(start vertex)。即计算"顶点vs"到其它顶点的最短路径。
     *     prev -- 前驱顶点数组。即，prev[i]的值是"顶点vs"到"顶点i"的最短路径所经历的全部顶点中，位于"顶点i"之前的那个顶点。
     *     dist -- 长度数组。即，dist[i]是"顶点vs"到"顶点i"的最短路径的长度。
     */
    public void dijkstra(int vs, int[] prev, int[] dist) {
        // flag[i]=true表示"顶点vs"到"顶点i"的最短路径已成功获取。
        boolean[] flag = new boolean[mVexs.length];
        
        // 初始化
        for (int i = 0; i < mVexs.length; i++) {
            flag[i] = false;            // 顶点i的最短路径还没获取到。
            prev[i] = 0;                // 顶点i的前驱顶点为0。
            dist[i] = getWeight(vs, i); // 顶点i的最短路径为"顶点vs"到"顶点i"的权。
        }

        // 对"顶点vs"自身进行初始化
        flag[vs] = true;
        dist[vs] = 0;

        // 遍历mVexs.length-1次；每次找出一个顶点的最短路径。
        int k = 0;
        for (int i = 1; i < mVexs.length; i++) {
            // 寻找当前最小的路径；
            // 即，在未获取最短路径的顶点中，找到离vs最近的顶点(k)。
            int min = INF;
            for (int j = 0; j < mVexs.length; j++) {
                if (flag[j]==false && dist[j]<min) {
                    min = dist[j];
                    k = j;
                }
            }
            // 标记"顶点k"为已经获取到最短路径
            flag[k] = true;

            // 修正当前最短路径和前驱顶点
            // 即，当已经"顶点k的最短路径"之后，更新"未获取最短路径的顶点的最短路径和前驱顶点"。
            for (int j = 0; j < mVexs.length; j++) {
                int tmp = getWeight(k, j);
                tmp = (tmp==INF ? INF : (min + tmp)); // 防止溢出
                if (flag[j]==false && (tmp<dist[j]) )
                {
                    dist[j] = tmp;
                    prev[j] = k;
                }
            }
        }

        // 打印dijkstra最短路径的结果
        System.out.printf("dijkstra(%c): \n", mVexs[vs].data);
        for (int i = 0; i < mVexs.length; i++)
            System.out.printf("  shortest(%c, %c)=%d\n", mVexs[vs].data, mVexs[i].data, dist[i]);
    }

    /*
     * floyd最短路径。
     * 即，统计图中各个顶点间的最短路径。
     *
     * 参数说明：
     *     path -- 路径。path[i][j]=k表示，"顶点i"到"顶点j"的最短路径会经过顶点k。
     *     dist -- 长度数组。即，dist[i][j]=sum表示，"顶点i"到"顶点j"的最短路径的长度是sum。
     */
    public void floyd(int[][] path, int[][] dist) {

        // 初始化
        for (int i = 0; i < mVexs.length; i++) {
            for (int j = 0; j < mVexs.length; j++) {
                dist[i][j] = getWeight(i, j);  // "顶点i"到"顶点j"的路径长度为"i到j的权值"。 
                path[i][j] = j;                // "顶点i"到"顶点j"的最短路径是经过顶点j。
            }
        }

        // 计算最短路径
        for (int k = 0; k < mVexs.length; k++) {
            for (int i = 0; i < mVexs.length; i++) {
                for (int j = 0; j < mVexs.length; j++) {

                    // 如果经过下标为k顶点路径比原两点间路径更短，则更新dist[i][j]和path[i][j]
                    int tmp = (dist[i][k]==INF || dist[k][j]==INF) ? INF : (dist[i][k] + dist[k][j]);
                    if (dist[i][j] > tmp) {
                        // "i到j最短路径"对应的值设，为更小的一个(即经过k)
                        dist[i][j] = tmp;
                        // "i到j最短路径"对应的路径，经过k
                        path[i][j] = path[i][k];
                    }
                }
            }
        }

        // 打印floyd最短路径的结果
        System.out.printf("floyd: \n");
        for (int i = 0; i < mVexs.length; i++) {
            for (int j = 0; j < mVexs.length; j++)
                System.out.printf("%2d  ", dist[i][j]);
            System.out.printf("\n");
        }
    }

    // 边的结构体
    private static class EData {
        char start; // 边的起点
        char end;   // 边的终点
        int weight; // 边的权重

        public EData(char start, char end, int weight) {
            this.start = start;
            this.end = end;
            this.weight = weight;
        }
    };

    public static void main(String[] args) {
        char[] vexs = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
        EData[] edges = {
                   // 起点 终点 权
            new EData('A', 'B', 12), 
            new EData('A', 'F', 16), 
            new EData('A', 'G', 14), 
            new EData('B', 'C', 10), 
            new EData('B', 'F',  7), 
            new EData('C', 'D',  3), 
            new EData('C', 'E',  5), 
            new EData('C', 'F',  6), 
            new EData('D', 'E',  4), 
            new EData('E', 'F',  2), 
            new EData('E', 'G',  8), 
            new EData('F', 'G',  9), 
        };
        ListUDG pG;

        // 自定义"图"(输入矩阵队列)
        //pG = new ListUDG();
        // 采用已有的"图"
        pG = new ListUDG(vexs, edges);

        //pG.print();   // 打印图
        //pG.DFS();     // 深度优先遍历
        //pG.BFS();     // 广度优先遍历
        //pG.prim(0);   // prim算法生成最小生成树
        //pG.kruskal(); // Kruskal算法生成最小生成树

        int[] prev = new int[pG.mVexs.length];
        int[] dist = new int[pG.mVexs.length];
        // dijkstra算法获取"第4个顶点"到其它各个顶点的最短距离
        //pG.dijkstra(3, prev, dist);

        int[][] path = new int[pG.mVexs.length][pG.mVexs.length];
        int[][] floy = new int[pG.mVexs.length][pG.mVexs.length];
        // floyd算法获取各个顶点之间的最短距离
        pG.floyd(path, floy);
    }
}
