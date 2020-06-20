#pragma once
#include "OrthListStruct.h"
#include "ChildSiblingTree.h"
#include <queue>
#include <stack>


using namespace std ;

// COrthList ����Ŀ��

class COrthListGrap : public CObject
{
public:
	COrthListGrap();

	virtual ~COrthListGrap();
public:
	// ��������
	int m_iVexNum;
public:
	// ������
	int m_iArcNum;
public:
	//��������
	OrthListVexNode xlist[MAX_VERTEX_NUM];
public:
	//�������������������
	queue<int> BFSQueue;
public:
	// ����data�ڵ��λ�ã�data��Ψһ��
	int LocateVex(CString key);
public:
	//��Ӷ���
	Status AddVex(CString key,CString moreInfo, CPoint pt ,int radius= 16);
public:
	//ɾ������
	Status DelVex(CString key);
public:
	// ��ӻ�
	Status AddArc(int headVex, int tailVex, int weight);
public:
	// ɾ����
	Status DelArc(int headVex, int tailVex);
public:
	// ���ػ�ָ��
	OrthListArcBox* GetArc(int headVex, int tailVex);
public:
	// �õ���ǰ������õĽڵ��±�
	int GetCanUse(void);

public:
	//�õ�ǰһ��ͬͷ�ڵ�Ļ�
	OrthListArcBox* FrontHeadArc(OrthListArcBox* pArc);
public:
	//�õ�ǰһ��ͬβ�ڵ�Ļ�
	OrthListArcBox* FrontTailArc(OrthListArcBox* pArc);
public:
	//������ʱ��
	void clearVisted(void);
public:
	// �õ�index�ڵ�ĵ�һ���ڽӵ㣨�з���
	int FirstAdjVex(int index);
public:	
	// �õ�index�ڵ����һ���ٽڵ�
	int NextAdjVex( int index);
public:
	//�Ӷ���vex���������������������<��ͨͼ>
	void DepthFirstSearch(int vex ,queue<int> &visitOrder);
public:
	//�Ӷ���vex��������������������� <vex������ͨ����>
	void BreadthFirstSearth(int vex ,queue<int> &VisitOrder);
public:
	// ��ͨ����
	int ConnComponent(void);
public:
	//���ػ�����ɫ
	COLORREF GetArcColor(OrthListArcBox* pArc);
public:
	//���û�����ɫ
	void SetArcColor( int headVex, int tailVex, COLORREF color);
public:
	//���ڽӾ��󴴽�ʮ������
	void CreateOrthListFromMatrix(void);
public:
	//���ͼ
	void Clear(void);
public:
	//��From��to����������ȷ��ʣ�
	bool DFSfromto(int from, int to, stack<int> &vexStack);
public:
	// �����Ƿ����·��
	bool FindPath(CString headKey, CString tailKey,bool ResetColor = true, bool changColor = true);
public:
	// �������л�����ɫ
	void ResetAllArcColor();
public:
	//�����������
	CString DFSVisitOrder( int begin);
public:
	//��������������ر������У��ַ�����
	CString BFSVisitOrder( int begin);
public:
	//���������������ɭ��
	void CreateDFSForest(void);
public:
	//��������������ɭ��
	void CreateBFSForest(void);
public:
	void SortPos(CSTree& tree, CPoint &pt) ;
public:
	//�����������������
	void CreateDFSTree(int vex, CSTree& tree);
public:
	//�����
	bool CheckAnnulus(void);
public:
	//��ǻ�
	void MarkAnnulus( CString key );
public:
	//�����½ڵ㣨�ؼ���
	CSNode* NewNode(CString key, CPoint pt);
public:
	//�ؼ�·��
	bool CriticalPath(void);
public:
	//�������ж���ؼ����
	void ResetAllVexStyle(void);
public:
	//�õ������������е��߼�λ��
	int GetLogicPos(int pos);
public:
	//���·��
	void DrawPath(CString Begin, CString End, CString Path);
public:
	//�ָ��ַ���
	int SplitString(CString str, CStringArray& outStr);
public:
	//�����޸ı�� �� ֪ͨ��ı�
	void SetChangeMark(void);
};


