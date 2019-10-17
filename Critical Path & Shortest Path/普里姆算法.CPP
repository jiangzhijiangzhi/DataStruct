#define INFINITY INT_MAX // 表无穷大 
typedef VertexType string;
typedef struct  
{  
    int adj;//顶点关系类型。对无权图，用1(是)或0(否)表示相邻否;对带权图，c则为权值类型  
    InfoType *info;  
}ArcCell,AdjMatrix[MAX_VEX_NUM][MAX_VEX_NUM];  
typedef struct  
{  
    VertexType vexs[MAX_VEX_NUM];  
    AdjMatrix arcs;  
    int vexnum,arcnum;//当前顶点数和弧数  
    GraphKind kind;  
}MGraph; 
struct CloseEdge{
       int    adjvex;
       int    lowcost;
} closedge[MAX_VERTEX_NUM];

int minimum(struct CloseEdge closedge[],int n)
{int i,min,index=0;
 min=INFINITY;
 for(i=0;i<n;i++)
   if(closedge[i].lowcost&&closedge[i].lowcost<min)
     {min=closedge[i].lowcost;
      index=i;
     }
 return index;
}
void MiniSpanTree_PRIM(MGraph G, int u) {  
  int i,j,k;
  k = LocateVex ( G, u );//查找顶点下标 
  for ( j=0; j<G.vexnum; ++j ) {
    if (j!=k) 
     { closedge[j].adjvex=u; 
	   closedge[j].lowcost=G.arcs[k][j].adj; }
     }
  closedge[k].lowcost = 0; 
  for (i=1; i<G.vexnum; ++i) {  
    k = minimum(closedge,G.vexnum); 
    printf(closedge[k].adjvex, G.vexs[k]);   
    closedge[k].lowcost = 0;    
    for (j=0; j<G.vexnum; ++j)
      if (G.arcs[k][j].adj < closedge[j].lowcost) { 
        closedge[j].adjvex=G.vexs[k];
        closedge[j].lowcost=G.arcs[k][j].adj;
      }
  }
} 

