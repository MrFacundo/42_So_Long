#ifndef WINDOW_H
# define WINDOW_H

typedef struct window
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		height;
	int		width;
}	t_window;

typedef struct s_img
{
	t_window	win;
	void	*img_ptr;
	char	*addr;
	int		height;
	int		width;
	int		bpp;
	int		endian;
	int		line_len;
}		t_img;

#endif
