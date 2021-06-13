#include<stdio.h>
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

tnode CREATENODE(int k)
{
 tnode temp;
 temp=(tnode)malloc(sizeof(struct tnode));
 temp->key=k;
 temp->left=NULL;
 temp->right=NULL;
 temp->p=NULL;
 return temp;
}

tnode INSERT(tnode T,tnode x)
{
  tnode y=NULL;
  tnode z=T;
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
   T=x;
 else if(x->key<y->key)
   y->left=x;
 else
   y->right=x;

return T;
}

 tnode SEARCH(tnode T,int k)
{
 tnode x=T;
 while (x!=NULL && k!=x->key)
  {
    if(k<x->key)
         x=x->left;
    else
        x=x->right;
  }

return x;
 
}

tnode TRANSPLANT(tnode T,tnode u,tnode v)

{
  if(u->p==NULL)
    T=v;
  else if(u==u->p->left)
    u->p->left=v;
   else
     u->p->right=v;
  if(v!=NULL)
    v->p=u->p;
   return T; 
  
}

tnode MINVALUE(tnode x)
{
  while(x->left!=NULL)
   x=x->left;
 return x;
}

tnode MAXVALUE(tnode x)
{
  while(x->right!=NULL)
   x=x->right;
 return x;
}


tnode DELETE(tnode T,tnode z)
{
  tnode y;
  if(z->left==NULL)
   T=TRANSPLANT(T,z,z->right);
  else if(z->right==NULL)
   T=TRANSPLANT(T,z,z->left);
   else
    {
      y=MINVALUE(z->right);
      if(y->p!=z)
        {
          T=TRANSPLANT(T,y,y->right);
          y->right=z->right;
          y->right->p=y;
        }
       T=TRANSPLANT(T,z,y);
       y->left=z->left;
       y->left->p=y;
    }
   printf("%d",z->key);
    free(z);
return T;
}


tnode PREDECESSOR(tnode T,int y)
 {

 tnode s=SEARCH(T,y);
  if(s!=NULL)
   {
     if(s->left!=NULL)
       return (MAXVALUE(s->left));
     tnode y=s->p;
     while(y!=NULL && s==y->left)
        {
          s=y;
          y=y->p;
        }
     return y;
  }

 else
    return NULL;

   
 }


tnode SUCCESSOR(tnode T,int y)
 {

  tnode s=SEARCH(T,y);
  if(s!=NULL)
   {
     if(s->right!=NULL)
       return (MINVALUE(s->right));
     tnode y=s->p;
     while(y!=NULL && s==y->right)
        {
          s=y;
          y=y->p;
        }
     return y;
  }

 else
    return NULL;

}

        
     
int find_level(tnode t,int c_key,int level)
{
   int l_level,r_level;
   if(t==NULL)
      return -1;
  
  if(t->key==c_key)
    return level;
  
    l_level=find_level(t->left,c_key,level+1);
    r_level=find_level(t->right,c_key,level+1);

    if(l_level!=-1)
     return l_level;
    else
      return r_level;
 
}

int LEVEL(tnode T,int k)
{
  tnode s=SEARCH(T,k);
  if(s!=NULL)
    {
      if(s==T)
         return 1;
      else if(s==T->left || s==T->left)
         return 2;
       
       else
        {
          int level=find_level(T,k,1);
          return level;
        }

     }

 else
    return -1;
}

void INORDER(tnode t)
{

        
	if(t!=NULL)
	{
		INORDER(t->left);
		printf("%d ",t->key);
		INORDER(t->right);
	}
}
void PREORDER(tnode t)
{
        
	if(t!=NULL)
	{
		printf("%d ",t->key);
		PREORDER(t->left);
		PREORDER(t->right);
	}
}
void POSTORDER(tnode t)
{
        
	if(t!=NULL)
	{
		POSTORDER(t->left);
		POSTORDER(t->right);
		printf("%d ",t->key);
	}
}



void main()
{
//TREE T;
tnode T;
//(tnode)malloc(sizeof(struct tnode));
//T=(TREE)malloc(sizeof(struct Tree));
T=NULL;
//T->rot=NULL;
int k;
char ch;
tnode x,y,s;
  
  scanf("%c",&ch);
  

  while(ch!='e')
  {
    switch(ch)
     {
        case  'a': scanf("%d",&k);
                   x=CREATENODE(k);
                   T=INSERT(T,x);
                   break;

        case  'd': scanf("%d",&k);
                   y=SEARCH(T,k);
                    if(y==NULL)
                      printf("%d\n",-1);
                    else
                    {
                    T=DELETE(T,y);
                    printf("\n"); }
                    break;

        case  's': scanf("%d",&k);
                   s=SEARCH(T,k);
                   if(s==NULL)
                      printf("%d\n",-1);
                   else
                      printf("%d\n",1);
                  // DELETE(T,x);
                   //T=INSERT(x);
                   break;

        case 'l' : scanf("%d",&k);
                    printf("%d\n",LEVEL(T,k));
                    break;

        case 'm' :printf("%d\n",(MINVALUE(T))->key);
                  break;
        case 'x' :printf("%d\n",(MAXVALUE(T))->key);
                  break;

        case 'r' : scanf("%d",&k);
                     x=PREDECESSOR(T,k);
                      
                     if(x!=NULL)
                         printf("%d\n",x->key);
                      else
                         printf("-1\n");
                   //free(x);
                   break;
                     

        case 'u' : scanf("%d",&k);
                  
                    x=SUCCESSOR(T,k);
                      
                     if(x!=NULL)
                         printf("%d\n",x->key);
                      else
                         printf("-1\n");

                      //free(x);
                      break;

                  
        case  'i': 
                   INORDER(T);
                   printf("\n");
                   break;
        case  'p': PREORDER(T);
                   printf("\n");
                   break;
        case  't': 
                   POSTORDER(T);
                   printf("\n");
                   break;
      }
scanf("%c",&ch);
}





}

