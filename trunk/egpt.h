/*
+-----------------------------------------------------------+
|
|	filename:	egpt.h
|	created:	05/09/2007
|	author:		Zhang Li
|
|	purpose:	�ļ��м�����ʵ��
|
+-----------------------------------------------------------+
|	�ļ��м��ܹ��� (http://jonlee.cnblogs.com)
+-----------------------------------------------------------+
*/

#ifndef egpt_h__
#define egpt_h__

#pragma once
#include <afx.h>
#include <fstream>
#pragma warning(disable: 4800)
#pragma warning(disable: 4267)

class FileEncryptor
{
public:

	FileEncryptor();
	~FileEncryptor();

	//> ����һ���ļ���
	//> szDirName �ļ���·��
	void EncryptDir(char *szDirName);

	//> ����һ���ļ���
	//> szDirName �ļ���·��
	void DecryptDir(char *szDirName);

private:

	//> ����һ���ļ�
	//> szFilename �ļ�·��
	void _Encrypt(char *szFilename);

	//> ����һ���ļ�
	//> szFilename �ļ�·��
	void _Decrypt(char *szFilename);

	//> ����һ���ļ��У����ܻ���ܣ�
	//> mode	true	����
	//			false	����
	void _ProcDir(char *szDirName, bool mode);

	//һ���ļ��Ƿ�ӹ���
	bool _IsEncrypted(char *szFileName);

	//�Ƿ�������ͼ�ļ�
	bool _IstmDB(char *szFileName);


	std::ifstream m_isHead;
	size_t m_iHeadlength;
	char *m_szHeadbuffer;
};


#endif // egpt_h__
