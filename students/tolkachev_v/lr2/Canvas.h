typedef unsigned short uns;

const uns xMax=80;
const uns yMax=60;


class Canvas{
	public:
		Canvas(uns l, uns w);  //�������� ���� LxW		
		void OutPut();         //����� ���� �� �����
		void EraseRec(uns posL,uns posW,uns l,uns w);//������� �������������
		bool Paste(uns posL,uns posW,uns l,uns w,uns k);//��������� �������������
		bool Check();			//��������, ��������� �� ����
		bool findCoords(uns startY,uns startX,uns &y,uns &x); //����� ������ ������������� ������ ������� � (startY,startX)
		uns canv[yMax][xMax];
		uns len,width;          //���-��, �� ������
};


