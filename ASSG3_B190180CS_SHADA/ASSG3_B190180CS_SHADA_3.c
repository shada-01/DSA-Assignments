#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct rbnode
 {
   int key;
   int c; // 0=RED  1=BLACK
   
   struct rbnode *left;
   struct rbnode *right;
   
 }*RBnode;

typedef struct Tree
 {
   RBnode root;
 }*TREE;

RBnode CREATE_NODE(int k)
{
  RBnode temp=(RBnode)malloc(sizeof(struct rbnode));
  temp->left=NULL;
  temp->right=NULL;
  temp->key=k;
  temp->c=0;

  return temp;

}

int bh(RBnode root)
{
 if(root==NULL)
   return 1;
 int hl=bh(root->left);
  int hr=bh(root->right);
  int x=hr>hl? hr: hl;
  if(root->c==1)
    return 1+x;
  return x;
}


RBnode LEFTROTATE(RBnode n)
  {
    if(n==NULL)
       return NULL;
    
    
    RBnode p;
    p=n->right;
    if(p==NULL)
         return n;
    n->right=p->left;
    p->left=n;
    //n->h=find_height(n);
    //>h=find_height(p);
    n=p;
    return n;
  } 

   RBnode RIGHTROTATE(RBnode n)
  {
    if(n==NULL)
        return NULL;
 
    RBnode p;
     p=n->left;
    if(p==NULL)
         return n;
      
    n->left=p->right;
    p->right=n;
    //n->h=find_height(n);
    //p->h=find_height(p);
    n=p;
    
    
    return n;
  } 


  /*Anode DOUBLE_RL(Anode n)
  {
    n->right=RIGHTROTATE(n->right);
    n=LEFTROTATE(n);
    return n;
  }
  

 Anode DOUBLE_LR(Anode n)
  {
    n->left=LEFTROTATE(n->left);
    n=RIGHTROTATE(n);
    return n;
  }*/


int col(RBnode r)
{
 if(r==NULL)
   return 1;
 else
   return (r->c);
}

RBnode rb_insert(RBnode r,RBnode x)
{
  RBnode y;
  if(r==NULL)
    return x;
   if(x->key<r->key)
     {
       r->left=rb_insert(r->left,x);
       if(r->left->c==0)
          {
            if( (col(r->left->left))==0 || col(r->left->right)==0)
              {
                if(col(r->right)==0)
                   {
                      r->left->c=1;
                      r->right->c=1;
                       r->c=0;
                      return r;
                    }
                 else
                   {
                      if(col(r->left->left)==0)
                         {
                           y=RIGHTROTATE(r);
                           y->right->c=0;
                           y->c=1;
                           return y;
                         }
                        else
                           {
                             r->left=LEFTROTATE(r->left);
                             y=RIGHTROTATE(r);
                              y->right->c=0;
                              y->c=1;
                              return y;
                            }
                     }
                 }
                 else
                    return r;
           }
           else
              return r;
    }
  
  else if(x->key>r->key)
   {

       r->right=rb_insert(r->right,x);
       if(r->right->c==0)
          {
            if(col(r->right->left)==0 || col(r->right->right)==0)
              {
                if(col(r->left)==0)
                   {
                      r->left->c=1;
                      r->right->c=1;
                       r->c=0;
                      return r;
                    }
                 else
                   {
                      if(col(r->right->right)==0)
                         {
                           y=LEFTROTATE(r);
                           y->left->c=0;
                           y->c=1;
                           return y;
                         }
                        else
                           {
                             r->right=RIGHTROTATE(r->right);
                             y=LEFTROTATE(r);
                              y->left->c=0;
                              y->c=1;
                              return y;
                            }
                     }
                 }
                 else
                    return r;
           }
           else
              return r;
   
   }

         

  }                           
                       

RBnode RB_INSERT(TREE T,int k)
{
  RBnode x=CREATE_NODE(k);
  T->root=rb_insert(T->root,x);
  if(T->root->c==0)
     T->root->c=1;
   return T->root;
}

char color(RBnode r)
{
  if(r->c==0)
    return 'R';
  else
    return 'B';
}
void PRINT(RBnode t)
 {
  printf("( ");
  if(t!=NULL)
	{
		printf("%d %c ",t->key,color(t));
		PRINT(t->left);
		PRINT(t->right);
	}
   printf(") ");
  }


void main()
{
char n[7];
int val;
scanf("%s",n);
val=atoi(n);
TREE T;
T=(TREE)malloc(sizeof(struct Tree));
T->root=NULL;
while(strcmp(n,"t")!=0)
{
  val=atoi(n);
  T->root=RB_INSERT(T,val);
  PRINT(T->root);
  printf("\n");
  scanf("%s",n);
  
  
  
}

}
