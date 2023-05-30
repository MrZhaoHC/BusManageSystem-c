#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

//管理员登录账号，密码 (可修改)
char userName[] = { "admin" };
char passWord[] = { "admin" };

#define BUS_INFOR_FILE "busInfor.txt"		//公交车信息文件
#define BUS_ROUTE_FILE "busRoute.txt"		//公交车线路文件
#define BUS_SCHEDUL_FILE "busSchedul.txt"	//公交班次文件

//公交车结构体
typedef struct Bus
{
	char busNumber[30];		//车牌号
	char busID[30];			//车编号
	char busType[30];		//车型
	char seatNum[10];		//座位数
}Bus;

typedef struct Route
{
	char name[30];			//线路名称
	char route[30][50];		//途径站 route[0]起点 route[station-1]为终点 
	char stationNum[10];	//线路上一共有的车站数

}Route;

typedef struct BusSchedule {
	char busNumber[20];		//班次号
	char departureTime[20];	//出发时间
	char arrivalTime[20];	//到达时间
}BusSchedule;

//登录验证函数
bool LoginSystem()
{
	char name[10];
	char pwd[20];
	do
	{
		cout << "-----------------------------------登录----------------------------------" << endl;
		cout << endl;//换行
		cout << "请输入管理员账号: ";
		cin >> name;
		cout << "请输入管理员密码: ";
		cin >> pwd;
		if (strcmp(name, userName) == 0 && strcmp(pwd, passWord) == 0)//登录成功
		{
			system("cls");//清屏
			return true;
		}
		else//登陆失败
		{
			cout << "管理员账号或密码输入错误！请重新输入!" << endl;
			system("pause");
			system("cls");
		}
	} while (true);
}

void addBusInfor(Bus busInfor[], int* busNum)
{
	//判断数组越界
	if (*busNum >= 50)
	{
		system("pause");
		system("cls");//清屏
		cout << "添加失败!" << endl;
		return;
	}
	cout << endl;
	cout << "请输入新增公交车的 车辆编号: "; cin >> busInfor[*busNum].busID;
	cout << "请输入新增公交车的 车牌号: "; cin >> busInfor[*busNum].busNumber;
	cout << "请输入新增公交车的 车辆类型: "; cin >> busInfor[*busNum].busType;
	cout << "请输入新增公交车的 车座位数: "; cin >> busInfor[*busNum].seatNum;
	//车数辆+1
	++* busNum;
	cout << "添加成功!" << endl;
	system("pause");
	system("cls");//清屏
}

void removeBussInfor(Bus busInfor[], int* busNum)
{
	if (*busNum <= 0)
	{
		cout << "没有数据可以删除!" << endl;
		system("pause");
		system("cls");//清屏
		return;
	}
	cout << endl;
	int input;
	cout << "请选择你要删除数据前的序号: ";
	cin >> input;
	if (input > *busNum)
	{
		cout << "没有序号为" << input << "的车辆信息" << endl;
		system("pause");
		system("cls");//清屏
		return;
	}
	for (int i = input - 1; i < *busNum - 1; ++i)
	{
		busInfor[i] = busInfor[i + 1];

	}
	--* busNum;
	cout << "车辆信息删除成功!" << endl;
	system("pause");
	system("cls");//清屏
}

//车辆信息管理
void BusInformationManage()
{
	system("cls");//清屏
	//车辆信息保存格式			115 辽A1234 新空调车 20
	char buffer[100];		//读缓冲区
	Bus busInfor[50];		//保存已有的车辆信息 可保存50条
	int busNum = 0;			//记录已保存信息的车辆数

	FILE* fp;
	fp = fopen(BUS_INFOR_FILE, "a+"); //以追加的形式打开文本文件(若不存在，则新建；反之，在原文件后追加),在文件尾部追加数据后，可以从头开始读
	if (fp == NULL)//如果文件打开失败，返回
	{
		cout << "Failed to open file" << endl;
		return;
	}

	//从文件读取车辆信息，按行读取，每次读的信息存在buffer中
	while (fgets(buffer, sizeof(buffer), fp) != NULL)
	{
		//使用strcspn(buffer, "\n")找到第一个换行符的位置，并将其替换为字符串结束符('\0')，这样就去除了额外的换行符
		buffer[strcspn(buffer, "\n")] = '\0';

		//把每条车辆信息分离出来，存储到定义的结构体数组中
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
		cout << "----------------------------车辆信息管理------------------------------" << endl;
		cout << endl;//换行
		//打印输出当前已存车辆信息
		cout << "序号\t车辆编号\t车牌号\t\t车辆类型\t座位数量" << endl;
		for (int i = 0; i < busNum; ++i)
		{
			cout << i + 1 << "\t" << busInfor[i].busID << "\t\t" << busInfor[i].busNumber << "\t\t" << busInfor[i].busType << "\t\t" << busInfor[i].seatNum << endl;
		}
		cout << endl;
		cout << "1.添加车辆信息" << endl;
		cout << "2.删除车辆信息" << endl;
		cout << "0.返回主界面" << endl;
		cout << "请输入你要操作前的编号: ";
		cin >> input;
		switch (input)
		{
		case '1':
			//调用添加函数
			addBusInfor(busInfor, &busNum);
			break;
		case '2':
			//调用删除函数
			removeBussInfor(busInfor, &busNum);
			break;
		case '0':
			system("cls");//清屏
			break;
		default:
			cout << "您的输入有误请重新输入!" << endl;
			system("pause");
			system("cls");//清屏
			break;
		}
	} while (input != '0');

	fp = fopen(BUS_INFOR_FILE, "w");//以只写的形式打开文本文件(若不存在则新建，反之，则从文件起始位置写，覆盖原内容)
	if (fp == NULL) {
		cout<<"无法打开文件"<<endl;
		return;
	}
	for (int i = 0; i < busNum; ++i)
	{
		char str[100];
		sprintf(str, "%s %s %s %s", busInfor[i].busID, busInfor[i].busNumber, busInfor[i].busType, busInfor[i].seatNum);	//拼接数据
		fputs(str,fp);		//把数据写入文件
		fputs("\n", fp);	//添加换行符
	}
	fclose(fp);
}

void addRoute(Route busRoute[], int* routeNum)
{
	//判断数组越界
	if (*routeNum >= 50)
	{
		system("pause");
		system("cls");//清屏
		cout << "添加失败!" << endl;
		return;
	}
	cout << endl;
	cout << "请输入要添加的线路名称: "; cin >> busRoute[*routeNum].name;
	cout << "请输入线路上车站，每个车站间用空格隔开例: 青年大街 长青路" << endl;
	int num = 0;	//记录车站数量
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
	//车数辆+1
	++* routeNum;
	cout << "添加成功!" << endl;
	system("pause");
	system("cls");//清屏
}

void removeRoute(Route busRoute[], int* routeNum)
{
	if (*routeNum <= 0)
	{
		cout << "没有数据可以删除!" << endl;
		system("pause");
		system("cls");//清屏
		return;
	}
	cout << endl;
	int input;
	cout << "请选择你要删除数据前的序号: ";
	cin >> input;
	if (input > *routeNum)
	{
		cout << "没有序号为" << input << "的线路信息" << endl;
		system("pause");
		system("cls");//清屏
		return;
	}
	for (int i = input - 1; i < *routeNum - 1; ++i)
	{
		busRoute[i] = busRoute[i + 1];

	}
	--* routeNum;
	cout << "线路信息删除成功!" << endl;
	system("pause");
	system("cls");//清屏
}

//公交车线路管理函数
void BusRouteManage()
{
	system("cls");//清屏
	//线路信息保存格式			1号线 3 青年大街 北京路 天安门广场
	char buffer[200];		//读缓冲区
	Route busRoute[50];		//保存已有的线路信息 可保存50条
	int routeNum = 0;			//记录已保存线路信息个数

	FILE* fp;
	fp = fopen(BUS_ROUTE_FILE, "a+"); //以追加的形式打开文本文件(若不存在，则新建；反之，在原文件后追加),在文件尾部追加数据后，可以从头开始读
	if (fp == NULL)//如果文件打开失败，返回
	{
		cout << "Failed to open file" << endl;
		return;
	}

	//从文件读取线路信息，按行读取，每次读的信息存在buffer中
	while (fgets(buffer, sizeof(buffer), fp) != NULL)
	{
		//使用strcspn(buffer, "\n")找到第一个换行符的位置，并将其替换为字符串结束符('\0')，这样就去除了额外的换行符
		buffer[strcspn(buffer, "\n")] = '\0';

		//把每条车辆信息分离出来，存储到定义的结构体数组中
		char* token;
		token = strtok(buffer, " ");
		strcpy(busRoute[routeNum].name, token);
		token = strtok(NULL, " ");
		strcpy(busRoute[routeNum].stationNum, token);
		for (int i = 0; i < atoi(busRoute[routeNum].stationNum); ++i)//atoi(busRoute[routeNum].stationNum)把字符型的数字转换成整形
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
		cout << "----------------------------线路信息管理------------------------------" << endl;
		cout << endl;//换行
		//打印输出当前已存线路信息
		for (int i = 0; i < routeNum; ++i)
		{
			cout << i + 1 << "\t线路名称:" << busRoute[i].name << "起始站: " << busRoute[i].route[0] << " 途径站:";
			for (int j = 1; j < atoi(busRoute[i].stationNum) - 1; ++j)
			{
				cout << busRoute[i].route[j] << " ";
			}
			cout << "终点站: " << busRoute[i].route[atoi(busRoute[i].stationNum) - 1] << endl;
		}

		cout << endl;
		cout << "1.添加线路信息" << endl;
		cout << "2.删除线路信息" << endl;
		cout << "0.返回主界面" << endl;
		cout << "请输入你要操作前的编号: ";
		cin >> input;
		switch (input)
		{
		case '1':
			//调用添加函数
			addRoute(busRoute, &routeNum);
			break;
		case '2':
			//调用删除函数
			removeRoute(busRoute, &routeNum);
			break;
		case '0':
			system("cls");//清屏
			break;
		default:
			cout << "您的输入有误请重新输入!" << endl;
			system("pause");
			system("cls");//清屏
			break;
		}
	} while (input != '0');

	fp = fopen(BUS_ROUTE_FILE, "w");//以只写的形式打开文本文件(若不存在则新建，反之，则从文件起始位置写，覆盖原内容)
	if (fp == NULL) {
		cout << "无法打开文件" << endl;
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
		fputs("\n", fp);	//添加换行符
	}
	fclose(fp);
}

void addSchedul(BusSchedule busSchedules[], int *scheduleNum)
{
	//判断数组越界
	if (*scheduleNum >= 50)
	{
		system("pause");
		system("cls");//清屏
		cout << "添加失败!" << endl;
		return;
	}
	cout << endl;
	cout << "请输入要添加的班次号: "; cin >> busSchedules[*scheduleNum].busNumber;
	cout << "请输入要添加的班次的发车时间 例:2017/3/30: "; cin >> busSchedules[*scheduleNum].departureTime;
	cout << "请输入要添加的班次的到站时间 例:2017/3/30: "; cin >> busSchedules[*scheduleNum].arrivalTime;

	//班次数辆+1
	++* scheduleNum;
	cout << "添加成功!" << endl;
	system("pause");
	system("cls");//清屏
}

void removeSchedul(BusSchedule busSchedules[], int* scheduleNum)
{
	if (*scheduleNum <= 0)
	{
		cout << "没有数据可以删除!" << endl;
		system("pause");
		system("cls");//清屏
		return;
	}
	cout << endl;
	int input;
	cout << "请选择你要删除数据前的序号: ";
	cin >> input;
	if (input > *scheduleNum)
	{
		cout << "没有序号为" << input << "的班次信息" << endl;
		system("pause");
		system("cls");//清屏
		return;
	}
	for (int i = input - 1; i < *scheduleNum - 1; ++i)
	{
		busSchedules[i] = busSchedules[i + 1];
	}
	--* scheduleNum;
	cout << "线路信息删除成功!" << endl;
	system("pause");
	system("cls");//清屏
}

void BusScheduleManage()
{
	system("cls");//清屏
	//车辆信息保存格式			111 2003/3/4/18:30 2005/4/3/3:20
	char buffer[100];				//读缓冲区
	BusSchedule busSchedules[50];		//保存已有的班次信息 可保存50条
	int scheduleNum = 0;			//记录已保存班次信息的数量

	FILE* fp;
	fp = fopen(BUS_SCHEDUL_FILE, "a+"); //以追加的形式打开文本文件(若不存在，则新建；反之，在原文件后追加),在文件尾部追加数据后，可以从头开始读
	if (fp == NULL)//如果文件打开失败，返回
	{
		cout << "Failed to open file" << endl;
		return;
	}

	//从文件读取班次信息，按行读取，每次读的信息存在buffer中
	while (fgets(buffer, sizeof(buffer), fp) != NULL)
	{
		//使用strcspn(buffer, "\n")找到第一个换行符的位置，并将其替换为字符串结束符('\0')，这样就去除了额外的换行符
		buffer[strcspn(buffer, "\n")] = '\0';

		//把每条班次信息分离出来，存储到定义的结构体数组中
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
		cout << "----------------------------班次信息管理------------------------------" << endl;
		cout << endl;//换行
		//打印输出当前已存班次信息
		cout << "序号\t班次号\t\t发车时间\t\t到达时间" << endl;
		for (int i = 0; i < scheduleNum; ++i)
		{
			cout << i + 1 << "\t" << busSchedules[i].busNumber << "\t\t" << busSchedules[i].departureTime << "\t\t" << busSchedules[i].arrivalTime << endl;
		}
		cout << endl;
		cout << "1.添加班次信息" << endl;
		cout << "2.删除班次信息" << endl;
		cout << "0.返回主界面" << endl;
		cout << "请输入你要操作前的编号: ";
		cin >> input;
		switch (input)
		{
		case '1':
			//调用添加函数
			addSchedul(busSchedules, &scheduleNum);
			break;
		case '2':
			//调用删除函数
			removeSchedul(busSchedules, &scheduleNum);
			break;
		case '0':
			system("cls");//清屏
			break;
		default:
			cout << "您的输入有误请重新输入!" << endl;
			system("pause");
			system("cls");//清屏
			break;
		}
	} while (input != '0');

	fp = fopen(BUS_SCHEDUL_FILE, "w");//以只写的形式打开文本文件(若不存在则新建，反之，则从文件起始位置写，覆盖原内容)
	if (fp == NULL) {
		cout << "无法打开文件" << endl;
		return;
	}
	for (int i = 0; i < scheduleNum; ++i)
	{
		char str[100];
		sprintf(str, "%s %s %s", busSchedules[i].busNumber, busSchedules[i].departureTime, busSchedules[i].arrivalTime);	//拼接数据
		fputs(str, fp);		//把数据写入文件
		fputs("\n", fp);	//添加换行符
	}
	fclose(fp);
}

//主菜单
void MainMenu()
{
	char input;
	do
	{
		cout << "----------------------------公交车管理系统------------------------------" << endl;
		cout << endl;//换行
		cout << "                            1.车辆信息管理                              " << endl;
		cout << "                            2.线路信息管理                              " << endl;
		cout << "                            3.班次信息管理                              " << endl;
		cout << "                            4.司机信息管理                              " << endl;
		cout << "                            0.退出系统                                  " << endl;
		cout << endl;//换行
		cout << "------------------------------------ -----------------------------------" << endl;
		cout << "请输入你要操作前的编号: ";
		cin >> input;
		switch (input)
		{
		case '1':
			BusInformationManage();	//调用公交车信息管理函数
			break;
		case '2':
			BusRouteManage();				//调用公交车线路管理函数
			break;
		case '3':
			BusScheduleManage();			//调用公交车班次管理函数
			break;
		case '4':
			break;
		case '0':
			break;
		default:
			cout << "您的输入有误请重新输入!" << endl;
			system("pause");
			system("cls");//清屏
			break;
		}
	} while (input != '0');
}

//主函数
int main()
{
	//登录验证函数
	LoginSystem();

	//主界面函数
	MainMenu();

	return 0;
}