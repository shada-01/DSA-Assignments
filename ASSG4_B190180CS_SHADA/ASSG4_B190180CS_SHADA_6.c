#include<stdio.h>
#include<stdlib.h>


typedef struct tree
{
  int key;
  int deg;
  int mark;
  struct tree *child; 
  struct tree *left;
  struct tree *right;
  struct tree *p;
  
}tnode;

typedef struct heap
{
  tnode *min;
  int n;
}*hnode;

hnode MAKEHEAP()
{
  hnode H=(hnode)malloc(sizeof(struct heap));
  H->min=NULL;
  H->n=0;
  return H;
}

tnode *CREATE_NODE(int k)
{
  tnode *t=(tnode*)malloc(sizeof(struct tree));
  t->child=NULL;
  t->left=t;
  t->right=t;
  t->p=NULL;
  t->key=k;
  t->deg=0;
  t->mark=0;
  return t;
}

tnode *insert_to_rootlist(tnode *min,tnode *new)
{
  (min->left)->right=new;
   new->right=min;
   new->left=min->left;
   min->left=new;
  return min;
}

hnode INSERT(hnode H,int x)
{
  tnode *new=CREATE_NODE(x);
  if(H->min==NULL)
    H->min=new;
  else
   {
      H->min=insert_to_rootlist(H->min,new);
      if(new->key<H->min->key)
            H->min=new;

   }
 H->n++;
 return H;
}

tnode *MINIMUM(hnode H)
{
  return (H->min);
}

void swap(tnode *x,tnode *y)
{
  tnode *t;
   t=x;
  x=y;
  y=t;
}


void LINK(hnode H,tnode *y,tnode *x)
{
 ( y->right)->left=y->left;
 (y->left)->right=y->right;

 if(x->right==x)
   H->min==x;
 y->left=y;
 y->right=y;
 y->p=x;

 if(x->child==NULL)
   x->child=y;
 
 y->right=x->child;
 y->left=(x->child)->left;
(( x->child)->left)->right=y;
 (x->child)->left=y;
 if(y->key < (x->child)->key)
  x->child=y;
x->deg++;
y->mark=0;


}
  
int logn(int n)
 {
  //printf("nodes:%d ",n);
   int count=0;
   while(n>0)
   {
     n=n/2;
     count++;
   }
//printf("n:%d",count);
  return (count);
 }
  

hnode CONSOLIDATE(hnode H)
{
  int n_,d;
  n_=(logn(H->n));
   tnode *a[n_];
  for(int i=0;i<=n_;i++)
   a[i]=NULL;
 tnode *t1,*t2,*x,*y;
 t1=H->min;
 t2=H->min;
 do
  {
    //t2=t1=>right;
     x=t1;
     d=x->deg;
    while(a[d]!=NULL)
      {
         y=a[d];
         if(x->key>y->key)
            {
              tnode *t;
               t=x;
               x=y;
               y=t;
              
            }
         if(y==H->min)
           H->min=x;
         LINK(H,y,x);
         if(x->right==x)
           H->min=x;
         a[d]=NULL;
         d++;
      }
    a[d]=x;
    t1=x->right;
 }while(t1!=H->min);


//printf(" a[1]:%d",a[1]->key);
H->min=NULL;
for(int i=0;i<n_;i++)
 {
   if(a[i]!=NULL)
     {
       a[i]->right=a[i];
       a[i]->left=a[i];
       if(H->min==NULL)
            H->min=a[i];
         else
            {
              H->min=insert_to_rootlist(H->min,a[i]);
              if(a[i]->key<H->min->key)
                  H->min=a[i];
             }
        if(H->min==NULL)
            H->min=a[i];
        else if(a[i]->key<H->min->key)
             H->min=a[i];
       }
  }

return H;

}   
    
  

hnode EXTRACTMIN(hnode H)
{
  
  tnode *z,*c,*temp,*temp1;
  
 if(H->min!=NULL)
 {
  z=H->min;
  temp=z;
if(z->child!=NULL)
 {
  c=z->child;
  do
    {
      temp1=c->right;
      H->min=insert_to_rootlist(H->min,c);
      if(c->key<H->min->key)
        H->min=c;
      c->p=NULL;
      c=temp1;
    }while(temp1!=z->child);
 }
    (z->left)->right=z->right;
    (z->right)->left=z->left;
if(z==z->right && z->child==NULL)
  H->min==NULL;
else
  {
    H->min=z->right;
    H=CONSOLIDATE(H);
   }
H->n--;

}
return H;

} 

tnode *SEARCH(tnode *H,int x,tnode *C,int count)
{
  tnode *tmp=H;
  tnode *tmp1=NULL;
   if(tmp==NULL)
    return NULL;
 if(tmp==C && count>0)
  return NULL;
  
  if(tmp->key==x)
    {
       tmp1=tmp;
       return tmp1;
    }
    if(tmp->child!=NULL && tmp1==NULL)
        tmp1=SEARCH(tmp->child,x,C,count+1);
    if(tmp->right!=tmp && tmp1==NULL)
        tmp1=SEARCH(tmp->right,x,C,count+1);
  

return tmp1;
  
}

void CUT(hnode H,tnode *x,tnode *y)
{
  tnode *t=x;
   (x->left)->right=x->right;
    (x->right)->left=x->left;
   
   
   
   if(y->child==x)
        y->child=x->right;
  
   if(x==x->right)
     y->child=NULL;
  
     y->deg--;

   //adding to rrot list
     x->p=NULL;
     x->left=x;
     x->right=x;
     x->mark=0;
   

    H->min=insert_to_rootlist(H->min,x);
}

void CASCUT(hnode H,tnode *pr)
{
  tnode *gp=pr->p;
  if(gp!=NULL)
   {
       if(pr->mark==0)
           pr->mark=1;
       else
         {
           CUT(H,pr,gp);
           CASCUT(H,gp);
         }
   }

}
  
   
         
      
int DECREASEKEY(hnode H,int x,int y)  
{
  tnode *t=SEARCH(H->min,x,H->min,0);
 if(t!=NULL)
{
 t->key=y;
 
  //printf("%d\n",t->key);
}
  else{
    printf("-1\n");
    return 0;}

tnode *pr;
pr=t->p;

if(pr!=NULL && pr->key>t->key)
{
  CUT(H,t,pr);
  CASCUT(H,pr);
}

if(t->key < H->min->key)
  H->min=t;

return 1;

}

hnode DELETE(hnode H,int x)
{
 
 tnode *temp=SEARCH(H->min,x,H->min,0);
 if(temp!=NULL)
{

 printf("%d\n",temp->key);
 int h=DECREASEKEY(H,x,-9999);
 
 H=EXTRACTMIN(H); }
else
  printf("-1\n");


return H;
}

typedef struct node
 {
   tnode *data;
   struct node *next;
 }*node;

typedef struct queue
{
 node head;
 node tail;
}*queue;
int QUEUE_EMPTY(queue Q)
 {
   if(Q->head==NULL)
     return -1;
   else
     return 1;
  }

node CREATENODE(tnode *k)
{
 node temp;
 temp=(node)malloc(sizeof(struct node));
 temp->data=k;
 temp->next=NULL;
 return temp;
}

void ENQUEUE(queue Q,tnode *y)
{
 node x=CREATENODE(y);
 if(QUEUE_EMPTY(Q)==-1)
  Q->head=x;
 else
    Q->tail->next=x;
  Q->tail=x;
 //return Q;
}

void DEQUEUE(queue Q)
 {
   if(QUEUE_EMPTY(Q)!=-1)
     {
        node temp=Q->head;
        if(Q->head==Q->tail)
          Q->tail=NULL;
        Q->head=Q->head->next;
         
     }
//return temp->data;
}

void QUEUE_DELETE(queue Q)
 {
    //tnode temp;
   while(QUEUE_EMPTY(Q)!=-1)
    {
      DEQUEUE(Q);
    }
  //free(temp);
}
    
void traverse(tnode *root)
{
  if(root==NULL)
    return;
printf("%d ", root->key) ;
  if(root->child==NULL)
    return;

   queue Q;
   Q=(queue)malloc(sizeof(struct queue));
    Q->head=NULL;
    Q->tail=NULL;
    tnode *cur=root->child;
   ENQUEUE(Q,cur);
   tnode *t,*s,*tem;
   //tem=Q->head->data;
   while(QUEUE_EMPTY(Q)!=-1)
     {
       t=Q->head->data;
       s=t;
       DEQUEUE(Q);
        do
          {
              printf("%d ",t->key);
              if(t->child!=NULL)
                   ENQUEUE(Q,t->child);
              t=t->right;
           }while(t!=s );

     /* while(t!=NULL)
          {
              printf("%d ",t->key);
              if(t->child!=NULL)
                   ENQUEUE(Q,t->child);
              t=t->right;
              if(t==s)
               break;
           }*/
    }
}

void PRINT(tnode *t)
{
  tnode *q=t;
 if(t!=NULL)
  do
    { 

       printf("%d ",t->key);
        //traverse(t);

        t=t->right;
        
     }while(t!=q);

return;
}

void main()
{

 char ch;
 int x,y;
 scanf("%c",&ch);
 hnode H;
 H=MAKEHEAP();
 
 
  while(ch!='e')
   {
     switch(ch)
       {
         case 'i' : scanf("%d",&x);
                    H=INSERT(H,x);
                    break;
         case 'd' : scanf("%d",&x);
                    H=DELETE(H,x);
                   
                    break;
        case 'p' : PRINT(H->min);
                    printf("\n");
                    break;
         case 'm' : printf("%d\n",(MINIMUM(H))->key);
                    break;
         case 'x' : printf("%d\n",(MINIMUM(H))->key);
                    H=EXTRACTMIN(H);
                    
                    break;
         case 'r' : scanf("%d",&x);
                    scanf("%d",&y);
                    int h=DECREASEKEY(H,x,y);
                    if(h==1)
                     printf("%d\n",y);
                    break;
      }
    scanf("%c",&ch);
  }      
         

}
