#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

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



int SEARCH(tnode t,int k)
{
 if(t==NULL)
   return 0;
if(t->key==k)
  return 1;
int temp=SEARCH(t->left,k);
if(temp)
  return 1;
int temp2=SEARCH(t->right,k);
   return temp2;
  

 
}

int print_level(tnode t ,int level,int c_key)
{
   static int count=0;
 if(t==NULL)
   return 0;
 if(level==1 )
  {
    int printflag=0;
    if(t->p->left!=NULL){
      if(t->p->left->key==c_key){
        printflag=1;
      }
    }
    if(t->p->right!=NULL){
      if(t->p->right->key==c_key){
        printflag=1;
      }
    }
    if(printflag==0)
    {
    printf("%d ",t->key);count++;
    }

  }
else if(level>1)
    {
      print_level(t->left,level-1,c_key);
     print_level(t->right,level-1,c_key);
    }
return count;
}


int print_cousins(TREE T,int c_key)

 {
   int level;
   
     if(SEARCH(T->root,c_key)==0)
       return 0;
      else
       {
         level=find_level(T->root,c_key,1);
         //printf("%d\n",level);
         if(level<=2)
             return 0;
         return (print_level(T->root,level,c_key));
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
int cousin_key;
 char e[1000000];
 
 TREE T;
 T=(TREE)malloc(sizeof(struct Tree));
  T->root=NULL;
  scanf("%[^\n]%*c",e);
  scanf("%d",&cousin_key);
  int n=strlen(e);
  
         
  T->root=CREATE_TREE(e,0,n-1);
  //PRINT(T->root);
  //printf("\n");
  //tnode c_node=CREATE_TREE_NODE(cousin_key);
  int flag=print_cousins(T,cousin_key);
  if(flag==0)
   printf("-1");
 
}
  
  




