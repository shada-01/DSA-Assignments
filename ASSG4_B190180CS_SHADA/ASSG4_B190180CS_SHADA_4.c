#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct node
{
    int k;
    char col; // b-black g-gray w-white
    struct node *pi;
    int d;
    struct node *nnext;
}*node;


typedef struct List
{
    node head;
}list;
typedef struct graph
{
    list *L;
    int v;
}graph;

typedef struct qnode
 {
   node data;
   struct qnode *next;
 }*qnode;

typedef struct queue
{
 qnode front;
 qnode tail;
}*queue;
int QUEUE_EMPTY(queue Q)
 {
   if(Q->front==NULL)
     return -1;
   else
     return 1;
  }

qnode CREATENODE(node k)
{
 qnode temp;
 temp=(qnode)malloc(sizeof(struct qnode));
 temp->data=k;
 temp->next=NULL;
 return temp;
}

void ENQUEUE(queue Q,node y)
{
 qnode x=CREATENODE(y);
 if(QUEUE_EMPTY(Q)==-1)
  Q->front=x;
 else
    Q->tail->next=x;
  Q->tail=x;
 //return Q;
}

void DEQUEUE(queue Q)
 {
   if(QUEUE_EMPTY(Q)!=-1)
     {
        qnode temp=Q->front;
        if(Q->front==Q->tail)
          Q->tail=NULL;
        Q->front=Q->front->next;
         
     }
//return temp->data;
}

void BFS(graph g,int src)
{
  // printf("COMEON");
   node t,s,temp;
   int *vis;
    vis=(int*)malloc((g.v)*sizeof(int));
    for(int i=0;i<g.v;i++)
     {
      if(i==src)
      vis[i]=1;
      else
      vis[i]=0;
     }
    s=(node)malloc(sizeof(struct node));
    s->k=src;
    s->pi=NULL;
    s->d=0;
    s->col='g';
    s->nnext=NULL;
   queue Q;
   Q=(queue)malloc(sizeof(struct queue));
    Q->front=NULL;
    Q->tail=NULL;
    ENQUEUE(Q,s);
    while(QUEUE_EMPTY(Q)!=-1)
      {
         t=Q->front->data;
          printf("%d ",t->k);
           DEQUEUE(Q);
           temp=g.L[t->k].head;
          while(temp!=NULL)
            {
              if(temp->col=='w' && vis[temp->k]==0)
                {
                  vis[temp->k]=1;
                  temp->col='g';
                  temp->d=t->d+1;
                   temp->pi=t;
                   ENQUEUE(Q,temp);
                }
              else if (temp->col=='w')
                 temp->col='g';
               
             temp=temp->nnext;
            }
            t->col='b';
       }
  }
  

void print_slot(node temp)
{
  node s;
  s=temp;
  while(temp!=NULL) {
    printf("%d->",temp->k);
    temp=temp->nnext; 
   }
}

void PRINT(graph g)
{
    for(int i=0;i<g.v;i++)
    {
        
    printf("%d: ",i);
     print_slot(g.L[i].head);
     
     
      printf("\n");
    }

}

graph change(graph g)
{
  node new;
  for(int i=0;i<g.v;i++)
   {
      new=g.L[i].head;
     while(new!=NULL)
     {
    new->pi=NULL;
    new->d=INT_MAX;
    new->col='w';
    
    new=new->nnext;
    }
  }
 return g;
 }
node INSERT(list l,int key)
{
    node new=(node)malloc(sizeof(struct node));
    new->k=key;
    new->pi=NULL;
    new->d=INT_MAX;
    new->col='w';
    new->nnext=NULL;
    if(l.head==NULL || (l.head)->k >= new->k)
      {
        new->nnext=l.head;
        l.head=new;
      }
    else
       {
         node t=l.head;
         while(t->nnext!=NULL && t->nnext->k < new->k)
            t=t->nnext;
         new->nnext=t->nnext;
         t->nnext=new;
       }
   return l.head;
         
}

node LIST_SEARCH(list L,int x)
 {
 
   node s=L.head;
   while(s!=NULL && s->k!=x)
     s=s->nnext;
   
   return s;
 }

void dfs(graph g,node s,int vis[])
 {
   node t;
    vis[s->k]=1;
    s->col='g';
    printf("%d ",s->k);
    
    t=g.L[s->k].head;
    
    while(t!=NULL)
     {
       if(t->col=='w' && vis[t->k]==0)
         dfs(g,t,vis);
       else if(t->col=='w')
          t->col='g';
        t=t->nnext;
     }
     s->col='b';
 }
           

void DFS(graph g,int src)
{
    node s;
    int vis[g.v];
   // vis=(int*)malloc((g.v)*sizeof(int));
    for(int i=0;i<g.v;i++)
     {
      if(i==src)
      vis[i]=1;
      else
      vis[i]=0;
     }
    s=(node)malloc(sizeof(struct node));
    s->k=src;
    s->pi=NULL;
    s->d=0;
    s->col='g';
    s->nnext=NULL;

    dfs(g,s,vis);
    for(int i=0;i<g.v;i++)
     {
       if(i!=src)
         {
            if(vis[i]==0)
              {
                 s->k=i;
                s->pi=NULL;
                s->d=0;
                 s->col='g';
                  s->nnext=NULL;
                
               dfs(g,s,vis);
               }
         }
     }
}


  

void main()
{
 	 int m,n,i,j,src;
	 scanf("%d",&n);
	 scanf("%d",&m);
    graph g,g_; 
     
    node tmp;
    g.v=n;
    g.L=(list*)malloc(n*sizeof(struct List));
    
  
    for(int p=0;p<n;p++)
    {
      g.L[p].head=NULL;
    }
     for(int k=0;k<m;k++)
       {
           
           scanf("%d %d",&i,&j);
           g.L[i].head=INSERT(g.L[i],j);
           //printf("%d+",k);
       }

      scanf("%d",&src);

      //PRINT(g);
    
      for(int i=0;i<n;i++)
        {
           tmp=LIST_SEARCH(g.L[i],src);
          if(tmp!=NULL)
             {
               //printf("ha+");
               tmp->col='g';
               tmp->pi=NULL;
               tmp->d=0;
              }
          //printf("\n");
          }
     g_=g;
       BFS(g,src);
      
     g=change(g);
     printf("\n");
    DFS(g,src);
           
}
