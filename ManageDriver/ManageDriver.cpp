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
		//������������ʧ��
		auto temp = GetLastError();
		if (temp == ERROR_SERVICE_EXISTS)
		{
			cout << "�������Ѿ�����,�����ظ����" << endl;
			return false;
		}
		cout << "������������ʧ��,�������Ϊ: "<<temp << endl;
		return false;
	}
	cout << "������������ɹ�" << endl;
	return true;
}

bool StartServe()
{
	//�ȴ�ָ������
	hSer = OpenServiceA(hSCM, SER_NAME, SERVICE_ALL_ACCESS);
	if (hSer == NULL)
	{
		auto temp = GetLastError();
		cout << "������ʧ��,�������Ϊ: " << temp << endl;
		return false;
	}
	else
	{
		auto temp = StartServiceA(hSer, NULL, NULL);
		if (temp == 0)
		{
			cout << "������������ʧ�ܣ�" << endl;
			auto errorCode = GetLastError();
			if (errorCode == ERROR_SERVICE_ALREADY_RUNNING)
			{
				cout << "����������������" << endl;
			}
			else
			{
				cout << "�������Ϊ: " << errorCode << endl;
			}
			return false;
		}
		cout << "������������ɹ�" << endl;
		return true;
	}
}
bool StopServe()
{
	hSer = OpenServiceA(hSCM, SER_NAME, SERVICE_ALL_ACCESS);
	if (hSer == NULL)
	{
		auto temp = GetLastError();
		cout << "�򿪷�������ʧ�ܣ��������Ϊ��" << temp << endl;
	}
	else
	{
		SERVICE_STATUS tempSerStatus{ 0 };
		auto temp = ControlService(hSer, SERVICE_CONTROL_STOP, &tempSerStatus);
		if (temp == 0)
		{
			temp = GetLastError();
			cout << "ֹͣ��������ʧ��,�������Ϊ: " <<temp<< endl;
			return false;
		}
		cout << "ֹͣ��������ɹ�" << endl;
		return true;
	}
}

bool DeleteServe()
{
	hSer = OpenServiceA(hSCM, SER_NAME, SERVICE_ALL_ACCESS);
	if (hSer == NULL)
	{
		auto tempError = GetLastError();
		cout << "�򿪷�������ʧ�ܣ��������Ϊ��" << tempError << endl;
	}
	else
	{
		auto temp = DeleteService(hSer);
		if (temp == 0)
		{
			auto tempError = GetLastError();
			cout << "ɾ����������ʧ��,�������Ϊ: "<<tempError << endl;
			return false;
		}
		cout << "ɾ����������ɹ�" << endl;
		return true;
	}
}


int main()
{
	int Operator;
	//�򿪷��������
	hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCM == NULL)
	{
		auto temp = GetLastError();
		cout << "�����������ʧ�ܣ��������Ϊ: "<< temp<< endl;
		return 0;
	}

	//�Զ��崦������
	cout << "��ӭʹ������������" << endl;
	cout << "����1Ϊ�������" << endl;
	cout << "����2Ϊ��������" << endl;
	cout << "����3Ϊֹͣ����" << endl;
	cout << "����4Ϊɾ������" << endl;
	cout << "�����ı�ʾ�˳�" << endl;
	cout << "ע�������ļ�Ӧ�������棬������ΪTestDriver" << endl;
	cout << endl << endl << endl;
	while (1)
	{
		cin >> Operator;
		switch (Operator)
		{
		case 1:
			//������������
			CreateServe();
			break;

		case 2:
			//������������
			StartServe();
			break;

		case 3:
			//ֹͣ��������
			StopServe();
			break;

		case 4:
			//ɾ����������
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