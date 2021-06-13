#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<limits.h>
int count=0;
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

/*typedef struct BST
{
  int flag;
  int sum;
}BST;*/

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


int find_max(tnode t)
{
  if(t==NULL)
    return INT_MIN;

   int cur=t->key;
  
   int l_cur=find_max(t->left);
   int r_cur=find_max(t->right);
    
   if(l_cur>cur)
      cur=l_cur;
   if(r_cur>cur)
      cur=r_cur;

 return cur;



}


int find_min(tnode t)
{
  if(t==NULL)
    return INT_MAX;

   int cur=t->key;
   
   int l_cur=find_min(t->left);
   int r_cur=find_min(t->right);
    
   if(l_cur<cur)
      cur=l_cur;
   if(r_cur<cur)
      cur=r_cur;

 return cur;

}


int BST(tnode t)
{
  int lmax=INT_MIN,rmin=INT_MAX;
  if(t==NULL)
    return 1;
  if(t->left==NULL && t->right==NULL)
    return 1;
  
  if(t->left!=NULL)
       
      lmax=find_max(t->left);
    

  if(t->right!=NULL)
 
     rmin=find_min(t->right);
    
  if (!(lmax<=t->key && rmin>=t->key))
     return 0;
 
 if (!(BST(t->left) && BST(t->right)))
     return 0;

  return 1;
}

int sum(tnode t)
{
  if(t==NULL)
    return 0;
  
   return (t->key + sum(t->left) + sum(t->right));
}

int count_BST(tnode t,int k)
{
 //static int count=0;

 if(t==NULL)
   return 0;

 if(BST(t) && sum(t)==k)
   return(1+count_BST(t->left,k) + count_BST(t->right,k));
 
 else
     return(count_BST(t->left,k) + count_BST(t->right,k));

 
 

}



  

     
void main()
{
  
int k;
 char e[1000000];
 
 TREE T;
 T=(TREE)malloc(sizeof(struct Tree));
  T->root=NULL;
  scanf("%[^\n]%*c",e);
  scanf("%d",&k);
  int n=strlen(e);
  
         
  T->root=CREATE_TREE(e,0,n-1);
  //PRINT(T->root);
  //printf("\n");
  //tnode c_node=CREATE_TREE_NODE(cousin_key);
  
   int count=count_BST(T->root,k);
   printf("%d",count);

  

}


