typedef struct CSNode
{
	CString		key;
	CDragStatic* DragBox;		//�ؼ�ָ��;
	CSNode *firstChild;
	CSNode *nextSibling;
} CSNode, *CSTree;
