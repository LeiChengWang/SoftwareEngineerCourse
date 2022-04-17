#include <iostream>
using namespace std;
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <fstream>
#include <iomanip>

#pragma warning(disable:4996)  //strcpy��strcmp������


/*------------------------Note--------------------------
��ȡ�ı��ļ�ʱ���ı��ļ��ı����ʽ��ANSI,�������Ļ�����
���ϵı��������� ������ �����Ǿ������Ʒ���� ����
��ϵͳ���ڿ����ڹر����´򿪺����ʹ��֮ǰ������
��ѯ��¼�ķ�������ģ������

--------------------------Note--------------------------*/


/*------------------------�궨��start--------------------------*/

//������¼��ѯģʽ
#define First_search     1     //�״β�ѯ
#define Continue_search  2     //����ɸѡ
#define Clear_list       3     //��ղ�ѯ����


//����ģʽ��Ծ
#define normal          0     
#define jump_to_first   1
#define jump_to_second  2
#define jump_to_third   3
#define jump_to_forth   4
#define jump_to_fifth   5




/*------------------------�ṹ��start--------------------------*/

//���ڡ��ꡢ�¡��ա�
struct Data
{
	int year; 
	int month;
	int day;
};

//����
struct material
{
	char seri_number[20];      //���
	char name[20];             //����
	float unit_price;          //����

	char in_out[5];            //������¼

	int  in_num;               //�������
	struct Data in_time;       //���ʱ��

	int out_num;               //��������
	struct Data out_time;      //����ʱ��

	char person[20];           //������
	int  store_num;            //�������
	char note[100];            //��ע

	material* next;            //��һ�����ָ��
};


/*--------------------------ö��start---------------------------*/

//���˵�
enum main_menu
{
	add_record=1,    //��Ӽ�¼
	show_record,   //��ʾ��¼
	search_record, //��ѯ��¼
	change_record, //�޸ļ�¼
	write_file,	   //д���ļ� 
	exit_out       //�˳�ϵͳ
}main_menu_switch;


//��һ���Ӳ˵�
enum first_menu
{
	add_more=1,                 //��Ӹ���ļ�¼
	first_exit_to_main         //�������˵�
}first_menu_switch;

//��Ӽ�¼ģʽ�˵�
enum add_record_modei_menu
{
	add_one=1,      //���һ����¼
	add_two,        //��Ӷ�����¼
	add_from_file   //���ļ���Ӽ�¼
}add_record_model_menu;

//�ڶ����Ӳ˵�
enum second_menu
{
	show_more=1,     //��ʾ����ļ�¼
	second_exit_to_main  //�������˵�
}second_menu_switch;

//��ʾ��¼ģʽ�˵�
enum show_record_mode_menu
{
	record_List=1,   //��ʾ����¼
	cangku_Item      //��ʾ�ֿ���Ʒ�嵥
}show_record_mode_menu;

//�������Ӳ˵�
enum third_menu
{
	conti_to_search=1,     //����ɸѡ
	anew_search,         //����ɸѡ 
	third_exit_to_main    //�������˵�
}third_menu_switch;

//���ĸ��Ӳ˵�
enum forth_menu
{
	 change_one=1,       //�޸ĵ�������¼
	 change_together   //�����޸�

}forth_menu_switch;

//���ĸ����Ӳ˵�
enum forth_sub_menu
{
	continue_change = 1,     //�����޸ı���¼��������
	change_others,           //�޸���������¼
	show_change_data,        //��ʾ�޸ĺ������
	forth_exit_to_main       //�������˵�
}forth_sub_menu_switch;

//�������Բ˵�
enum material_menu
{
	seri_number=1,   //���
	name,            //����
	unit_price,      //����
	person,          //������	
	in_out_way,      //����ⷽʽ
	record_data,     //��¼������
	note,			 //��ע
	num,             //����
	all,             //ȫ������
	in_out_time,     //�����ʱ��
	change_all,       //�޸�ȫ��
	in_out_num       //���������
}sec_sub,third_sub,forth_sub;


//������Ӳ˵�
enum fifth_menu
{
	save_to_other=1,       //���浽�����ĵط�
	fifth_exit_to_main    //�������˵�
}fifth_menu_switch;


//���Ͽ��ʼ��ģʽ�˵�
enum material_Base_init
{
	file_in = 1,   //�ļ�����
	handwrite,      //�ֶ�����
	continue_to_use   //����ʹ��
}Base_init;



/*--------------------------��������start---------------------*/

//�˵���������
int Main_menu();         //��ʾ���˵�
int First_menu();        //��ʾ��һ���Ӳ˵�    
int Second_menu();       //��ʾ�ڶ����Ӳ˵�    
int Third_menu();        //��ʾ�������Ӳ˵�  
int Forth_menu();        //��ʾ���ĸ��Ӳ˵�
int Forth_sub_menu();    //��ʾ���ĸ��Ӳ˵����Ӳ˵�
int Material_menu();      //��ʾ�������Բ˵�(���Ͳֿ�)
int Fifth_menu();         //��ʾ������Ӳ˵�   
int material_base_menu();  //��ʾ���ϳ�ʼ��ģʽ�˵�
void Add_record_menu();     //��ʾ��Ӽ�¼�˵�
int Add_record_model_menu();  //��ʾ��Ӽ�¼ģʽ�˵�
int Show_record_mode_menu();     //��ʾ��¼ģʽ�˵�
int Search_record_mode();         //��ʾ��ѯģʽ�˵�     //��ѯ����¼���ǲֿ���Ʒ
int Search_record_menu();          //��ʾѡ���ѯ����¼���ԵĲ˵�
int Change_record_menu();           //��ʾ�޸Ĳ������Բ˵�
int Write_record_ku_menu();           //��ʾд���ļ�ģʽ�˵�  ����¼���ǲֿ���Ʒ�嵥


//���ܺ�������

void Delay(int i);        //��ʱ����
int Find_in_part(char* search_data, char* now_node, enum material_menu link);   //ģ����ѯ�㷨  ���ַ���  ��ѯ��Χ������¼���ֿ���Ʒ

//����صĺ���

struct material* Creat_ku();               //�������Ͽ⡾��������
void print_ori(struct material* head,int mode);     //���ԭʼ��
struct material* Creat_Item_List();        //������Ʒ�Ĳֿ�(����һ��ͷ���)  
void Print_ku(struct material* thi_head);  //����ֿ����Ʒ

void Handout_ku_init(struct material* head, struct material* sec_head);   //����¼�����ʼ�����ֿ���Ʒ���ࡿ

//Update ��صĺ���
void Join_to_record_List(struct material* new_record, struct material* record_List);  //��ĳ�����¼���¼�¼������
int Join_record(struct material* now_record, struct material* sec_head,int mode);            //��ĳ�����¼���µ��ֿ���Ʒ��

//��Ӽ�¼��صĺ���

int Add_one_record(int mode);       //��ӵ�����¼�����кͲֿ���  
void Add_many_record();             //��Ӷ�����¼�����Ͳֿ���
void Add_file_record();             //����ļ���¼�����Ͳֿ���

void Show_related_record(enum material_menu link);   //��ʾ��صı���¼
void Show_Cangku_Item();    //��ʾ�ֿ���Ʒ�嵥



void Search_related_record(enum material_menu link,int mode);     //��ѯ����¼  ����˵��:link-�жϼ������� mode-�жϼ���ģʽ 
void Search_ku_item();         //��ѯ�ֿ��¼
  
void Change_record(enum material_menu link, int mode);      //�޸ĵ�������¼���� 
void Update_change_to_record(struct material* Change_record_head, struct material* now_search_head, struct material* base_head);   //���޸ĵĵ�����ѯ��¼���µ�����¼��
void Change_many_record(enum material_menu link, int mode);   //�޸Ķ�������¼����
void Write_in_file(int mode);    //д���ļ�����  ����˵�� mode 1-�������¼ 2-����ֿ���Ʒ�嵥


/*---------------------------ȫ�ֱ�����ָ��start-------------------*/

int all_temp=0;  //���ڼ�¼ʵʱѡ��ĸ��ֲ˵�ֵ
int sum_record=0;       //��������
int sum_item=0;         //�ֿ���Ʒ������
int sum_search = 0;     //���������м�¼������
int mode_jump= normal;          //����������Ҫʱ�����в�ͬģʽ֮�����ת��������˳��ִ�еģ��������ʵ����Ծ
material* base_head=NULL;       //���Ͽ����¼��ͷָ��
material* ku_head=NULL;         //�ֿ���Ʒ��ͷָ��
material* Search_head=NULL;     //��ѯ��¼ʱͷָ��
material* Change_record_head = NULL;     //�޸ļ�¼λ��ָ��

ofstream outfile;       //�ļ�ָ��  ���ڹ���5���ݵ���
ifstream infile;        //�ļ�ָ��  ���ڶ����ļ�

int main()
{
	//���Ͽ��ʼ������
	sum_record = 0;
	sum_item = 0;
	
	cout << "*******************************************" << endl;
	cout << "*  �û�����!��ʹ��ǰ��Ҫ����ϵͳ��ʼ��!   *" << endl;
	cout << "*******************************************" << endl << endl;

	Delay(1500);
	//������  
	base_head=Creat_ku();	
	//print_ori(base_head,1);     //���ԭʼ�ı���¼

	//�����ֿ�
	ku_head=Creat_Item_List();

	cout << "����¼���ݳ�ʼ�����µ��ղֿ⣡" << endl;
	Handout_ku_init(base_head, ku_head);     //���ոս����ı���¼���µ��ֿ����Ʒ�嵥�У���ʼ��������
	Delay(1500);

	//Print_ku(ku_head);            //����ֿ����Ʒ�嵥

	cout << "ϵͳ��ʼ����ɣ���" << endl;
	Delay(1500);
	cout << "��������ֿ�ʵʱ���Ϲ���ϵͳ" << endl;
	Delay(3000);
	system("cls");
	cout << "��ӭʹ�ã���" << endl;
	Delay(2500);
	system("cls");

	//����ֿ��ʵʱ���Ϲ���ϵͳ
	while (1)
	{
		//��Ծģʽ�ر�  ��������ģʽ���û��Լ�����ѡ��
		if (mode_jump == normal)
		{
			all_temp = Main_menu();  //�õ����˵���ѡ��ֵ

			main_menu_switch = (main_menu)all_temp;  //ö�����͵�ת��
		}

		//������Ծģʽ
		if (mode_jump == jump_to_third)
		{
			main_menu_switch = search_record;
		}

		

		//ִ����Ӽ�¼����1
		if (main_menu_switch == add_record)
		{
			while (1)
			{
				//��Ӽ�¼��صĹ���
				all_temp=Add_record_model_menu();   //��ʾ��Ӽ�¼ģʽ�˵�
				add_record_model_menu = (add_record_modei_menu)all_temp;
				if (add_record_model_menu == add_one)
				{
					Add_record_menu();         //��ʾ��Ӽ�¼�˵�

					//��ӵ�����¼����
					Add_one_record(1);
				}
				else if (add_record_model_menu == add_two)
				{
					Add_record_menu();         //��ʾ��Ӽ�¼�˵�

					//��Ӷ�����¼�Ĺ���
					Add_many_record();
				}
				else if (add_record_model_menu == add_from_file)
				{

					//���ļ���Ӽ�¼�Ĺ���
					Add_file_record();
				}
				

				//������¼
				all_temp = First_menu();
				first_menu_switch = (first_menu)all_temp;
				//������Ӽ�¼
				if (first_menu_switch == add_more)   continue;
				//�ص����˵�
				else if (first_menu_switch == first_exit_to_main)  break;			
			}
		}

		//ִ����ʾ��¼����2
		else if (main_menu_switch == show_record)
		{
			while (1)
			{
				//��ʾ��¼��صĹ���

				 //��ʾ��¼ģʽ�˵�
				all_temp=Show_record_mode_menu();    
				show_record_mode_menu = (enum show_record_mode_menu)all_temp;
				
				//����¼�������ʾ
				if(show_record_mode_menu== record_List)
				{
					//ѡ����ʾ����¼������
					all_temp = Material_menu();
					sec_sub = (material_menu)all_temp;
					//��ʾ����
					if (sec_sub == unit_price)
					{
						Show_related_record(sec_sub);
					}
					//��ʾ����
					else if (sec_sub == num)
					{
						Show_related_record(sec_sub);
					}
					//��ʾ������
					else if (sec_sub == person)
					{
						Show_related_record(sec_sub);
					}
					//��ʾ��ע
					else if (sec_sub == note)
					{
						Show_related_record(sec_sub);
					}
					//��ʾȫ���ļ�¼
					else if (sec_sub == all)
					{
						Show_related_record(sec_sub);
					}

					
				}


				//�ֿ��嵥�������ʾ
				else if (show_record_mode_menu == cangku_Item)
				{
					//��ʾ�ֿ��ȫ����Ʒ�嵥
					Show_Cangku_Item();

				}



				
				


				//��ʾ���¼
				all_temp = Second_menu();
				second_menu_switch = (second_menu)all_temp;
				//������Ӽ�¼
				if (second_menu_switch == show_more)   continue;
				//��ʾ���˵�
				else if (second_menu_switch == second_exit_to_main)  break;
			}
		}
		
		//ִ�в�ѯ��¼����3
		else if (main_menu_switch == search_record)
		{
			int search_mode = 0;  //��¼��ѯģʽ ��һ�Ρ�����������
			while (1)
			{
				if (mode_jump == normal)
				{
					//��ѯ��¼��صĹ���
					if (search_mode == 0)
					{
						//ѡ���ѯģʽ
						all_temp = Search_record_mode();

					}
				}

				//���޸�ģʽ��ת���ˣ����б���¼�Ĳ�ѯ
				else if (mode_jump == jump_to_third)
				{
					all_temp = 1;
				}
				
				
				//��ѯ����¼
				if (all_temp == 1)
				{
					//ѡ���ѯ�ı���¼������
					all_temp=Search_record_menu();
					third_sub = (enum material_menu)all_temp;


					//��ѯ����¼����
					if (search_mode == 0)
					{
						search_mode = First_search;
					}
					//���ձ�Ž��м���
					if (third_sub == seri_number)
					{
						Search_related_record(third_sub, search_mode);
					}

					//�������ƽ��м���
					if (third_sub == name)
					{
						Search_related_record(third_sub, search_mode);
					}

					//�������ڽ��м���
					if (third_sub == record_data)
					{
						Search_related_record(third_sub, search_mode);
					}

					//���ձ����˽��м���
					if (third_sub == person)
					{
						Search_related_record(third_sub, search_mode);
					}

					//���ձ�ע���м���
					if (third_sub == note)
					{
						Search_related_record(third_sub, search_mode);
					}

					

				}

				//��ѯ�ֿ���Ʒ��¼
				else if (all_temp == 2)
				{
					//��ѯ�ֿ���Ʒ��¼����
					Search_ku_item();

				}



				//��ѯ���¼
				all_temp = Third_menu();
				third_menu_switch = (third_menu)all_temp;
				
				//����ɸѡ
				if (third_menu_switch == conti_to_search)
				{
					if (all_temp == 1)
					{
						search_mode = Continue_search;
					}
					
				}
				
				//���²�ѯ
				else if (third_menu_switch == anew_search)
				{
					if (all_temp == 1)
					{
						search_mode = 0;
						Search_related_record(third_sub, Clear_list);   //��ղ�ѯ����
					}
					else if (all_temp == 2)
					{
						search_mode = 0;
					}
			
				}
				
				//�ص����˵�
				else if (third_menu_switch == third_exit_to_main)
				{
					//������Ծģʽ
					if (mode_jump == jump_to_third)
					{
						main_menu_switch = change_record;
						mode_jump = jump_to_forth;
					}
					break;
				}

			}
		}

		//ִ���޸ļ�¼����4
		else if (main_menu_switch == change_record)
		{
			int change_flag = 1;  //�޸ı�־λ
			while (1)
			{
				//�״ν����޸�ģʽ������ģʽѡ��
				if (mode_jump == normal)
				{
					//ѡ���޸�ģʽ
					all_temp = Forth_menu();
					forth_menu_switch = (forth_menu)all_temp;
				}

				//����Ծģʽ�Ӳ�ѯ��������Ͳ�������ѡ���޸�ģʽ
				else if (mode_jump!=normal)
				{
					forth_menu_switch = forth_menu_switch;  
				}
			
				if (forth_menu_switch == change_one)
				{
					while (1)
					{
						//�Ѿ��Ӳ�ѯģʽ�������ָ�����ģʽ
						if (mode_jump == jump_to_forth)
						{
							mode_jump = normal;
						}
						//ѯ���û���Ҫ�޸ĵľ���ı���¼  ִ����Ծģʽ
						else if (mode_jump != jump_to_third&& change_flag!=2&& change_flag!=3)
						{
							mode_jump = jump_to_third;
							break;
						}
						

						//��һ���޸ĵ�������¼
						if (change_flag == 1)
						{
								//�����ɲ�ѯģʽ�õ��ı���¼��λ�������еľ���λ��
							     
								//��������....................................
								
								cout << "���ҵ���Ҫ�޸ĵı���¼������" << endl;

								//ѡ��Ҫ�޸ĵĲ�������ֵ	
								all_temp = Change_record_menu();
								forth_sub = (material_menu)all_temp;

								system("cls");

								//ִ�е�һ���޸Ĺ���
								Change_record(forth_sub,1);

						}

						//�����޸ĸñ���¼
						else if (change_flag == 2)
						{
								//ѡ�����Ҫ�޸ĵĲ�������ֵ	
								all_temp = Change_record_menu();
								forth_sub = (material_menu)all_temp;
								Change_record(forth_sub,2);

								//����ִ���޸Ĺ���
						}

						else if (change_flag == 3)
						{
							//ִ���޸ĺ�������ʾ�Ĺ���
							Change_record(forth_sub, 3);
						}



						//�޸���ɺ� 
						
						all_temp = Forth_sub_menu();
						forth_sub_menu_switch = (forth_sub_menu)all_temp;
						if (forth_sub_menu_switch == continue_change)
						{
								change_flag = 2;
						}
						if (forth_sub_menu_switch == change_others)
						{
								change_flag = 1;
						}
						if (forth_sub_menu_switch == show_change_data)
						{
								change_flag = 3;
						}
						if (forth_sub_menu_switch == forth_exit_to_main)
						{
								break;    //�˳��޸�ģʽ
						}
					}

				}
				
				if (forth_menu_switch == change_together)
				{
					while (1)
					{
						//�����޸ı���¼

						//�Ѿ��Ӳ�ѯģʽ�������ָ�����ģʽ
						if (mode_jump == jump_to_forth)
						{
							mode_jump = normal;
						}
						//ѯ���û���Ҫ�޸ĵľ���ı���¼  ִ����Ծģʽ
						else if (mode_jump != jump_to_third && change_flag != 2 && change_flag != 3)
						{
							mode_jump = jump_to_third;
							break;
						}

						//��һ���޸ĵ�������¼
						if (change_flag == 1)
						{
							//ѡ��Ҫ�޸ĵĲ�������ֵ	
							all_temp = Change_record_menu();
							forth_sub = (material_menu)all_temp;

							//ִ�е�һ���޸Ĺ���

							Change_many_record(forth_sub,1);
						}

						//�����޸ĸñ���¼
						else if (change_flag == 2)
						{
							//ѡ�����Ҫ�޸ĵĲ�������ֵ	
							all_temp = Material_menu();
							forth_sub = (material_menu)all_temp;

							//����ִ���޸Ĺ���
							Change_many_record(forth_sub,2);
						}

						else if (change_flag == 3)
						{
							//ִ���޸ĺ�������ʾ�Ĺ���
							Change_many_record(forth_sub,3);

						}


						//�޸���ɺ�
						all_temp = Forth_sub_menu();
						forth_sub_menu_switch = (forth_sub_menu)all_temp;
						if (forth_sub_menu_switch == continue_change)
						{
							change_flag = 2;
						}
						if (forth_sub_menu_switch == change_others)
						{
							change_flag = 1;
						}
						if (forth_sub_menu_switch == show_change_data)
						{
							change_flag = 3;
						}
						if (forth_sub_menu_switch == forth_exit_to_main)
						{
							break;  //�˳��޸�ģʽ
						}
					}
				}
				
				break;  //�˻������˵�
			}
		}

		//ִ��д���ļ�����5
		else if (main_menu_switch == write_file)
		{
			while (1)
			{
				//д���ļ���صĹ���

				//ѡ��д�����¼���ǲֿ���Ʒ�嵥
				all_temp=Write_record_ku_menu();

				//�������¼
				if (all_temp == 1)
				{
					Write_in_file(1);
				}
				//����ֿ���Ʒ�嵥
				else if (all_temp == 2)
				{
					Write_in_file(2);
				}

				//д����ɺ�
				all_temp = Fifth_menu();
				fifth_menu_switch = (fifth_menu)all_temp;
				
				//�ļ����Ϊ����λ��
				if (fifth_menu_switch == save_to_other)  continue;
				//�ص����˵�
				else if (fifth_menu_switch == fifth_exit_to_main)  break;

			}
		}

		//ִ���˳�ϵͳ����
		else if (main_menu_switch == exit_out)
		{
			struct material* pp = base_head->next;  //���ڱ�������¼
			char address[100];
			strcpy(address, "C:\\Users\\31711\\Desktop\\�߼�������ƴ���ҵ\\ϵͳ��ʷ����.txt");
			outfile.open(address);
			for (int i = 0; i < sum_record; i++)
			{
				if (strcmp(pp->in_out, "���") == 0)
				{
					outfile << pp->in_out << setw(8) << pp->seri_number << setw(8) << pp->name << setw(8) << pp->unit_price << setw(8) << pp->in_num
						<< setw(8) << pp->in_time.year << " " << pp->in_time.month << " " << pp->in_time.day << " "
						<< setw(8) << pp->person << setw(8) << pp->note << endl;
				}

				if (strcmp(pp->in_out, "����") == 0)
				{
					outfile << pp->in_out << setw(8) << pp->seri_number << setw(8) << pp->name << setw(8) << pp->unit_price << setw(8) << pp->out_num
						<< setw(8) << pp->out_time.year << " " << pp->out_time.month << " " << pp->out_time.day << " " << setw(8)
						<< pp->person << setw(8) << pp->note << endl;
				}
				pp = pp->next;
			}
			outfile << "ok" << endl;
			outfile.close();
			cout << "ϵͳ�����ѱ���" << endl;
			exit(0);
		}		

	}
	return 0;
}


/*-----------------------�˵�����---------------------------*/

//��ʾ���˵�  //����ֵ��ѡ��Ĳ˵�ֵ
int Main_menu()
{
	cout << "/*---------���˵�------------*/" << endl;
	cout << "1.��Ӽ�¼" << endl;
	cout << "2.��ʾ��¼" << endl;
	cout << "3.��ѯ��¼" << endl;
	cout << "4.�޸ļ�¼" << endl;
	cout << "5.д���ļ�" << endl;
	cout << "6.�˳�ϵͳ" << endl;
	cout << "/*--------------------------*/" << endl;
	cout << "��������Ҫִ�еĹ��ܣ�" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}

//��ʾ��һ���Ӳ˵�    //����ֵ��ѡ��Ĳ˵�ֵ
int First_menu()
{
	cout << "/*---------�Ӳ˵�1------------*/" << endl;
	cout << "1.��Ӹ����¼"<< endl;
	cout << "2.�������˵�" << endl;
	cout << "/*--------------------------*/" << endl;
	cout << "��������Ҫִ�еĹ��ܣ�" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}

//��ʾ��Ӽ�¼ģʽ�˵�
int Add_record_model_menu()
{
	cout << "1.��ӵ�����¼" << endl;
	cout << "2.��Ӷ�����¼" << endl;
	cout << "3.���ļ���Ӽ�¼" << endl;
	cout << "��ѡ����Ӽ�¼��ģʽ��" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;

}

//��ʾ��Ӽ�¼�˵�
void Add_record_menu()
{
	cout << "�밴�����µĸ�ʽ�������¼������" << endl;
	cout << "��/���|���|����|����|��/�����|��/���ʱ�䡾��.��.�ա�|������|��ע" << endl;
}


//��ʾ�ڶ����Ӳ˵�    //����ֵ��ѡ��Ĳ˵�ֵ
int Second_menu()
{
	cout << "/*---------�Ӳ˵�2------------*/" << endl;
	cout << "1.��ʾ����ļ�¼" << endl;
	cout << "2.�������˵�" << endl;
	cout << "/*--------------------------*/" << endl;
	cout << "��������Ҫִ�еĹ��ܣ�" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}

//��ʾ��¼ģʽ�˵�
int Show_record_mode_menu()
{
	cout << "1.��ʾ����¼" << endl;
	cout << "2.��ʾ�ֿ��嵥" << endl;
	cout << "������Ҫ��ʾ��¼�����ͣ�" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}

//��ʾ�������Ӳ˵�    //����ֵ��ѡ��Ĳ˵�ֵ
int Third_menu()
{
	cout << "/*---------�Ӳ˵�3------------*/" << endl;
	cout << "1.����ɸѡ(��ʾ:����ѯ����¼����ʹ�øù��ܣ�)" << endl;
	cout << "2.���²�ѯ" << endl;
	cout << "3.�������˵�" << endl;
	cout << "/*--------------------------*/" << endl;
	cout << "��������Ҫִ�еĹ��ܣ�" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}

//��ʾ��ѯģʽ�˵�  //��ѯ����¼���ǲֿ���Ʒ
int Search_record_mode()
{
	cout << "1.��ѯ����¼" << endl;
	cout << "2.��ѯ�ֿ���Ʒ" <<endl;
	cout << "��ѡ���ѯģʽ: " << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}

//��ʾѡ���ѯ����¼���ԵĲ˵�
int Search_record_menu()
{
	cout << "1.���" << endl;
	cout << "2.����" << endl;
	cout << "3.����" << endl;
	cout << "4.������" << endl;
	cout << "5.��ע"<<endl;
	cout << "������ɸѡ����: " << endl;
	int temp;
	cin >> temp;
	switch (temp)
	{
		case 1:
			temp = 1; break;
		case 2:
			temp = 2; break;
		case 3:
			temp = 6; break;
		case 4:
			temp = 4; break;
		case 5:
			temp = 7; break;
	}
	system("cls");
	return temp;
}

//��ʾ���ĸ��Ӳ˵�    //����ֵ��ѡ��Ĳ˵�ֵ
int Forth_menu()
{
	cout << "/*---------�Ӳ˵�4------------*/" << endl;
	cout << "1.�޸ĵ�������¼" << endl;
	cout << "2.�����޸ı���¼" << endl;
	cout << "/*--------------------------*/" << endl;
	cout << "��������Ҫִ�е��޸�ģʽ��" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}


//��ʾ�������Բ˵�(��)    //����ֵ��ѡ��Ĳ˵�ֵ
int Material_menu()
{
	int temp;

		cout << "/*---------����¼���ϵ����Բ˵�------------*/" << endl;
		cout << "1.����" << endl;
		cout << "2.����" << endl;
		cout << "3.������" << endl;
		cout << "4.��ע" << endl;
		cout << "5.ȫ����ʾ" << endl;
		cout << "��������Ҫѡ��Ĳ��ϵ�����:" << endl;
		cin >> temp;
		switch (temp)
		{
			case 1:
				temp = 3; break;
			case 2:
				temp = 8; break;
			case 3:
				temp = 4; break;
			case 4:
				temp = 7; break;
			case 5:
				temp = 9; break;
		
		}
	system("cls");
	return temp;
}

//��ʾ�޸Ĳ������Բ˵�
int Change_record_menu()
{
	cout << "��ѡ����Ҫ�޸ĵı���¼�����ԣ�" << endl;
	cout << "1.���" << endl;
	cout << "2.����" << endl;
	cout << "3.����" << endl;
	cout << "4.������¼" << endl;
	cout << "5.�����/������" << endl;
	cout << "6.���/����ʱ��" << endl;
	cout << "7.������" << endl;
	cout << "8.��ע" << endl;
	cout << "9.ȫ���޸�" << endl;
	int temp;
	cin >> temp;
	switch (temp)
	{
	case 1:
		temp = 1; break;
	case 2:
		temp = 2; break;
	case 3:
		temp = 3; break;
	case 4:
		temp = 5; break;
	case 5:
		temp = 12; break;
	case 6:
		temp = 6; break;
	case 7:
		temp = 4; break;
	case 8:
		temp = 7; break;
	case 9:
		temp = 11; break;
	}
	return temp;
}



//��ʾ���ĸ��Ӳ˵����Ӳ˵�      //����ֵ��ѡ��Ĳ˵�ֵ
int Forth_sub_menu()
{
	cout << "/*---------���Ӳ˵�2------------*/" << endl;
	cout << "1.�����޸ı���¼��������" << endl;
	cout << "2.�޸���������¼" << endl;
	cout << "3.��ʾ�޸ĺ������" << endl;
	cout << "4.�������˵�" << endl;
	cout << "/*--------------------------*/" << endl;
	cout << "��������Ҫִ�еĹ��ܣ�" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}

//��ʾ������Ӳ˵�    //����ֵ��ѡ��Ĳ˵�ֵ
int Fifth_menu()
{
	cout << "/*---------�Ӳ˵�5------------*/" << endl;
	cout << "1.���浽�����ĵط�" << endl;
	cout << "2.�������˵�" << endl;
	cout << "/*--------------------------*/" << endl;
	cout << "��������Ҫִ�еĹ��ܣ�" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}

//��ʾд���ļ�ģʽ�˵�  ����¼���ǲֿ���Ʒ�嵥
int Write_record_ku_menu()
{
	cout << "��������Ҫ�洢����¼���ǲֿ��¼"<<endl;
	cout << "1.�������¼" << endl;
	cout << "2.����ֿ��¼" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}

//��ʾ���ϳ�ʼ��ģʽ�˵�      //����ֵ��ѡ��Ĳ˵�ֵ
int material_base_menu()
{
	cout << "/*---------����ʼ��ģʽ�˵�------------*/" << endl;
	cout << "1.�ļ�����" << endl;
	cout << "2.�ֶ�����" << endl;
	cout << "3.����ʹ��֮ǰ����" << endl;
	cout << "/*--------------------------*/" << endl;
	cout << "������Ҫѡ���ı���ʼ��ģʽ��" << endl;
	int temp;
	cin >> temp;
	system("cls");
	return temp;
}


/*-----------------------�⺯��---------------------------*/

//��������¼����������  ����ͷ��㣩
struct material* Creat_ku()  
{
	int flag = 0;  //�����ͱ�־
	int n = 0;     //�����жϽ����
	struct material* head = NULL;  //ͷָ��
	struct material* p1 = NULL;    //���ڲ��ϵش����µĽ��
	struct material* p2 = NULL;    //����ָ�����������һ�����
	head = (struct material*)malloc(sizeof(material));
	head->next = NULL;
	cout << "�Ƿ����յı�?����--1/��--0��"<<endl;
	cin >> flag;
	system("cls");
	//�����յı�
	if (flag == 1)
	{
		sum_record = 0;
		return head;
	}

	//�����еļ�¼�����
	else if (flag == 0)
	{
		all_temp=material_base_menu();
		Base_init = (material_Base_init)all_temp;

		//�ļ������ʼ����
		if (Base_init == file_in)
		{
			char address[100];
			cout << "�������ȡ�ļ���λ��: " << endl;
			cin >> address;
			infile.open(address);
			for (int i = 0;; i++)    //���ص�
			{
				p1 = (struct material*)malloc(sizeof(material));
				infile >> p1->in_out;
				if (strcmp(p1->in_out, "ok") == 0)
				{
					system("cls");
					break;
				}

				//����¼
				if (strcmp(p1->in_out, "���") == 0)
				{
					infile >> p1->seri_number >> p1->name >> p1->unit_price >> p1->in_num >> p1->in_time.year >> p1->in_time.month >> p1->in_time.day >> p1->person >> p1->note;
				}
				//�����¼
				else
				{
					infile >> p1->seri_number >> p1->name >> p1->unit_price >> p1->out_num >> p1->out_time.year >> p1->out_time.month >> p1->out_time.day >> p1->person >> p1->note;
				}

				n++;
				sum_record++;
				if (n == 1)
				{
					head->next = p1;
				}
				else
				{
					p2->next = p1;
				}
				p2 = p1;	
			}
			if (sum_record != 0)
				p2->next = NULL;

			infile.close();
			cout << "�ļ�������ɣ���" << endl;
			
			return head;

		}

		//�ֶ������ʼ����
		else if (Base_init == handwrite)
		{
			bool error=0;  //��ʾ��ǰ���Ƿ��д���

			cout << "���������¼��" << endl;
			cout << "��/���|���|����|����|��/�����|��/���ʱ�䡾��.��.�ա�|������|��ע"<<endl;
			cout << "**����ok��������¼�����**"<<endl;


			for (int i = 0;; i++)    //���ص�
			{
				p1 = (struct material*)malloc(sizeof(material));
				cin >> p1->in_out;
				if (strcmp(p1->in_out, "ok") == 0)
				{
					system("cls");
					break;
				}
				
					//����¼
					if (strcmp(p1->in_out, "���") == 0)
					{
						cin >> p1->seri_number >> p1->name >> p1->unit_price >> p1->in_num >> p1->in_time.year >> p1->in_time.month >> p1->in_time.day >> p1->person >> p1->note;
					}
					//�����¼
					else
					{
						cin >> p1->seri_number >> p1->name >> p1->unit_price >> p1->out_num >> p1->out_time.year >> p1->out_time.month >> p1->out_time.day >> p1->person >> p1->note;
					}


					//�������ݵ���Ч��
					if (strcmp(p1->in_out, "���") != 0 && strcmp(p1->in_out, "����") != 0)
					{
						cout << "Error::	**δ��������ⷽʽ**  ��������¼�����Ч������" << endl;
						cout << "�����������Ч����¼ �� ����ok����" << endl;
						error = 1;
					}
					else if (strcmp(p1->in_out, "���") == 0)
					{
						if (p1->in_time.year < 0
							|| p1->in_time.month < 0
							|| p1->in_time.month>12
							|| p1->in_time.day < 1
							|| p1->in_time.day>31)
						{
							cout << "Error::	*���ڸ�ʽ����**  ��������¼�����Ч������" << endl;
							cout << "�����������Ч����¼ �� ����ok����" << endl;
							error = 1;
						}

						if (p1->in_num < 0)
						{
							cout << "Error::	*���ϵ���������Ϊ��ֵ**  ��������¼�����Ч������" << endl;
							cout << "�����������Ч����¼ �� ����ok����" << endl;
							error = 1;
						}


						if (p1->unit_price < 0)
						{
							cout << "Error::	*���ϵĵ��۲���Ϊ��ֵ**  ��������¼�����Ч������" << endl;
							cout << "�����������Ч����¼ �� ����ok����" << endl;
							error = 1;
						}


					}
					else if (strcmp(p1->in_out, "����") == 0)
					{
						if (p1->out_time.year < 0
							|| p1->out_time.month < 0
							|| p1->out_time.month>12
							|| p1->out_time.day < 1
							|| p1->out_time.day>31)
						{
							cout << "Error::	*���ڸ�ʽ����**  ��������¼�����Ч������" << endl;
							cout << "�����������Ч����¼ �� ����ok����" << endl;
							error = 1;
						}

						if (p1->out_num < 0)
						{
							cout << "Error::	*���ϵ���������Ϊ��ֵ**  ��������¼�����Ч������" << endl;
							cout << "�����������Ч����¼ �� ����ok����" << endl;
							error = 1;
						}


						if (p1->unit_price < 0)
						{
							cout << "Error::	*���ϵĵ��۲���Ϊ��ֵ**  ��������¼�����Ч������" << endl;
							cout << "�����������Ч����¼ �� ����ok����" << endl;
							error = 1;
						}

					}


					//��������д��������ʾ��Ϣ
					if (error == 1)
					{
						Delay(2000);
						
					}


					//���ü�¼�洢������
					if (error == 0)
					{
						n++;
						sum_record++;
						if (n == 1)
						{
							head->next = p1;
						}
						else
						{
							p2->next = p1;
						}
						p2 = p1;
					}
				error = 0;
			}
			if (sum_record != 0)
				p2->next = NULL;

			
			return head;
		}

		else if (Base_init == continue_to_use)
		{
			char address[100];  //ϵͳ��ʷ���ݱ���λ��
			strcpy(address, "C:\\Users\\31711\\Desktop\\�߼�������ƴ���ҵ\\ϵͳ��ʷ����.txt");
			infile.open(address);
			for (int i = 0;; i++)    //���ص�
			{
				p1 = (struct material*)malloc(sizeof(material));
				infile >> p1->in_out;
				if (strcmp(p1->in_out, "ok") == 0)
				{
					system("cls");
					break;
				}

				//����¼
				if (strcmp(p1->in_out, "���") == 0)
				{
					infile >> p1->seri_number >> p1->name >> p1->unit_price >> p1->in_num >> p1->in_time.year >> p1->in_time.month >> p1->in_time.day >> p1->person >> p1->note;
				}
				//�����¼
				else
				{
					infile >> p1->seri_number >> p1->name >> p1->unit_price >> p1->out_num >> p1->out_time.year >> p1->out_time.month >> p1->out_time.day >> p1->person >> p1->note;
				}

				n++;
				sum_record++;
				if (n == 1)
				{
					head->next = p1;
				}
				else
				{
					p2->next = p1;
				}
				p2 = p1;
			}
			if (sum_record != 0)
				p2->next = NULL;

			infile.close();
			cout << "��ʷ���ݶ�����ɣ���" << endl;

			return head;
		}
	}

	
}


//�������¼   ����˵���� mode����������ģʽ 1-���ԭʼ�� 2-�����ѯ�����¼
void print_ori(struct material* head,int mode)
{
	int number = 0;
	struct material* pp = head->next;
	//������ı�����
	cout << "��/���|���|����|����|��/�����|��/���ʱ�䡾��.��.�ա�|������|��ע" << endl;

	if (mode == 1)         //��ʾԭʼ�ı���¼
	{
		number = sum_record;
	}
	else if (mode == 2)    //��ʾ��ѯ����
	{
		number = sum_search;
	}


	for (int i = 0; i < number; i++)
	{
		//��ν������������Ű�����???

		if (strcmp(pp->in_out,"���") == 0)
		{
			cout<<setw(5)<< pp->in_out << setw(5) << pp->seri_number << setw(5) << pp->name << setw(6) << pp->unit_price << setw(5) << pp->in_num << setw(5)
				<< pp->in_time.year << "��"  << pp->in_time.month << "��" << pp->in_time.day << "��" << setw(8)
				<< pp->person << setw(8) << pp->note << endl;
		}

		if (strcmp(pp->in_out, "����") == 0)
		{
			cout << setw(5) << pp->in_out << setw(5) << pp->seri_number << setw(5) << pp->name << setw(6) << pp->unit_price << setw(5) << pp->out_num << setw(5)
				<< pp->out_time.year << "��" << pp->out_time.month << "��" << pp->out_time.day << "��"<<setw(8)
				<< pp->person << setw(8) << pp->note << endl;
		}

		pp = pp->next;
	}
}


//������Ʒ�Ĳֿ�(����һ��ͷ���)
struct material* Creat_Item_List()
{
	struct material* sec_head = NULL;  //�ֿ��ͷָ��
	struct material* p1 = NULL; 
	sec_head = (struct material*)malloc(sizeof(material));
	sec_head->next = NULL;
	sum_item = 0;
	cout << "�ղֿ⽨����ɣ���" << endl;
	Delay(1500);
	return sec_head;
}


//����ֿ����Ʒ
void Print_ku(struct material* thi_head)
{
	struct material* pp = thi_head->next;
	for (int i = 0; i < sum_item; i++)
	{
		cout << pp->seri_number << " " << pp->name << " " << pp->store_num << " "<<endl;
		pp = pp->next;
	}
}

//��������໥��ֵ  ��p2��ֵ��p1
void Copy_node_to_node(struct material* p1, struct material* p2);


/*-----------------------���ܺ���---------------------------*/


//����¼�����ʼ�����ֿ���Ʒ���ࡿ
void Handout_ku_init(struct material* head, struct material* sec_head)
{
	struct material* record_head = head;
	struct material* cangku_head = sec_head;
	
	for (int i = 0; i < sum_record; i++)
	{
		record_head = record_head->next;   //��һ���ı���¼

		//���ñ���¼�����ݷ���ֿ���Ʒ��
		Join_record(record_head,sec_head,0);		
	}
}

//��ĳ�����¼���¼�¼������
void Join_to_record_List(struct material* new_record,struct material* record_List)
{
	struct material* record_head_temp = record_List;
	//�ҵ��������һ����¼
	for (int i = 0; i < sum_record; i++)
	{
		record_head_temp = record_head_temp->next;
	}

	//���ü�¼��ӵ�����
	record_head_temp->next = new_record;
	new_record->next = NULL;

	//����¼����һ
	sum_record++;	
}

//��ĳ�����¼���µ��ֿ���Ʒ��  ����ֵ 1-���ݴ���
int Join_record(struct material* now_record, struct material* sec_head,int mode)
{
	struct material* cangku_head = sec_head;
	int flag = 0;      //�ֿ�����Ʒ�ı�־λ
	for (int i = 0; i < sum_item;i++)
	{
		cangku_head = cangku_head->next;  //�����ֿ��е���Ʒ

		//�ñ���¼�ǲֿ������е���Ʒ
		if (strcmp(cangku_head->seri_number,now_record->seri_number) == 0
			&& strcmp(cangku_head->name, now_record->name) == 0)
		{
			//��Ʒ�������
			if (strcmp(now_record->in_out, "���") == 0)
			{
				cangku_head->store_num += now_record->in_num;
			}

			//��Ʒ���г���  **��Ҫ���Ǹ���Ʒ�������Ƿ񹻳����
			else
			{
				//���ڱ���¼�ĳ�ʼ������ӵ�����¼
				if (mode == 0)
				{
					//����ֿ��и���Ʒ�����Ļ�
					if (cangku_head->store_num < now_record->out_num)
					{
						cout << "Error::��������¼�ڸ��µ��ֿ�ʱ����" << endl;
						cout << "�ֿ���" << cangku_head->name << "��������" << "   ";
						if (cangku_head->store_num < 0)  cangku_head->store_num = 0;
						cout << "�ֿ���" << cangku_head->name << "ʣ������: " << cangku_head->store_num << endl;
						cout << "��ѡ�� ���ϸü�¼(1)-��-���ٳ�����(2)" << endl;
						int temp;
						cin >> temp;

						//���ϸü�¼
						if (temp == 1)
						{
							now_record->out_num = 0;
							cout << "��¼������!!!";
							Delay(1500);
							system("cls");
							return 31;
						}
						//�������������
						if (temp == 2)
						{
							cout << "�������޸ĺ�ĳ�����" << endl;
							cin >> now_record->out_num;
							cangku_head->store_num -= now_record->out_num;
							cout << "���ĺ�ı���¼������!!!" << endl;
							Delay(1500);
							system("cls");
						}
					}
					else
						cangku_head->store_num -= now_record->out_num;
				}
				//������Ӷ�����¼���ļ���¼
				if (mode == 1)
				{
					//����ֿ��и���Ʒ�����Ļ�
					if (cangku_head->store_num < now_record->out_num)
					{
						cout << "Error::��������¼�ڸ��µ��ֿ�ʱ����" << endl;
						cout << "�ֿ���" << cangku_head->name << "��������" << "   ";
						if (cangku_head->store_num < 0)  cangku_head->store_num = 0;
						cout << "�ֿ���" << cangku_head->name << "ʣ������: " << cangku_head->store_num << endl;
						return 1;    //���������
					}
					else
						cangku_head->store_num -= now_record->out_num;
					
				}
			}

			flag = 1;
			break;
		}
	}
	//���û�ҵ�����Ʒ���½���Ʒ
	if (flag == 0)
	{
		
		cangku_head = sec_head;
		
		//�ҵ�β���
		for (int i = 0; i < sum_item; i++)
		{
			if(sum_item!=0)
			cangku_head = cangku_head->next;
		}

		struct material* p0;
		p0 = (struct material*)malloc(sizeof(material));
		strcpy(p0->seri_number, now_record->seri_number); //��Ÿ�ֵ
		strcpy(p0->name,now_record->name);                //���Ƹ�ֵ

		//��Ʒ�������
		if (strcmp(now_record->in_out, "���") == 0)
		{
			p0->store_num = now_record->in_num;
		}

		//��Ʒ���г���--������
		else if (strcmp(now_record->in_out, "����") == 0)
		{
			//��ʼ��
			if (mode == 0)
			{
				cout << "Error::��������¼�ڸ��µ��ֿ�ʱ����" << endl;
				cout << "�ֿ���û��" << now_record->name << "��һ��Ʒ" << endl;
				cout << "��ѡ�� ���ϸü�¼(1)����ĸ�����¼(2)" << endl;

				int temp;
				cin >> temp;

				//���ϸü�¼
				if (temp == 1)
				{
					now_record->out_num = 0;
					cout << "��¼������!!!";
					Delay(1500);	
					system("cls");
					return 3;
				}
				//�������������
				if (temp == 2)
				{
					cout << "ԭ����¼Ϊ:" << endl;
					if (strcmp(now_record->in_out, "���") == 0)
					{
						cout << now_record->in_out << " " << now_record->seri_number << " " << now_record->name << " " << now_record->unit_price << " " << now_record->in_num << " "
							<< now_record->in_time.year << "��" << now_record->in_time.month << "��" << now_record->in_time.day << "��" << " "
							<< now_record->person << " " << now_record->note << endl;
					}

					if (strcmp(now_record->in_out, "����") == 0)
					{
						cout << now_record->in_out << " " << now_record->seri_number << " " << now_record->name << " " << now_record->unit_price << " " << now_record->out_num << " "
							<< now_record->out_time.year << "��" << now_record->out_time.month << "��" << now_record->out_time.day << "��" << " "
							<< now_record->person << " " << now_record->note << endl;
					}
					cout << "����������ñ���¼:" << endl;
					cin >> now_record->in_out;
					//����¼
					if (strcmp(now_record->in_out, "���") == 0)
					{
						cin >> now_record->seri_number >> now_record->name >> now_record->unit_price
							>> now_record->in_num >> now_record->in_time.year >> now_record->in_time.month
							>> now_record->in_time.day >> now_record->person >> now_record->note;
						p0->store_num = now_record->in_num;
					}


					cout << "���ĺ�ı���¼������!!!" << endl;
					Delay(1500);
					system("cls");
				}

			}
			//��ӹ���
			if (mode == 1)
			{
				cout << "Error::��������¼�ڸ��µ��ֿ�ʱ����" << endl;
				cout << "�ֿ���û��" << now_record->name << "��һ��Ʒ" << endl;				
				return 2;
			}

		}

		cangku_head->next = p0;
		p0->next = NULL;
		sum_item++;
	}
	return 0;
}


//��ӵ�����¼�����кͲֿ���   ����ֵ�жϵ�����¼�����Ƿ����  0-���� 1-������� 2-������� 3-�ļ����
int Add_one_record(int mode)
{
	if (mode == 1)
	{
		int error = 0;
		struct material* new_one;
		new_one = (struct material*)malloc(sizeof(material));
		cin >> new_one->in_out;

		//����¼
		if (strcmp(new_one->in_out,"���") == 0)
		{
			cin >> new_one->seri_number >> new_one->name >> new_one->unit_price >> new_one->in_num >> new_one->in_time.year >> new_one->in_time.month >> new_one->in_time.day >> new_one->person >> new_one->note;
		}
		//�����¼
		else
		{
			cin >> new_one->seri_number >> new_one->name >> new_one->unit_price >> new_one->out_num >> new_one->out_time.year >> new_one->out_time.month >> new_one->out_time.day >> new_one->person >> new_one->note;
		}

		//��¼��ʽ���
		if (strcmp(new_one->in_out, "���") != 0 && strcmp(new_one->in_out, "����") != 0)
		{
			cout << "Error::	**δ��������ⷽʽ**  ��������¼�����Ч������" << endl;
			error = 1;
		}
		else if (strcmp(new_one->in_out, "���") == 0)
		{
			if (new_one->in_time.year < 0
				|| new_one->in_time.month < 0
				|| new_one->in_time.month>12
				|| new_one->in_time.day < 1
				|| new_one->in_time.day>31)
			{
				cout << "Error::	*���ڸ�ʽ����**  ��������¼�����Ч������" << endl;
				error = 1;
			}

			if (new_one->in_num < 0)
			{
				cout << "Error::	*���ϵ���������Ϊ��ֵ**  ��������¼�����Ч������" << endl;
				error = 1;
			}


			if (new_one->unit_price < 0)
			{
				cout << "Error::	*���ϵĵ��۲���Ϊ��ֵ**  ��������¼�����Ч������" << endl;
				error = 1;
			}


		}
		else if (strcmp(new_one->in_out, "����") == 0)
		{
			if (new_one->out_time.year < 0
				|| new_one->out_time.month < 0
				|| new_one->out_time.month>12
				|| new_one->out_time.day < 1
				|| new_one->out_time.day>31)
			{
				cout << "Error::	*���ڸ�ʽ����**  ��������¼�����Ч������" << endl;
				error = 1;
			}

			if (new_one->out_num < 0)
			{
				cout << "Error::	*���ϵ���������Ϊ��ֵ**  ��������¼�����Ч������" << endl;
				error = 1;
			}


			if (new_one->unit_price < 0)
			{
				cout << "Error::	*���ϵĵ��۲���Ϊ��ֵ**  ��������¼�����Ч������" << endl;
				error = 1;
			}

		}


		//��������д��������ʾ��Ϣ
		if (error == 1)
		{
			Delay(3500);
			system("cls");
		}

		

		if (error == 0)
		{
			//���ü�¼��ӵ�����
			Join_to_record_List(new_one, base_head);

			int ok_flag = 1;
			//���ü�¼���µ��ֿ���
			ok_flag=Join_record(new_one, ku_head,0);
			if(ok_flag==0)
			cout << "������¼�����ɣ�����";
			Sleep(1500);
			system("cls");
		}
		
		
		return 1;
	}
	else if (mode == 2)
	{
		
		for (int i=0;;i++)
		{
			int error = 0;
			struct material* new_one;
			new_one = (struct material*)malloc(sizeof(material));
			cin >> new_one->in_out;


			if (strcmp(new_one->in_out,"ok") == 0)
			{
				break;
			}	
			//����¼
			else if (strcmp(new_one->in_out,"���") == 0)
			{
				cin >> new_one->seri_number >> new_one->name >> new_one->unit_price >> new_one->in_num >> new_one->in_time.year >> new_one->in_time.month >> new_one->in_time.day >> new_one->person >> new_one->note;
			}
			//�����¼
			else 
			{
				cin >> new_one->seri_number >> new_one->name >> new_one->unit_price >> new_one->out_num >> new_one->out_time.year >> new_one->out_time.month >> new_one->out_time.day >> new_one->person >> new_one->note;
			}
			//��¼��ʽ���
			if (strcmp(new_one->in_out, "���") != 0 && strcmp(new_one->in_out, "����") != 0)
			{
				cout << "Error::	**δ��������ⷽʽ**  ��������¼�����Ч������" << endl;
				error = 1;
			}
			else if (strcmp(new_one->in_out, "���") == 0)
			{
				if (new_one->in_time.year < 0
					|| new_one->in_time.month < 0
					|| new_one->in_time.month>12
					|| new_one->in_time.day < 1
					|| new_one->in_time.day>31)
				{
					cout << "Error::	*���ڸ�ʽ����**  ��������¼�����Ч������" << endl;
					error = 1;
				}

				if (new_one->in_num < 0)
				{
					cout << "Error::	*���ϵ���������Ϊ��ֵ**  ��������¼�����Ч������" << endl;
					error = 1;
				}


				if (new_one->unit_price < 0)
				{
					cout << "Error::	*���ϵĵ��۲���Ϊ��ֵ**  ��������¼�����Ч������" << endl;
					error = 1;
				}


			}
			else if (strcmp(new_one->in_out, "����") == 0)
			{
				if (new_one->out_time.year < 0
					|| new_one->out_time.month < 0
					|| new_one->out_time.month>12
					|| new_one->out_time.day < 1
					|| new_one->out_time.day>31)
				{
					cout << "Error::	*���ڸ�ʽ����**  ��������¼�����Ч������" << endl;
					error = 1;
				}

				if (new_one->out_num < 0)
				{
					cout << "Error::	*���ϵ���������Ϊ��ֵ**  ��������¼�����Ч������" << endl;
					error = 1;
				}


				if (new_one->unit_price < 0)
				{
					cout << "Error::	*���ϵĵ��۲���Ϊ��ֵ**  ��������¼�����Ч������" << endl;
					error = 1;
				}

			}
			if (error == 1)
			{
				cout << endl;
			}
			else if (error == 0)
			{
				//���ü�¼��ӵ�����
				Join_to_record_List(new_one, base_head);

				int wrong_flag = 0;
				//���ü�¼���µ��ֿ���
				wrong_flag=Join_record(new_one, ku_head,1);  //��¼���µ��ֿ�ʱ���������⣬����ֱ�Ӿ���һ����
				
				//��¼���µ��ֿ������
				//(�ֿ��и���Ʒ��������)
				while(wrong_flag == 1)
				{
					cout << "��ѡ�� ���ϸü�¼(1)-��-���ٳ�����(2)" << endl;
					int temp;
					cin >> temp;
					//���ϸü�¼
					if (temp == 1)
					{
						new_one->out_num = 0;
						cout << "��¼������!!!" << endl;
						Delay(1500);
						wrong_flag = 0;
						cout << "�������Ӽ�¼������ok����:" << endl;
					}
					//�������������
					if (temp == 2)
					{
						cout << "�������޸ĵĳ�����:" << endl;
						cin >> new_one->out_num;
						wrong_flag = Join_record(new_one, ku_head, 1);
						if (wrong_flag == 0)
						{
							cout << "���ĺ�ı���¼������!!!" << endl;	
							cout << "�������Ӽ�¼������ok����:" << endl;
						}
						
						
					}
					
				}
				//�ֿ���û�и���Ʒ���޷�����
				while (wrong_flag == 2)
				{
					cout << "��ѡ�� ���ϸü�¼(1)����ĸ�����¼(2)" << endl;
					int temp;
					cin >> temp;
					//���ϸü�¼
					if (temp == 1)
					{
						new_one->out_num = 0;
						cout << "��¼������!!!" << endl;
						Delay(1500);
						wrong_flag = 0;
						cout << "�������Ӽ�¼������ok����:" << endl;
					}
					//�������������
					if (temp == 2)
					{
						cout << "����������ñ���¼:" << endl;
						//��������
						cin >> new_one->in_out;
						//����¼
						if (strcmp(new_one->in_out, "���") == 0)
						{
							cin >> new_one->seri_number >> new_one->name >> new_one->unit_price >> new_one->in_num >> new_one->in_time.year >> new_one->in_time.month >> new_one->in_time.day >> new_one->person >> new_one->note;
						}
						//�����¼
						else
						{
							cin >> new_one->seri_number >> new_one->name >> new_one->unit_price >> new_one->out_num >> new_one->out_time.year >> new_one->out_time.month >> new_one->out_time.day >> new_one->person >> new_one->note;
						}
						wrong_flag = Join_record(new_one, ku_head, 1);
						if (wrong_flag == 0)
						{
							cout << "���ĺ�ı���¼������!!!" << endl;
							cout << "�������Ӽ�¼������ok����:" << endl;
						}
					}
					
				}
				
			}
			
		}
		Delay(2000);
		return 2;
	}
	//�ļ�����
	if (mode == 3)
	{
		char address[100];
		cout << "�������ȡ�ļ���λ��: " << endl;
		cin >> address;
		infile.open(address);
		for (int i = 0;; i++)
		{
			int error = 0;
			struct material* new_one;
			new_one = (struct material*)malloc(sizeof(material));
			infile >> new_one->in_out;

			if (strcmp(new_one->in_out, "ok") == 0)
			{
				break;
			}
			//����¼
			else if (strcmp(new_one->in_out, "���") == 0)
			{
				infile >> new_one->seri_number >> new_one->name >> new_one->unit_price >> new_one->in_num >> new_one->in_time.year >> new_one->in_time.month >> new_one->in_time.day >> new_one->person >> new_one->note;
			}
			//�����¼
			else
			{
				infile >> new_one->seri_number >> new_one->name >> new_one->unit_price >> new_one->out_num >> new_one->out_time.year >> new_one->out_time.month >> new_one->out_time.day >> new_one->person >> new_one->note;
			}

			//���ü�¼��ӵ�����
			Join_to_record_List(new_one, base_head);

			int wrong_flag = 0;
			//���ü�¼���µ��ֿ���
			wrong_flag = Join_record(new_one, ku_head, 1);  //��¼���µ��ֿ�ʱ���������⣬����ֱ�Ӿ���һ����

			//��¼���µ��ֿ������
			//(�ֿ��и���Ʒ��������)
			while (wrong_flag == 1)
			{
				cout << "��ѡ�� ���ϸü�¼(1)-��-���ٳ�����(2)" << endl;
				int temp;
				cin >> temp;
				//���ϸü�¼
				if (temp == 1)
				{
					new_one->out_num = 0;
					cout << "��¼������!!!" << endl;
					Delay(1500);
					wrong_flag = 0;
				}
				//�������������
				if (temp == 2)
				{
					cout << "�������޸ĵĳ�����:" << endl;
					cin >> new_one->out_num;
					wrong_flag = Join_record(new_one, ku_head, 1);
					if (wrong_flag == 0)
					{
						cout << "���ĺ�ı���¼������!!!" << endl;
						cout << "�������Ӽ�¼������ok����:" << endl;
					}


				}

			}
			//�ֿ���û�и���Ʒ���޷�����
			while (wrong_flag == 2)
			{
				cout << "��ѡ�� ���ϸü�¼(1)����ĸ�����¼(2)" << endl;
				int temp;
				cin >> temp;
				//���ϸü�¼
				if (temp == 1)
				{
					new_one->out_num = 0;
					cout << "��¼������!!!" << endl;
					Delay(1500);
					wrong_flag = 0;
				}
				//�������������
				if (temp == 2)
				{
					cout << "ԭ����¼Ϊ:" << endl;
					if (strcmp(new_one->in_out, "���") == 0)
					{
						cout << new_one->in_out << " "<< new_one->seri_number << " "<< new_one->name << " "  << new_one->unit_price << " " << new_one->in_num << " "
							<< new_one->in_time.year << "��" << new_one->in_time.month << "��" << new_one->in_time.day << "��" << " "
							<< new_one->person << " " << new_one->note << endl;
					}

					if (strcmp(new_one->in_out, "����") == 0)
					{
						cout  << new_one->in_out << " "<< new_one->seri_number << " " << new_one->name << " " << new_one->unit_price << " " << new_one->out_num << " "
							 << new_one->out_time.year << "��"  << new_one->out_time.month << "��" << new_one->out_time.day << "��" << " " 
							<< new_one->person << " " << new_one->note << endl;
					}
					cout << "����������ñ���¼:" << endl;
					//��������
					cin >> new_one->in_out;
					//����¼
					if (strcmp(new_one->in_out, "���") == 0)
					{
						cin >> new_one->seri_number >> new_one->name >> new_one->unit_price >> new_one->in_num >> new_one->in_time.year >> new_one->in_time.month >> new_one->in_time.day >> new_one->person >> new_one->note;
					}
					//�����¼
					else
					{
						cin >> new_one->seri_number >> new_one->name >> new_one->unit_price >> new_one->out_num >> new_one->out_time.year >> new_one->out_time.month >> new_one->out_time.day >> new_one->person >> new_one->note;
					}
					wrong_flag = Join_record(new_one, ku_head, 1);
					if (wrong_flag == 0)
					{
						cout << "���ĺ�ı���¼������!!!" << endl;
					}
				}

			}
			

		}
		cout << "�ļ���¼������!!!" << endl;
		infile.close();
		Delay(2000);
		system("cls");
		return 3;
	}
	return 0;   //�����¼ʧ�ܣ�
}

//��Ӷ�����¼�����Ͳֿ���
void Add_many_record()
{
	int end_flag;
	end_flag=Add_one_record(2);
	if (end_flag == 2)
	{
		cout << "������¼�����ɣ�����";
		Sleep(1500);
		system("cls");
	}
}

//����ļ���¼�����Ͳֿ���
void Add_file_record()
{
	Add_one_record(3);
}

//��ʱ����
void Delay(int i)
{
	Sleep(i);
}

//��ʾ��صı���¼
void Show_related_record(enum material_menu link)
{
	cout << "**һ����" << sum_record << "������¼**" << endl << endl;
	material* pp = base_head;
	if (link == unit_price)
	{
		cout << "��� | ���� | ��/������� | ����ⷽʽ | ����" << endl;
		for (int i = 0; i < sum_record; i++)
		{
			pp = pp->next;
			cout << pp->seri_number << setw(5) << pp->name << " ";
			if (strcmp(pp->in_out,"���") == 0)
			{
				cout << setw(5) << pp->in_time.year << setw(5) << pp->in_time.month << setw(5) << pp->in_time.day << " ";
			}
			else if (strcmp(pp->in_out, "����") == 0)
			{
				cout << setw(5) << pp->out_time.year << setw(5) << pp->out_time.month << setw(5) << pp->out_time.day << " ";
			}
			cout << setw(5) << pp->in_out << setw(5) << pp->unit_price << endl;
		}

	}
	else if (link == num)
	{
		cout << "��� | ���� | ��/������� | ����ⷽʽ | ��/�����" << endl;
		for (int i = 0; i < sum_record; i++)
		{
			pp = pp->next;
			cout << pp->seri_number << setw(5) << pp->name << " ";
			if (strcmp(pp->in_out, "���") == 0)
			{
				cout << setw(5) << pp->in_time.year << setw(5) << pp->in_time.month << setw(5) << pp->in_time.day << " ";
				cout << setw(5) << pp->in_out << setw(5) << pp->in_num << endl;
			}
			else if (strcmp(pp->in_out, "����") == 0)
			{
				cout << setw(5) << pp->out_time.year << setw(5) << pp->out_time.month << setw(5) << pp->out_time.day << " ";
				cout << setw(5) << pp->in_out << setw(5) << pp->out_num << endl;
			}
			
		}
	}
	else if (link == person)
	{
		cout << "��� | ���� | ��/������� | ����ⷽʽ | ������" << endl;
		for (int i = 0; i < sum_record; i++)
		{
			pp = pp->next;
			cout << pp->seri_number << setw(5) << pp->name << " ";
			if (strcmp(pp->in_out, "���") == 0)
			{
				cout << setw(5) << pp->in_time.year << setw(5) << pp->in_time.month << setw(5) << pp->in_time.day << " ";
			}
			else if (strcmp(pp->in_out, "����") == 0)
			{
				cout << setw(5) << pp->out_time.year << setw(5) << pp->out_time.month << setw(5) << pp->out_time.day << " ";
			}
			cout << setw(5) << pp->in_out << setw(8) << pp->person << endl;
		}
	}
	else if (link == note)
	{
		cout << "��� | ���� | ��/������� | ����ⷽʽ | ��ע" << endl;
		for (int i = 0; i < sum_record; i++)
		{
			pp = pp->next;
			cout << pp->seri_number << setw(5) << pp->name << " ";
			if (strcmp(pp->in_out, "���") == 0)
			{
				cout << setw(5) << pp->in_time.year << setw(5) << pp->in_time.month << setw(5) << pp->in_time.day << " ";
			}
			else if (strcmp(pp->in_out, "����") == 0)
			{
				cout << setw(5) << pp->out_time.year << setw(5) << pp->out_time.month << setw(5) << pp->out_time.day << " ";
			}
			cout << setw(5) << pp->in_out << setw(5) << pp->note << endl;
		}
	
	}
	else if (link == all)
	{
		cout << "��/�������||��/��ⷽʽ||����||��/�����||������||��ע " << endl;
		for (int i = 0; i < sum_record; i++)
		{
			pp = pp->next;
			cout << pp->seri_number << setw(5) << pp->name << " ";
			if (strcmp(pp->in_out, "���") == 0)
			{
				cout << setw(5) << pp->in_time.year << setw(5) << pp->in_time.month << setw(5) << pp->in_time.day << setw(5);
				cout << setw(8) << pp->in_out << setw(8) << pp->unit_price << setw(8) << pp->in_num << setw(8) << pp->person << setw(8) << pp->note << endl;
			}
			else if (strcmp(pp->in_out, "����") == 0)
			{
				cout << setw(5) << pp->out_time.year << setw(5) << pp->out_time.month << setw(5) << pp->out_time.day << setw(5);
				cout << setw(8) << pp->in_out << setw(8) << pp->unit_price << setw(8) << pp->out_num << setw(8) << pp->person << setw(8) << pp->note << endl;
			}
			
		}
	}
}

//��ʾ�ֿ���Ʒ�嵥
void Show_Cangku_Item()
{
	cout << "**�ֿ���һ����" << sum_item << "����Ʒ**" << endl << endl;
	cout << "���|����|�ִ�����" << endl;
	material* pp= ku_head;
	for (int i = 0; i < sum_item; i++)
	{
		pp = pp->next;
		cout << pp->seri_number << " " << pp->name<<" " << pp->store_num<<endl;
	}
}


//��ѯ����¼  ����˵��:link-�жϼ������� mode-�жϼ���ģʽ 
void Search_related_record(enum material_menu link,int mode)
{
	material search;  //��¼����������
	int flag = 0;  //�����жϵ�ǰ��¼�Ƿ��������
	int n = 0;
	//��һ�μ���
	if (mode == First_search)
	{
		
		
		sum_search = 0;

		Search_head = (material *)malloc(sizeof(material));
		Search_head->next = NULL;
		material *p1=NULL, *p2=NULL;
		material* biao_dan = base_head;

		
		//���ձ�Ž��м���
		if (link == seri_number)
		{
			cout << "��������Ҫ�����Ĳ��ϵı��: " << endl;
			cin >> search.seri_number;
		}

		//�������ƽ��м���
		if (link == name)
		{
			cout << "��������Ҫ�����Ĳ��ϵ�����: " << endl;
			cin >> search.name;
		}

		//�������ڽ��м���
		if (link == record_data)
		{
			cout << "��������Ҫ�����Ĳ��ϳ�����������:" << endl;
			cin >> search.in_time.year>> search.in_time.month>> search.in_time.day;  //�˴������������ڷŵ����������
		}

		//���ձ����˽��м���
		if (link == person)
		{
			cout << "��������Ҫ�����Ĳ��ϵı�����: " << endl;
			cin >> search.person;
		}

		//���ձ�ע���м���
		if (link == note)
		{
			cout << "��������Ҫ�����Ĳ��ϵı�ע: " << endl;
			cin >> search.note;
		}

		system("cls");

		//����ɼ������ݵ����룬��������Ҫ���м���
		for (int i = 0; i < sum_record; i++)
		{
			biao_dan = biao_dan->next;

			//���ձ�Ž��м���
			if (link == seri_number)
			{
				if (Find_in_part(search.seri_number, biao_dan->seri_number,link))
				{
					flag = 1;
				}
			}

			//�������ƽ��м���
			if (link == name)
			{
				if (Find_in_part(search.name, biao_dan->name,link))
				{
					flag = 1;
				}
			}

			//�������ڽ��м���
			if (link == record_data)
			{
				//���������¼
				if (strcmp(biao_dan->in_out, "���") == 0)
				{
					if (search.in_time.year == biao_dan->in_time.year
						&& search.in_time.month == biao_dan->in_time.month
						&& search.in_time.day == biao_dan->in_time.day)
					{
						flag = 1;
					}
				}
				//����ǳ����¼
				else if (strcmp(biao_dan->in_out,"����") == 0)
				{
					if (search.out_time.year == biao_dan->out_time.year
						&& search.out_time.month == biao_dan->out_time.month
						&& search.out_time.day == biao_dan->out_time.day)
					{
						flag = 1;
					}
				}
				
			}

			//���ձ����˽��м���
			if (link == person)
			{
				if (Find_in_part(search.person, biao_dan->person,link))
				{
					flag = 1;
				}
			}

			//���ձ�ע���м���
			if (link == note)
			{
				if (Find_in_part(search.note, biao_dan->note,link))
				{
					flag = 1;
				}
			}


			//����ü�¼���ϼ�����¼�Ļ����ͽ��ü�¼�ӵ�����������
			if (flag == 1)
			{
				n++;
				//��¼��ֵ
				p1 = (material*)malloc(sizeof(material));

				strcpy(p1->seri_number,biao_dan->seri_number);
				strcpy(p1->name, biao_dan->name);
				p1->unit_price = biao_dan->unit_price;
				strcpy(p1->in_out, biao_dan->in_out);
				if (strcmp(biao_dan->in_out, "���") == 0)
				{
					p1->in_num=biao_dan->in_num;
					p1->in_time.year = biao_dan->in_time.year;
					p1->in_time.month = biao_dan->in_time.month;
					p1->in_time.day = biao_dan->in_time.day;
				}
				else if (strcmp(biao_dan->in_out, "����") == 0)
				{
					p1->out_num = biao_dan->out_num;
					p1->out_time.year = biao_dan->out_time.year;
					p1->out_time.month = biao_dan->out_time.month;
					p1->out_time.day = biao_dan->out_time.day;
				}
				strcpy(p1->person, biao_dan->person);
				strcpy(p1->note, biao_dan->note);

				//�½����ӵ�����������
				if (n == 1)
				{
					Search_head->next = p1;
				}
				else
				{
					p2->next = p1;
				}
				p2 = p1;
			
				flag = 0;  //������ϼ�����־λ
				sum_search++;  //��¼���ϼ����ļ�¼����
			}

			
		}
		if(p2!=NULL)
		p2->next = NULL;
	}

	//��������
	else if (mode == Continue_search)
	{
		int sum_search_temp = sum_search;
		material* p1 = NULL, * p2 = NULL;
		material* biao_dan = Search_head;
		material* temp_head = (material*)malloc(sizeof(material));
		temp_head->next = NULL;
		//���ձ�Ž��м���
		if (link == seri_number)
		{
			cout << "��������Ҫ�����Ĳ��ϵı��: " << endl;
			cin >> search.seri_number;
		}

		//�������ƽ��м���
		if (link == name)
		{
			cout << "��������Ҫ�����Ĳ��ϵ�����: " << endl;
			cin >> search.name;
		}

		//�������ڽ��м���
		if (link == record_data)
		{
			cout << "��������Ҫ�����Ĳ��ϳ�����������:" << endl;
			cin >> search.in_time.year >> search.in_time.month >> search.in_time.day;  //�˴������������ڷŵ����������
		}

		//���ձ����˽��м���
		if (link == person)
		{
			cout << "��������Ҫ�����Ĳ��ϵı�����: " << endl;
			cin >> search.person;
		}

		//���ձ�ע���м���
		if (link == note)
		{
			cout << "��������Ҫ�����Ĳ��ϵı�ע: " << endl;
			cin >> search.note;
		}

		system("cls");

		//������ٴ�ɸѡ���ݵ����룬��������Ҫ�Ӳ�ѯ���������¼���
		for (int i = 0; i < sum_search_temp; i++)
		{
			biao_dan = biao_dan->next;

			//���ձ�Ž��м���
			if (link == seri_number)
			{
				if (strcmp(search.seri_number, biao_dan->seri_number) == 0)
				{
					flag = 1;
				}
			}

			//�������ƽ��м���
			if (link == name)
			{
				if (strcmp(search.name, biao_dan->name) == 0)
				{
					flag = 1;
				}
			}

			//�������ڽ��м���
			if (link == record_data)
			{
				//���������¼
				if (strcmp(biao_dan->in_out, "���") == 0)
				{
					if (search.in_time.year == biao_dan->in_time.year
						&& search.in_time.month == biao_dan->in_time.month
						&& search.in_time.day == biao_dan->in_time.day)
					{
						flag = 1;
					}
				}
				//����ǳ����¼
				else if (strcmp(biao_dan->in_out, "����") == 0)
				{
					if (search.out_time.year == biao_dan->out_time.year
						&& search.out_time.month == biao_dan->out_time.month
						&& search.out_time.day == biao_dan->out_time.day)
					{
						flag = 1;
					}
				}

			}

			//���ձ����˽��м���
			if (link == person)
			{
				if (strcmp(search.person, biao_dan->person) == 0)
				{
					flag = 1;
				}
			}

			//���ձ�ע���м���
			if (link == note)
			{
				if (strcmp(search.note, biao_dan->note) == 0)
				{
					flag = 1;
				}
			}


			//����ü�¼���ϼ�����¼�Ļ����ͽ��ü�¼�ӵ�����������
			if (flag == 1)
			{
				n++;
				//��¼��ֵ
				p1 = (material*)malloc(sizeof(material));

				strcpy(p1->seri_number, biao_dan->seri_number);
				strcpy(p1->name, biao_dan->name);
				p1->unit_price = biao_dan->unit_price;
				strcpy(p1->in_out, biao_dan->in_out);
				if (strcmp(biao_dan->in_out, "���") == 0)
				{
					p1->in_num = biao_dan->in_num;
					p1->in_time.year = biao_dan->in_time.year;
					p1->in_time.month = biao_dan->in_time.month;
					p1->in_time.day = biao_dan->in_time.day;
				}
				else if (strcmp(biao_dan->in_out, "����") == 0)
				{
					p1->out_num = biao_dan->out_num;
					p1->out_time.year = biao_dan->out_time.year;
					p1->out_time.month = biao_dan->out_time.month;
					p1->out_time.day = biao_dan->out_time.day;
				}
				strcpy(p1->person, biao_dan->person);
				strcpy(p1->note, biao_dan->note);

				//�½����ӵ�����������
				if (n == 1)
				{
					temp_head->next = p1;
				}
				else
				{
					p2->next = p1;
				}
				p2 = p1;

				flag = 0;  //������ϼ�����־λ
				sum_search++;  //��¼���ϼ����ļ�¼����
			}

			if(flag==0)
			{
				sum_search--;
			}

		}
		if(p2!=NULL)
		p2->next = NULL;

		Search_head = temp_head;
		
	}

	if (mode == First_search || mode == Continue_search)
	{
		if (Search_head->next == NULL)  cout << "�Բ���δ�ҵ�����Ҫ��ѯ�ı���¼" << endl;
		else
		{
			cout << "**����ѯ��" << sum_search << "������¼**" << endl << endl;
			print_ori(Search_head, 2);
		}
	}

		//��ռ�������
	else if (mode == Clear_list)
	{
		
		material* temp_head_behind = Search_head->next;
		material* temp_head_front= Search_head->next;
		for (int i = 0; i < sum_search; i++)
		{
			temp_head_front = temp_head_front->next;
			free(temp_head_behind);
			temp_head_behind = temp_head_front;

		}
		system("cls");
	}
	

	
}


//��ѯ�ֿ��¼			
void Search_ku_item()
{
	material* temp_head = ku_head;
	material* search = (material*)malloc(sizeof(material));
	material* p1 = NULL, * p2 = NULL;

	enum material_menu link = name;
	int find_flag = 0;

	cout << "��������Ҫ��ѯ�ֿ���Ʒ������: "<<endl;
	cin >> search->name;

	system("cls");
	for (int i = 0; i < sum_item; i++)
	{
		
		temp_head = temp_head->next;

		if (Find_in_part(search->name, temp_head->name,link))  //֮ǰ������ˣ����²鲻��
		{
			cout << temp_head->seri_number << " " << temp_head->name << " " << temp_head->store_num << endl;
			find_flag = 1;
		}
	}
	if (find_flag == 0)  cout << "�Բ��𣬲ֿ���δ���ָ���Ʒ" << endl;
	
}


//�����ɲ�ѯģʽ�õ��ı���¼��λ�������еľ���λ��


//�޸ĵ�������¼����   ����˵�� link: �޸ĵı���¼����  mode:�޸�ģʽ 1-�״��޸� 2-�����޸� 3-��ʾ��¼
void Change_record(enum material_menu link,int mode)
{
	struct material* temp_data = (material*)malloc(sizeof(material));  //��ʱ���ݴ洢
	int mode_change_all = 0;
	if (link == all)  mode_change_all = 1;  //����޸�ȫ�������� ��Ҫ�����е�ifִ��һ��
	struct material* one_record;  //���ڱ����ѯ���ĵ���ԭʼ����¼


	//�״��޸�
	if (mode == 1||mode==2)
	{

		//�ҵ�Ҫ�޸ĵı���¼
		one_record = Search_head->next;

		//��ԭʼ�Ľ��ֵ������ʱ���ݴ洢���
		Copy_node_to_node(temp_data, one_record);
		

		//�޸�ĳһ����
		
		//�޸ı��
		if (link == seri_number|| mode_change_all==1)
		{
			cout << "�������޸ĺ�ı��" << endl;
			cin >> temp_data->seri_number;
		}
		//�޸�����
		if (link == name || mode_change_all == 1)
		{
			cout << "�������޸ĺ������" << endl;
			cin >> temp_data->name;
		}
		//�޸ĵ���
		if (link == unit_price || mode_change_all == 1)
		{
			cout << "�������޸ĺ�ĵ���" << endl;
			cin >> temp_data->unit_price;
		}
		//�޸ĳ�����¼
		if (link == in_out_way || mode_change_all == 1)
		{
			cout << "�������޸ĺ�ĳ�����¼" << endl;
			cin >> temp_data->in_out;
		}
		//�޸ĳ��������
		if (link == in_out_num || mode_change_all == 1)
		{
			cout << "�������޸ĺ�ĳ��������" << endl;
			if (strcmp(temp_data->in_out, "���") == 0)
			{
				cin >> temp_data->in_num;
			}
			else if (strcmp(temp_data->in_out, "����") == 0)
			{
				cin >> temp_data->out_num;
			}
		}

		//�޸ĳ����ʱ��
		if (link == in_out_time || mode_change_all == 1)
		{
			cout << "�������޸ĺ�ĳ����ʱ��" << endl;
			if (strcmp(temp_data->in_out, "���") == 0)
			{
				cin >> temp_data->in_time.year >> temp_data->in_time.month >> temp_data->in_time.day;

			}
			else if (strcmp(temp_data->in_out, "����") == 0)
			{
				cin >> temp_data->out_time.year >> temp_data->out_time.month >> temp_data->out_time.day;
			}
		}
		//�޸ı�����
		if (link==person || mode_change_all == 1)
		{
			cout << "�������޸ĺ�ı�����" << endl;
			cin >> temp_data->person;
		}
		//�޸ı�ע
		if (link == note || mode_change_all == 1)
		{
			cout << "�������޸ĺ�ı�ע" << endl;
			cin >> temp_data->note;
		}
		//ȫ���޸�
		if (link == all)
		{
			cout <<"�Ѿ�ȫ���޸����";
		}
		

		//����������ǽ���ѯ�ı���¼�޸���

		//���޸ĵĲ�ѯ��¼���µ�����¼��
		Update_change_to_record(temp_data, one_record,base_head);

		//������¼���µ��ֿ���
		ku_head->next = NULL;  //�Ƚ��ֿ����Ʒ���
		sum_item = 0;    //�ֿ���Ʒ����
		Handout_ku_init(base_head,ku_head);

		//���޸������ʱ������¸�ֵ����ѯ�����еĽ��,�Ա�����һ���޸�
		Copy_node_to_node(one_record, temp_data);
	}


	//��ʾ��¼
	if (mode == 3)
	{
		temp_data = Search_head->next;
		if (strcmp(temp_data->in_out, "���") == 0)
		{
			cout << temp_data->in_out << " " << temp_data->seri_number << " " << temp_data->name << " " << temp_data->unit_price << " " << temp_data->in_num << " "
				<< temp_data->in_time.year << "��" << temp_data->in_time.month << "��" << temp_data->in_time.day << "��" << " "
				<< temp_data->person << " " << temp_data->note << endl;
		}

		if (strcmp(temp_data->in_out, "����") == 0)
		{
			cout << temp_data->in_out << " " << temp_data->seri_number << " " << temp_data->name << " " << temp_data->unit_price << " " << temp_data->out_num << " "
				<< temp_data->out_time.year << "��" << temp_data->out_time.month << "��" << temp_data->out_time.day << "��" << " "
				<< temp_data->person << " " << temp_data->note << endl;

		}
	}
}


//���޸ĵĵ�����ѯ��¼���µ�����¼��  ����˵���� ��һ�����޸ĺ�������   �ڶ�������Ӧ�Ĳ�ѯ����ԭʼ�������  �������Ǳ���¼ͷָ��
void Update_change_to_record(struct material* Change_record_head, struct material* now_search_head, struct material* base_head)
{
	int find_flag = 0;  //������־λ 0-û�ҵ� 1-�ҵ�

	struct material* now_base_record = base_head->next;  //���ڱ��������ָ��


	//��������¼,�ҵ���ǰ�Ĳ�ѯ��¼��Ӧ�ı���¼��λ�ã������޸ĵĽ�㸳ֵ���������Ľ��
	for (int i = 0; i < sum_record; i++)
	{
		if (strcmp(now_base_record->seri_number, now_search_head->seri_number) == 0)
		{
			if (strcmp(now_base_record->name, now_search_head->name) == 0)
			{
				if (now_base_record->unit_price == now_search_head->unit_price)
				{
					if (strcmp(now_base_record->in_out, now_search_head->in_out) == 0)
					{
						if (strcmp(now_base_record->in_out, "���") == 0)
						{
							if (now_base_record->in_num == now_search_head->in_num)
							{
								if (now_base_record->in_time.year == now_search_head->in_time.year
									&& now_base_record->in_time.month == now_search_head->in_time.month
									&& now_base_record->in_time.day == now_search_head->in_time.day)
								{
									if (strcmp(now_base_record->person, now_search_head->person) == 0)
									{
										if (strcmp(now_base_record->note, now_search_head->note) == 0)
										{
											//ִ�е�������ҵ�һ���Ľ����
											//���и�ֵ
											Copy_node_to_node(now_base_record, Change_record_head);
											break;
										}
									}
								}
							}

						}
						else if (strcmp(now_base_record->in_out, "����") == 0)
						{
							if (now_base_record->out_num == now_search_head->out_num)
							{
								if (now_base_record->out_time.year == now_search_head->out_time.year
									&& now_base_record->out_time.month == now_search_head->out_time.month
									&& now_base_record->out_time.day == now_search_head->out_time.day)
								{
									if (strcmp(now_base_record->person, now_search_head->person) == 0)
									{
										if (strcmp(now_base_record->note, now_search_head->note) == 0)
										{
											//ִ�е�������ҵ�һ���Ľ����
											//���и�ֵ
											Copy_node_to_node(now_base_record, Change_record_head);
											break;
										}
									}
								}
							}
						}
					}
				}
			}
		}

		now_base_record = now_base_record->next;
	}

}


//��������໥��ֵ  ��p2��ֵ��p1
void Copy_node_to_node(struct material* p1, struct material* p2)
{
	strcpy(p1->seri_number, p2->seri_number);
	strcpy(p1->name, p2->name);
	p1->unit_price = p2->unit_price;
	strcpy(p1->in_out, p2->in_out);
	if (strcmp(p1->in_out, "���") == 0)
	{
		p1->in_num = p2->in_num;
		p1->in_time.year = p2->in_time.year;
		p1->in_time.month = p2->in_time.month;
		p1->in_time.day = p2->in_time.day;

	}
	else if (strcmp(p1->in_out, "����") == 0)
	{
		p1->out_num = p2->out_num;
		p1->out_time.year = p2->out_time.year;
		p1->out_time.month = p2->out_time.month;
		p1->out_time.day = p2->out_time.day;
	}
	strcpy(p1->person, p2->person);
	strcpy(p1->note, p2->note);
}

//�޸Ķ�������¼����
void Change_many_record(enum material_menu link, int mode)
{
	struct material* temp_data = (material*)malloc(sizeof(material));  //��ʱ���ݴ洢
	int mode_change_all = 0;
	if (link == all)  mode_change_all = 1;  //����޸�ȫ�������� ��Ҫ�����е�ifִ��һ��
	struct material* one_record;  //���ڱ�����ѯ���Ķ���ԭʼ����¼
	struct material* Copy_search_head = NULL;   //��ѯ����ĸ���������ͷ��㣩 
	struct material* one_copy_record;         //���ڱ�����������

	//�״��޸�
	if (mode == 1 || mode == 2)
	{
		//�ҵ�Ҫ�޸ĵı���¼
		one_record = Search_head->next;
		Copy_node_to_node(temp_data,one_record);  //��ʼ����ʱ���ݽ��

		//����ѯ������һ�ݣ��õ�Copy_search_list,�޸ĸ�����������ݣ�ԭʼ�Ĳ�ѯ�������Զ�
		//׼������
		int n = 0;
		Copy_search_head = (struct material*)malloc(sizeof(material));
		struct material* p1 = NULL;    //���ڲ��ϵش����µĽ��
		struct material* p2 = NULL;    //����ָ�����������һ�����
		Copy_search_head->next = NULL;

		//��ʼ����
		for (int i = 0; i < sum_search; i++)
		{
			n++;
			p1= (struct material*)malloc(sizeof(material));
			Copy_node_to_node(p1, one_record);
			if (n == 1)
			{
				Copy_search_head->next = p1;
			}
			else if (n > 1)
			{
				p2->next = p1;
			}
			p2 = p1;

			one_record = one_record->next;   //��ѯ�������һ�����
			

		}
		p2->next = NULL;

		//�޸�ĳһ���� �޸ĵ�ֵ������ʱ���
		//�޸ı��
		if (link == seri_number || mode_change_all == 1)
		{
			cout << "�������޸ĺ�ı��" << endl;
			cin >> temp_data->seri_number;
		}
		//�޸�����
		if (link == name || mode_change_all == 1)
		{
			cout << "�������޸ĺ������" << endl;
			cin >> temp_data->name;
		}
		//�޸ĵ���
		if (link == unit_price || mode_change_all == 1)
		{
			cout << "�������޸ĺ�ĵ���" << endl;
			cin >> temp_data->unit_price;
		}
		//�޸ĳ�����¼
		if (link == in_out_way || mode_change_all == 1)
		{
			cout << "�������޸ĺ�ĳ�����¼" << endl;
			cin >> temp_data->in_out;
		}
		//�޸ĳ��������
		if (link == in_out_num || mode_change_all == 1)
		{
			cout << "��ѡ����Ҫ�޸���������ǳ�����??  ����<���> or <����>"<<endl;
			cin >> temp_data->in_out;
			cout << "�������޸ĺ�ĳ��������" << endl;
			if (strcmp(temp_data->in_out, "���") == 0)
			{
				cin >> temp_data->in_num;
			}
			else if (strcmp(temp_data->in_out, "����") == 0)
			{
				cin >> temp_data->out_num;
			}
		}

		//�޸ĳ����ʱ��
		if (link == in_out_time || mode_change_all == 1)
		{
			cout << "��ѡ����Ҫ�޸����ʱ�仹�ǳ���ʱ��??  ����<���> or <����>" << endl;
			cin >> temp_data->in_out;
			cout << "�������޸ĺ�ĳ����ʱ��" << endl;
			if (strcmp(temp_data->in_out, "���") == 0)
			{
				cin >> temp_data->in_time.year >> temp_data->in_time.month >> temp_data->in_time.day;

			}
			else if (strcmp(temp_data->in_out, "����") == 0)
			{
				cin >> temp_data->out_time.year >> temp_data->out_time.month >> temp_data->out_time.day;
			}
		}
		//�޸ı�����
		if (link == person || mode_change_all == 1)
		{
			cout << "�������޸ĺ�ı�����";
			cin >> temp_data->person;
		}
		//�޸ı�ע
		if (link == note || mode_change_all == 1)
		{
			cout << "�������޸ĺ�ı�ע" << endl;
			cin >> temp_data->note;
		}
		//ȫ���޸�
		if (link == all)
		{
			cout << "�Ѿ�ȫ���޸����";
		}
		
		one_record = Search_head->next;               //����ָ���ѯ����ĵ�һ�����
		one_copy_record = Copy_search_head->next;     //ָ��ֵ����ĵ�һ�����

		//�����������еĽ��һ��һ�����޸�  ��һ���Ե��޸Ļ���ȫ�����Ե��޸�
		for (int i = 0; i < sum_search; i++)
		{
			if (link == seri_number)
			{
				strcpy(one_copy_record->seri_number,temp_data->seri_number);
			}
			//�޸�����
			if (link == name)
			{
				strcpy(one_copy_record->name, temp_data->name);
			}
			//�޸ĵ���
			if (link == unit_price)
			{
				one_copy_record->unit_price= temp_data->unit_price;
			}
			//�޸ĳ�����¼
			if (link == in_out_way)
			{
				strcpy(one_copy_record->in_out,temp_data->in_out);
			}
			//�޸ĳ��������
			if (link == in_out_num)
			{
				cout << "�������޸ĺ�ĳ��������" << endl;
				if (strcmp(temp_data->in_out, "���") == 0)
				{
					one_copy_record->in_num= temp_data->in_num;
				}
				else if (strcmp(temp_data->in_out, "����") == 0)
				{
					one_copy_record->out_num=temp_data->out_num;
				}
			}

			//�޸ĳ����ʱ��
			if (link == in_out_time)
			{
				cout << "�������޸ĺ�ĳ����ʱ��" << endl;
				if (strcmp(temp_data->in_out, "���") == 0)
				{
					one_copy_record->in_time.year= temp_data->in_time.year;
					one_copy_record->in_time.month = temp_data->in_time.month;
					one_copy_record->in_time.day = temp_data->in_time.day;

				}
				else if (strcmp(temp_data->in_out, "����") == 0)
				{
					one_copy_record->out_time.year = temp_data->out_time.year;
					one_copy_record->out_time.month = temp_data->out_time.month;
					one_copy_record->out_time.day = temp_data->out_time.day;
				}
			}
			//�޸ı�����
			if (link == person)
			{
				strcpy(one_copy_record->person,temp_data->person);
			}
			//�޸ı�ע
			if (link == note)
			{
				strcpy(one_copy_record->note, temp_data->note);
			}
			//ȫ���޸�
			if (link == all)
			{
				Copy_node_to_node(one_copy_record, temp_data);
			}

			
			one_copy_record = one_copy_record->next;     //�����������е���һ�����
		} 

		one_record = Search_head->next;               //����ָ���ѯ����ĵ�һ�����
		one_copy_record = Copy_search_head->next;     //ָ��ֵ����ĵ�һ�����

		//����������ǽ���ѯ����Ľ���޸���

		//���޸ĵĲ�ѯ��¼���µ�����¼��
		for (int i = 0; i < sum_search; i++)
		{
			Update_change_to_record(one_copy_record, one_record, base_head);
			one_record = one_record->next;
			one_copy_record = one_copy_record->next;
		}
		

		//������¼���µ��ֿ���
		ku_head->next = NULL;  //�Ƚ��ֿ����Ʒ���
		sum_item = 0;    //�ֿ���Ʒ����
		Handout_ku_init(base_head, ku_head);

		one_record = Search_head->next;               //����ָ���ѯ����ĵ�һ�����
		one_copy_record = Copy_search_head->next;     //ָ��ֵ����ĵ�һ�����

		//���޸������ʱ������¸�ֵ����ѯ�����еĽ��,�Ա�����һ���޸�
		for (int i = 0; i < sum_search; i++)
		{
			Copy_node_to_node(one_record, one_copy_record);
			one_record = one_record->next;
			one_copy_record = one_copy_record->next;
		}
		
		
	}


	//��ʾ��¼
	if (mode == 3)
	{
		print_ori(Search_head,2);
	}
}

//д���ļ�����  ����˵�� mode 1-�������¼ 2-����ֿ���Ʒ�嵥
void Write_in_file(int mode)
{
	//�������¼
	if (mode == 1)
	{
		struct material* pp = base_head->next;  //���ڱ�������¼
		char address[100];
		cout << "��������Ҫ�����λ��: " << endl;
		cin >> address;
		outfile.open(address);
		for (int i = 0; i < sum_record; i++)
		{
			if (strcmp(pp->in_out, "���") == 0)
			{
				outfile << pp->in_out<< setw(8) << pp->seri_number<< setw(8) << pp->name<< setw(8) << pp->unit_price<< setw(8) << pp->in_num
					<< setw(8) << pp->in_time.year << " "<< pp->in_time.month << " " << pp->in_time.day << " "
					<< setw(8) << pp->person<< setw(8) << pp->note << endl;
			}

			if (strcmp(pp->in_out, "����") == 0)
			{
				outfile << pp->in_out << setw(8) << pp->seri_number<< setw(8) << pp->name << setw(8) << pp->unit_price<< setw(8) << pp->out_num 
					<< setw(8) << pp->out_time.year << " "<< pp->out_time.month << " "<< pp->out_time.day << " "<< setw(8)
					<< pp->person<< setw(8) << pp->note << endl;
			}
			pp = pp->next;
		}

		outfile.close();
		cout << "����¼�Ѿ��洢��ָ��λ�ã�" << endl;
	}
	//����ֿ���Ʒ�嵥
	else if (mode == 2)
	{
		material* pp = ku_head->next;
		char address[100];
		cout << "��������Ҫ�����λ��: " << endl;
		cin >> address;
		outfile.open(address);
		for (int i = 0; i < sum_item; i++)
		{		
			outfile << pp->seri_number <<setw(8)<< pp->name <<setw(8)<< pp->store_num << endl;
			pp = pp->next;
		}
		outfile.close();
		cout << "�ֿ���Ʒ�嵥�Ѿ��洢��ָ��λ�ã�" << endl;
	}
}


//ģ����ѯ�㷨  ���ַ���  ��ѯ��Χ������¼���ֿ���Ʒ
//���Σ������ҽ���ַ���  ��ǰ��ѯ����Ľ��

int Find_in_part(char* search_data, char* now_node,enum material_menu link)
{
	char search[100] = { '\0' };  //�洢�����ַ���
	char* s1;    //�����ַ����ı���ָ��
	char wait_find[100] = { '\0' };  //�洢�������ַ���
	char* w1;    //�����ַ����ı���ָ��
	int size_search = 0;    //�����ַ����ĳ���
	int size_wait_find = 0;   //�������ַ����ĳ���
	int find_num = 0;



	strcpy(search, search_data);  //�����ַ�����ֵ
	strcpy(wait_find,now_node);   //�������ַ�����ֵ

	s1 = search;
	w1 = wait_find;
	

	for (int i = 0;; i++)
	{
		if (search[i] == '\0')break;
		else  size_search++;
	}
	for (int i = 0;; i++)
	{
		if (wait_find[i] == '\0')break;
		else  size_wait_find++;
	}


	//��ʼ����
	if (link == name || link == person)
	{
		for (int i = 0; i < size_search; i += 2)
		{
			s1 = &search[i];
			for (int j = 0; j < size_wait_find; j += 2)
			{
				w1 = &wait_find[j];
				if (*s1 == *w1 && *(s1 + 1) == *(w1 + 1))  //����ռ�����ֽڣ�����Ҫ���������ıȽ�
				{
					find_num++;
				}
			}
		}
		if (find_num == size_search/2)  return 1;
	}

	else if (link == seri_number || link == note)
	{
		for (int i = 0; i < size_search; i ++)
		{
			s1 = &search[i];
			for (int j = 0; j < size_wait_find; j ++)
			{
				w1 = &wait_find[j];
				if (*s1 == *w1)  //��ĸ������ռһ���ֽڣ�����Ҫ�����Ƚ�
				{
					find_num++;
				}
			}
		}
		if (find_num == size_search)  return 1;

	}

	return 0;
}
