#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int k;
    struct node *next;
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

node INSERT(list L,int key)
{
    node x=(node)malloc(sizeof(struct node));
    x->k=key;

    node new;
    
    if(L.head==NULL)
     L.head=x;
    else
     {
       new=L.head;
       while(new->next!=NULL)
          new=new->next;
       new->next=x;
     }
return L.head;
}

void print_slot(node temp)
{
  node s;
  s=temp;
  while(temp!=NULL) {
    printf("%d ",temp->k);
    temp=temp->next; 
   }
}

void PRINT(graph g)
{
    for(int i=0;i<g.v;i++)
    {
        
    
     print_slot(g.L[i].head);
     
     
      printf("\n");
    }

}

void compute_edges(int n,int a[][n],graph g)
{
  for(int i=0;i<n;i++)
 {
   g.L[i].head=INSERT(g.L[i],i);
   //printf("%d ",i);
   for(int j=0;j<n;j++)
    {
      if(a[i][j]==1)
         INSERT(g.L[i],j);
      
   }
    //printf("\n");
 }

  
}
void main()
{

int n;
scanf("%d",&n);
int a[n][n];

for(int i=0;i<n;i++)
 {
   for(int j=0;j<n;j++)
    {
      scanf("%d",&a[i][j]);
   }
 }

    graph g;
    g.v=n;
    g.L=(list*)malloc(n*sizeof(struct List));
    
    //strcat(s," ");
    for(int i=0;i<g.v-1;i++)
    {
      g.L[i].head=NULL;
    }

compute_edges(n,a,g);
PRINT(g);

}

