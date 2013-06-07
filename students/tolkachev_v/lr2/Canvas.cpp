#include "Canvas.h"
#include "windows.h"
#include <iostream>
using namespace std;


//------------------------------------------------------
Canvas::Canvas(uns l, uns w){//создание поля lxw
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
void Canvas::OutPut(){           //вывод поля на экран
	HANDLE hStdout=GetStdHandle( STD_OUTPUT_HANDLE );
	char ch=0xb2;

	cout<<"+";//граница
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

	cout<<"+";//граница
	for(uns i=0;i<width;i++)
		cout<<"-";
	cout<<"+\n";
}
//------------------------------------------------------
void Canvas::EraseRec(uns posL,uns posW,uns l,uns w){//стереть прямоугольник
	for(uns i=posL;i<posL+l;i++)
		for(uns j=posW;j<posW+w;j++)
			canv[i][j]=0;
}
//------------------------------------------------------
/*
posL - координата y для вставки
posW - координата x для вставки
l,w - длина, ширина прямоугольника
k - номер прямоугольника
*/
bool Canvas::Paste(uns posL,uns posW,uns l, uns w,uns k){//выставить прямоугольник
	bool t=true;
	if( (posL+l>len) && (posW+w>width) )
		t=false;

	for(uns i=posL;(i<posL+l) && t;i++)   //проверяем вместится ли он
		for(uns j=posW;(j<posW+w) && t;j++)
			if (canv[i][j]!=0)
				t=false;

	if (t) //если вместится вставляем
		for(uns i=posL;i<posL+l;i++)
			for(uns j=posW;j<posW+w;j++)
				canv[i][j]=k;

	return t;	
}
//------------------------------------------------------
bool Canvas::Check(){//проверка, заполнено ли поле
	bool t=true;
	
	for(uns i=0;(i<len) && t;i++)
		for(uns j=0;(j<width) && t;j++)
			t=canv[i][j]!=0;

	return t;
}
//------------------------------------------------------
/*
startY - координата y с которой начинается поиск
startX - координата x с которой начинается поиск
y,x - координаты пустой клетки(выходные параметры)
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