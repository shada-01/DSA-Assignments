#include<stdio.h>
#include<stdlib.h>

typedef struct avlnode
 {
   int key;
   int h;
    int count;
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
  temp->count=1;

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
 
 if(x->left!=NULL && x->right!=NULL)
  bf=(x->left)->h - (x->right)->h;
  else if(x->left==NULL && x->right!=NULL)
   bf= -1 - (x->right)->h;
   else if(x->right==NULL && x->left!=NULL)
   bf=  (x->left)->h - -1;
   else
   bf=0;

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
   /*else if(a->key==r->key)
     {
       r->count++;
      }*/

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
   //r->count=1;
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

TREE array_insert(int a[],int n)
{
  TREE T;
  Anode s;
  T=(TREE)malloc(sizeof(struct Tree));
  T->root=NULL;
  
  for(int i=0;i<n;i++)
   {
     s=SEARCH(T,a[i]);
     if(s==NULL)
           T= INSERT(T,a[i]);
       else if(s->key==a[i])
          {
           //printf("%d\n",s->key);
           ++(s->count);
           }
    }
 return T;
}

/*TREE array_insert(int a[],int n)
{
 TREE T;
  //Anode s;
  T=(TREE)malloc(sizeof(struct Tree));
  for(int i=0;i<n;i++)
   {
     T= INSERT(T,a[i]);
    }
return T;
}*/

void inorder(Anode r,int a[],int *k)
{
  if(r!=NULL)
    {
     inorder(r->left,a,k);
      if(r->count==1)
        {
          a[*k]=r->key;
          (*k)++;
         
        }
       else
         {
          int lim=(*k)+r->count;
          for(int i=(*k);i<(lim);i++)
             {
               a[i]=r->key;
               (*k)++;
             }
      
          }
                   /*for(int i=0;i<(r->count);i++)
             {
               a[*k]=r->key;
               (*k)++;
             }*/

            
    
        inorder(r->right,a,k);
     }

}

void PRINT(Anode t)
 {
  printf("( ");
  if(t!=NULL)
	{
		printf("%d-->%d",t->key,t->count);
		PRINT(t->left);
		PRINT(t->right);
	}
   printf(") ");
  }
  
void print(int a[],int n)
{
 for(int i=0;i<n;i++)
  printf("%d ",a[i]);
printf("\n");
}       


void main()
{

int n;
scanf("%d",&n);
int a[n];
for(int i=0;i<n;i++)
scanf("%d",&a[i]);

TREE T;
T=(TREE)malloc(sizeof(struct Tree));
T->root=NULL;
T=array_insert(a,n);

//PRINT(T->root);
//printf("\n");
int k=0;
inorder(T->root,a,&k);
print(a,n);


}
