#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<ctype.h>

/*typedef struct words
{
    char w[20];
    int l;
}words;*/

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

node INSERT_FRONT(LL l,char w[])
{
    node new=(node)malloc(sizeof(struct node));
    strcpy(new->word,w);
    new->next=l.head;
    l.head=new;
    return l.head;
}

/*table* HASHTABLE(int m);
{
    table *T;
    T=(table*)malloc(m*sizeof(struct TABLE));
    T->m=m;
    return T;

}*/

int SEARCH(LL l,char w[])
{
    node s=l.head;
   while(s!=NULL && (strcmp(s->word,w)!=0))
     s=s->next;
   
   if(s!=NULL)
     return 1;
    else
    {
         return 0;
    }
    

}

table CREATE_TABLE(char s[],table T)
{
   int pos;
    char w[50];
    strcpy(w,"");
    for(int i=0;i<strlen(s);i++)
    {
        if(s[i]==' ')
          {
              int l=strlen(w);
              
                    pos=(l*l)%(T.k);
                     //printf("%d\n",pos);
                    if(SEARCH(T.L[pos],w)==0)
                    T.L[pos].head=INSERT_FRONT(T.L[pos],w);
                    strcpy(w,"")  ;
                    continue;  
                    
                
          }
        strncat(w,&s[i],1);


    }
return T;
}

void print_slot(node head,LL l)
{
    node temp=head;
   if(temp->next==NULL )
    {
     if(temp!=l.head)
     printf("%s-",temp->word);
     else
      printf("%s",temp->word);
     return;
   }
    else
    {
     print_slot(temp->next,l);
     if(temp!=l.head)
     printf("%s-",temp->word);
     else
      printf("%s",temp->word);
   }
}

void PRINT_TABLE(table T)
{
    for(int i=0;i<T.k;i++)
    {
        printf("%d:",i);
     if(T.L[i].head!=NULL)
         print_slot(T.L[i].head,T.L[i]);
      else
         printf("null");
     
      printf("\n");
    }

}

void main()
{
    int k;
    char *s;
    s=(char*)malloc(5000*sizeof(char));
    
    scanf("%d %[^\n]s",&k,s);
    
    table T;
    T.k=k;
    T.L=(LL*)malloc(k*sizeof(struct LL));
    
    strcat(s," ");
    for(int i=0;i<T.k-1;i++)
    {
      T.L[i].head=NULL;
    }


T=CREATE_TABLE(s,T);
PRINT_TABLE(T);

}
