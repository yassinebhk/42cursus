// mlx xpm
// by ol

#include <OpenGL/gl3.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include	"mlx_int.h"

typedef struct  s_xpm_col
{
  int           name;
  int           col;
} t_xpm_col;


struct  s_col_name
{
  char  *name;
  int   color;
};

//extern struct s_col_name mlx_col_name[];
#include "mlx_rgb.c"


#define	RETURN	{ if (colors) free(colors); if (tab) free(tab); \
		  if (colors_direct) free(colors_direct); \
                  if (img) mlx_destroy_image(xvar, img);   \
                  return ((void *)0); }




char	*mlx_int_get_line(char *ptr,int *pos,int size)
{
  int	pos2;
  int	pos3;
  int	pos4;

  if ((pos2 = mlx_int_str_str(ptr+*pos,"\"",size-*pos))==-1)
    return ((char *)0);
  if ((pos3 = mlx_int_str_str(ptr+*pos+pos2+1,"\"",size-*pos-pos2-1))==-1)
    return ((char *)0);
  *(ptr+*pos+pos2) = 0;
  *(ptr+*pos+pos2+1+pos3) = 0;
  pos4 = *pos+pos2+1;
  *pos += pos2+pos3+2;
  return (ptr+pos4);
}
// The mlx_int_get_line function takes three arguments: a pointer to a char, a pointer to an int, and an int.
// The function returns a pointer to a char and is used to get a line from a string. The function takes a pointer to a char, a pointer to an int, and an int as arguments.




char	*mlx_int_static_line(char **xpm_data,int *pos,int size)
{
  static char	*copy = 0;
  static int	len = 0;
  int		len2;
  char		*str;

  str = xpm_data[(*pos)++];
  if ((len2 = strlen(str))>len)
    {
      if (copy)
	free(copy);
      if (!(copy = malloc(len2+1)))
	return ((char *)0);
      len = len2;
    }
  /* strcpy(copy,str); */
  strlcpy(copy, str, len2+1);
  return (copy);
}
// The mlx_int_static_line function takes three arguments: a pointer to a pointer to a char, a pointer to an int, and an int.
// The function returns a pointer to a char and is used to get a line from a string.
// The function uses a static variable to store the line and its length, and returns a pointer to the line.


int	mlx_int_get_col_name(char *str,int size)
{
  int	result;

  result = 0;
  while (size--)
    result = (result<<8)+*(str++);
  return (result);
}
// The mlx_int_get_col_name function takes two arguments: a pointer to a char and an int.
// The function returns an int and is used to get the color name from a string.


int	mlx_int_get_text_rgb(char *name, char *end)
{
  int	i;
  char	buff[64];

  if (*name == '#')
    return (strtol(name+1,0,16));
  if (end)
    {
      snprintf(buff, 64, "%s %s", name, end);
      name = buff;
    }
  i = 0;
  while (mlx_col_name[i].name)
    {
      if (!strcasecmp(mlx_col_name[i].name, name))
	return (mlx_col_name[i].color);
      i ++;
    }
  return (0);
}
// The mlx_int_get_text_rgb function takes two arguments: a pointer to a char and a pointer to a char.
// The function returns an int and is used to get the RGB value of a color from a string.


void	mlx_int_xpm_set_pixel(mlx_img_list_t *img, char *data, int opp, int col, int x)
{
  /*
  int	dec;

  dec = opp;
  while (dec--)
    {
      if (img->image->byte_order)
	*(data+x*opp+dec) = col&0xFF;
      else
	*(data+x*opp+opp-dec-1) = col&0xFF;
      col >>= 8;
    }
  */
  // opp is 4, do it the simple way
  *((unsigned int *)(data+4*x)) = col;
}
// The mlx_int_xpm_set_pixel function takes four arguments: a pointer to an mlx_img_list_t, a pointer to a char, an int, and an int.
// The function returns void and is used to set the color of a pixel in an image.
// The function uses the opp argument to determine the number of bytes per pixel, and sets the color of the pixel using the col argument.
// The function uses the x argument to determine the position of the pixel in the image.
// The function uses the data argument to determine the buffer of the image.
// The function uses the img argument to determine the image.
// The function uses the image argument to determine the image.
// The function uses the byte_order argument to determine the byte order of the image.


void	*mlx_int_parse_xpm(mlx_ptr_t *xvar,void *info,int info_size,char *(*f)())
{
  int	pos;
  char	*line;
  char	**tab;
  char	*data;
  char	*clip_data;
  int	nc;
  int	opp;
  int	cpp;
  int	col;
  int	rgb_col;
  int	col_name;
  int	method;
  int	x;
  int	i;
  int	j;
  mlx_img_list_t	*img;
  t_xpm_col	*colors;
  int		*colors_direct;
  int	width;
  int	height;

  colors = 0;
  colors_direct = 0;
  img = 0;
  tab = 0;
  pos = 0;
  if (!(line = f(info,&pos,info_size)) ||
      !(tab = mlx_int_str_to_wordtab(line)) || !(width = atoi(tab[0])) ||
      !(height = atoi(tab[1])) || !(nc = atoi(tab[2])) ||
      !(cpp = atoi(tab[3])) )
    RETURN;
  free(tab);
  tab = 0;

  method = 0;
  if (cpp<=2)
    {
      method = 1;
      if (!(colors_direct = malloc((cpp==2?65536:256)*sizeof(int))))
	RETURN;
    }
  else
    if (!(colors = malloc(nc*sizeof(*colors))))
      RETURN;

  clip_data = 0;

  i = nc;
  while (i--)
    {
      if (!(line = f(info,&pos,info_size)) ||
	  !(tab = mlx_int_str_to_wordtab(line+cpp)) )
	RETURN;
      j = 0;
      while (tab[j] && strcmp(tab[j++],"c"));

      if (!tab[j])
	RETURN;

      rgb_col = mlx_int_get_text_rgb(tab[j], tab[j+1]);
      /*      
      if ((rgb_col = mlx_int_get_text_rgb(tab[j], tab[j+1]))==-1)
	{
	  if (!(clip_data = malloc(4*width*height)) ||   // ok, nice size ..
	      !(clip_img = XCreateImage(xvar->display, xvar->visual,
					1, XYPixmap, 0, clip_data,
					width, height, 8, (width+7)/8)) )
	    RETURN;
	  memset(clip_data, 0xFF, 4*width*height);
	}
      */
      if (method)
	colors_direct[mlx_int_get_col_name(line,cpp)] = rgb_col;
      //	  rgb_col>=0?mlx_get_color_value(xvar, rgb_col):rgb_col;
      else
	{
	  colors[i].name = mlx_int_get_col_name(line,cpp);
	  colors[i].col = rgb_col; // rgb_col>=0?mlx_get_color_value(xvar,rgb_col):rgb_col;
	}
      free(tab);
      tab = 0;
    }

  if (!(img = mlx_new_image(xvar,width,height)))
    RETURN;
  //opp = img->bpp/8;
  opp = 4;


  i = height;
  data = img->buffer;
  while (i--)
    {
      if (!(line = f(info,&pos,info_size)))
	RETURN;
      x = 0;
      while (x<width)
	{
	  col = 0;
	  col_name = mlx_int_get_col_name(line+cpp*x,cpp);
	  if (method)
	    col = colors_direct[col_name];
	  else
	    {
	      j = nc;
	      while (j--)
		if (colors[j].name==col_name)
		  {
		    col = colors[j].col;
		    j = 0;
		  }
	    }
	  //	  if (col==-1)
	  //	    XPutPixel(clip_img, x, height-1-i, 0);
	  //	  else
	  if (col==-1)
	    col = 0xFF000000;
	  mlx_int_xpm_set_pixel(img, data, opp, col, x);
	  x ++;
	}
      //      data += img->size_line;
      data += img->width*4;
    }
  /*
  if (clip_data)
    {
      if (!(clip_pix = XCreatePixmap(xvar->display, xvar->root,
					   width, height, 1)) )
	RETURN;
      img->gc = XCreateGC(xvar->display, clip_pix, 0, &xgcv);
      XPutImage(xvar->display, clip_pix, img->gc, clip_img,
		0, 0, 0, 0, width, height);
      XFreeGC(xvar->display, img->gc);
      xgcv.clip_mask = clip_pix;
      xgcv.function = GXcopy;
      xgcv.plane_mask = AllPlanes;
      img->gc = XCreateGC(xvar->display, xvar->root, GCClipMask|GCFunction|
			  GCPlaneMask, &xgcv);
      XSync(xvar->display, False);
      XDestroyImage(clip_img);
    }
  */
  if (colors)
    free(colors);
  if (colors_direct)
    free(colors_direct);
  return (img);
}
// The mlx_int_parse_xpm function takes four arguments: a pointer to an mlx_ptr_t, a pointer to void, an int, and a pointer to a function that takes a pointer to a char, a pointer to an int, and an int as arguments and returns a pointer to a char.
// The function returns a pointer to void and is used to parse an XPM file and create an image from it.
// The function uses the info argument to determine the XPM file.
// The XPm file is parsed using the f argument to get a line from the file.
// A XPM file is a text file that contains a list of colors and their RGB values.


void	mlx_int_file_get_rid_comment(char *ptr, int size)
{
  int	com_begin;
  int	com_end;

  while ((com_begin = mlx_int_str_str_cote(ptr,"/*",size))!=-1)
    {
      com_end = mlx_int_str_str(ptr+com_begin+2,"*/",size-com_begin-2);
      memset(ptr+com_begin,' ',com_end+4);
    }
  while ((com_begin = mlx_int_str_str_cote(ptr,"//",size))!=-1)
    {
      com_end = mlx_int_str_str(ptr+com_begin+2,"\n",size-com_begin-2);
      memset(ptr+com_begin,' ',com_end+3);
    }
}


void	*mlx_xpm_file_to_image(mlx_ptr_t *xvar,char *file,int *width,int *height)
{
  int	fd;
  int	size;
  char	*ptr;
  mlx_img_list_t	*img;

  if ((fd = open(file,O_RDONLY))==-1 || (size = lseek(fd,0,SEEK_END))==-1 ||
      (ptr = mmap(0,size,PROT_WRITE|PROT_READ,MAP_PRIVATE,fd,0))==
      (void *)MAP_FAILED)
    {
      if (fd>=0)
	close(fd);
      return ((void *)0);
    }
  mlx_int_file_get_rid_comment(ptr, size);
  if ((img = mlx_int_parse_xpm(xvar,ptr,size,mlx_int_get_line)))
    {
      *width = img->width;
      *height = img->height;
    }
  munmap(ptr,size);
  close(fd);
  return (img);
}

void	*mlx_xpm_to_image(mlx_ptr_t *xvar,char **xpm_data,int *width,int *height)
{
  mlx_img_list_t	*img;

  if ((img = mlx_int_parse_xpm(xvar,xpm_data,0,mlx_int_static_line)))
    {
      *width = img->width;
      *height = img->height;
    }
  return (img);
}
// The mlx_xpm_to_image function takes four arguments: a pointer to an mlx_ptr_t, a pointer to a pointer to a char, a pointer to an int, and a pointer to an int.
// The function returns a pointer to void and is used to create an image from an XPM file.
// The function uses the xvar argument to determine the MLX context.
