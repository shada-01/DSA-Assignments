#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct tnode
{
  int key;
  struct tnode *left;
  struct tnode *right;
  
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
 //temp->p=NULL;
 return temp;
}

int find_pos(char e[],int start,int last)
{
  int pos=0;
  if(last<start)
    return -1;
  else
   {
     for(int i=start;i<=last;i++)
      {
        if(e[i]=='(')
          pos++;
         else if(e[i]==')')
           {
            pos--;
            if(pos==0)
            return i;
           }
       }
   }
    return -1;
 }
      



tnode CREATE_TREE(char e[],int start,int last)
{
  tnode root;int i;
  int op=0;int pos=-1;

  if(last<start || e[start+2]==')')
    return NULL;
      
    int sign=start+2;
  
     for( i=start+2;(isdigit(e[i]) || e[i]=='-') ;i++)
      {
                if(isdigit(e[i]))
                   op=(op*10)+(int)(e[i]-'0');
             
              
       }
       if(e[sign]=='-')
          op=op*-1;
        
       root=CREATE_TREE_NODE(op);
     if(e[i+1]=='(' && (i+1)<=last)
         pos=find_pos(e,i+1,last);
      if(pos!=-1)
        {
          root->left=CREATE_TREE(e,i+1,pos);
          root->right=CREATE_TREE(e,pos+2,last-2);
          /*if(root->left!=NULL)
              root->left->p=root;
          if(root->right!=NULL)
             root->right->p=root;*/
         }
        return root;
   }

tnode SEARCH(TREE T,int k)
{
 tnode x=T->root;
 while (x!=NULL && k!=x->key)
  {
    if(k<x->key)
         x=x->left;
    else
        x=x->right;
  }

return x;
 
}

int NODES_COUNT(tnode root)
{
 if(root==NULL)
   return 0;
 else
   return(1+ NODES_COUNT(root->left) + NODES_COUNT(root->right));
}
  
tnode maximum(tnode x)
{
  while(x->right!=NULL)
   x=x->right;
 return x;
}

tnode minimum(tnode x)
{
  while(x->left!=NULL)
   x=x->left;
 return x;
}



void KSMALL(tnode t,int k,int *count)
{
  //static int count=0;
        
	if(t!=NULL)
	{
		KSMALL(t->left,k,count);
                (*count)++;
                if(*count==k)
                  {
                   printf("%d\n",t->key);
                   return;
                   
                  }
		KSMALL(t->right,k,count);
	}
}

void KSMALLEST(tnode t,int k)
{
  int count=0;
  KSMALL(t,k,&count);
}

void KLARG(tnode t,int k,int *count)
{
   //int n;
  
 
        
	if(t!=NULL)
	{
               
		KLARG(t->right,k,count);
                (*count)++;
                if(*count==k)
                  {
                   printf("%d\n",t->key);
                   return;
                  }
		KLARG(t->left,k,count);
	}
  
}

void KLARGEST(tnode t,int k)
{
  int count=0;
   KLARG(t,k,&count);
}
tnode SUCC(tnode r,int k)
{
  if(r->key==k)
   {
     if(r->right!=NULL)
       return minimum(r->right);
     else
        return NULL;
   }
  else
   {
     if(k<r->key)
       {
         if(SUCC(r->left,k)==NULL)
             return r;
          else
             return (SUCC(r->left,k));
        }
       else
           return (SUCC(r->right,k));  
    }
}

tnode SUCCESSOR(TREE T,int k)
{
  if(T->root==NULL)
    return NULL;
  else if((T->root->right==NULL) &&(T->root->key==k))
     return NULL;
else
   return SUCC(T->root,k);
}

tnode PRED(tnode r,int k)
{
  if(r->key==k)
   {
     if(r->left!=NULL)
       return maximum(r->left);
     else
        return NULL;
   }
  else
   {
     if(k>r->key)
       {
         if(PRED(r->right,k)==NULL)
             return r;
          else
             return (PRED(r->right,k));
        }
       else
           return (PRED(r->left,k));  
    }
}

tnode PREDECESSOR(TREE T,int k)
{
  if(T->root==NULL)
    return NULL;
  else if((T->root->left==NULL) &&(T->root->key==k))
     return NULL;
else
   return PRED(T->root,k);
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

void main()
{

TREE T;
T=(TREE)malloc(sizeof(struct Tree));
//T=NULL;
T->root=NULL;
int k;
char ch;
char e[1000000];
scanf("%[^\n]%*c",e);
  //scanf("%d",&k);
  int n=strlen(e);
  
         
  T->root=CREATE_TREE(e,0,n-1);
tnode x,y,s;
  
  scanf("%c",&ch);
  

  while(ch!='e')
  {
    switch(ch)
     {
        

        case 'l' : scanf("%d",&k);
                    if(NODES_COUNT(T->root)>=k)
                    KLARGEST(T->root,k);
                    else
                    printf("-1");
                     
                    break;

        case 's' :scanf("%d",&k);
                    if(NODES_COUNT(T->root)>=k)
                    KSMALLEST(T->root,k);
                     else
                    printf("-1");                                      
                    break;
       
        case 'r' : scanf("%d",&k);
                   if(SEARCH(T,k)!=NULL)
                    {
                     x=PREDECESSOR(T,k);
                      
                     if(x!=NULL)
                         printf("%d\n",x->key);
                      else
                         printf("-1\n");
                      }
                   else
                       printf("-1\n");
                   //free(x);
                   break;
                     

        case 'u' : scanf("%d",&k);
                    if(SEARCH(T,k)!=NULL)
                    {
                    x=SUCCESSOR(T,k);
                      
                     if(x!=NULL)
                         printf("%d\n",x->key);
                      else
                         printf("-1\n");
                      }
                    else
                       printf("-1\n");
                     
                      //free(x);
                      break;

                  
        case  'i': 
                   INORDER(T->root);
                   printf("\n");
                   break;
        
      }
scanf("%c",&ch);
}



}

