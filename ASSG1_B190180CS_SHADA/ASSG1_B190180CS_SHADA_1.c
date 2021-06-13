#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

typedef struct tnode
{
  int key;
  struct tnode *left;
  struct tnode *right;
  struct tnode *p;
}*tnode;
 

typedef struct Tree
{
 tnode root;
}*TREE;

typedef struct node
 {
   tnode data;
   struct node *next;
 }*node;

typedef struct queue
{
 node head;
 node tail;
}*queue;

node CREATE_NODE(tnode k)
{
 node temp;
 temp=(node)malloc(sizeof(struct node));
 temp->data=k;
 temp->next=NULL;
 return temp;
}

tnode CREATE_TREE_NODE(int k)
{
 tnode temp;
 temp=(tnode)malloc(sizeof(struct tnode));
 temp->key=k;
 temp->left=NULL;
 temp->right=NULL;
 temp->p=NULL;
 return temp;
}

int QUEUE_EMPTY(queue Q)
 {
   if(Q->head==NULL)
     return -1;
   else
     return 1;
  }

void ENQUEUE(queue Q,tnode y)
{
 node x=CREATE_NODE(y);
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
    
      


TREE INSERT(TREE T,int k)
{
  //tnode y=NULL;
  int flag=0;
  queue Q;
  node t;
  tnode new_node=CREATE_TREE_NODE(k);
  if(T->root==NULL)
    T->root=new_node;
   
  else
   {
    Q=(queue)malloc(sizeof(struct queue));
    Q->head=NULL;
    Q->tail=NULL;
    ENQUEUE(Q,T->root);
    while(flag==0 || QUEUE_EMPTY(Q)!=-1)
     {
        t=Q->head;
        if(t->data->left==NULL)
          {
            t->data->left=new_node;
            new_node->p=t->data;
            flag=1;
            QUEUE_DELETE(Q);
          }
         
          else if(t->data->right==NULL)
           {
            t->data->right=new_node;
            new_node->p=t->data;
            flag=1;
            QUEUE_DELETE(Q);
           }
         else
           {
             ENQUEUE(Q,t->data->left);
             ENQUEUE(Q,t->data->right);
             DEQUEUE(Q);
           }
        }
         
    }    
             
  
             
            

    
  
  
  

  
  return T;
 
 }

void PRINT(tnode t)
 {
  printf("( ");
  if(t!=NULL)
	{
		printf("%d ",t->key);
		PRINT(t->left);
		PRINT(t->right);
	}
   printf(") ");
  }
  

void main()
{
  TREE T;
  T=(TREE)malloc(sizeof(struct Tree));
  T->root=NULL;
  char ch;
  int k;
  tnode x;
  
  scanf("%c",&ch);
  

  while(ch!='e')
  {
    switch(ch)
     {
        case  'i': scanf("%d",&k);
                   
                   T=INSERT(T,k);
                   break;


       
                  
        case  'p': PRINT(T->root);
                   printf("\n");
                   break;
        
      }
    scanf("%c",&ch);
  }

}



//( 4 ( 3 ( 5 ( ) ( )  ) ( 6 (  ) (  )  )  ) ( 9 ( 1 (  ) (  )  ) ( 8 (  ) (  )  )  )  )
 // ( 4 ( 3 ( 5 ( ) ( ) ) ( 6 ( ) ( ) ) ) ( 9 ( 1 ( ) ( ) ) ( 8 ( ) ( ) ) ) )
 // ( 4 ( 3 ( 5 ( ) ( ) ) ( 6 ( ) ( ) ) ) ( 9 ( 1 ( ) ( ) ) ( 8 ( ) ( ) ) ) )
