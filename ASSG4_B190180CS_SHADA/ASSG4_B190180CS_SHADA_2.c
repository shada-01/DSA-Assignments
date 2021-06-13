#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct edge
{
  int s,d,w;

  struct edge *nexte;
}*edge;

typedef struct edgel
{
  edge e;
  int n_v,n_e;
}*edgel;

typedef struct node
{
    int key;
   
    int wt;
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
}*graph;

typedef struct setnode
{
  int rank;
  int k;
  struct setnode *p;
}set;

typedef struct pnode
{
  int weight,p,check;
}pnode;
  
  

node INSERT(list l,int key)
{
    node new=(node)malloc(sizeof(struct node));
    new->key=key;
    
    new->nnext=NULL;
    if(l.head==NULL || (l.head)->key >= new->key)
      {
        new->nnext=l.head;
        l.head=new;
      }
    else
       {
         node t=l.head;
         while(t->nnext!=NULL && t->nnext->key < new->key)
            t=t->nnext;
         new->nnext=t->nnext;
         t->nnext=new;
       }
   return l.head;
         
}

  void print_slot(node temp)
{
  node s;
  s=temp;
  while(temp!=NULL) {
    printf("%d(%d) -> ",temp->key,temp->wt);
    temp=temp->nnext; 
   }
}

void PRINT(graph g)
{
    for(int i=0;i<g->v;i++)
    {
        
    printf("%d: ",i);
     print_slot(g->L[i].head);
     
     
      printf("\n");
    }

}

edge makeedgenode(int i,int ver,int w)
   {
     edge new = (edge)malloc(sizeof(struct edge));
    new->s = i;
    new->d = ver;
    new->w = w;
    new->nexte = NULL;
   
   return new;
  }
     

edgel insert_edge(edgel E,int i,int ver,int w)
{

  edge new = makeedgenode(i,ver,w);
    

    if(E->e == NULL)
        E->e=new;
    else {
        edge *temp = &(E->e);
        while(*temp != NULL && (*temp)->w < new->w)
            temp = &((*temp)->nexte);
        new->nexte = *temp;
        *temp = new;
    }
    (E->n_e)++;

 return E;
}

edgel create_edge(graph g,int n)
{
  edgel E = (edgel)malloc(sizeof(struct edge));
    E->n_v = g->v;
    E->n_e = 0;
    E->e = NULL;

    for(int i=0; i<n; i++){
        node temp = g->L[i].head;
        while(temp!=NULL){
            if(temp->key > i)
               E= insert_edge(E, i,temp->key,temp->wt);
            temp = temp->nnext;
        }
    }
    return E;
}  


set *makeset(int i){

    set *n = (set*)malloc(sizeof(struct setnode));
    n->k = i;
    n->p = n;
    n->rank = 0;
    return n;
}

set *find_set(set *x){

    while(x->p!=x)
     {
       x=x->p;
     }
  return x;
}

set **Union(set **s,set *x, set *y){
    set *x_rep = find_set(x);
    set *y_rep = find_set(y);
    
    if(s[x_rep->k]->rank > s[y_rep->k]->rank)
       s[y_rep->k]->p=x_rep;
    else {
           s[x_rep->k]->p=y_rep;
        if(s[x_rep->k]->rank== s[y_rep->k]->rank)
           (s[y_rep->k]->rank)++;
    }

 return s;
}

edgel kruse(edgel E,int n){
    
    edgel k = (edgel)malloc(sizeof(struct edgel));
      
    k->n_e = 0;
    k->n_v= n;
    k->e = NULL;
     set **s;
    s=(set**)malloc(n*sizeof(set*));
   
      
    for(int i=0; i<n; i++)
        s[i] = makeset(i);

   
  

  

    edge head = E->e;
    while(head != NULL)
     {
        if(find_set(s[head->s]) != find_set(s[head->d]))
           {
            k=insert_edge(k, head->s, head->d, head->w);
            s=Union(s,s[head->s],s[head->d]);
           }
        head = head->nexte;
    }
    return k;
}    

void KRUS()
{
  int n,val,i_;
  char c;
  scanf("%d",&n);
      graph g; 
     g=(graph)malloc(sizeof(struct graph));
    node tmp;
    g->v=n;
    g->L=(list*)malloc(n*sizeof(struct List));
    
    //strcat(s," ");
    for(int p=0;p<n;p++)
    {
      g->L[p].head=NULL;
    }
    for(int i=0;i<n;i++)
     {
       c=' ';
       scanf("%d",&i_);
       while(c!='\n')
        {
          scanf(" %d%c",&val,&c);
           g->L[i_].head=INSERT(g->L[i_],val);
        }
     }

    int w;
  for(int i=0;i<n;i++)
    {
      scanf("%d",&i_);
      node t=g->L[i_].head;
      while(t!=NULL)
        {
          
          scanf(" %d",&w);
          t->wt=w;
          t=t->nnext;
          }
    }

   edgel E=create_edge(g,n);
   edgel k=kruse(E,n);
   
   edge ef=k->e;
   int cost=0;
   while(ef!=NULL)
    {
      cost+=ef->w;
      ef=ef->nexte;
    }
   printf("%d\n",cost);
   

}

int getmin(pnode *p,int n){
    int min_element, min_weight = INT_MAX;
    for(int i=0; i<n; i++)
      {
        if(p[i].check == 0 && p[i].weight < min_weight)
            {
            min_weight = p[i].weight;
            min_element = i;
            }
       }
    return min_element;
}

pnode *init_prior(pnode *p,int n)
{
  for(int i=0; i<n; i++){
      
        p[i].weight = INT_MAX;
        p[i].check = 0;
        p[i].p=-1;
      
    }

   p[0].weight=0; 
 return p;
}

pnode *Prim(graph g,int n){
    
    pnode *p;
     p=(pnode*)malloc(n*sizeof(pnode));
     p=init_prior(p,n);
    


    for(int i=0; i<n; i++)
      {
        int u = getmin(p,n);
        p[u].check =1;
        
        node temp = g->L[u].head;
        while(temp != NULL)
           {
            if(p[temp->key].check == 0 && temp->wt < (p[temp->key]).weight)
            {
                p[temp->key].p = u;
                p[temp->key].weight = temp->wt;
            }
            temp = temp->nnext;
          }
    }

    return p;
}


 
      
  void PRISM()
{
  int n,val,i_;
  char c;
  scanf("%d",&n);
      graph g; 
     g=(graph)malloc(sizeof(struct graph));
    node tmp;
    g->v=n;
    g->L=(list*)malloc(n*sizeof(struct List));
    
    //strcat(s," ");
    for(int p=0;p<n;p++)
    {
      g->L[p].head=NULL;
    }
    for(int i=0;i<n;i++)
     {
       c=' ';
       scanf("%d",&i_);
       while(c!='\n')
        {
          scanf(" %d%c",&val,&c);
           g->L[i_].head=INSERT(g->L[i_],val);
        }
     }

    int w;
  for(int i=0;i<n;i++)
    {
      scanf("%d",&i_);
      node t=g->L[i_].head;
      while(t!=NULL)
        {
          
          scanf(" %d",&w);
          t->wt=w;
          t=t->nnext;
          }
    }

   pnode *p=Prim(g,n);
   int cost=0;
   for(int i=0;i<n;i++)
     {
       cost+=p[i].weight;
      }

  printf("%d\n",cost);
       
   

 


}  
    

void main()
{
  char ch;
  scanf("%c",&ch);
  switch(ch)
   {
      case 'a' : KRUS();
                 break;
    
     case 'b':  PRISM();
                break;
   }

}

  
  

