#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct TABLE
{
    int key;
    int m;
    int f[3];
}table;

table* HASHTABLE(int m)
{
    table *T;
    T=(table*)malloc(m*sizeof(table));
    T->m=m;
    return T;

}

int hash_func_a(table *T,int x)
{
  int pos;
    for(int i=0;i<T->m;i++)
    {
       int i2=pow(i,2);
        pos=(((x % T->m ) + (T->f[1]*i) + (T->f[2]*i2)) % T->m);
        if((T+pos)->key==-1)
         {
             return pos;
         }
    }
    return -1;
}

int hash_func_b(table *T,int x)
{
    int R;
    
    for(int k=(T->m)-1;k>=2;k--)
    {
        int count=0;
        for(int j=2;j<=k/2;j++)
        {
            if(k%j==0)
            count++;
        }
        if(count==0)
        {
            R=k;
            break;
        }
    }

    for(int i=0;i<T->m;i++)
    {
        int pos=(((x%T->m) +( (R-(x % R))*i ) ) % T->m );
        if((T+pos)->key==-1)
         {
             return pos;
         }

    }
    return -1;
}

table* INSERT(table *T,int x)
{
    int pos;
    if(T->f[0]==1)
    {
         pos=hash_func_a(T,x);
        
    }
    else if(T->f[0]==0)
    {
       pos=hash_func_b(T,x);

    }

    if(pos!=-1)
        (T+pos)->key=x;

    return T;
}


int SEARCH(table *T,int x)
{
    for(int i=0;i<T->m;i++)
     {
         if((T+i)->key==x)
           return i;
     }
     return -1;
}

table* DELETE(table *T,int x)
{
    int pos=SEARCH(T,x);
    if(pos!=-1)
     (T+pos)->key=-1;

     return T;

}

void PRINT(table *T)
{
    for(int i=0;i<T->m;i++)
    {
        if((T+i)->key!=-1)
         printf("%d (%d)\n",i,(T+i)->key );
         else
         {
            printf("%d ()\n",i ); 
         }
         
    }
}

void main()
{
    int m,c1,c2,x;
    table *T;
    char ch,h;
    scanf("%c",&h);
    scanf("%d",&m);
    if(h=='a')
     {
         scanf("%d",&c1);
         scanf("%d",&c2);
     }
    scanf("%c",&ch);
    T=HASHTABLE(m);

    if(h=='a')
    {
        T->f[0]=1;
        T->f[1]=c1;
        T->f[2]=c2;
    }
    else if(h=='b')
    {
        T->f[0]=0;
        T->f[1]=-1;
        T->f[2]=-1;

    }
    for(int i=0;i<m;i++)
      (T+i)->key=-1;


    while(ch!='t')
    {
        switch(ch)
        {
            case 'i'://int x;
                    scanf("%d",&x);
                    T=INSERT(T,x);
                    break;
                    
            case 's'://int x;
                     scanf("%d",&x);
                     int s=SEARCH(T,x);
                     if( s!=-1)
                        printf("1\n");
                    else
                    {
                         printf("-1\n");
                    }
                    
                      break;

            case 'd'://int x;
                     scanf("%d",&x);
                     T=DELETE(T,x);
                     break;

            case 'p': PRINT(T) ;
                     break;

        }
        scanf("%c",&ch);

    }
}
