#include "SDLVisualSort.h"

SDL_Surface* InitSDL(){//Инциализация
  if (SDL_Init( SDL_INIT_EVERYTHING ) != NULL){
		SDL_Quit();/*SDL_Quit() Завершает работу всех подсистем 
		SDL, выгружает динамически связанные библиотеки и освобождает
		выделенные ресурсы*/
		exit(1);//Выход из программы
	}
	SDL_Surface* screen = NULL;
	screen = SDL_SetVideoMode( WIDTH, HEIGHT, 32, SDL_SWSURFACE );
	/*SDL_SetVideoMode принимает параметры: ширина, 
	высота, 4 бита на пиксель, создание поверхности в системной памяти*/
	return screen; 
}

void InitFont() {//Инициализация шрифта
	if (TTF_Init() != NULL) {
		SDL_Quit();
		exit(1);
	}
}

void put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel ) {
	//Зажечь пиксель определенного цвета по координате на surface
	if ((x <= WIDTH)&&(y <= HEIGHT)) {
		Uint32 *pixels = (Uint32 *)surface->pixels;
		pixels[ ( y * surface->w ) + x ] = pixel;
		/*координаты: строка у со смещением x*/
	}
}

void Line(float x1, float y1, float x2, float y2, SDL_Surface *surface, Uint32 color) {
	// Алгоритм Брезенхема для рисования линии 
	// Линия из точки (x1, y1) в (x2, y2)
	const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
	float temp;
	if(steep) {
		//swap(x1, y1)
		temp = x1;
		x1 = y1;
		y1 = temp;
		//swap(x2, y2)
		temp = x2;
		x2 = y2;
		y2 = temp;
	}

	if(x1 > x2) {
		//swap(x1, x2)
		temp = x1;
		x1 = x2;
		x2 = temp;
		//swap(y1, y2)
		temp = y1;
		y1 = y2;
		y2 = temp;
	}

	const float dx = x2 - x1;
	const float dy = fabs(y2 - y1);

	float error = dx / 2.0f;
	const int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;

	const int maxX = (int)x2;

	for(int x=(int)x1; x<maxX; x++) {
		if(steep) {
			put_pixel32(surface,y,x, color);
		}
		else {
			put_pixel32(surface,x,y, color);
		}

		error -= dy;
		if(error < 0) {
			y += ystep;
			error += dx;
		}
	}
}

void DrawParallelogram(unsigned x, unsigned y, int h, unsigned w,Uint32 color, SDL_Surface* source){
	if (h > 0)//просто рисуем горизональные линии, пока не достигнем нужной высоты
		//длину линий определяет ширина параллелограмма (см.DrawSort)
		for (int i = 0; i<h; i++) {
			Line(float(x), float(y-i), float(x+w), float(y-i), source, color);
		}
	else
		for (int i = h; i<0; i++) {
			Line(float(x), float(y-i), float(x+w), float(y-i), source, color);
		}
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, 
	SDL_Rect* clip = NULL ) {
    SDL_Rect offset;//структура SDL_Rect - определяет прямоугольную область(см. SDL_video.h)
    
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( source, NULL, destination, &offset );
	/*SDL_BlitSurface в данной работе используется для наложения чисел на прямоугольники*/
	/*поверхность source, накладывается на поверхность destination и сохраняется на области offset,
	если бы вместо offset стоял NULL, сохранялось бы в левый верхний угол*/
}

void DrawSort(float* arr, unsigned n, SDL_Surface* source){
	Line(0, HEIGHT/2, WIDTH, HEIGHT/2, source, 0xffffff);//средняя линия

	float hMax = abs(arr[0]);// Максимальное по модулю значения в массиве

	for (unsigned i = 1; i<n; i++) {
		if (abs(arr[i]) > hMax)
			hMax = arr[i];
	}/*на выходе получаем максимальный по модулю элемент
	(в графическом отображении - максимальную высоту)*/

	// ширина параллелограммов
	// = ширина окна - расстояние между ними - отступы по краям
	unsigned parallW = (WIDTH - 1*n - 10)/n;
	// х позиция параллелограма
	unsigned parallX = 5;
	// высота
	int parallH = 0;
	unsigned j = 0;

	SDL_Surface *text = NULL;
	char *buf = new char[19]; 

	SDL_Color black	= {0, 0, 0};//(см. SDL_video.h)
	SDL_Color white	= {255, 255, 255};

	sprintf(buf, "%17.2lf", double(hMax));
	while (buf[j] == 32) //пропускаем пробелы
			j++;
	TTF_Font *font;
	int fontSize = parallW/(15-j);
	font = TTF_OpenFont("Courier_New.ttf", fontSize);
	if (font == NULL) { // Ошибка открытия файла шрифта
		TTF_Quit();
		SDL_Quit();
		exit(1);
	}

	// Рисуем параллелограмы пишем числа
	for (unsigned i = 0; i<n; i++) {
		parallH = int((arr[i]/hMax)*(HEIGHT/2 - 20));//высота
		DrawParallelogram(parallX, HEIGHT/2, parallH, parallW, 0xffffff, source);

		sprintf(buf, "%17.2lf", double(arr[i]));
		j = 0;
		while (buf[j] == 32) //пропускаем пробелы
			j++;
		buf[18] = 0;
		//если высота пар-мма меньше размера шрифта, числа белые, иначе чёрные
		if (abs(parallH) < fontSize)
			text = TTF_RenderText_Solid(font, buf+j, white);
		else
			text = TTF_RenderText_Solid(font, buf+j, black);

		if (parallH > 0)
			if (parallH < fontSize)
				/*если высота пар-мма меньше размера шрифта и больше нуля, то пишем 
				числа выше, иначе внутри пар-мма*/
				apply_surface(parallX+2, HEIGHT/2-parallH-fontSize, text, source);
			else
			apply_surface(parallX+2, HEIGHT/2-parallH, text, source);
		else
			if (abs(parallH) < fontSize)
				apply_surface(parallX+2, HEIGHT/2-parallH, text, source);
			else
				apply_surface(parallX+2, HEIGHT/2-parallH-fontSize, text, source);
		
		parallX += parallW + 1;/*позиция следующего пар-мма = позиция
		текущего + ширина + 1(отступ)*/
	}

	SDL_Flip(source);//обновить экран
	SDL_FillRect(source, NULL, 0x000000);/*заполнение source
	(грубо говоря всей поверхности) черным цветом*/
}

void DrawSort(float* arr, unsigned n, SDL_Surface* source, unsigned p1){
	Line(0, HEIGHT/2, WIDTH, HEIGHT/2, source, 0xffffff);

	float hMax = abs(arr[0]);// Максимальное по модулю элемент в массиве

	for (unsigned i = 1; i<n; i++) {
		if (abs(arr[i]) > hMax)
			hMax = arr[i];
	}

	// ширина параллелограмов
	// = ширина окна - расстояние между ними - отступы по краям
	unsigned parallW = (WIDTH - 1*n - 10)/n;
	// х позиция параллелограма
	unsigned parallX = 5;
	// высота
	int parallH = 0;
	unsigned j = 0;

	SDL_Surface *text = NULL;
	char *buf = new char[19]; 

	SDL_Color black	= {0, 0, 0};
	SDL_Color white	= {255, 255, 255};
	SDL_Color blue = {0, 0, 255};

	sprintf(buf, "%17.2lf", double(hMax));
	while (buf[j] == 32) //пропускаем пробелы
			j++;
	TTF_Font *font;
	int fontSize = parallW/(15-j);
	font = TTF_OpenFont("Courier_New.ttf", fontSize);
	if (font == NULL) { // Ошибка открытия файла шрифта
		TTF_Quit();
		SDL_Quit();
		exit(1);
	}
	int parallColor;

	// Рисуем параллелограмы пишем числа
	for (unsigned i = 0; i<n; i++) {
		parallH = int((arr[i]/hMax)*(HEIGHT/2 - 20));
		if (i == p1) parallColor = 0xcbf000;
		else  parallColor = 0x88ed74;
		DrawParallelogram(parallX, HEIGHT/2, parallH, parallW, parallColor, source);

		sprintf(buf, "%17.2lf", double(arr[i]));
		j = 0;
		while (buf[j] == 32) //пропускаем пробелы
			j++;
		buf[18] = 0;


		if (abs(parallH) < fontSize)
			text = TTF_RenderText_Solid(font, buf+j, white);
		else
			text = TTF_RenderText_Solid(font, buf+j, black);

		if (parallH > 0)
			if (parallH < fontSize)
				apply_surface(parallX+2, HEIGHT/2-parallH-fontSize, text, source);
			else
			apply_surface(parallX+2, HEIGHT/2-parallH, text, source);
		else
			if (abs(parallH) < fontSize)
				apply_surface(parallX+2, HEIGHT/2-parallH, text, source);
			else
				apply_surface(parallX+2, HEIGHT/2-parallH-fontSize, text, source);
	
		parallX += parallW + 1;

	}

	SDL_Flip(source);
	SDL_FillRect(source, NULL, 0x000000); 
}

void DrawSort(float* arr, unsigned n, SDL_Surface* source, unsigned p1, unsigned p2){
	Line(0, HEIGHT/2, WIDTH, HEIGHT/2, source, -1);

	float hMax = abs(arr[0]);// Максимальное по модулю значения в массиве

	for (unsigned i = 1; i<n; i++) {
		if (abs(arr[i]) > hMax)
			hMax = arr[i];
	}

	// ширина параллелограмов
	// = ширина окна - расстояние между ними - отступы по краям
	unsigned parallW = (WIDTH - 1*n - 10)/n;
	// х позиция параллелограма
	unsigned parallX = 5;
	// высота
	int parallH = 0;
	unsigned j = 0;

	SDL_Surface *text = NULL;
	char *buf = new char[19]; 

	SDL_Color black	= {0, 0, 0};
	SDL_Color white	= {255, 255, 255};
	SDL_Color blue = {0, 0, 255};

	sprintf(buf, "%17.2lf", double(hMax));
	while (buf[j] == 32) //пропускаем пробелы
			j++;
	TTF_Font *font;
	int fontSize = parallW/(15-j);
	font = TTF_OpenFont("Courier_New.ttf", fontSize);
	if (font == NULL) { // Ошибка открытия файла шрифта
		TTF_Quit();
		SDL_Quit();
		exit(1);
	}
	int parallColor;

	// Рисуем параллелограмы пишем числа
	for (unsigned i = 0; i<n; i++) {
		parallH = int((arr[i]/hMax)*(HEIGHT/2 - 20));
		if (i == p1) parallColor = 0xF0F0;
		else if (i == p2) parallColor = 0x9F07;
		else  parallColor = -1;
		DrawParallelogram(parallX, HEIGHT/2, parallH, parallW, parallColor, source);

		sprintf(buf, "%17.2lf", double(arr[i]));
		j = 0;
		while (buf[j] == 32) //пропускаем пробелы
			j++;
		buf[18] = 0;


		if (abs(parallH) < fontSize)
			text = TTF_RenderText_Solid(font, buf+j, white);
		else
			text = TTF_RenderText_Solid(font, buf+j, black);

		if (parallH > 0)
			if (parallH < fontSize)
				apply_surface(parallX+2, HEIGHT/2-parallH-fontSize, text, source);
			else
			apply_surface(parallX+2, HEIGHT/2-parallH, text, source);
		else
			if (abs(parallH) < fontSize)
				apply_surface(parallX+2, HEIGHT/2-parallH, text, source);
			else
				apply_surface(parallX+2, HEIGHT/2-parallH-fontSize, text, source);
	
		parallX += parallW + 1;

	}

	SDL_Flip(source);
	SDL_FillRect(source, NULL, 0x000000); 
}
