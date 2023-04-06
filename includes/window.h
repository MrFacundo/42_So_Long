#ifndef WINDOW_H
# define WINDOW_H

typedef struct	s_vector
{
	int	x;
	int	y;
}				t_vector;

typedef struct	s_window {
	void		*win_ptr;
	t_vector	size;
}				t_window;

typedef struct	s_image {
	void		*img_ptr;
	t_vector	size;
	char		*pixels;
	int			bits_per_pixel;
	int			line_len;
	int			endian;
}				t_image;

typedef struct s_map
{
	int		rows;
	int		cols;
	int		px;
	int		a;
	int		b;
	char	**lines;
}	t_map;

typedef struct	s_program {
	void		*mlx_ptr;
	t_window	window;
	t_map		map;
	char		**lines;
	void		*wall;
	void		*collectable;
	void		*exit;
	void		*player;
}				t_program;


#endif
