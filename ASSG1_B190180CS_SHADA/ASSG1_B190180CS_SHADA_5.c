#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

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
 //int size;
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
          if(root->left!=NULL)
              root->left->p=root;
          if(root->right!=NULL)
             root->right->p=root;
         }
        return root;
   }

void Ksmallest(tnode t,int k)
{
  static int count=0;
        
	if(t!=NULL)
	{
		Ksmallest(t->left,k);
                count++;
                if(count==k)
                  {
                   printf("%d",t->key);
                   exit(1);
                  }
		Ksmallest(t->right,k);
	}
}

 
     
       

void main()
{

char e[1000000];
 int k;
 TREE T;
 T=(TREE)malloc(sizeof(struct Tree));
  T->root=NULL;
  scanf("%[^\n]%*c",e);
  scanf("%d",&k);
  int n=strlen(e);
  
         
  T->root=CREATE_TREE(e,0,n-1);
  Ksmallest(T->root,k);
  

}


