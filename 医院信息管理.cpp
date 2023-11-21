#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#define MIN 1
#define MAX 30
#define LEN_P sizeof(struct Patient)     //��LEN����ṹ���"����"
#define LEN_C sizeof(struct Consume)     //��LEN����ṹ���"����"

struct Patient* head;			//ȫ��ͷָ�룬����ȫ�ֲ����������� 
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
struct Patient* load();				//���ļ���ȡ�������������� 
void regeist();						/*�ȹ�������������β����
									Ȼ��ͨ��save����ʵ���������ݸ���д��ԭ�ļ�*/	
void search_patient();				//������������ ���ԱȲ�����������ѯ�������ڵ����� 
void show_all();					//�������������𣬶�ÿһ���ڵ㶼��ʾ 
void search_consume();
void save(); 						//���ļ�����ȫ��ͷָ����ָ���������д洢 
void savec();
void search_stock();

int main() {
	char choice;
	do {
		head=load();
		head_consume=loadc(); 
		printf("\n\n��ӭʹ��ҽԺ����ϵͳ\n\n");
		printf("\n*************************************************\n");
		printf("1.ע���²���\n2.��ѯ����������Ϣ\n3.�г����в�����Ϣ\n");
		printf("4.�������Ѳ�ѯ\n5.���Ӳ��������嵥\n6.��ѯ���\n7.���没����Ϣ\n0.�˳�\n");
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
		printf("\n\n�밴�����������\n");
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
   		printf("�޷����ļ���\n");
   		getch();
   		exit(0);
	   }
	   ch=fgetc(fp);
	   system("cls");
	   printf("\n\n\t\t�����Ϣ:(��û����Ϣ�뷵�ش���)");
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
	pb = (struct Consume*)malloc(LEN_C);    //�����µĽڵ�
	s = (struct Consume*)malloc(LEN_C);
	if ((pb == NULL) || (s == NULL))
	{
		printf("��̬�ڴ����ʧ�ܣ�\n");
		getch();
		exit(0);
	}
	if ((fp = fopen("D:\\hospitalmanager\\c\\consume.txt", "rb")) == NULL)
	{
		printf("�޷����ļ���\n");
		getch();
		exit(0);
	}
	head_consume = pb;								//head����û�пռ䣬ֻ��ָ�룬��ָ��һ���¿ռ䣬Ȼ��������� 
	while (fread(s, LEN_C, 1, fp))         //��ȡ��ǰ����Ϣ�����浽�����У� 
	{
		pb->next = s;
		pb = s;
		s = (struct Consume*)malloc(LEN_C);//��pbָ��β�ڵ㣬Ȼ��ʹ��s��Ϊָ���¿ռ�Ľڵ㣬�Դ�ѭ�� 
	}
	pb->next = NULL;
	fclose(fp);
	return head_consume;                    //����������ͷָ�� 
}

struct Patient* load()                 //����load������ȡ��ǰ����Ϣ�����浽�ڴ�������
{
	FILE* fp;
	struct Patient* pb, * s;
	pb = (struct Patient*)malloc(LEN_P);    //�����µĽڵ�
	s = (struct Patient*)malloc(LEN_P);
	if ((pb == NULL) || (s == NULL))
	{
		printf("��̬�ڴ����ʧ�ܣ�\n");
		getch();
		exit(0);
	}
	if ((fp = fopen("D:\\hospitalmanager\\c\\patient.txt", "rb")) == NULL)
	{
		printf("�޷����ļ���\n");
		getch();
		exit(0);
	}
	head = pb;								//head����û�пռ䣬ֻ��ָ�룬��ָ��һ���¿ռ䣬Ȼ��������� 
	while (fread(s, LEN_P, 1, fp))         //��ȡ��ǰ����Ϣ�����浽�����У� 
	{
		pb->next = s;
		pb = s;
		s = (struct Patient*)malloc(LEN_P);//��pbָ��β�ڵ㣬Ȼ��ʹ��s��Ϊָ���¿ռ�Ľڵ㣬�Դ�ѭ�� 
	}
	pb->next = NULL;
	fclose(fp);
	return head;                    //����������ͷָ�� 
}
void savec(){
	FILE* fp;
	struct Consume* p1, * p2, * p;
	int flag=0;
	if ((fp = fopen("consume.txt", "w+")) == NULL)
	{
		printf("�޷����ļ���\n");
		getch();
		exit(0);
	}	
	p1=head_consume;
	p=head_consume;
	p2=head_consume->next;
	while(p2!=NULL){
		flag=1;
		p1=p2;				//p2���ߣ�p1���ߣ���p2ʧ�㣬��p1Ϊβ�ڵ� 
		p2=p2->next;
	}
	//p1��β�ڵ�
	if(flag==1){
		do{
			p=p->next;						//�˾���ǰ���Դ˿��Ա����ȡͷ�ڵ� 
			fwrite(p, LEN_C, 1, fp);		//���ڵ��������ݸ���ԭ�ļ� 
		}while(p!=p1);
	}
	else{
		printf("����������"); 
	}
	fclose(fp);
}
void save(){
	FILE* fp;
	struct Patient* p1, * p2, * p;
	int flag=0;
	if ((fp = fopen("patient.txt", "w+")) == NULL)
	{
		printf("�޷����ļ���\n");
		getch();
		exit(0);
	}	
	p1=head;
	p=head;
	p2=head->next;
	while(p2!=NULL){
		flag=1;
		p1=p2;				//p2���ߣ�p1���ߣ���p2ʧ�㣬��p1Ϊβ�ڵ� 
		p2=p2->next;
	}
	//p1��β�ڵ�
	if(flag==1){
		do{
			p=p->next;						//�˾���ǰ���Դ˿��Ա����ȡͷ�ڵ� 
			fwrite(p, LEN_P, 1, fp);		//���ڵ��������ݸ���ԭ�ļ� 
		}while(p!=p1);
	}
	else{
		printf("����������"); 
	}
	fclose(fp); 
}


void regeist()                              //��һ��������regeist����ʵ��ע�Ṧ�� 
{

	char ch[2];
	int id;
	struct Patient* p1, * p2, * pa;
	p1 = (struct Patient*)malloc(LEN_P);
	if (p1 == NULL)
	{
		printf("��̬�ڴ����ʧ�ܣ�\n");
		getch();
		exit(0);
	}
	printf("\n�����벡����Ϣ��\n");//��ȡ��Ϣ��p1 
	printf("�����벡��ID:");
	scanf("%d", &id);
	p1->patient_id = id;               
	printf("name:\t");
	scanf("%s", p1->name);
	printf("sex:\t");
	scanf("%s", p1->sex);
	printf("record:\n");
	scanf("%s",p1->record);
	p1->next = NULL;				//p1��Ϊβ���ڵ� 
	p2=head;						//p2��ͷ���������ָ��β���ڵ� 
	while(p2->next!=NULL){
		p2=p2->next;
	}
	if (head == NULL)                          //���������Ϣ���浽����
	{
		head = p1;
		p2 = p1;
	}
	else
	{
		p2->next = p1;
		p2 = p1;							 
	}               
	printf("\n��ѡ���Ƿ����ע�Ს����Ϣ(y/n):");   
	scanf("%s", ch);
	if ((strcmp(ch, "y") != 0))
	{
		printf("\n�Ǽǲ�����Ϣ�ɹ���");
		save();
		return;
	}
	else regeist();
	return;                                //�Ǽ���ɺ󷵻�ͷ����ָ�� 
}


void search_patient()                     
{
	char ch[2];
	char patientname[20];                      
	struct Patient* pa;
	printf("\n��������Ҫ�鿴�Ĳ���������");
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
				printf("\n��ѡ���Ƿ�����鿴��Ϣ(y/n):\n");
				scanf("%s", ch);
				if ((strcmp(ch, "Y") != 0) && (strcmp(ch, "y") != 0))
				{
					return;
				}
				else
				{
					printf("\n��������Ҫ�鿴�Ĳ���������");
					scanf("%s", patientname);
					pa = head->next;
					continue;
				}
			}
			pa = pa->next;
		}
		else
		{
			printf("\nû�в鵽�ò��˵���Ϣ");
			return;
		}
	} while (1);
}


void show_all()                        //��һ����������show_all������������ʾ���в�����Ϣ 
{
	struct Patient* pa;
	pa = head->next;
	printf("\n���в��˵���Ϣ���£�\n");
	while (pa)                             //��ʾ���еĲ�����Ϣ
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
	printf("\n��������Ҫ�鿴�Ĳ���id��");
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
				printf("\nû�в鵽�ò��˵�������Ϣ");
			return;
			}
			if(flag==1){
				printf("\t\t�ܹ����ѣ�%d",sum); 
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
		printf("��̬�ڴ����ʧ�ܣ�\n");
		getch();
		exit(0);
	}
	printf("\n������������Ϣ��\n");//��ȡ��Ϣ��p1 
	printf("�����벡��ID:");
	scanf("%d", &id);
	p1->patient_id = id;               
	printf("����:\t");
	scanf("%s", p1->data);
	printf("����:\t");
	scanf("%s", p1->reason);
	printf("money:\n");
	scanf("%d",&p1->money);
	p1->next = NULL;				//p1��Ϊβ���ڵ� 
	p2=head_consume;						//p2��ͷ���������ָ��β���ڵ� 
	while(p2->next!=NULL){
		p2=p2->next;
	}
	if (head_consume == NULL)                          //���������Ϣ���浽����
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
	printf("\n��ѡ���Ƿ�����������Ϣ(y/n):");   
	scanf("%s", ch);
	if ((strcmp(ch, "y") != 0))
	{
		printf("\n�Ǽǲ���������Ϣ�ɹ���");
		
		return;
	}
	else addconsume();
	return; 
}


