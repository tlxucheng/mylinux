#include "DragStatic.h"


#define Status int			

#define SUCCESS			0	//�ɹ�
#define VEX_EXIST		-1	//�����Ѵ���
#define ARC_EXIST		-2	//���Ѵ���
#define VEX_NOT_FOUND	-3	//���㲻����
#define ARC_NOT_FOUND	-4	//��������
#define NEW_ARC_ERR		-5	//�����»�ʧ��
#define VEX_TOO_MANY	-6	//�������ѵ�����
#define NO_ADJ_VEX		-7	//û���ڽڵ�

#define MINI_AREA_WIDTH		400
#define MINI_AREA_HEIGHT	300

#define MAX_VERTEX_NUM	300

typedef struct arcInfo  
{
	int quan;
}arcInfo;//����Ϣ


typedef struct OrthListArcBox{
	int tailVex; 
	int headVex;
	OrthListArcBox* m_pNextSameHead;	//��һ��ͬͷ�ڵ�Ļ�ָ��--�뻡
	OrthListArcBox* m_pNextSameTail;	//��һ��ͬβ�ڵ�Ļ�ָ��--����
	arcInfo data;
	COLORREF color;		//������ɫ
	int PenWidth;		//���Ŀ��
} OrthListArcBox;//���ڵ�

typedef struct vexInfo 
{
	CString key;	//�ؼ���--Ψһ
	int inDegree;	//���
	int outDegree;	//����
	CString moreInfo;//��ע	
}vexInfo;//������Ϣ


typedef struct OrthListVexNode{
	vexInfo data;				//�ڵ����Ϣ
	OrthListArcBox* m_pThisHead;	//��һ���Դ�Ϊ��ͷ�Ļ�ָ��--�뻡	
	OrthListArcBox* m_pThisTail;	//��һ���Դ�Ϊ��β�Ļ�ָ��--����
	CDragStatic* DragBox;		//�ؼ�ָ��
	bool visited;		//���ʱ�־
	OrthListArcBox* m_pNowVisitVexArc;//���Ӹýڵ�͵�ǰ���ʽڵ�Ļ�ָ�룬����ʹ��
	bool m_bUsed;		//�ڵ��Ƿ���Ч
} OrthListVexNode;//����ڵ�

