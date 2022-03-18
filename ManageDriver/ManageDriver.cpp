#include"ManageDriver.h"

bool CreateServe()
{

	hSer = CreateServiceA(
		hSCM,
		SER_NAME,
		SER_NAME,
		SC_MANAGER_ALL_ACCESS,
		SERVICE_KERNEL_DRIVER,
		SERVICE_DEMAND_START,
		SERVICE_ERROR_IGNORE,
		SER_POSITION,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL
	);
	if (hSer == NULL)
	{
		//创建驱动服务失败
		auto temp = GetLastError();
		if (temp == ERROR_SERVICE_EXISTS)
		{
			cout << "该驱动已经存在,不能重复添加" << endl;
			return false;
		}
		cout << "创建驱动服务失败,错误代码为: "<<temp << endl;
		return false;
	}
	cout << "创建驱动服务成功" << endl;
	return true;
}

bool StartServe()
{
	//先打开指定服务
	hSer = OpenServiceA(hSCM, SER_NAME, SERVICE_ALL_ACCESS);
	if (hSer == NULL)
	{
		auto temp = GetLastError();
		cout << "打开驱动失败,错误代码为: " << temp << endl;
		return false;
	}
	else
	{
		auto temp = StartServiceA(hSer, NULL, NULL);
		if (temp == 0)
		{
			cout << "启动驱动服务失败，" << endl;
			auto errorCode = GetLastError();
			if (errorCode == ERROR_SERVICE_ALREADY_RUNNING)
			{
				cout << "该驱动正在运行中" << endl;
			}
			else
			{
				cout << "错误代码为: " << errorCode << endl;
			}
			return false;
		}
		cout << "启动驱动服务成功" << endl;
		return true;
	}
}
bool StopServe()
{
	hSer = OpenServiceA(hSCM, SER_NAME, SERVICE_ALL_ACCESS);
	if (hSer == NULL)
	{
		auto temp = GetLastError();
		cout << "打开服务驱动失败，错误代码为：" << temp << endl;
	}
	else
	{
		SERVICE_STATUS tempSerStatus{ 0 };
		auto temp = ControlService(hSer, SERVICE_CONTROL_STOP, &tempSerStatus);
		if (temp == 0)
		{
			temp = GetLastError();
			cout << "停止驱动服务失败,错误代码为: " <<temp<< endl;
			return false;
		}
		cout << "停止驱动服务成功" << endl;
		return true;
	}
}

bool DeleteServe()
{
	hSer = OpenServiceA(hSCM, SER_NAME, SERVICE_ALL_ACCESS);
	if (hSer == NULL)
	{
		auto tempError = GetLastError();
		cout << "打开服务驱动失败，错误代码为：" << tempError << endl;
	}
	else
	{
		auto temp = DeleteService(hSer);
		if (temp == 0)
		{
			auto tempError = GetLastError();
			cout << "删除驱动服务失败,错误代码为: "<<tempError << endl;
			return false;
		}
		cout << "删除驱动服务成功" << endl;
		return true;
	}
}


int main()
{
	int Operator;
	//打开服务管理器
	hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCM == NULL)
	{
		auto temp = GetLastError();
		cout << "服务管理器打开失败，错误代码为: "<< temp<< endl;
		return 0;
	}

	//自定义处理驱动
	cout << "欢迎使用驱动管理器" << endl;
	cout << "输入1为添加驱动" << endl;
	cout << "输入2为启动驱动" << endl;
	cout << "输入3为停止驱动" << endl;
	cout << "输入4为删除驱动" << endl;
	cout << "输入别的表示退出" << endl;
	cout << "注：驱动文件应放在桌面，且名字为TestDriver" << endl;
	cout << endl << endl << endl;
	while (1)
	{
		cin >> Operator;
		switch (Operator)
		{
		case 1:
			//创建驱动服务
			CreateServe();
			break;

		case 2:
			//启动驱动服务
			StartServe();
			break;

		case 3:
			//停止驱动服务
			StopServe();
			break;

		case 4:
			//删除驱动服务
			DeleteServe();
			break;
		default:
			system("pause");
			return 0;
			break;
		}
	}





	return 0;
}