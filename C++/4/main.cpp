#include <stdio.h>;
#include<stdlib.h>;
#include<string.h>;
#include <windows.h>;

typedef struct node
{
  char name[10];
  int prio;
  int round;
  int cputime;
  int needtime;
  int count;
  char state;
  struct node *next;
}PCB;

PCB *finish,*ready,*tail,*run;
int N;
void firstin(void);
void print1(char a);
void print2(char chose,PCB *p);
void print(char chose);
void insert_prio(PCB *q);
void prior_init(char chose);
void priority(char chose);
void insert_rr(PCB *q);
void roundrun_init(char chose);
void roundrun(char chose);

void main()
{
   char chose='\0';
   while((chose!='q')&&(chose!='Q'))
   {
       fflush(stdin);
       printf("选择进程优先级算法请输入P，选择循环轮转算法请输入Q\n");
       printf("请输入你的选择：");
           scanf("%c",&chose);
           if((chose!='q')&&(chose!='Q'))
           {
              system("cls");
              if((chose=='P')||(chose=='p'))
              {
                 prior_init(chose);
                 priority(chose);
                 system("cls");
              }
              else if((chose=='r')||(chose=='R'))
              {
                 roundrun_init(chose);
                 roundrun(chose);
                 system("cls");
              }
           }
   }
   printf("谢谢使用！\n");
}

void firstin(void)
{
   if(ready!=NULL)
   {
      run=ready;
      ready=ready->next;
      run->state='R';
      run->next=NULL;
   }
   else
   {
      run=NULL;
   }
}

void print1(char a)
{
   if(toupper(a)=='P')
   {
      printf("name cputime needtime priority state\n");
   }
   else
   {
      printf("name cputime needtime count round state\n");
   }
}

void print2(char chose,PCB *p)
{
   if(toupper(chose)=='P')
   {
      printf("%s\t%d\t%d\t%d\t%c\n",p->name,p->cputime,p->needtime,p->prio,p->state);
   }
   else
   {
      printf("%s\t%d\t%d\t%d\t%d\t%c\n",p->name,p->cputime,p->needtime,p->count,p->round,p->state);
   }
}

void print(char chose)
{
   PCB *p;
   print1(chose);

   if(run!=NULL)
   {
      print2(chose,run);
   }
   p=ready;
   while(p!=NULL)
   {
      print2(chose,p);
      p=p->next;
   }
   p=finish;
    while(p!=NULL)
   {
      print2(chose,p);
      p=p->next;
   }
}

void insert_prio(PCB *q)
{
   PCB *p,*s,*r;
   s=q;
   p=ready;
   r=p;
   if(s->prio>ready->prio)
   {
      s->next=ready;
      ready=s;
   }
   else
   {
      while(p)
      {
         if(p->prio>=s->prio)
         {
            r=p;
            p=p->next;
         }
         else
             break;
      }
      s->next=p;
      r->next=s;
   }
}

void prior_init(char chose)
{
    PCB *p;
    int i,time;
    char na[10];
    ready=NULL;
    finish=NULL;
    run=NULL;
    printf("输入进程的个数N:\n");
    scanf("%d",&N);
    for(i=0;i<N;i++)
    {
        p=(PCB*)malloc(sizeof(PCB));
        printf("输入第%d个进程\n",i+1);
        scanf("%s",na);
        printf("完成进程需要的时间片数\n");
        scanf("%d",&time);
        strcpy(p->name,na);
        p->cputime=0;
        p->needtime=time;
        p->state='W';
        p->prio=50-time;
        if(ready==NULL)
        {
           ready=p;
           ready->next=NULL;
        }
        else
        {
           insert_prio(p);
        }
        printf("当前就绪队列的进程的信息\n");
        print(chose);
    }
    printf("%d个进程以按优先级从高到低进到就绪队列中\n",N);
    printf("按回车键开始模拟优先级算法......\n");
    fflush(stdin);
    getchar();
    firstin();
}

void priority(char chose)
{
    int i=1;
    while(run!=NULL)
    {
       run->cputime+=1;
       run->needtime-=1;
       run->prio-=1;
       if(run->needtime==0)
       {
           run->next=finish;
           finish=run;
           run->state='F';
           run->prio=0;
           run=NULL;
           firstin();
       }
       else
       {
           if((ready!=NULL)&&(run->prio<ready->prio))
           {
               run->state='W';
               insert_prio(run);
               run=NULL;
               firstin();
           }
       }
       print(chose);
    }
    getchar();
}

void insert_rr(PCB *q)
{
    tail->next=q;
    tail=q;
    q->next=NULL;
}

void roundrun_init(char chose)
{
    PCB *p;
    int i,time;
    char na[10];
    ready=NULL;
    finish=NULL;
    run=NULL;
    printf("\t\t  循环轮转算法模拟全过程\n\n");
    printf("输入进程的个数N:\n");
    scanf("%d",&N);
    for(i=0;i<N;i++)
    {
        p=(PCB*)malloc(sizeof(PCB));
        printf("输入第%d个进程\n",i+1);
        scanf("%s",na);
        printf("完成进程需要的时间片数\n");
        scanf("%d",&time);
        strcpy(p->name,na);
        p->cputime=0;
        p->needtime=time;
        p->count=0;
        p->state='W';
        p->round=2;
        if(ready==NULL)
        {
           insert_rr(p);
        }
        else
        {
           p->next=ready;
           ready=p;
           tail=p;
        }
        printf("当前就绪队列的进程的信息\n");
        print(chose);
    }
    printf("%d个进程以按优先级从高到低进到就绪队列中\n",N);
    printf("按回车键开始模拟优先级算法......\n");
    fflush(stdin);
    getchar();
    run=ready;
    ready=ready->next;
    run->state='R';
}

void roundrun(char chose)
{
    int i=1;
    while(run!=NULL)
    {
       run->cputime+=1;
       run->needtime-=1;
       run->count+=1;
       if(run->needtime==0)
       {
           run->next=finish;
           finish=run;
           run->state='F';
           run->prio=0;
           run=NULL;
           if(ready!=NULL)
           {
               firstin();
           }
       }
       else
       {
           if(run->count==run->round)
           {
               run->count=0;
               if(ready!=NULL)
               {
                   run->state='W';
                   insert_rr(run);
                   firstin();
               }
           }
       }
       print(chose);
    }
    getchar();
}
