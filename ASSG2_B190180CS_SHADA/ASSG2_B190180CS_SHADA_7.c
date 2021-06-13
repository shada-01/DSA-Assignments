#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<math.h>

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

TREE INSERT(TREE T,tnode x)
{
  tnode y=NULL;
  tnode z=T->root;
  while(z!=NULL)
  {
    y=z;
    if(x->key<z->key)
      z=z->left;
    else
      z=z->right;
   }
 x->p=y;
 if(y==NULL)
   T->root=x;
 else if(x->key<y->key)
   y->left=x;
 else
   y->right=x;

return T;
}

void INSERT_MOD(TREE T, int A[],int first,int last)
{

  if(first>last)
    return;
  int mid=(first+last)/2;
  tnode x=CREATE_TREE_NODE(A[mid]);
  T=INSERT(T,x);
  INSERT_MOD(T,A,first,mid-1);
  INSERT_MOD(T,A,mid+1,last);

}

int sum_level(tnode t ,int level)
{
 // static int sum=0;
 if(t==NULL)
   return 0;
 if(level==1)
   return ( t->key);
else if(level>1)
    {
      return( sum_level(t->left,level-1)+sum_level(t->right,level-1) );
     
    }
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

int n;
scanf("%d",&n);
int *A;
 TREE T;
 T=(TREE)malloc(sizeof(struct Tree));
  T->root=NULL;
A=(int*)malloc(n*sizeof(int));
for(int i=0;i<n;i++)
  scanf("%d",&A[i]);

INSERT_MOD(T,A,0,n-1);
PRINT(T->root);
printf("\n");

int h=floor(log(n)/log(2))+1;
for(int i=1;i<=h;i++)
{
  printf("%d ",sum_level(T->root,i));
  
}
}



