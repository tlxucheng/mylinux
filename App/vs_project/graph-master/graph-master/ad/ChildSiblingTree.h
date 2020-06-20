#pragma once
#include "childsiblingstruct.h"


// CChildSiblingTree

class CChildSiblingTree : public CObject
{
	DECLARE_DYNAMIC(CChildSiblingTree)

public:
	CChildSiblingTree();
	virtual ~CChildSiblingTree();



public:
	// ����
	CSNode* root;
public:
	//�Ƿ���Ҫ�޸�
	bool bNeedChange;

public:
	//ɾ���ڵ㼰���ӽڵ�
	void DelVex(CSNode* &pVex);
public:
	//���ؽڵ㼰���ӽڵ�
	void HideVex(CSNode* &pVex ,int showMode);
public:
	//������������
	void MaxPoint(CSNode *tree,  CPoint& pt);
public:
	CSNode* GetNode(CString key);
private:
	void FindNode(CSNode* pVex ,CString key, CSNode* & result);
};


