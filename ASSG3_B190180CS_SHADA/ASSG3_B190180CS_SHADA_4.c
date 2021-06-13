#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct tree
{
  int key;
  int deg;
  struct tree *left; 
  struct tree *rsib;
  struct tree *p;
  
}tnode;

typedef struct heap
{
  tnode *head;
}*hnode;

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
  if(root->left==NULL)
    return;

   queue Q;
   Q=(queue)malloc(sizeof(struct queue));
    Q->head=NULL;
    Q->tail=NULL;
    tnode *cur=root->left;
   ENQUEUE(Q,cur);
   tnode *t;
   while(QUEUE_EMPTY(Q)!=-1)
     {
       t=Q->head->data;
       DEQUEUE(Q);
        while(t!=NULL)
          {
              printf("%d ",t->key);
              if(t->left!=NULL)
                   ENQUEUE(Q,t->left);
              t=t->rsib;
           }
    }
}

void PRINT(tnode *t)
{
 //tnode *t=H->head;
  while(t!=NULL)
    { 

      //***
      //printf("%d ",t->key);
      //if(t->left!=NULL)
        traverse(t);

        t=t->rsib;
        //*****
     }
 //printf("\n");
}
                 

hnode MAKE_BINHEAP()
{
  hnode H=(hnode)malloc(sizeof(struct heap));
  H->head=NULL;
  return H;
}
tnode *CREATE_NODE(int k)
{
  tnode *t=(tnode*)malloc(sizeof(struct tree));
  t->left=NULL;
  t->rsib=NULL;
  t->p=NULL;
  t->key=k;
  t->deg=0;
  return t;
}
 /*tnode *merge(tnode *H1, tnode *H2) {
    hnode h = MAKE_BINHEAP();
    tnode *H=h->head;
     tnode* y;
    tnode* z;
    tnode* a;
     tnode* b;
    y = H1;
    z = H2;
    if (y != NULL) {
        if (z != NULL && y->deg <= z->deg)
            H = y;
        else if (z != NULL && y->deg > z->deg)
             need some modifications here;the first and the else conditions can be merged together!!!! 
            H = z;
        else
            H = y;
    } else
        H = z;
    while (y != NULL && z != NULL) {
        if (y->deg < z->deg) {
            y = y->rsib;
        } else if (y->deg == z->deg) {
            a = y->rsib;
            y->rsib = z;
            y = a;
        } else {
            b = z->rsib;
            z->rsib = y;
            z = b;
        }
    }
    return H;
}*/




tnode *merge(tnode *h1,tnode *h2)

{
  if(h1==NULL)
    return h2;
  else if(h2==NULL)
     return h1;
  else if(h1->deg<=h2->deg)
      {
         h1->rsib=merge(h1->rsib,h2);
         return h1;
      }
   else
     {
       h2->rsib=merge(h1,h2->rsib);
         return h2;
     }

}


tnode *MERGE(hnode H1,hnode H2)
{
  tnode *h=merge(H1->head,H2->head);
  return h;
} 

void BINOMIAL_LINK(tnode *x,tnode *y)
{

x->p=y;
x->rsib=y->left;
y->left=x;
y->deg+=1;

//return y;

}

hnode UNION( hnode H1,hnode H2)
{

hnode H=MAKE_BINHEAP();
H->head=MERGE(H1,H2);
if(H->head==NULL)
  return NULL;
tnode *x,*prev_x,*next_x;
x=H->head;
prev_x=NULL;
next_x=x->rsib;

while(next_x!=NULL)
{
  if(x->deg!=next_x->deg || next_x->rsib!=NULL && next_x->rsib->deg==x->deg)
     {
       prev_x=x;
       x=next_x;
      }
   else 
      {
       if(x->key<= next_x->key)
        {
       x->rsib=next_x->rsib;
       BINOMIAL_LINK(next_x,x);
         }
       else {
        if (prev_x==NULL)
         H->head=next_x;
       else
         prev_x->rsib=next_x;
        BINOMIAL_LINK(x ,next_x);
      x=next_x;
      }
   }
    next_x=x->rsib;
}
    
return H;
 }

tnode *MINIMUM(hnode H)
{
tnode *temp=H->head;
tnode *y;
y=temp;
int min=temp->key;
temp=temp->rsib;

while(temp!=NULL)
 {
  if(temp->key<min)
    {
      min=temp->key;
      y=temp;
   }
  temp=temp->rsib;
 }
return y;
  
}







hnode INSERT(hnode H,int x)
{
  tnode *n=CREATE_NODE(x);
 // if(H->head==NULL)
   // H->head=n;
  hnode H_;
  H_=MAKE_BINHEAP();
  H_->head=n;
  H=UNION(H,H_);
  return H;
}
  

tnode *reverse(tnode *x)
{
	tnode *temp = x ;
	tnode **arr = (tnode**) calloc(1000,sizeof(tnode*)) ;
	int i = 0 ;
	if(x==NULL)
		return NULL ; 
	while(temp!=NULL)
	{
		arr[i++] = temp ;
		temp->p = NULL ;
		temp = temp->rsib ;
	}
	int j = i-1 ; 
	i -= 1 ;
	while(i>0)
	{
		arr[i]->p = NULL ;
		arr[i]->rsib = arr[i-1] ;
		i -= 1 ;
	}
	arr[0]->rsib = NULL ;
	temp = arr[j] ;
	free(arr) ;
	return temp ;
}

hnode EXTRACT_MINIMUM(hnode H)
{
  tnode *t=H->head;
  if(t==NULL)
    printf("-1");
  tnode *min=MINIMUM(H);
  min->p=NULL;
  //min->rsib=NULL;
  //printf("%d\n",min->key);
  min->key=INT_MIN;
  if(min==t)
   H->head=H->head->rsib;
 else
   {
     for(tnode *tmp=t;tmp!=NULL;tmp=tmp->rsib)
       {
         if(tmp->rsib==min)
          {
            tmp->rsib=min->rsib;
            break;
          }
      }
  }
  min->rsib=NULL;
  tnode *x,*y;
  x=min->left;
  y=reverse(x);
  hnode H_=MAKE_BINHEAP();
  H_->head=y;
  H=UNION(H,H_);

  
return H;
 
}

tnode *SEARCH(tnode *H,int x)
{
  tnode *tmp=H;
  tnode *tmp1=NULL;
  if(tmp==NULL)
    return NULL;
  if(tmp->key==x)
    {
       tmp1=tmp;
       return tmp1;
    }
    if(tmp->left!=NULL && tmp1==NULL)
        tmp1=SEARCH(tmp->left,x);
    if(tmp->rsib!=NULL && tmp1==NULL)
        tmp1=SEARCH(tmp->rsib,x);

return tmp1;
  
}

hnode DECREASEKEY(hnode H,int x,int y)
{
 tnode *t=SEARCH(H->head,x);
 if(t!=NULL)
 t->key=x-y;
  else{
    printf("-1\n");
    return H;}

 tnode *r,*q;
 r=t;
 q=r->p;
 while(q!=NULL && r->key<q->key)
  {
    int val=r->key;
    r->key=q->key;
    q->key=val;
    r=q;
    q=r->p;
}

return H;


 }

  
hnode DELETE(hnode H,int x)
{
 
 tnode *temp=SEARCH(H->head,x);
 if(temp!=NULL)
{

 printf("%d\n",temp->key);
 H=DECREASEKEY(H,x,9999);
 
 H=EXTRACT_MINIMUM(H); }
else
  printf("-1\n");


return H;
}



/*void PRINT(tnode *t)
{
 printf("A");
 //tnode *t=H->head;
  while(t!=NULL)
    {
        traverse(t);
        t=t->rsib;
     }
 //printf("\n");
}*/



  
void main()
{

 char ch;
 int x,y;
 scanf("%c",&ch);
 hnode H;
 H=MAKE_BINHEAP();
 
 
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
         case 'p' : PRINT(H->head);
                    printf("\n");
                    break;
         case 'm' : printf("%d\n",(MINIMUM(H))->key);
                    break;
         case 'x' : printf("%d\n",(MINIMUM(H))->key);
                    H=EXTRACT_MINIMUM(H);
                    
                    break;
         case 'r' : scanf("%d",&x);
                    scanf("%d",&y);
                    H=DECREASEKEY(H,x,y);
                    break;
      }
    scanf("%c",&ch);
  }      
         


}
