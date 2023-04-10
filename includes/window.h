#ifndef WINDOW_H
# define WINDOW_H

# define BUFFER_SIZE 42
# define ESC 53
# define LEFT 0
# define RIGHT 2
# define DOWN 1
# define UP 13
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
typedef struct s_player
{
	int			c;
	int			moves;
	t_vector	attempt;
	t_vector	current;
}	t_player;

typedef struct	s_program {
	void		*mlx_ptr;
	t_window	window;
	t_map		map;
	char		**lines;
	void		*floor;
	void		*wall;
	void		*collectable;
	void		*exit;
	t_player	player;
}				t_program;


#endif
