#pragma once
#include "AdjMatrixStruct.h"
#include "OrthListGrap.h"
#include <afxtempl.h>


// CAdjMatrix ����Ŀ��

class CAdjMatrixGrap : public CObject
{
public:

	CAdjMatrixGrap();
	virtual ~CAdjMatrixGrap();

public:
	// ������Ϣ
	VexNode vexs[MAX_VERTEX_NUM]; 
public:
	//������Ϣ
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; 	               
public:
	// ������
	int vexNum; 

public:
	//���ͼ����
	void Clear(void);
public:
	//��ʮ�����������ڽӾ���
	void CreateAdjMatrixGrap();
public:
	//�������ļ�
	void Save(CString pathName);
public:
	//���ļ�����һ��ͼ
	bool CreateFromFile(void);
public:
	//���ļ�����һ��ͼ
	bool CreateFromFile(CString filePath);
public:
	//�ָ��ַ���
	bool SplitString(CString str,CString& str1, CString& str2);
public:
	//�ָ��ַ���
	bool SplitString(CString str,int num, CStringArray& outStr) ;
public:
	//���·��-�Ͻ�˹����
	void ShortPath_DJJ(CString BeginKey , CStringArray &EndKey, CStringArray &pathResult ,CStringArray & pathLength  );
public:
	//���ؽڵ��������е�����
	int LocateVex(CString key);
};


