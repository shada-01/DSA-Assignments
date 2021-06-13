#include<stdio.h>
#include<stdlib.h>

#include<ctype.h>
#include<string.h>

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

tnode CREATENODE(int k)
{
 tnode temp;
 temp=(tnode)malloc(sizeof(struct tnode));
 temp->key=k;
 temp->left=NULL;
 temp->right=NULL;

 return temp;
}

int max(int a,int b)
{
if(a>b)
return a;
else
return b;
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
 //x->p=y;
 if(y==NULL)
   T->root=x;
 else if(x->key<y->key)
   y->left=x;
 else
   y->right=x;

return T;
}

tnode LOW_COM_ANC(tnode cur,tnode t1,tnode t2)
{
  //printf("1");
  if (cur==NULL)
    return NULL;
  if(cur->key>t1->key && cur->key>t2->key)
     return (LOW_COM_ANC(cur->left,t1,t2));
   else if(cur->key<t1->key && cur->key<t2->key)
     return(LOW_COM_ANC(cur->right,t1,t2));
   else if((cur->key<t1->key && cur->key>t2->key) || (cur->key>t1->key && cur->key<t2->key))
   return cur;
   /*else if((cur->key==t1->key)|| (cur->key==t2->key))
     {
        //printf("1");
        if(cur->key==t2->key && t1->key<t2->key)
           return(cur->left);
        if(cur->key==t2->key && t1->key>t2->key)
           return(cur->right);
        if(cur->key==t1->key && t1->key>t2->key)
           return(cur->left);
         if(cur->key==t1->key && t1->key<t2->key)
           return(cur->right);
      } */
          
return cur;
}

int MAXIMUM(tnode r,int a,int b)
{
 if(r->key==a)
     return(-9999);
 //if(r->key>a)
   // return r->key;
 tnode temp=r;
 int val=-9999;
tnode prev=NULL;
  while( temp!=NULL &&  temp->key!=a )
   {
      if(temp->key!=b)
      prev=temp;
      if(temp->key<a)
          temp=temp->right;
       else
          temp=temp->left;
       if(prev!=NULL)
       val=max(prev->key,val);
   }

return((val));


}

void main()
{
char t1[10000];
int a,b;
scanf("%[^\n]%*c",t1);
//fgets(t1,10000,stdin);
scanf("%d %d",&a,&b);
//scanf("%d",&b);
TREE T1;
T1=(TREE)malloc(sizeof(struct Tree));
T1->root=NULL;
tnode x;

//printf("1");
for(int i=0;i<strlen(t1);i++)
{
  int flag=1;
 if(t1[i]==' ')
  continue;
  else
  { 
     if(t1[i]=='-')
        {
          flag=-1;
          i++;
        }
     int op=0;
     while(t1[i]!=' ' && t1[i]!='\0' && isdigit(t1[i]))
     {
               op=(op*10)+(int)(t1[i]-'0');
               i++;
      }
     if(flag==1)
      
            x=CREATENODE(op);
      else
            x=CREATENODE(op*-1);

     T1=INSERT(T1,x);
  
  }

}
//printf("1");
tnode A=CREATENODE(a);
tnode B=CREATENODE(b);
//printf("1");
tnode anc=LOW_COM_ANC(T1->root,A,B);

//printf("%d",anc->key);
int max1=MAXIMUM(anc,a,b);
int max2=MAXIMUM(anc,b,a);
int maximum=max(max1,max2);
printf("%d",maximum);

}
