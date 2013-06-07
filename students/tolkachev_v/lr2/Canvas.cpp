#include "Canvas.h"
#include "windows.h"
#include <iostream>
using namespace std;


//------------------------------------------------------
Canvas::Canvas(uns l, uns w){//�������� ���� lxw
	if(l<yMax && w<xMax){
		len=l;
		width=w;
		for(uns i=0;i<l;i++)
			for(uns j=0;j<w;j++)
				canv[i][j]=0;
	}
	else{
		cerr<<"Error: length or width(too large)!\n";
		exit(1);
	}
}
//------------------------------------------------------
void Canvas::OutPut(){           //����� ���� �� �����
	HANDLE hStdout=GetStdHandle( STD_OUTPUT_HANDLE );
	char ch=0xb2;

	cout<<"+";//�������
	for(uns i=0;i<width;i++)
		cout<<"-";
	cout<<"+\n";

	for(uns i=0;i<len;i++){
		cout<<"|";
		for(uns j=0;j<width;j++){
			SetConsoleTextAttribute(hStdout, canv[i][j]);
			cout<<ch;
		}
		SetConsoleTextAttribute(hStdout, 15);
		cout<<"|\n";
	}

	cout<<"+";//�������
	for(uns i=0;i<width;i++)
		cout<<"-";
	cout<<"+\n";
}
//------------------------------------------------------
void Canvas::EraseRec(uns posL,uns posW,uns l,uns w){//������� �������������
	for(uns i=posL;i<posL+l;i++)
		for(uns j=posW;j<posW+w;j++)
			canv[i][j]=0;
}
//------------------------------------------------------
/*
posL - ���������� y ��� �������
posW - ���������� x ��� �������
l,w - �����, ������ ��������������
k - ����� ��������������
*/
bool Canvas::Paste(uns posL,uns posW,uns l, uns w,uns k){//��������� �������������
	bool t=true;
	if( (posL+l>len) && (posW+w>width) )
		t=false;

	for(uns i=posL;(i<posL+l) && t;i++)   //��������� ��������� �� ��
		for(uns j=posW;(j<posW+w) && t;j++)
			if (canv[i][j]!=0)
				t=false;

	if (t) //���� ��������� ���������
		for(uns i=posL;i<posL+l;i++)
			for(uns j=posW;j<posW+w;j++)
				canv[i][j]=k;

	return t;	
}
//------------------------------------------------------
bool Canvas::Check(){//��������, ��������� �� ����
	bool t=true;
	
	for(uns i=0;(i<len) && t;i++)
		for(uns j=0;(j<width) && t;j++)
			t=canv[i][j]!=0;

	return t;
}
//------------------------------------------------------
/*
startY - ���������� y � ������� ���������� �����
startX - ���������� x � ������� ���������� �����
y,x - ���������� ������ ������(�������� ���������)
*/
bool Canvas::findCoords(uns startY,uns startX,uns &y,uns &x){
	uns i=startY,j=startX;
	bool t=false;

	while(!t && (i<len)){
		if(i==startY)
			j=startX;
		else
			j=0;		
		while(!t && (j<width)){
			t=canv[i][j]==0;
			j++;
		}
		i++;		
	}
	if (t){
		x=j-1;
		y=i-1;
	}
	return t;
}