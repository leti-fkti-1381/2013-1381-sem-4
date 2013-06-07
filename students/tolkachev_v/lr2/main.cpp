#include <vector>
#include "conio.h"
#include "Canvas.h"
#include "windows.h"
#include <iostream>
using namespace std;


uns width,len;//������, ����� ����
uns key;      //������� �������, ��� ������������
int t1,t3;    //��� ������� �������
int step=0;   //���������� ��������� �����, ��� ������ �����-�����
vector<int> rem(1); //���������� �������� �� ����� ���� ��������
bool draw=true;     //���� ���������
bool func(vector<vector<uns>> &inf,uns w,uns l,int mainSq,uns k,Canvas &f);//������� ������� �������� "����������"
bool paste(vector<vector<uns>> &inf,Canvas &f, uns k);//��������� � ������ ������� ����� ���������������
bool fullSearch(vector<vector<uns>> inf,Canvas &f);   //��� �������� ���� ��������� � ������
void Time(vector<int> &rem);                          //����� ������� ���������� �� ����� ��������
//-----------------------------------------------------------------
/*
inf - ��� �������� "����������"
w,l - ������, ����� �������������� �� �������� ������ ���������� �������������
mainSq - ��� �� �������� �������
k - ����� ��������������
f - ����
*/
bool func(vector<vector<uns>> &inf,uns w,uns l,int mainSq,uns k,Canvas &f){
	uns j=1,i,limW;
	int sq,leftSq;
	bool state;

	if(l>width)    //���������� ������� �������� ������ ��������������
		limW=width;//���� ����� ������ ������ ����, �� ��� ������ ����
	else           //�����, ��� ����� (�.�. ��������� ����� �������)
		limW=l-1;

	
	while(w+j<=limW){        //������� �� ������
		i=1;
		while(l-i>=w+j){     //������� �� �����
			sq=(w+j)*(l-i);  //������� ��������������
			leftSq=mainSq-sq;//���������� �������
			if(leftSq>0){    //���� ���� �� �������
				rem.resize(k);//���������� ��������
				rem[k-1]=(limW-w-j)*(w+j-1);
				inf[0].resize(k); //������� � ������ "����������"
				inf[1].resize(k);
				inf[0][k-1]=w+j;
				inf[1][k-1]=l-i;
				state=func(inf,w+j,l-i,leftSq,k+1,f);//���� ���������� ��������� �� �������� ��������������
				if(!state){
					inf[0].resize(k-1);//���� ������ �� ���� ����� �������, ����������� �� ������
					inf[1].resize(k-1);
				}
				else
					return true;
			}
			if(leftSq==0){  //������ "����������" �����
				step++;     //������� �����(������ �������)
				if(step==110)
					Time(rem);
				inf[0].resize(k);//������� � ������ "����������"
				inf[1].resize(k);
				inf[0][k-1]=w+j;
				inf[1][k-1]=l-i;
				return fullSearch(inf,f);//���������� ���������, ������ �� ������� ���� ������ ����������������
			}
			if(leftSq<0){//������� �����(������ �������)
				step++;
				if(step==110)
					Time(rem);
			}
			i++;//��������� ���������� �������������
		}
		j++;//��������� ���������� �������������
	}
	return false;
}
//-----------------------------------------------------------------
bool paste(vector<vector<uns>> &inf, Canvas &f,uns k){
	uns r=0,c,x,y,tmpL,tmpW;
	bool coord=false,turn=false;

	while(!coord && (r<len)){//����� ��������� ��� �������
		c=0;
		while(!coord && (c<width)){
			coord=f.findCoords(r,c,y,x);
crdMrk:		c++;
		}
	r++;
	}
	c=x;
	r=y;
	if(coord){         //���� ������� ����������
		tmpL=inf[1][k];
		tmpW=inf[0][k];
pstMrk:	if(f.Paste(y,x,tmpL,tmpW,k+1)){//���������
			if(draw){     //���������� ������������ �� ���������
				cout<<"Press \"enter\" to render or any key for disable the render.\n";
				key=getch();
				if(key==13)
					draw=true;
				else{
					system("cls");
					cout<<"Processing...\n";
					draw=false;
				}
		
			}
			if(draw){
				system("cls");
				f.OutPut();
			}
			if(!f.Check()) //���������, ����������� �� ����, ���� ��� ��������� ��������� �������������
				if(!paste(inf,f,k+1)){//���� �� ������ �������
					f.EraseRec(y,x,tmpL,tmpW);//�������
trnMrk:				if(!turn){         //�������� �������� ����������
						turn=true;
						tmpL=inf[0][k];;
						tmpW=inf[1][k];
						goto pstMrk;
					}
					else{          //���� � ���������� �� �������� ���� ����� ����������
						turn=false;
						coord=false;
						goto crdMrk;
					}
				}
				else
					return true;
			else
				return true;
		}
		else
			goto trnMrk;//���� �� ��������, ��������� ����������
	}
	else
		return false;	
}
//-----------------------------------------------------------------
bool fullSearch(vector<vector<uns>> inf,Canvas &f){
	uns size=inf[0].size(),tmp1,tmp2;
	bool state;

	for(uns i=0;i<size;i++){//0-�� ��-� � i-�� ��-� ������ �������
		if(i!=0){
			tmp1=inf[0][0];
			tmp2=inf[1][0];
			inf[0][0]=inf[0][i];
			inf[1][0]=inf[1][i];
			inf[0][i]=tmp1;
			inf[1][i]=tmp2;
		}

		f.Paste(0,0,inf[1][0],inf[0][0],1);//��������� ������ �������������
		state=paste(inf,f,1); //�������� �������
		if (!state)
			f.EraseRec(0,0,inf[1][0],inf[0][0]);
		else
			return true;
	}
	return state;
}
//-----------------------------------------------------------------
void Time(vector<int> &rem){
	t3=GetTickCount();//����� ��������
	double t=(t3-t1)/110;// � ������������ �� ���
	uns sec=0,min=0,h=0;//�������, ������, ����
	long c;             //���������� ����� � ��������
	long tmp;
	uns size=rem.size();
	for(uns i=0;i<size;i++)
		t=t*rem[i];

	t=t/1000;
	c=t;
	sec=c%60;
	tmp=c/60;
	min=tmp%60;
	h=tmp/60;
	cout<<"Time before the enumeration:\n"<<h<<"hours "<<min<<"minutes "<<sec<<"seconds\n";

}
//-----------------------------------------------------------------
int main(){
	bool t=false;
	int t2;
	uns tmp;
	vector<vector<uns>> inf(2);//������ "����������"

	cout<<"Enter length and width:\n";
	cin>>len>>width; //���� �����, ������ ����

	if(len<width){//������ ��� ��� ����� ������ ������ ������
		tmp=len;
		len=width;
		width=tmp;
	}

	Canvas f(len,width);
	uns i=1,j=len-2;
	
	t1=GetTickCount(); //����� �������
	while(i<=width && !t){//��������� ��������� �������������
		j=len-2;
		while(j>=i && !t){
			//������� � ������
			inf[0].resize(1);//������
			inf[1].resize(1);//�����
			inf[0][0]=i;
			inf[1][0]=j;
			rem.resize(1);
			rem[0]=(len-2-i)*(width-i);
			t=func(inf,i,j,len*width-i*j,2,f);//�������� ������ ��������� ���������������
			j--;
		}
		i++;
	}
	t2=GetTickCount();//����� �������

	if(t){
		system("cls");
		f.OutPut();
		cout<<"Covered\nTime:"<<t2-t1<<"\n";
	}
	else{
		system("cls");
		cout<<"Not covered\nTime:"<<t2-t1<<"\n";
	}
	system("pause");
}