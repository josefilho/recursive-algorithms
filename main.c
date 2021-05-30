//-------------------------------- Includes -----------------------------------
#include "gfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//--------------------------------- Defines -----------------------------------

#define HEIGHT 60
#define WIDTH 150

//-------------------------------- Functions ----------------------------------

/*
 * This function is intended to create Sierpinski triangles recursively. 
 * NOTE: It will not create more triangles if its height is less than 1 pixel.
 * 
 * @param X used to receive X axis
 * @param Y used to receives Y axis
 * @param H used to receives triangle height
 * @param delta used to receives recursion level
 * 
 * @return void
*/
void DrawTriangles(float X, float Y, float H, int delta);

/*
  * This function is intended to recursively create overlapping squares. 
  * NOTE: It will not create more triangles if its height is less than 1 pixel.
  * 
  * @param X used to receive X axis
  * @param Y used to receives Y axis
  * @param H used to receives square height
  * @param delta used to receives recursion level
  * @param A used to receives a auxiliar recursion level
  * 
  * @return void
*/
void DrawSquare (int X, int Y, int H, int N, int A);

int main()
{
  unsigned imageOption = 0, imageSize, recursionLevel;

	printf("----- Informe a figura desejada -----\n\
  1 - Triangulo\n\
  2 - Quadrado\n");
  scanf("%u", &imageOption);

  printf("----- Informe a altura do desenho (SIZE >= 100 ) -----\n");
  do {
    scanf("%u", &imageSize);
  }while(imageSize < 100);

  printf("----- Informe o nivel de recursao (LEVEL >= 0)-----\n");
  scanf("%u", &recursionLevel);

  switch (imageOption){
    //Draw squares
    case 2: {
      gfx_init(WIDTH + imageSize, HEIGHT + imageSize, "Square");
      DrawSquare((WIDTH + imageSize) / 2, (HEIGHT + imageSize) / 2, (HEIGHT + imageSize) / 2, recursionLevel, 1);
    } break;
  
    //Draw triangles
    default: {
      gfx_init(WIDTH + imageSize, HEIGHT + imageSize, "Triangle"),
      DrawTriangles((WIDTH + imageSize) / 2, 2 * (HEIGHT + imageSize) / 3, (HEIGHT + imageSize) / 2, recursionLevel);
    }break;
  }

  gfx_set_color(255, 255, 255);
  gfx_paint();
	sleep(10);
	gfx_quit();
  
	return 0;
}

void DrawTriangles(float X, float Y, float H, int delta){
  if(delta < 0 || H < 1) return;

  if(delta >= 0) {
    gfx_line(X - (H + 0) / sqrt(3), Y - (H + 0) / 3, X + (H + 0) / sqrt(3), Y - (H + 0) / 3);
    gfx_line(X - (H + 0) / sqrt(3), Y - (H + 0) / 3, X, Y + 2 * (H + 0) / 3);
    gfx_line(X, Y + 2 * (H + 0) / 3, X + (H + 0) / sqrt(3), Y - (H + 0) / 3);
  }

  DrawTriangles(X, Y - 2 * H / 3, H / 2, delta - 1);
  DrawTriangles(X - H / sqrt(3), Y + H / 3, H / 2, delta - 1);
  DrawTriangles(X + H / sqrt(3), Y + H / 3, H / 2, delta - 1);
}

void DrawSquare (int X, int Y, int H, int delta, int A){
  if(H < 1) return;

	if (delta > A){
    DrawSquare(X + H / 2, Y - H / 2, H / 2, delta, A + 1);
    DrawSquare(X - H / 2, Y + H / 2, H / 2, delta, A + 1);
    DrawSquare(X - H / 2, Y - H / 2, H / 2, delta, A + 1);
    DrawSquare(X + H / 2, Y + H / 2, H / 2, delta, A + 1);
  }          
	
  gfx_set_color(255, 255, 255);
  gfx_rectangle(X + H / 2, Y - H / 2, X - H / 2, Y + H / 2);
  gfx_set_color(0, 0, 0); 
  gfx_filled_rectangle(X + H / 2 - 1, Y - H / 2 + 1, X - H / 2 + 1, Y + H / 2 - 1);
}