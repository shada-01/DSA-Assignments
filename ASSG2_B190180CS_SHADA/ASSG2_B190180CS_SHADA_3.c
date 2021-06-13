#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<ctype.h>


typedef struct node
{
    char word[50];
    struct node *next;
}*node;


typedef struct LL
{
    node head;
}LL;
typedef struct table
{
    LL *L;
    int k;
}table;

node CREATE_NODE(char s[])
{
  node new=(node)malloc(sizeof(struct node));
    strcpy(new->word,s);
    new->next=NULL;
   return new;
}
 

/*node INSERT_FRONT(LL l,char w[])
{
    node new=(node)malloc(sizeof(struct node));
    strcpy(new->word,w);
    new->next=l.head;
    l.head=new;
    return l.head;
}*/


int find_index(char c)
{
  switch(c)
   {
     case 'a':return 0;
     case 'b':return 1;
     case 'c':return 2;
     case 'd':return 3;
     case 'e':return 4;
     case 'f':return 5;
     case 'g':return 6;
     case 'h':return 7;
  }
}
     
int pow_value(char s[])
{
 int count[8];
 for(int i=0;i<8;i++)
  count[i]=0;
 int ind,sum=0;
 for(int i=0;i<strlen(s);i++)
  {
    int val=find_index(s[i]);
    if(count[val]<1)
    {
    switch(s[i])
     {
       case 'a':ind=1<<0;
                count[0]++;
                break; 
      case 'b':ind=1<<1;
                count[1]++;
                break; 
      case 'c':ind=1<<2;
               count[2]++;
                break; 
      case 'd':ind=1<<3;
               count[3]++;
                break; 
      case 'e':ind=1<<4;
               count[4]++;
                break; 
      case 'f':ind=1<<5;
               count[5]++;
                break; 
      case 'g':ind=1<<6;
               count[6]++;
                break; 
      case 'h':ind=1<<7;
               count[7]++;
                break; 
      
     }
   }
  else
    ind=0;
   //printf("%d ",ind);
   sum+=ind;
   
 
    
  }
 return sum;
}

int cmp(char s1[],char s2[])
{
  return(strcmp(s1,s2));
}

node INSERT(node head,node x)
{
  if(head==NULL ||  cmp(head->word,x->word)>0)
    {
      x->next=head;
      head=x;
    }
   else
    {
      node temp=head;
      while(temp->next!=NULL && cmp(temp->next->word,x->word)<0)
          temp=temp->next;
       x->next=temp->next;
       temp->next=x;
     }
return head;
}
       
          

table CREATE_TABLE(table T,char s[],node x)
{
 
 int pow=pow_value(s)%(T.k);
 //printf("%d\n",pow);
 T.L[pow].head=INSERT(T.L[pow].head,x);
 return T;
 }

void print_slot(node head)
{
    node temp=head;
   while(temp!=NULL)
    {
      printf("%s ",temp->word);
      temp=temp->next;
    }
}

void PRINT_TABLE(table T)
{
  for(int i=0;i<255;i++)
   {
     if(T.L[i].head!=NULL)
     {
     print_slot(T.L[i].head);
     printf("\n");
     }
    }
}
 

void main()
{
    int m;
    char *s;
    s=(char*)malloc(50*sizeof(char));
    
    scanf("%d",&m);
    
    table T;
    T.k=255;
    T.L=(LL*)malloc(255*sizeof(struct LL));
    
    //strcat(s," ");

    for(int i=0;i<=T.k-1;i++)
    {
      T.L[i].head=NULL;
    }
    for(int i=0;i<m;i++)
    {
      scanf("%s",s);
      node x=CREATE_NODE(s);
      T=CREATE_TABLE(T,s,x);
     
    }



PRINT_TABLE(T);

}
