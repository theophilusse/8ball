#include "sdl_util.h"

void draw_line_width(SDL_Surface *s, uchar *rgb, int x1, int y1, int x2, int y2, int w)
{
  int dx, dy, k;

  k = w / 2;
  if ((dx = x2 - x1) != 0)
  {
    if (dx > 0)
	{
      if ((dy = y2 - y1) != 0)
	  {
        if (dy > 0)
		{
          // vecteur oblique dans le 1er quadran

          if (dx >= dy)
		  {
            // vecteur diagonal ou oblique proche de l’horizontale, dans le 1er octant
            int e;
			e = dx;
            dx = e * 2 ;
			dy = dy * 2 ;  // e est positif
            while (1)
			{  // déplacements horizontaux
              square(s, x1 - k, y1 - k, w, w, rgb);
              if ((x1 = x1 + 1) == x2)
				break;
              if ((e = e - dy) < 0)
			  {
                y1 = y1 + 1 ;  // déplacement diagonal
                e = e + dx ;
			  }
			}
		  }
          else
		  {
            // vecteur oblique proche de la verticale, dans le 2d octant
            int e ;
			e = dy;
            dy = e * 2 ;
			dx = dx * 2 ;  // e est positif
            while (1)
			{  // déplacements verticaux
              square(s, x1 - k, y1 - k, w, w, rgb);
              if ((y1 = y1 + 1) == y2)
				break;
              if ((e = e - dx) < 0)
			  {
                x1 = x1 + 1 ;  // déplacement diagonal
                e = e + dy ;
              }
            }
          }
        }
        else  // dy < 0 (et dx > 0)
		{
          // vecteur oblique dans le 4e cadran

          if (dx >= -dy)
		  {
            // vecteur diagonal ou oblique proche de l’horizontale, dans le 8e octant
            int  e ;
			e = dx;
            dx = e * 2 ;
			dy = dy * 2 ;  // e est positif
            while (1)
			{  // déplacements horizontaux
              square(s, x1 - k, y1 - k, w, w, rgb);
              if ((x1 = x1 + 1) == x2)
				break;
              if ((e = e + dy) < 0)
			  {
                y1 = y1 - 1 ;  // déplacement diagonal
                e = e + dx ;
              }
            }
		  }
          else  // vecteur oblique proche de la verticale, dans le 7e octant
		  {
            int  e ;
			e = dy;
            dy = e * 2 ;
			dx = dx * 2 ;  // e est négatif
            while (1)
			{  // déplacements verticaux
              square(s, x1 - k, y1 - k, w, w, rgb);
              if ((y1 = y1 - 1) == y2)
				break;
              if ((e = e + dx) > 0)
			  {
                x1 = x1 + 1 ;  // déplacement diagonal
                e = e + dy ;
              }
            }
          }
        }
	  }
      else  // dy = 0 (et dx > 0)
	  {
        // vecteur horizontal vers la droite
        do
		{
          square(s, x1 - k, y1 - k, w, w, rgb);
		}
		while ((x1 = x1 + 1) != x2);
      }
	}
    else  // dx < 0
	{
      if ((dy = y2 - y1) != 0)
	  {
        if (dy > 0)
		{
          // vecteur oblique dans le 2d quadran

          if (-dx >= dy)
		  {
            // vecteur diagonal ou oblique proche de l’horizontale, dans le 4e octant
            int  e ;
			e = dx;
            dx = e * 2 ;
			dy = dy * 2 ;  // e est négatif
            while (1)
			{  // déplacements horizontaux
              square(s, x1 - k, y1 - k, w, w, rgb);
              if ((x1 = x1 - 1) == x2)
				break;
              if ((e = e + dy) >= 0)
			  {
                y1 = y1 + 1 ;  // déplacement diagonal
                e = e + dx ;
              }
            }
		  }
          else
		  {
            // vecteur oblique proche de la verticale, dans le 3e octant
            int  e ;
			e = dy;
            dy = e * 2 ;
			dx = dx * 2 ;  // e est positif
            while (1)
			{  // déplacements verticaux
              square(s, x1 - k, y1 - k, w, w, rgb);
              if ((y1 = y1 + 1) == y2)
				break;
              if ((e = e + dx) <= 0)
			  {
                x1 = x1 - 1 ;  // déplacement diagonal
                e = e + dy ;
              }
            }
          }
        }
        else  // dy < 0 (et dx < 0)
		{
          // vecteur oblique dans le 3e cadran

          if (dx <= dy)
		  {
            // vecteur diagonal ou oblique proche de l’horizontale, dans le 5e octant
            int  e ;
			e = dx;
            dx = e * 2 ;
			dy = dy * 2 ;  // e est négatif
            while (1)
			{  // déplacements horizontaux
              square(s, x1 - k, y1 - k, w, w, rgb);
              if ((x1 = x1 - 1) == x2)
				break;
              if ((e = e - dy) >= 0)
			  {
                y1 = y1 - 1 ;  // déplacement diagonal
                e = e + dx ;
              }
            }
		  }
          else  // vecteur oblique proche de la verticale, dans le 6e octant
		  {
            int  e ;
			e = dy;
            dy = e * 2 ;
			dx = dx * 2 ;  // e est négatif
            while (1)
			{  // déplacements verticaux
              square(s, x1 - k, y1 - k, w, w, rgb);
              if ((y1 = y1 - 1) == y2)
				break;
              if ((e = e - dx) >= 0)
			  {
                x1 = x1 - 1 ;  // déplacement diagonal
                e = e + dy ;
              }
            }
          }

        }
	  }
      else  // dy = 0 (et dx < 0)
	  {

        // vecteur horizontal vers la gauche
        do
		{
          square(s, x1 - k, y1 - k, w, w, rgb);
		}
        while ((x1 = x1 - 1) != x2);

      }
    }
  }
  else  // dx = 0
  {
    if ((dy = y2 - y1) != 0)
	{
      if (dy > 0)
	  {
        // vecteur vertical croissant
        do
		{
          square(s, x1 - k, y1 - k, w, w, rgb);
		}
		while ((y1 = y1 + 1) != y2);
      }
      else  // dy < 0 (et dx = 0)
	  {

        // vecteur vertical décroissant
        do
		{
          square(s, x1 - k, y1 - k, w, w, rgb);
		}
        while ((y1 = y1 - 1) != y2);
      }
    }
  }
  // le pixel final (x2, y2) n’est pas tracé.
}

void draw_line(SDL_Surface *s, uchar *rgb, int x1, int y1, int x2, int y2)
{
  int dx, dy;

  if ((dx = x2 - x1) != 0)
  {
    if (dx > 0)
	{
      if ((dy = y2 - y1) != 0)
	  {
        if (dy > 0)
		{
          // vecteur oblique dans le 1er quadran

          if (dx >= dy)
		  {
            // vecteur diagonal ou oblique proche de l’horizontale, dans le 1er octant
            int e;
			e = dx;
            dx = e * 2 ;
			dy = dy * 2 ;  // e est positif
            while (1)
			{  // déplacements horizontaux
              put_pixel(s, rgb, x1, y1);
              if ((x1 = x1 + 1) == x2)
				break;
              if ((e = e - dy) < 0)
			  {
                y1 = y1 + 1 ;  // déplacement diagonal
                e = e + dx ;
			  }
			}
		  }
          else
		  {
            // vecteur oblique proche de la verticale, dans le 2d octant
            int e ;
			e = dy;
            dy = e * 2 ;
			dx = dx * 2 ;  // e est positif
            while (1)
			{  // déplacements verticaux
              put_pixel(s, rgb, x1, y1) ;
              if ((y1 = y1 + 1) == y2)
				break;
              if ((e = e - dx) < 0)
			  {
                x1 = x1 + 1 ;  // déplacement diagonal
                e = e + dy ;
              }
            }
          }
        }
        else  // dy < 0 (et dx > 0)
		{
          // vecteur oblique dans le 4e cadran

          if (dx >= -dy)
		  {
            // vecteur diagonal ou oblique proche de l’horizontale, dans le 8e octant
            int  e ;
			e = dx;
            dx = e * 2 ;
			dy = dy * 2 ;  // e est positif
            while (1)
			{  // déplacements horizontaux
              put_pixel(s, rgb, x1, y1) ;
              if ((x1 = x1 + 1) == x2)
				break;
              if ((e = e + dy) < 0)
			  {
                y1 = y1 - 1 ;  // déplacement diagonal
                e = e + dx ;
              }
            }
		  }
          else  // vecteur oblique proche de la verticale, dans le 7e octant
		  {
            int  e ;
			e = dy;
            dy = e * 2 ;
			dx = dx * 2 ;  // e est négatif
            while (1)
			{  // déplacements verticaux
              put_pixel(s, rgb, x1, y1) ;
              if ((y1 = y1 - 1) == y2)
				break;
              if ((e = e + dx) > 0)
			  {
                x1 = x1 + 1 ;  // déplacement diagonal
                e = e + dy ;
              }
            }
          }
        }
	  }
      else  // dy = 0 (et dx > 0)
	  {
        // vecteur horizontal vers la droite
        do
		{
          put_pixel(s, rgb, x1, y1) ;
		}
		while ((x1 = x1 + 1) != x2);
      }
	}
    else  // dx < 0
	{
      if ((dy = y2 - y1) != 0)
	  {
        if (dy > 0)
		{
          // vecteur oblique dans le 2d quadran

          if (-dx >= dy)
		  {
            // vecteur diagonal ou oblique proche de l’horizontale, dans le 4e octant
            int  e ;
			e = dx;
            dx = e * 2 ;
			dy = dy * 2 ;  // e est négatif
            while (1)
			{  // déplacements horizontaux
              put_pixel(s, rgb, x1, y1) ;
              if ((x1 = x1 - 1) == x2)
				break;
              if ((e = e + dy) >= 0)
			  {
                y1 = y1 + 1 ;  // déplacement diagonal
                e = e + dx ;
              }
            }
		  }
          else
		  {
            // vecteur oblique proche de la verticale, dans le 3e octant
            int  e ;
			e = dy;
            dy = e * 2 ;
			dx = dx * 2 ;  // e est positif
            while (1)
			{  // déplacements verticaux
              put_pixel(s, rgb, x1, y1);
              if ((y1 = y1 + 1) == y2)
				break;
              if ((e = e + dx) <= 0)
			  {
                x1 = x1 - 1 ;  // déplacement diagonal
                e = e + dy ;
              }
            }
          }
        }
        else  // dy < 0 (et dx < 0)
		{
          // vecteur oblique dans le 3e cadran

          if (dx <= dy)
		  {
            // vecteur diagonal ou oblique proche de l’horizontale, dans le 5e octant
            int  e ;
			e = dx;
            dx = e * 2 ;
			dy = dy * 2 ;  // e est négatif
            while (1)
			{  // déplacements horizontaux
              put_pixel(s, rgb, x1, y1) ;
              if ((x1 = x1 - 1) == x2)
				break;
              if ((e = e - dy) >= 0)
			  {
                y1 = y1 - 1 ;  // déplacement diagonal
                e = e + dx ;
              }
            }
		  }
          else  // vecteur oblique proche de la verticale, dans le 6e octant
		  {
            int  e ;
			e = dy;
            dy = e * 2 ;
			dx = dx * 2 ;  // e est négatif
            while (1)
			{  // déplacements verticaux
              put_pixel(s, rgb, x1, y1) ;
              if ((y1 = y1 - 1) == y2)
				break;
              if ((e = e - dx) >= 0)
			  {
                x1 = x1 - 1 ;  // déplacement diagonal
                e = e + dy ;
              }
            }
          }

        }
	  }
      else  // dy = 0 (et dx < 0)
	  {

        // vecteur horizontal vers la gauche
        do
		{
          put_pixel(s, rgb, x1, y1) ;
		}
        while ((x1 = x1 - 1) != x2);

      }
    }
  }
  else  // dx = 0
  {
    if ((dy = y2 - y1) != 0)
	{
      if (dy > 0)
	  {
        // vecteur vertical croissant
        do
		{
          put_pixel(s, rgb, x1, y1) ;
		}
		while ((y1 = y1 + 1) != y2);
      }
      else  // dy < 0 (et dx = 0)
	  {

        // vecteur vertical décroissant
        do
		{
          put_pixel(s, rgb, x1, y1) ;
		}
        while ((y1 = y1 - 1) != y2);
      }
    }
  }
  // le pixel final (x2, y2) n’est pas tracé.
}

void draw_line_dim(SDL_Surface *s, uchar *rgb, int x1, int y1, int x2, int y2, int *maxDim, int *minDim)
{
  int dx, dy;

  if ((dx = x2 - x1) != 0)
  {
    if (dx > 0)
	{
      if ((dy = y2 - y1) != 0)
	  {
        if (dy > 0)
		{
          // vecteur oblique dans le 1er quadran

          if (dx >= dy)
		  {
            // vecteur diagonal ou oblique proche de l’horizontale, dans le 1er octant
            int e;
			e = dx;
            dx = e * 2 ;
			dy = dy * 2 ;  // e est positif
            while (1)
			{  // déplacements horizontaux
              put_pixel_dim(s, rgb, x1, y1, maxDim, minDim);
              if ((x1 = x1 + 1) == x2)
				break;
              if ((e = e - dy) < 0)
			  {
                y1 = y1 + 1 ;  // déplacement diagonal
                e = e + dx ;
			  }
			}
		  }
          else
		  {
            // vecteur oblique proche de la verticale, dans le 2d octant
            int e ;
			e = dy;
            dy = e * 2 ;
			dx = dx * 2 ;  // e est positif
            while (1)
			{  // déplacements verticaux
              put_pixel_dim(s, rgb, x1, y1, maxDim, minDim) ;
              if ((y1 = y1 + 1) == y2)
				break;
              if ((e = e - dx) < 0)
			  {
                x1 = x1 + 1 ;  // déplacement diagonal
                e = e + dy ;
              }
            }
          }
        }
        else  // dy < 0 (et dx > 0)
		{
          // vecteur oblique dans le 4e cadran

          if (dx >= -dy)
		  {
            // vecteur diagonal ou oblique proche de l’horizontale, dans le 8e octant
            int  e ;
			e = dx;
            dx = e * 2 ;
			dy = dy * 2 ;  // e est positif
            while (1)
			{  // déplacements horizontaux
              put_pixel_dim(s, rgb, x1, y1, maxDim, minDim) ;
              if ((x1 = x1 + 1) == x2)
				break;
              if ((e = e + dy) < 0)
			  {
                y1 = y1 - 1 ;  // déplacement diagonal
                e = e + dx ;
              }
            }
		  }
          else  // vecteur oblique proche de la verticale, dans le 7e octant
		  {
            int  e ;
			e = dy;
            dy = e * 2 ;
			dx = dx * 2 ;  // e est négatif
            while (1)
			{  // déplacements verticaux
              put_pixel_dim(s, rgb, x1, y1, maxDim, minDim) ;
              if ((y1 = y1 - 1) == y2)
				break;
              if ((e = e + dx) > 0)
			  {
                x1 = x1 + 1 ;  // déplacement diagonal
                e = e + dy ;
              }
            }
          }
        }
	  }
      else  // dy = 0 (et dx > 0)
	  {
        // vecteur horizontal vers la droite
        do
		{
          put_pixel_dim(s, rgb, x1, y1, maxDim, minDim) ;
		}
		while ((x1 = x1 + 1) != x2);
      }
	}
    else  // dx < 0
	{
      if ((dy = y2 - y1) != 0)
	  {
        if (dy > 0)
		{
          // vecteur oblique dans le 2d quadran

          if (-dx >= dy)
		  {
            // vecteur diagonal ou oblique proche de l’horizontale, dans le 4e octant
            int  e ;
			e = dx;
            dx = e * 2 ;
			dy = dy * 2 ;  // e est négatif
            while (1)
			{  // déplacements horizontaux
              put_pixel_dim(s, rgb, x1, y1, maxDim, minDim) ;
              if ((x1 = x1 - 1) == x2)
				break;
              if ((e = e + dy) >= 0)
			  {
                y1 = y1 + 1 ;  // déplacement diagonal
                e = e + dx ;
              }
            }
		  }
          else
		  {
            // vecteur oblique proche de la verticale, dans le 3e octant
            int  e ;
			e = dy;
            dy = e * 2 ;
			dx = dx * 2 ;  // e est positif
            while (1)
			{  // déplacements verticaux
              put_pixel_dim(s, rgb, x1, y1, maxDim, minDim);
              if ((y1 = y1 + 1) == y2)
				break;
              if ((e = e + dx) <= 0)
			  {
                x1 = x1 - 1 ;  // déplacement diagonal
                e = e + dy ;
              }
            }
          }
        }
        else  // dy < 0 (et dx < 0)
		{
          // vecteur oblique dans le 3e cadran

          if (dx <= dy)
		  {
            // vecteur diagonal ou oblique proche de l’horizontale, dans le 5e octant
            int  e ;
			e = dx;
            dx = e * 2 ;
			dy = dy * 2 ;  // e est négatif
            while (1)
			{  // déplacements horizontaux
              put_pixel_dim(s, rgb, x1, y1, maxDim, minDim) ;
              if ((x1 = x1 - 1) == x2)
				break;
              if ((e = e - dy) >= 0)
			  {
                y1 = y1 - 1 ;  // déplacement diagonal
                e = e + dx ;
              }
            }
		  }
          else  // vecteur oblique proche de la verticale, dans le 6e octant
		  {
            int  e ;
			e = dy;
            dy = e * 2 ;
			dx = dx * 2 ;  // e est négatif
            while (1)
			{  // déplacements verticaux
              put_pixel_dim(s, rgb, x1, y1, maxDim, minDim) ;
              if ((y1 = y1 - 1) == y2)
				break;
              if ((e = e - dx) >= 0)
			  {
                x1 = x1 - 1 ;  // déplacement diagonal
                e = e + dy ;
              }
            }
          }

        }
	  }
      else  // dy = 0 (et dx < 0)
	  {

        // vecteur horizontal vers la gauche
        do
		{
          put_pixel_dim(s, rgb, x1, y1, maxDim, minDim) ;
		}
        while ((x1 = x1 - 1) != x2);

      }
    }
  }
  else  // dx = 0
  {
    if ((dy = y2 - y1) != 0)
	{
      if (dy > 0)
	  {
        // vecteur vertical croissant
        do
		{
          put_pixel_dim(s, rgb, x1, y1, maxDim, minDim) ;
		}
		while ((y1 = y1 + 1) != y2);
      }
      else  // dy < 0 (et dx = 0)
	  {

        // vecteur vertical décroissant
        do
		{
          put_pixel_dim(s, rgb, x1, y1, maxDim, minDim) ;
		}
        while ((y1 = y1 - 1) != y2);
      }
    }
  }
  // le pixel final (x2, y2) n’est pas tracé.
}
