#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#define MIN 1
#define MAX 30
#define LEN_P sizeof(struct Patient)     //用LEN代替结构体的"长度"
#define LEN_C sizeof(struct Consume)     //用LEN代替结构体的"长度"

struct Patient* head;			//全局头指针，引领全局病人数据链表 
struct Consume* head_consume;
struct Consume {
	int patient_id;
	char data[20];
	char reason[20];
	int money;
	struct Consume* next;
};
struct Patient {
	int patient_id;
	char name[20];
	char sex[10];
	char record[100];
	struct Patient* next;
};


struct Consume* loadc();
void addconsume();
struct Patient* load();				//从文件读取数据至缓存链表 
void regeist();						/*先挂载数据至链表尾部，
									然后通过save（）实现链表内容覆盖写入原文件*/	
void search_patient();				//遍历缓存链表 ，对比病人姓名，查询该链表节点数据 
void show_all();					//遍历缓存链表吗，对每一个节点都显示 
void search_consume();
void save(); 						//打开文件，对全局头指针所指的链表进行存储 
void savec();
void search_stock();

int main() {
	char choice;
	do {
		head=load();
		head_consume=loadc(); 
		printf("\n\n欢迎使用医院管理系统\n\n");
		printf("\n*************************************************\n");
		printf("1.注册新病人\n2.查询单个病人信息\n3.列出所有病人信息\n");
		printf("4.病人消费查询\n5.添加病人消费清单\n6.查询库存\n7.保存病人信息\n0.退出\n");
		printf("\n*************************************************\n");
		choice = getch();
		switch (choice)
		{
		case '1':regeist(); break;
		case '2':search_patient(); break;
		case '3':show_all(); break;
		case '4':search_consume(); break;
		case '5':addconsume(); break;
		case '6':search_stock();break; 
		case '7':save();break;
		case '8':exit(0); break;
		default:printf("Error!"); break;
		}
		printf("\n\n请按任意键继续！\n");
		getch();
		system("cls");
	} while (1);
	return 0;
}

void search_stock(){
	FILE *fp;
   	char ch;
   	if((fp=fopen("stock.txt","r"))==NULL)
   	{
   		printf("无法打开文件！\n");
   		getch();
   		exit(0);
	   }
	   ch=fgetc(fp);
	   system("cls");
	   printf("\n\n\t\t库存信息:(若没有信息请返回创建)");
	   printf("\n-------------------------------------\n\n");
	   while(ch!=EOF) 
	   {
	   	putchar(ch);
	   	ch=fgetc(fp);
		} 
		fclose(fp);
}
struct Consume* loadc(){
	FILE* fp;
	struct Consume* pb, * s;
	pb = (struct Consume*)malloc(LEN_C);    //开辟新的节点
	s = (struct Consume*)malloc(LEN_C);
	if ((pb == NULL) || (s == NULL))
	{
		printf("动态内存分配失败！\n");
		getch();
		exit(0);
	}
	if ((fp = fopen("D:\\hospitalmanager\\c\\consume.txt", "rb")) == NULL)
	{
		printf("无法打开文件！\n");
		getch();
		exit(0);
	}
	head_consume = pb;								//head本身没有空间，只是指针，先指到一个新空间，然后进行链接 
	while (fread(s, LEN_C, 1, fp))         //读取当前的信息，并存到链表中， 
	{
		pb->next = s;
		pb = s;
		s = (struct Consume*)malloc(LEN_C);//用pb指向尾节点，然后使用s作为指向新空间的节点，以此循环 
	}
	pb->next = NULL;
	fclose(fp);
	return head_consume;                    //返回链表的头指针 
}

struct Patient* load()                 //定义load函数读取当前的信息，并存到内存链表中
{
	FILE* fp;
	struct Patient* pb, * s;
	pb = (struct Patient*)malloc(LEN_P);    //开辟新的节点
	s = (struct Patient*)malloc(LEN_P);
	if ((pb == NULL) || (s == NULL))
	{
		printf("动态内存分配失败！\n");
		getch();
		exit(0);
	}
	if ((fp = fopen("D:\\hospitalmanager\\c\\patient.txt", "rb")) == NULL)
	{
		printf("无法打开文件！\n");
		getch();
		exit(0);
	}
	head = pb;								//head本身没有空间，只是指针，先指到一个新空间，然后进行链接 
	while (fread(s, LEN_P, 1, fp))         //读取当前的信息，并存到链表中， 
	{
		pb->next = s;
		pb = s;
		s = (struct Patient*)malloc(LEN_P);//用pb指向尾节点，然后使用s作为指向新空间的节点，以此循环 
	}
	pb->next = NULL;
	fclose(fp);
	return head;                    //返回链表的头指针 
}
void savec(){
	FILE* fp;
	struct Consume* p1, * p2, * p;
	int flag=0;
	if ((fp = fopen("consume.txt", "w+")) == NULL)
	{
		printf("无法打开文件！\n");
		getch();
		exit(0);
	}	
	p1=head_consume;
	p=head_consume;
	p2=head_consume->next;
	while(p2!=NULL){
		flag=1;
		p1=p2;				//p2先走，p1后走，当p2失足，则p1为尾节点 
		p2=p2->next;
	}
	//p1是尾节点
	if(flag==1){
		do{
			p=p->next;						//此句在前，以此可以避免读取头节点 
			fwrite(p, LEN_C, 1, fp);		//将节点所有数据覆盖原文件 
		}while(p!=p1);
	}
	else{
		printf("链表无内容"); 
	}
	fclose(fp);
}
void save(){
	FILE* fp;
	struct Patient* p1, * p2, * p;
	int flag=0;
	if ((fp = fopen("patient.txt", "w+")) == NULL)
	{
		printf("无法打开文件！\n");
		getch();
		exit(0);
	}	
	p1=head;
	p=head;
	p2=head->next;
	while(p2!=NULL){
		flag=1;
		p1=p2;				//p2先走，p1后走，当p2失足，则p1为尾节点 
		p2=p2->next;
	}
	//p1是尾节点
	if(flag==1){
		do{
			p=p->next;						//此句在前，以此可以避免读取头节点 
			fwrite(p, LEN_P, 1, fp);		//将节点所有数据覆盖原文件 
		}while(p!=p1);
	}
	else{
		printf("链表无内容"); 
	}
	fclose(fp); 
}


void regeist()                              //下一个：定义regeist函数实现注册功能 
{

	char ch[2];
	int id;
	struct Patient* p1, * p2, * pa;
	p1 = (struct Patient*)malloc(LEN_P);
	if (p1 == NULL)
	{
		printf("动态内存分配失败！\n");
		getch();
		exit(0);
	}
	printf("\n请输入病人信息！\n");//获取信息到p1 
	printf("请输入病人ID:");
	scanf("%d", &id);
	p1->patient_id = id;               
	printf("name:\t");
	scanf("%s", p1->name);
	printf("sex:\t");
	scanf("%s", p1->sex);
	printf("record:\n");
	scanf("%s",p1->record);
	p1->next = NULL;				//p1作为尾部节点 
	p2=head;						//p2从头遍历，最后指向尾部节点 
	while(p2->next!=NULL){
		p2=p2->next;
	}
	if (head == NULL)                          //将输入的信息保存到链表
	{
		head = p1;
		p2 = p1;
	}
	else
	{
		p2->next = p1;
		p2 = p1;							 
	}               
	printf("\n请选择是否继续注册病人信息(y/n):");   
	scanf("%s", ch);
	if ((strcmp(ch, "y") != 0))
	{
		printf("\n登记病人信息成功！");
		save();
		return;
	}
	else regeist();
	return;                                //登记完成后返回头链表指针 
}


void search_patient()                     
{
	char ch[2];
	char patientname[20];                      
	struct Patient* pa;
	printf("\n请输入需要查看的病人姓名：");
	scanf("%s", patientname);
	pa = head->next;
	do
	{
		if (pa)
		{
			if (strcmp(patientname, pa->name) == 0)
			{
				printf("\n");
				printf("ID:\t%d", pa->patient_id);
				printf("\n");
				printf("name:\t\t%s", pa->name);
				printf("\n");
				printf("sex:\t\t%s", pa->sex);
				printf("\n");
				printf("record:\t\t%s", pa->record);
				printf("\n");
				printf("\n请选择是否继续查看信息(y/n):\n");
				scanf("%s", ch);
				if ((strcmp(ch, "Y") != 0) && (strcmp(ch, "y") != 0))
				{
					return;
				}
				else
				{
					printf("\n请输入需要查看的病人姓名：");
					scanf("%s", patientname);
					pa = head->next;
					continue;
				}
			}
			pa = pa->next;
		}
		else
		{
			printf("\n没有查到该病人的信息");
			return;
		}
	} while (1);
}


void show_all()                        //下一个：定义是show_all函数，用来显示所有病人信息 
{
	struct Patient* pa;
	pa = head->next;
	printf("\n所有病人的信息如下：\n");
	while (pa)                             //显示所有的病人信息
	{
		printf("\n");
		printf("name:\t\t%s", pa->name);
		printf("\n");
		printf("id:\t%d", pa->patient_id);
		printf("\n");
		printf("sex:\t\t%s", pa->sex);
		printf("\n");
		printf("record:\t\t%s", pa->record);
		printf("\n");
		pa = pa->next;
	}
}


void search_consume() {
	int sum=0,flag=0;
	char ch[2];
	int id;                      
	struct Consume* pa;
	printf("\n请输入需要查看的病人id：");
	scanf("%d", &id);
	pa = head_consume->next;
	do
	{
		if (pa)
		{
			if (id==pa->patient_id)
			{
				flag=1;
				printf("\n");
				printf("ID:\t%d", pa->patient_id);
				printf("\n");
				printf("data:\t\t%s", pa->data);
				printf("\n");
				printf("reason:\t\t%s", pa->reason);
				printf("\n");
				printf("money:\t\t%d", pa->money);
				printf("\n");
				sum+=pa->money;
			}
			pa = pa->next;
			 
		}
		else
		{
			if(flag==0){
				printf("\n没有查到该病人的消费信息");
			return;
			}
			if(flag==1){
				printf("\t\t总共消费：%d",sum); 
				return;
			}
		}
	} while (1);
}

void addconsume(){
	loadc(); 
	char ch[2];
	int id;
	struct Consume* p1, * p2, * pa;
	p1 = (struct Consume*)malloc(LEN_C);
	if (p1 == NULL)
	{
		printf("动态内存分配失败！\n");
		getch();
		exit(0);
	}
	printf("\n请完善消费信息！\n");//获取信息到p1 
	printf("请输入病人ID:");
	scanf("%d", &id);
	p1->patient_id = id;               
	printf("日期:\t");
	scanf("%s", p1->data);
	printf("事项:\t");
	scanf("%s", p1->reason);
	printf("money:\n");
	scanf("%d",&p1->money);
	p1->next = NULL;				//p1作为尾部节点 
	p2=head_consume;						//p2从头遍历，最后指向尾部节点 
	while(p2->next!=NULL){
		p2=p2->next;
	}
	if (head_consume == NULL)                          //将输入的信息保存到链表
	{
		head_consume = p1;
		p2 = p1;
	}
	else
	{
		p2->next = p1;
		p2 = p1;							 
	}   
	savec();            
	printf("\n请选择是否添加消费信息(y/n):");   
	scanf("%s", ch);
	if ((strcmp(ch, "y") != 0))
	{
		printf("\n登记病人消费信息成功！");
		
		return;
	}
	else addconsume();
	return; 
}


