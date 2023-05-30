#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

//����Ա��¼�˺ţ����� (���޸�)
char userName[] = { "admin" };
char passWord[] = { "admin" };

#define BUS_INFOR_FILE "busInfor.txt"		//��������Ϣ�ļ�
#define BUS_ROUTE_FILE "busRoute.txt"		//��������·�ļ�
#define BUS_SCHEDUL_FILE "busSchedul.txt"	//��������ļ�

//�������ṹ��
typedef struct Bus
{
	char busNumber[30];		//���ƺ�
	char busID[30];			//�����
	char busType[30];		//����
	char seatNum[10];		//��λ��
}Bus;

typedef struct Route
{
	char name[30];			//��·����
	char route[30][50];		//;��վ route[0]��� route[station-1]Ϊ�յ� 
	char stationNum[10];	//��·��һ���еĳ�վ��

}Route;

typedef struct BusSchedule {
	char busNumber[20];		//��κ�
	char departureTime[20];	//����ʱ��
	char arrivalTime[20];	//����ʱ��
}BusSchedule;

//��¼��֤����
bool LoginSystem()
{
	char name[10];
	char pwd[20];
	do
	{
		cout << "-----------------------------------��¼----------------------------------" << endl;
		cout << endl;//����
		cout << "���������Ա�˺�: ";
		cin >> name;
		cout << "���������Ա����: ";
		cin >> pwd;
		if (strcmp(name, userName) == 0 && strcmp(pwd, passWord) == 0)//��¼�ɹ�
		{
			system("cls");//����
			return true;
		}
		else//��½ʧ��
		{
			cout << "����Ա�˺Ż����������������������!" << endl;
			system("pause");
			system("cls");
		}
	} while (true);
}

void addBusInfor(Bus busInfor[], int* busNum)
{
	//�ж�����Խ��
	if (*busNum >= 50)
	{
		system("pause");
		system("cls");//����
		cout << "���ʧ��!" << endl;
		return;
	}
	cout << endl;
	cout << "������������������ �������: "; cin >> busInfor[*busNum].busID;
	cout << "������������������ ���ƺ�: "; cin >> busInfor[*busNum].busNumber;
	cout << "������������������ ��������: "; cin >> busInfor[*busNum].busType;
	cout << "������������������ ����λ��: "; cin >> busInfor[*busNum].seatNum;
	//������+1
	++* busNum;
	cout << "��ӳɹ�!" << endl;
	system("pause");
	system("cls");//����
}

void removeBussInfor(Bus busInfor[], int* busNum)
{
	if (*busNum <= 0)
	{
		cout << "û�����ݿ���ɾ��!" << endl;
		system("pause");
		system("cls");//����
		return;
	}
	cout << endl;
	int input;
	cout << "��ѡ����Ҫɾ������ǰ�����: ";
	cin >> input;
	if (input > *busNum)
	{
		cout << "û�����Ϊ" << input << "�ĳ�����Ϣ" << endl;
		system("pause");
		system("cls");//����
		return;
	}
	for (int i = input - 1; i < *busNum - 1; ++i)
	{
		busInfor[i] = busInfor[i + 1];

	}
	--* busNum;
	cout << "������Ϣɾ���ɹ�!" << endl;
	system("pause");
	system("cls");//����
}

//������Ϣ����
void BusInformationManage()
{
	system("cls");//����
	//������Ϣ�����ʽ			115 ��A1234 �¿յ��� 20
	char buffer[100];		//��������
	Bus busInfor[50];		//�������еĳ�����Ϣ �ɱ���50��
	int busNum = 0;			//��¼�ѱ�����Ϣ�ĳ�����

	FILE* fp;
	fp = fopen(BUS_INFOR_FILE, "a+"); //��׷�ӵ���ʽ���ı��ļ�(�������ڣ����½�����֮����ԭ�ļ���׷��),���ļ�β��׷�����ݺ󣬿��Դ�ͷ��ʼ��
	if (fp == NULL)//����ļ���ʧ�ܣ�����
	{
		cout << "Failed to open file" << endl;
		return;
	}

	//���ļ���ȡ������Ϣ�����ж�ȡ��ÿ�ζ�����Ϣ����buffer��
	while (fgets(buffer, sizeof(buffer), fp) != NULL)
	{
		//ʹ��strcspn(buffer, "\n")�ҵ���һ�����з���λ�ã��������滻Ϊ�ַ���������('\0')��������ȥ���˶���Ļ��з�
		buffer[strcspn(buffer, "\n")] = '\0';

		//��ÿ��������Ϣ����������洢������Ľṹ��������
		char* token;
		token = strtok(buffer, " ");
		strcpy(busInfor[busNum].busID, token);
		token = strtok(NULL, " ");
		strcpy(busInfor[busNum].busNumber, token);
		token = strtok(NULL, " ");
		strcpy(busInfor[busNum].busType, token);
		token = strtok(NULL, " ");
		strcpy(busInfor[busNum].seatNum, token);
		++busNum;
	}
	fclose(fp);

	char input;
	do
	{
		cout << "----------------------------������Ϣ����------------------------------" << endl;
		cout << endl;//����
		//��ӡ�����ǰ�Ѵ泵����Ϣ
		cout << "���\t�������\t���ƺ�\t\t��������\t��λ����" << endl;
		for (int i = 0; i < busNum; ++i)
		{
			cout << i + 1 << "\t" << busInfor[i].busID << "\t\t" << busInfor[i].busNumber << "\t\t" << busInfor[i].busType << "\t\t" << busInfor[i].seatNum << endl;
		}
		cout << endl;
		cout << "1.��ӳ�����Ϣ" << endl;
		cout << "2.ɾ��������Ϣ" << endl;
		cout << "0.����������" << endl;
		cout << "��������Ҫ����ǰ�ı��: ";
		cin >> input;
		switch (input)
		{
		case '1':
			//������Ӻ���
			addBusInfor(busInfor, &busNum);
			break;
		case '2':
			//����ɾ������
			removeBussInfor(busInfor, &busNum);
			break;
		case '0':
			system("cls");//����
			break;
		default:
			cout << "����������������������!" << endl;
			system("pause");
			system("cls");//����
			break;
		}
	} while (input != '0');

	fp = fopen(BUS_INFOR_FILE, "w");//��ֻд����ʽ���ı��ļ�(�����������½�����֮������ļ���ʼλ��д������ԭ����)
	if (fp == NULL) {
		cout<<"�޷����ļ�"<<endl;
		return;
	}
	for (int i = 0; i < busNum; ++i)
	{
		char str[100];
		sprintf(str, "%s %s %s %s", busInfor[i].busID, busInfor[i].busNumber, busInfor[i].busType, busInfor[i].seatNum);	//ƴ������
		fputs(str,fp);		//������д���ļ�
		fputs("\n", fp);	//��ӻ��з�
	}
	fclose(fp);
}

void addRoute(Route busRoute[], int* routeNum)
{
	//�ж�����Խ��
	if (*routeNum >= 50)
	{
		system("pause");
		system("cls");//����
		cout << "���ʧ��!" << endl;
		return;
	}
	cout << endl;
	cout << "������Ҫ��ӵ���·����: "; cin >> busRoute[*routeNum].name;
	cout << "��������·�ϳ�վ��ÿ����վ���ÿո������: ������ ����·" << endl;
	int num = 0;	//��¼��վ����
	while (true)
	{
		char str[30];
		cin >> str;
		strcpy(busRoute[*routeNum].route[num], str);
		++num;
		if (cin.peek() == '\n')
			break;
	}
	char str[10];
	sprintf(str, "%d", num);
	strcpy(busRoute[*routeNum].stationNum, str);
	//������+1
	++* routeNum;
	cout << "��ӳɹ�!" << endl;
	system("pause");
	system("cls");//����
}

void removeRoute(Route busRoute[], int* routeNum)
{
	if (*routeNum <= 0)
	{
		cout << "û�����ݿ���ɾ��!" << endl;
		system("pause");
		system("cls");//����
		return;
	}
	cout << endl;
	int input;
	cout << "��ѡ����Ҫɾ������ǰ�����: ";
	cin >> input;
	if (input > *routeNum)
	{
		cout << "û�����Ϊ" << input << "����·��Ϣ" << endl;
		system("pause");
		system("cls");//����
		return;
	}
	for (int i = input - 1; i < *routeNum - 1; ++i)
	{
		busRoute[i] = busRoute[i + 1];

	}
	--* routeNum;
	cout << "��·��Ϣɾ���ɹ�!" << endl;
	system("pause");
	system("cls");//����
}

//��������·������
void BusRouteManage()
{
	system("cls");//����
	//��·��Ϣ�����ʽ			1���� 3 ������ ����· �찲�Ź㳡
	char buffer[200];		//��������
	Route busRoute[50];		//�������е���·��Ϣ �ɱ���50��
	int routeNum = 0;			//��¼�ѱ�����·��Ϣ����

	FILE* fp;
	fp = fopen(BUS_ROUTE_FILE, "a+"); //��׷�ӵ���ʽ���ı��ļ�(�������ڣ����½�����֮����ԭ�ļ���׷��),���ļ�β��׷�����ݺ󣬿��Դ�ͷ��ʼ��
	if (fp == NULL)//����ļ���ʧ�ܣ�����
	{
		cout << "Failed to open file" << endl;
		return;
	}

	//���ļ���ȡ��·��Ϣ�����ж�ȡ��ÿ�ζ�����Ϣ����buffer��
	while (fgets(buffer, sizeof(buffer), fp) != NULL)
	{
		//ʹ��strcspn(buffer, "\n")�ҵ���һ�����з���λ�ã��������滻Ϊ�ַ���������('\0')��������ȥ���˶���Ļ��з�
		buffer[strcspn(buffer, "\n")] = '\0';

		//��ÿ��������Ϣ����������洢������Ľṹ��������
		char* token;
		token = strtok(buffer, " ");
		strcpy(busRoute[routeNum].name, token);
		token = strtok(NULL, " ");
		strcpy(busRoute[routeNum].stationNum, token);
		for (int i = 0; i < atoi(busRoute[routeNum].stationNum); ++i)//atoi(busRoute[routeNum].stationNum)���ַ��͵�����ת��������
		{
			token = strtok(NULL, " ");
			strcpy(busRoute[routeNum].route[i], token);
		}
		++routeNum;
	}
	fclose(fp);

	char input;
	do
	{
		cout << "----------------------------��·��Ϣ����------------------------------" << endl;
		cout << endl;//����
		//��ӡ�����ǰ�Ѵ���·��Ϣ
		for (int i = 0; i < routeNum; ++i)
		{
			cout << i + 1 << "\t��·����:" << busRoute[i].name << "��ʼվ: " << busRoute[i].route[0] << " ;��վ:";
			for (int j = 1; j < atoi(busRoute[i].stationNum) - 1; ++j)
			{
				cout << busRoute[i].route[j] << " ";
			}
			cout << "�յ�վ: " << busRoute[i].route[atoi(busRoute[i].stationNum) - 1] << endl;
		}

		cout << endl;
		cout << "1.�����·��Ϣ" << endl;
		cout << "2.ɾ����·��Ϣ" << endl;
		cout << "0.����������" << endl;
		cout << "��������Ҫ����ǰ�ı��: ";
		cin >> input;
		switch (input)
		{
		case '1':
			//������Ӻ���
			addRoute(busRoute, &routeNum);
			break;
		case '2':
			//����ɾ������
			removeRoute(busRoute, &routeNum);
			break;
		case '0':
			system("cls");//����
			break;
		default:
			cout << "����������������������!" << endl;
			system("pause");
			system("cls");//����
			break;
		}
	} while (input != '0');

	fp = fopen(BUS_ROUTE_FILE, "w");//��ֻд����ʽ���ı��ļ�(�����������½�����֮������ļ���ʼλ��д������ԭ����)
	if (fp == NULL) {
		cout << "�޷����ļ�" << endl;
		return;
	}
	for (int i = 0; i < routeNum; ++i)
	{
		char str[100];
		fputs(busRoute[i].name, fp); fputs(" ", fp);
		fputs(busRoute[i].stationNum, fp); fputs(" ", fp);
		for (int j = 0; j < atoi(busRoute[i].stationNum); ++j)
		{
			fputs(busRoute[i].route[j], fp); fputs(" ", fp);
		}
		fputs("\n", fp);	//��ӻ��з�
	}
	fclose(fp);
}

void addSchedul(BusSchedule busSchedules[], int *scheduleNum)
{
	//�ж�����Խ��
	if (*scheduleNum >= 50)
	{
		system("pause");
		system("cls");//����
		cout << "���ʧ��!" << endl;
		return;
	}
	cout << endl;
	cout << "������Ҫ��ӵİ�κ�: "; cin >> busSchedules[*scheduleNum].busNumber;
	cout << "������Ҫ��ӵİ�εķ���ʱ�� ��:2017/3/30: "; cin >> busSchedules[*scheduleNum].departureTime;
	cout << "������Ҫ��ӵİ�εĵ�վʱ�� ��:2017/3/30: "; cin >> busSchedules[*scheduleNum].arrivalTime;

	//�������+1
	++* scheduleNum;
	cout << "��ӳɹ�!" << endl;
	system("pause");
	system("cls");//����
}

void removeSchedul(BusSchedule busSchedules[], int* scheduleNum)
{
	if (*scheduleNum <= 0)
	{
		cout << "û�����ݿ���ɾ��!" << endl;
		system("pause");
		system("cls");//����
		return;
	}
	cout << endl;
	int input;
	cout << "��ѡ����Ҫɾ������ǰ�����: ";
	cin >> input;
	if (input > *scheduleNum)
	{
		cout << "û�����Ϊ" << input << "�İ����Ϣ" << endl;
		system("pause");
		system("cls");//����
		return;
	}
	for (int i = input - 1; i < *scheduleNum - 1; ++i)
	{
		busSchedules[i] = busSchedules[i + 1];
	}
	--* scheduleNum;
	cout << "��·��Ϣɾ���ɹ�!" << endl;
	system("pause");
	system("cls");//����
}

void BusScheduleManage()
{
	system("cls");//����
	//������Ϣ�����ʽ			111 2003/3/4/18:30 2005/4/3/3:20
	char buffer[100];				//��������
	BusSchedule busSchedules[50];		//�������еİ����Ϣ �ɱ���50��
	int scheduleNum = 0;			//��¼�ѱ�������Ϣ������

	FILE* fp;
	fp = fopen(BUS_SCHEDUL_FILE, "a+"); //��׷�ӵ���ʽ���ı��ļ�(�������ڣ����½�����֮����ԭ�ļ���׷��),���ļ�β��׷�����ݺ󣬿��Դ�ͷ��ʼ��
	if (fp == NULL)//����ļ���ʧ�ܣ�����
	{
		cout << "Failed to open file" << endl;
		return;
	}

	//���ļ���ȡ�����Ϣ�����ж�ȡ��ÿ�ζ�����Ϣ����buffer��
	while (fgets(buffer, sizeof(buffer), fp) != NULL)
	{
		//ʹ��strcspn(buffer, "\n")�ҵ���һ�����з���λ�ã��������滻Ϊ�ַ���������('\0')��������ȥ���˶���Ļ��з�
		buffer[strcspn(buffer, "\n")] = '\0';

		//��ÿ�������Ϣ����������洢������Ľṹ��������
		char* token;
		token = strtok(buffer, " ");
		strcpy(busSchedules[scheduleNum].busNumber, token);
		token = strtok(NULL, " ");
		strcpy(busSchedules[scheduleNum].departureTime, token);
		token = strtok(NULL, " ");
		strcpy(busSchedules[scheduleNum].arrivalTime, token);
		++scheduleNum;
	}
	fclose(fp);

	char input;
	do
	{
		cout << "----------------------------�����Ϣ����------------------------------" << endl;
		cout << endl;//����
		//��ӡ�����ǰ�Ѵ�����Ϣ
		cout << "���\t��κ�\t\t����ʱ��\t\t����ʱ��" << endl;
		for (int i = 0; i < scheduleNum; ++i)
		{
			cout << i + 1 << "\t" << busSchedules[i].busNumber << "\t\t" << busSchedules[i].departureTime << "\t\t" << busSchedules[i].arrivalTime << endl;
		}
		cout << endl;
		cout << "1.��Ӱ����Ϣ" << endl;
		cout << "2.ɾ�������Ϣ" << endl;
		cout << "0.����������" << endl;
		cout << "��������Ҫ����ǰ�ı��: ";
		cin >> input;
		switch (input)
		{
		case '1':
			//������Ӻ���
			addSchedul(busSchedules, &scheduleNum);
			break;
		case '2':
			//����ɾ������
			removeSchedul(busSchedules, &scheduleNum);
			break;
		case '0':
			system("cls");//����
			break;
		default:
			cout << "����������������������!" << endl;
			system("pause");
			system("cls");//����
			break;
		}
	} while (input != '0');

	fp = fopen(BUS_SCHEDUL_FILE, "w");//��ֻд����ʽ���ı��ļ�(�����������½�����֮������ļ���ʼλ��д������ԭ����)
	if (fp == NULL) {
		cout << "�޷����ļ�" << endl;
		return;
	}
	for (int i = 0; i < scheduleNum; ++i)
	{
		char str[100];
		sprintf(str, "%s %s %s", busSchedules[i].busNumber, busSchedules[i].departureTime, busSchedules[i].arrivalTime);	//ƴ������
		fputs(str, fp);		//������д���ļ�
		fputs("\n", fp);	//��ӻ��з�
	}
	fclose(fp);
}

//���˵�
void MainMenu()
{
	char input;
	do
	{
		cout << "----------------------------����������ϵͳ------------------------------" << endl;
		cout << endl;//����
		cout << "                            1.������Ϣ����                              " << endl;
		cout << "                            2.��·��Ϣ����                              " << endl;
		cout << "                            3.�����Ϣ����                              " << endl;
		cout << "                            4.˾����Ϣ����                              " << endl;
		cout << "                            0.�˳�ϵͳ                                  " << endl;
		cout << endl;//����
		cout << "------------------------------------ -----------------------------------" << endl;
		cout << "��������Ҫ����ǰ�ı��: ";
		cin >> input;
		switch (input)
		{
		case '1':
			BusInformationManage();	//���ù�������Ϣ������
			break;
		case '2':
			BusRouteManage();				//���ù�������·������
			break;
		case '3':
			BusScheduleManage();			//���ù�������ι�����
			break;
		case '4':
			break;
		case '0':
			break;
		default:
			cout << "����������������������!" << endl;
			system("pause");
			system("cls");//����
			break;
		}
	} while (input != '0');
}

//������
int main()
{
	//��¼��֤����
	LoginSystem();

	//�����溯��
	MainMenu();

	return 0;
}