#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/include/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>

# define SCREEN_X 1024
# define SCREEN_Y 512
# define FOV 60 // field of view

# if OS == 1
#  include "../minilibx-linux/mlx.h"
#  define ESC 65307
#  define LEFT 65361
#  define RIGHT 65363
#  define UP 65362
#  define DOWN 65364
#  define SHIFT_RIGHT 65506
#  define CTRL_RIGHT 65508
#  define W 119
#  define A 97
#  define S 115
#  define D 100
#  define SHIFT_LEFT 65505
#  define CTRL_LEFT 65507
#  define TAB 65289
#  define INCREASE 43
#  define DECREASE 45
#  define R 114
#  define L 108
#  define H 104
# elif OS == 2
# include "../minilibx/mlx.h"
#  define ESC 53
#  define LEFT 123
#  define RIGHT 124
#  define UP 126
#  define DOWN 125
#  define SHIFT_RIGHT
#  define CTRL_RIGHT
#  define W 13
#  define A 0
#  define S 1
#  define D 2
#  define SHIFT_LEFT
#  define CTRL_RIGHT
#  define TAB
#  define INCREASE 24
#  define DECREASE 27
#  define R 15
#  define L
#  define H
# endif

typedef struct s_map
{
	char	*map_folder; 	//? Ficheiro do mapa
	int		fd;			 	//? Fd para usar quando se abre o mapa
	char	**area;      	//? Array com o mapa
	int		map_y;       	//? Colunas do mapa
	int		map_x;       	//? Linhas do mapa
	//! Tudo que tinha haver com a parte do raytracer meti noutra estrutura
	int		dir_x;       	//? Valor de x do jogador (câmara está a olhar)
	int		dir_y;       	//? Valor de y do jogador (câmara está a olhar)
	int		plane_x;     	//? Posição de x da perpendicular á visão do jogador (plano da câmara)
	int		plane_y;     	//? Posição de y da perpendicular á visão do jogador (plano da câmara)
}				t_map;

typedef struct s_data
{
	void	*mlx;			//? Instância da mlx
	void	*win;			//? Janela da mlx
}				t_data;

typedef	struct s_playerPos {
	int		row;			//? Linha (x) onde o jogador está posicionado
	int		col;			//? Coluna (y) onde o jogador está posicionado
	char	orientation;	//? Orientação do jogador (N, S, E, W)
} t_playerPos;

typedef struct s_ray {
	double	*ray_dir_x;  	//? array raios x
	double	ray_dir_x_2; 	//? Direção do raio no plano em x para o pixel no plano da câmara
	double	*ray_dir_y;  	//? array raios y
	double	ray_dir_y_2; 	//? Direção do raio no plano em y para o pixel no plano da câmara
	double	*ray_pos_x;  	//? array coordenada do raio x
	double	*ray_pos_y;  	//? array coordenada do raio x
	double	screen_x;	 	//? Index do x relativamente á tela
	int		map_x;			//? Coordenada x no grid do mapa onde o raio está a interceptar
	int		map_y;			//? Coordenada y no grid do mapa onde o raio está a interceptar
	double	side_dist_x;	//? Distância inicial que o raio percorre até chegar ao primeiro x no grid
	double	side_dist_y;	//? Distância inicial que o raio percorre até chegar ao primeiro y no grid
	double	delta_dist_x;	//? Distância que o raio fez desde um lado do grid x até ao outro
	double	delta_dist_y;	//? Distância que o raio fez desde um lado do grid y até ao outro
} t_ray;

typedef struct s_game
{
	t_map		map;		//? Estrutura com as informações do mapa
	t_data		data;		//? Estrutura com as informações para a mlx
	t_ray		ray;		//? Estrutura com as informações para o raycasting
	t_playerPos pos;		//? Estrutura com as informações do jogador
}				t_game;

//* [src/map_check.c]
void map_validations(t_game *game);
t_playerPos	get_position(t_map *map);
void	set_direction(t_game *game, t_playerPos position);
void	calculate_rays(t_game *game);
void	render_rays(t_game *game);

void	init_game(t_game *game);

#endif