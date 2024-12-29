#include "HeightMap.h"
/*
            put_pixel( s, color, ox + x , oy + y );
            put_pixel( s, color, ox + y , oy + x );
            put_pixel( s, color, ox - x , oy + y );
            put_pixel( s, color, ox - y , oy + x );
            put_pixel( s, color, ox + x , oy - y );
            put_pixel( s, color, ox + y , oy - x );
            put_pixel( s, color, ox - x , oy - y );
            put_pixel( s, color, ox - y , oy - x );*/

static void         ellipse_put_pix(SDL_Surface *s, uchar *color, int ox, int oy, int x, int y)
{
    /*
    put_pixel( s, color, ox + x , oy + y );
    put_pixel( s, color, ox - x , oy + y );

    put_pixel( s, color, ox + x , oy - y );
    put_pixel( s, color, ox - x , oy - y );
    */
    int             i;

    i = x;
    if (i < 0)
        while (i < abs(x))
        {
            put_pixel( s, color, ox + x , oy + y );
            put_pixel( s, color, ox - x , oy + y );
            put_pixel( s, color, ox + x , oy - y );
            put_pixel( s, color, ox - x , oy - y );
            i++;
        }
    else
        while (i >= -x)
        {
            put_pixel( s, color, ox + x , oy + y );
            put_pixel( s, color, ox - x , oy + y );
            put_pixel( s, color, ox + x , oy - y );
            put_pixel( s, color, ox - x , oy - y );
            i--;
        }
}
//void ellipse(SDL_Surface *s, uchar *color, int ox, int oy, uint a, uint b) {
void ellipse(SDL_Surface *s, uchar *color, int ox, int oy, long a, long b) {
  int x,y ;
  double d1,d2 ;
  x = 0 ;
  y = b ;
  d1 = b*b - a*a*b + a*a/4 ;
  ///put_pixel(s, color, x + ox, y + oy);
  ellipse_put_pix(s, color, ox, oy, x, y);
  while ( a*a*(y-.5) > b*b*(x+1) ) {
  if ( d1 < 0 ) {
    d1 += b*b*(2*x+3) ;
    x++ ; }
    else {
    d1 += b*b*(2*x+3) + a*a*(-2*y+2) ;
    x++ ;
    y-- ; }
  ///put_pixel(s, color, x + ox, y + oy);
  ellipse_put_pix(s, color, ox, oy, x, y); }
  d2 = b*b*(x+.5)*(x+.5) + a*a*(y-1)*(y-1) - a*a*b*b ;
  while ( y > 0 ) {
  if ( d2 < 0 ) {
    d2 += b*b*(2*x+2) + a*a*(-2*y+3) ;
    y-- ;
    x++ ; }
    else {
    d2 += a*a*(-2*y+3) ;
    y-- ; }
  ///put_pixel(s, color, x + ox, y + oy);
  ellipse_put_pix(s, color, ox, oy, x, y); }
}
