#include "egpt.h"

void DealDir(char *szDirName, bool ed);

void ChangePassword(char *szNewPwd);

bool ValPassword(char *szNewPwd);


int main(int argc, char* argv[])
{
	char pwd[256] = {0};
	printf("�������룺");
	scanf("%s",pwd);
	if (!ValPassword(pwd))
	{
		printf("�������\n");
		system("pause");
		return 0;
	}
	
	if (argc != 3)
	{
		bool ed;
		for(;;)
		{
			system("cls");
			printf("> Dic Encryptor var 1.0 (�������İ�)\n> Author: Zhang Li\n");
			printf("------------------------------------------------------\n");
			printf("��ѡ��\n 1: ����\n 2: ����\n 3: �޸�����\n 4: �˳�\n����(1/2/3/4)��");
			char yn[1024] = {0};
			scanf("%s",&yn);
			if (strlen(yn) > 1)
			{
				continue;
			}
			switch(yn[0])
			{
			case '1':
				ed = true;
				goto _SELECT_END_;
			case '2':
				ed = false;
				goto _SELECT_END_;
			case '3':
				{
					char newpwd[256] = {0};
					char newpwd2[256] = {0};
					printf("����������룺");
					scanf("%s",newpwd);
					printf("���ٴμ������룺");
					scanf("%s",newpwd2);
					if (strcmp(newpwd,newpwd2) == 0)
					{
						ChangePassword(newpwd);
						printf("�����޸����\n");
					}
					else
					{
						printf("�������벻һ��\n");
					}
					system("pause");
				}
				break;
			case '4':
				return 0;
			}
		}

_SELECT_END_:
		printf("�����Ŀ���ļ���·�������϶�Ŀ���ļ��е��˴��ڣ�Ȼ���»س���\n");
		char szDir[1024];
		scanf("%s",szDir);
		DealDir(szDir,ed);
	}
	else
	{
		DealDir(argv[1], argv[2][0] == '1');
	}

	system("pause");
}

//����Ŀ¼
void DealDir( char *szDirName, bool ed)
{
	FileEncryptor eFor;
	if (ed)
	{
		eFor.EncryptDir(szDirName);
	}
	else
	{
		eFor.DecryptDir(szDirName);
	}
}

//�޸�����
void ChangePassword( char *szNewPwd )
{
	size_t l2 = strlen(szNewPwd);
	int *VAR = new int[l2];
	for (size_t i = 0; i < l2; ++i)
	{
		VAR[i] = (szNewPwd[i] ^ 64);
	}

	for (size_t i = l2 - 1; i > 0; --i)
	{
		VAR[i] = ( (VAR[i] * 2) % VAR[i - 1] - 129 );
	}
	for (size_t i = 0; i < l2 / 2; ++i)
	{
		int temp = VAR[i];
		VAR[i] = VAR[l2 - 1 - i];
		VAR[l2 - 1 - i] = temp;
	}
	std::ofstream os;
	os.open("config", std::ios_base::binary);
	os.seekp(0,std::ios_base::beg);
	os.write((char*)VAR, l2 * 4);
	os.close();

	delete[] VAR;
}

//��֤����
bool ValPassword( char *szNewPwd )
{
	std::ifstream is;
	is.open("config", std::ios_base::binary);
	is.seekg(0,std::ios_base::end);
	size_t l = is.tellg();
	is.seekg(0,std::ios_base::beg);
	char *opwd = new char[l];
	is.read(opwd,l);
	is.close();

	size_t l2 = strlen(szNewPwd);
	int *VAR = new int[l2];
	for (size_t i = 0; i < l2; ++i)
	{
		VAR[i] = (szNewPwd[i] ^ 64);
	}

	for (size_t i = l2 - 1; i > 0; --i)
	{
		VAR[i] = ( (VAR[i] * 2) % VAR[i - 1] - 129 );
	}
	for (size_t i = 0; i < l2 / 2; ++i)
	{
		int temp = VAR[i];
		VAR[i] = VAR[l2 - 1 - i];
		VAR[l2 - 1 - i] = temp;
	}

	if ( memcmp((char*)VAR,opwd,l) == 0)
	{
		delete[] VAR;
		return true;
	}
	delete[] VAR;
	return false;
}
