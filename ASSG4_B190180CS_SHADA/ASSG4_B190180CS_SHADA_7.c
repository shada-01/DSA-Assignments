#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
int acnt,bcnt,ccnt,dcnt;

typedef struct node
{

  int key;
  struct node *p;
   int rank;
}node;

node *CREATENODE(int k)
{
  node *temp=(node*)malloc(sizeof(struct node));
  temp->key=k;
  temp->p=NULL;
  temp->rank=0;

return temp;
}

node **makeset(node **a,int i)
{
   node *t=CREATENODE(i);
     if(a[i]!=NULL)
     {
       printf("-1\n");
       return a;
     }
    else
     {
       a[i]=t;
       a[i]->p=a[i];
       printf("%d\n",i);
     }
 return a;
}

node **makeset_b(node **b,int i)
{
   node *t=CREATENODE(i);
    if(b[i]==NULL)
     {
        b[i]=t;
       b[i]->p=b[i];
     }
return b;
}

node **makeset_c(node **c,int i)
{
    node *t=CREATENODE(i);      
    if(c[i]==NULL)
     {
        c[i]=t;
       c[i]->p=c[i];
     }
return c;
}

node **makeset_d(node **d,int i)
{
     node *t=CREATENODE(i);     
    if(d[i]==NULL)
     {
        d[i]=t;
       d[i]->p=d[i];
     }
       
 return d;
}

node *find_ab(node **a,int i,int j)
{
  node *t=a[i];
  if(t!=NULL)
    {
      while(t->p!=t)
        {
          t=t->p;
            if(j==0)
                 acnt++;
        else if(j==1)
          bcnt++;
        }
         if(j==0)
                 acnt++;
        else if(j==1)
          bcnt++;
     }
  return t;
}

int rep(node *t)
{
  while(t!=NULL  && t->p!=NULL)
   t=t->p;
  return (t->key);
}

node *find_cd(node **c,int i,int j)
 {

   node *t=c[i];
   if(t==NULL)
     return t;
   node *q,*q1;
    if(t->p!=t)
     {
       t->p=find_cd(c,t->p->key,j);
          if(j==0)
                 ccnt++;
        else if(j==1)
          dcnt++;
       return (t->p);
     }

  if(j==0)
                 ccnt++;
        else if(j==1)
          dcnt++;

   return t;
}

node *find(node *t)
{
  while(t->p!=NULL)
     t=t->p;
 return t;
}
node **uniona(node **a,int x,int y)
{
  node *n1=find_ab(a,x,0);
  node *n2=find_ab(a,y,0);
  if(n1==NULL || n2==NULL)
   {
    printf("-1 ");
     return a;
   }
 else if(n1!=n2)
   a[n2->key]->p=n1;
   //(n1->rank)++;
   printf("%d ",n1->key);
return a;
}

node **unionc(node **c,int x,int y)
{
  node *n1=find_cd(c,x,0);
  node *n2=find_cd(c,y,0);
  if(n1==NULL || n2==NULL)
   {
    printf("-1 ");
     return c ;
   }
 else if(n1!=n2)
   c[n2->key]->p=n1;
   //(n1->rank)++;
   printf("%d ",n1->key);
return c;
}
  
node **unionb(node **b,int x,int y)
{
   node *m1=find_ab(b,x,1);
  node *m2=find_ab(b,y,1);
  
   if(m1==NULL || m2==NULL)
      {
         printf("-1 ");
     return b ;
      }
  if(b[m1->key]->rank==b[m2->key]->rank)
    {
      (b[m2->key])->p=m1;
     (b[m1->key])->rank++;
     printf("%d ",m1->key);
    }
 else if(b[m1->key]->rank> b[m2->key]->rank)
   {
     b[m2->key]->p=m1; printf("%d ",m1->key);}
  else
    { b[m1->key]->p=m2; printf("%d ",m2->key);}

return b;

}
     
 node **uniond(node **d,int x,int y)
{
   node *m1=find_cd(d,x,1);
  node *m2=find_cd(d,y,1);
  
   if(m1==NULL || m2==NULL)
      {
         printf("-1 ");
     return d ;
      }
  if(d[m1->key]->rank==d[m2->key]->rank)
    {
      d[m2->key]->p=m1;
     (d[m1->key])->rank++;
     printf("%d\n",m1->key);
    }
 else if(d[m1->key]->rank >d[m2->key]->rank)
   {
     d[m2->key]->p=m1; printf("%d\n",m1->key);}
  else
    {d[m1->key]->p=m2; printf("%d\n",m2->key);}

return d;

}  

void main()
{

 char ch;
  int x,y;
  node **a,**b,**c,**d;
  node *a_,*b_,*c_,*d_;
  int n=10000;
  a=(node**)malloc(10000*sizeof(node*));
  b=(node**)malloc(10000*sizeof(node*));
  c=(node**)malloc(10000*sizeof(node*));
  d=(node**)malloc(10000*sizeof(node*));
  int s[4];
  s[0]=s[1]=s[2]=s[3]=0;

  for(int i=0;i<n;i++)
   {
   a[i]=NULL;
   b[i]=NULL;
   c[i]=NULL;
   d[i]=NULL;
  }

  //acnt=bcnt=ccnt=dcnt=0;
dcnt=0;
ccnt=0;
acnt=0;
bcnt=0;
  scanf("%c",&ch);
 while(ch!='s')
{
   switch(ch)
     {
        case 'm':scanf("%d",&x);
                 a= makeset(a,x);
                 b=makeset_b(b,x);
                 c=makeset_c(c,x);
                 d=makeset_d(d,x);
                  break;
       case 'f': scanf("%d",&x);
                 a_=find_ab(a,x,0);
                 b_=find_ab(b,x,1);
                 c_=find_cd(c,x,0);
                 d_=find_cd(d,x,1); 
                 if(a_==NULL)
                    printf("-1 ");
                 else
                     printf("%d ",a_->key);
                 if(b_==NULL)
                    printf("-1 ");
                 else
                     printf("%d ",b_->key);
                 if(c_==NULL)
                    printf("-1 ");
                 else
                     printf("%d ",c_->key);
                 if(d_==NULL)
                    printf("-1\n");
                 else
                     printf("%d\n",d_->key);
 
                  break;
       case 'u':  scanf("%d",&x);
                  scanf("%d",&y);
                   a=uniona(a,x,y);
                   b=unionb(b,x,y);
                 c=unionc(c,x,y);
                   d=uniond(d,x,y);
               
                  
                  break;
       /*case 's':printf("%d %d %d %d",acnt,bcnt,ccnt,dcnt);
                 return ;
                  break;*/
    }
 scanf("%c",&ch);
}

printf("%d %d %d %d",acnt,bcnt,ccnt,dcnt);
        

}



/*m 1
m 2
m 3
m 4
m 5
m 6
m 7
m 8
m 9
u 1 2
u 3 4
u 5 6
u 7 8
u 9 8
u 6 8
u 4 8
u 2 8
f 9
m 10
u 10 9
s*/
