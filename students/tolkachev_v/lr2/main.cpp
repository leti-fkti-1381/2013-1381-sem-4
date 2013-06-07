#include <vector>
#include "conio.h"
#include "Canvas.h"
#include "windows.h"
#include <iostream>
using namespace std;


uns width,len;//ширина, длина поля
uns key;      //нажатая клавиша, для визуализации
int t1,t3;    //для замеров времени
int step=0;   //количество сделанных шагов, для метода Монте-Карло
vector<int> rem(1); //оставшиеся варианты на кадом шаге рекурсии
bool draw=true;     //флаг отрислвки
bool func(vector<vector<uns>> &inf,uns w,uns l,int mainSq,uns k,Canvas &f);//главная функция набирает "кондидатов"
bool paste(vector<vector<uns>> &inf,Canvas &f, uns k);//размещает в данном порядке набор прямоугольников
bool fullSearch(vector<vector<uns>> inf,Canvas &f);   //для перебора всех сочетаний в наборе
void Time(vector<int> &rem);                          //вывод времени оставшееся до конца перебора
//-----------------------------------------------------------------
/*
inf - для хранения "кондидатов"
w,l - ширина, длина прямоугольника от которого строим несравнимы прямоугольник
mainSq - еще не покрытая площадь
k - номер прямоугольника
f - поле
*/
bool func(vector<vector<uns>> &inf,uns w,uns l,int mainSq,uns k,Canvas &f){
	uns j=1,i,limW;
	int sq,leftSq;
	bool state;

	if(l>width)    //определяем границу перебора ширины прямоугольника
		limW=width;//если длина больше ширины поля, то это ширина поля
	else           //иначе, это длина (т.е. последним будет квадрат)
		limW=l-1;

	
	while(w+j<=limW){        //перебор по ширине
		i=1;
		while(l-i>=w+j){     //перебор по длине
			sq=(w+j)*(l-i);  //площадь прямоугольника
			leftSq=mainSq-sq;//оставшаяся площадь
			if(leftSq>0){    //если поле не покрыто
				rem.resize(k);//оставшиеся варианты
				rem[k-1]=(limW-w-j)*(w+j-1);
				inf[0].resize(k); //заносим в список "кондидатов"
				inf[1].resize(k);
				inf[0][k-1]=w+j;
				inf[1][k-1]=l-i;
				state=func(inf,w+j,l-i,leftSq,k+1,f);//ищем следующего кондидата от текущего прямоугольника
				if(!state){
					inf[0].resize(k-1);//если нельзя от него найти решения, вычеркиваем из списка
					inf[1].resize(k-1);
				}
				else
					return true;
			}
			if(leftSq==0){  //список "кондидатов" готов
				step++;     //счетчик шагов(оценка времени)
				if(step==110)
					Time(rem);
				inf[0].resize(k);//заносим в список "кондидатов"
				inf[1].resize(k);
				inf[0][k-1]=w+j;
				inf[1][k-1]=l-i;
				return fullSearch(inf,f);//возваращем результат, смогли ли покрыть поле такими прямоугольниками
			}
			if(leftSq<0){//счетчик шагов(оценка времени)
				step++;
				if(step==110)
					Time(rem);
			}
			i++;//следующий несравнимы прямоугольник
		}
		j++;//следующий несравнимы прямоугольник
	}
	return false;
}
//-----------------------------------------------------------------
bool paste(vector<vector<uns>> &inf, Canvas &f,uns k){
	uns r=0,c,x,y,tmpL,tmpW;
	bool coord=false,turn=false;

	while(!coord && (r<len)){//поиск координат для вставки
		c=0;
		while(!coord && (c<width)){
			coord=f.findCoords(r,c,y,x);
crdMrk:		c++;
		}
	r++;
	}
	c=x;
	r=y;
	if(coord){         //если нашлись координаты
		tmpL=inf[1][k];
		tmpW=inf[0][k];
pstMrk:	if(f.Paste(y,x,tmpL,tmpW,k+1)){//вставляем
			if(draw){     //спрашиваем пользователя об отрисовке
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
			if(!f.Check()) //проверяем, заполнилось ли поле, если нет вставляем следующий прямоугольник
				if(!paste(inf,f,k+1)){//если не смогли покрыть
					f.EraseRec(y,x,tmpL,tmpW);//стираем
trnMrk:				if(!turn){         //пытаемся вставить повернутым
						turn=true;
						tmpL=inf[0][k];;
						tmpW=inf[1][k];
						goto pstMrk;
					}
					else{          //если и повернутым не подходит ищем новые координаты
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
			goto trnMrk;//если не вставили, вставляем повернутым
	}
	else
		return false;	
}
//-----------------------------------------------------------------
bool fullSearch(vector<vector<uns>> inf,Canvas &f){
	uns size=inf[0].size(),tmp1,tmp2;
	bool state;

	for(uns i=0;i<size;i++){//0-ой эл-т и i-ый эл-т меняем местами
		if(i!=0){
			tmp1=inf[0][0];
			tmp2=inf[1][0];
			inf[0][0]=inf[0][i];
			inf[1][0]=inf[1][i];
			inf[0][i]=tmp1;
			inf[1][i]=tmp2;
		}

		f.Paste(0,0,inf[1][0],inf[0][0],1);//вставляем первый прямоугольник
		state=paste(inf,f,1); //пытаемся покрыть
		if (!state)
			f.EraseRec(0,0,inf[1][0],inf[0][0]);
		else
			return true;
	}
	return state;
}
//-----------------------------------------------------------------
void Time(vector<int> &rem){
	t3=GetTickCount();//замер времемни
	double t=(t3-t1)/110;// в милисекундах на шаг
	uns sec=0,min=0,h=0;//секунды, минуты, чаыс
	long c;             //оставшееся время в секундах
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
	vector<vector<uns>> inf(2);//список "кондидатов"

	cout<<"Enter length and width:\n";
	cin>>len>>width; //ввод длины, шиирны поля

	if(len<width){//делаем так что длина всегда больше ширины
		tmp=len;
		len=width;
		width=tmp;
	}

	Canvas f(len,width);
	uns i=1,j=len-2;
	
	t1=GetTickCount(); //замер времени
	while(i<=width && !t){//очередной стартовый прямоугольник
		j=len-2;
		while(j>=i && !t){
			//заносим в список
			inf[0].resize(1);//ширина
			inf[1].resize(1);//длина
			inf[0][0]=i;
			inf[1][0]=j;
			rem.resize(1);
			rem[0]=(len-2-i)*(width-i);
			t=func(inf,i,j,len*width-i*j,2,f);//начинаем подбор остальных прямоугольников
			j--;
		}
		i++;
	}
	t2=GetTickCount();//замер времени

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