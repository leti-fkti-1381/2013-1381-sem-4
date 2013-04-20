#include "SDL.h"
#include "SDL_ttf.h"
#include <math.h>

#define WIDTH 1100//Ширина
#define HEIGHT 480//Высота

SDL_Surface* InitSDL();//Инициализациия поверхноси
void InitFont();//Инциалицация шрифта
void put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel );/*Зажечь пиксель определенного
цвета по координате на surface*/
void Line(float x1, float y1, float x2, float y2, SDL_Surface *surface, Uint32 color);/* Алгоритм 
Брезенхема для рисования линии*/ 
void DrawParallelogram(unsigned x, unsigned y, int h, unsigned w, Uint32 color, SDL_Surface* source);
//DrawParallelogram - функция для создания параллелограмма, при помощи линий
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip );
//apply_surface - функция для наложения чисел на прямоугольники
void DrawSort(float* arr, unsigned n, SDL_Surface* source);
//DrawSort - функция графического изображения процесса сортировки
void DrawSort(float* arr, unsigned n, SDL_Surface* source, unsigned i);
void DrawSort(float* arr, unsigned n, SDL_Surface* source, unsigned i, unsigned j);
