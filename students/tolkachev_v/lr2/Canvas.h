typedef unsigned short uns;

const uns xMax=80;
const uns yMax=60;


class Canvas{
	public:
		Canvas(uns l, uns w);  //создание пол€ LxW		
		void OutPut();         //вывод пол€ на экран
		void EraseRec(uns posL,uns posW,uns l,uns w);//стереть пр€моугольник
		bool Paste(uns posL,uns posW,uns l,uns w,uns k);//выставить пр€моугольник
		bool Check();			//проверка, заполнено ли поле
		bool findCoords(uns startY,uns startX,uns &y,uns &x); //найти первую незаполненную €чейку начина€ с (startY,startX)
		uns canv[yMax][xMax];
		uns len,width;          //кол-во, не индекс
};


