#include<stdio.h>
#include<stdlib.h>

typedef struct avlnode
 {
   int key;
   int h;
   struct avlnode *left;
   struct avlnode *right;
   
 }*Anode;


typedef struct Tree
 {
   Anode root;
 }*TREE;



Anode CREATE_NODE(int k)
{
  Anode temp=(Anode)malloc(sizeof(struct avlnode));
  temp->left=NULL;
  temp->right=NULL;
  temp->key=k;

  return temp;

}


int max(int h1,int h2)
{
 if(h1>=h2)
   return h1;
 else
   return h2;
}


int find_height(Anode x)
{
 int lh,rh;
  if(x==NULL)
    return 0;
  if(x->left==NULL && x->right==NULL)
    return 0;
  if(x->right==NULL)
    rh=0;
  else
     rh=1+x->right->h;
  
  if(x->left==NULL)
    lh=0;
  else
     lh=1+x->left->h;
    return max(lh,rh);
}
   
 Anode LEFTROTATE(Anode n)
  {
    Anode p=n->right;
    n->right=p->left;
    p->left=n;
    n->h=find_height(n);
    p->h=find_height(p);
    //n=p;
    return p;
  } 

   Anode RIGHTROTATE(Anode n)
  {
    Anode p=n->left;
    n->left=p->right;
    p->right=n;
    n->h=find_height(n);
    p->h=find_height(p);
   // n=p;
    
    
    return p;
  } 


  Anode DOUBLE_RL(Anode n)
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
  }



int balfac(Anode x)

{
int bf;

if(x==NULL)
  return 0;
else
 {
 
 if(x->left!=NULL && x->right!=NULL)
  bf=(x->left)->h - (x->right)->h;
  else if(x->left==NULL && x->right!=NULL)
   bf= -1 - (x->right)->h;
   else if(x->right==NULL && x->left!=NULL)
   bf=  (x->left)->h - -1;
   else
   bf=0;
 }

 /* int lh,rh;
  if(x==NULL)
    return 0;
  if(x->left==NULL && x->right==NULL)
    return 0;
  if(x->right==NULL)
    rh=0;
  else
     rh=1+x->right->h;
  
  if(x->left==NULL)
    lh=0;
  else
     lh=1+x->left->h;

  bf=lh-rh;*/

return bf;
}
 

Anode avl_insert(Anode r,Anode a)
{
  if(r==NULL)
     {
       r=a;
       //r->h=0;
       
     }

    else if (a->key<r->key)
     {
        r->left=avl_insert(r->left,a);
        if(balfac(r)==2)
            {
               if(a->key < r->left->key)
                    r= RIGHTROTATE(r);
               else
                     r= DOUBLE_LR(r);
            }
     }

   else if (a->key>r->key)
     {
        r->right=avl_insert(r->right,a);
        if(balfac(r)==-2)
            {
               if(a->key > r->right->key)
                     r=LEFTROTATE(r);
               else
                      r=DOUBLE_RL(r);
            }
     }

   r->h=find_height(r);
  return r;

}
    
  
TREE INSERT(TREE T,int k)
{
  Anode x=CREATE_NODE(k);
  Anode y=avl_insert(T->root,x);
  T->root=y;
  return T;
  
}



     
       
    


Anode SEARCH( TREE T,int k)
{
 Anode x=T->root;
 while (x!=NULL && k!=x->key)
  {
    if(k<x->key)
         x=x->left;
    else
        x=x->right;
  }

return x;

}

int GETBALANCE(TREE T,int k)
{


 Anode x=SEARCH(T,k);
 int bf=balfac(x);
 return bf;

}



 

void PRINT(Anode t)
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

Anode delete_avl(Anode r,Anode x)
{
  if(r==NULL)
       return NULL;
   if(x->key>r->key)
      {
         r->right=delete_avl(r->right,x);
         if(balfac(r)==2)
             {
               if(balfac(r->left)>=0)
                   r=RIGHTROTATE(r);
                else
                   r=DOUBLE_LR(r);
              }
       }

    else if(x->key<r->key)
      {
         r->left=delete_avl(r->left,x);
         if(balfac(r)==-2)
             {
               if(balfac(r->right)<=0)
                   r=LEFTROTATE(r);
                else
                   r=DOUBLE_RL(r);
              }
       }
     else
       {
          if(r->right==NULL)
             return r->left;
          else
             {
               Anode temp=r->right;
               while(temp->left!=NULL)
                   temp=temp->left;
                r->key=temp->key;
                r->right=delete_avl(r->right,temp);
                if(balfac(r)==2)
                  {
                    
               if(balfac(r->left)>=0)
                   r=RIGHTROTATE(r);
                else
                   r=DOUBLE_LR(r);
                }
            }

        }
   r->h=find_height(r);
   return r;
}
                       
               

TREE DELETE(TREE T,int k)
{
Anode x=SEARCH(T,k);
Anode y=delete_avl(T->root,x);
T->root=y;
return  T;
 
}

int isavl(Anode r)
{
  int bf=balfac(r);
    printf("a");
   if(bf<0)
       bf=bf*-1;
  if(r==NULL)
     return 1;
  if( bf<=1 && isavl(r->left) && isavl(r->right))
    return 1;
  return 0;
}
  
   


void ISAVL(TREE T)
{
   printf("a");
 int val= isavl(T->root);
  printf("a");
  if(val==0)
 printf("NOT AVL");
  else
 printf(" AVL");
   
}
   

void main()
{

TREE T;
T=(TREE)malloc(sizeof(struct Tree));
T->root=NULL;
int k;
Anode s;
char ch;
scanf("%c",&ch);
while(ch!='e')
{
  switch(ch)
   {
     case 'i' : scanf("%d",&k);
                T=INSERT(T,k);
                break;
     case 'd' : scanf("%d",&k);
                 s=SEARCH(T,k);
                if(s!=NULL)
                {
                  T=DELETE(T,k);
                  printf("%d\n",k);
                }
                  
                else
                    printf("FALSE\n");
                break;
     case 's' : scanf("%d",&k);
                 s=SEARCH(T,k);
                 if(s!=NULL)
                    printf("TRUE\n");
                 else
                    printf("FALSE\n");
                break;
     case 'b' : scanf("%d",&k);
                if(SEARCH(T,k)!=NULL)
                {
                  int bf=GETBALANCE(T,k);
                  printf("%d\n",bf);
                }
                else
                    printf("FALSE\n");
                break;

      
     /*case 'a': ISAVL(T);
                break;*/
           
      case 'p': PRINT(T->root);
                printf("\n");
                break;

   
  }
scanf("%c",&ch);

}

}
    
      
                




