#include "cub3d.h"

/*
** ft_put_pixel_to_img
** --------------------------------------------------------------------------
** @brief Coloca um pixel na imagem (buffer) do MiniLibX na posição (x, y)
**        com a cor especificada.
**
** Esta função é otimizada para trabalhar com imagens de 32 bits por pixel
** (comumente usadas no MiniLibX). Ela assume que a cor de entrada está no
** formato 0xAARRGGBB (Alpha, Red, Green, Blue). O MiniLibX e o sistema
** se encarregam da correta ordenação de bytes (endianness) ao escrever
** diretamente no ponteiro de 4 bytes.
**
** @param game Um ponteiro para a estrutura t_game, contendo os dados da imagem.
** @param x A coordenada X do pixel.
** @param y A coordenada Y do pixel.
** @param color A cor do pixel no formato 0xAARRGGBB.
*/
void	ft_put_pixel_to_img(t_game *game, int x, int y, int color)
{
    char	*dst;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return ;
    // Calcula o endereço do primeiro byte do pixel no buffer da imagem
    // game->data é o início do buffer
    // y * game->size_line avança para a linha correta
    // x * (game->bpp / 8) avança para a coluna correta, considerando bytes por pixel
    dst = game->data + (y * game->size_line + x * (game->bpp / 8));

    // Atribui diretamente o valor da cor (32 bits) ao endereço do pixel.
    // Esta é a maneira mais eficiente para imagens de 32 bpp,
    // deixando a manipulação de endianness para o sistema/MiniLibX.
    *(unsigned int *)dst = color;
}

/*
** ft_clear_image
** --------------------------------------------------------------------------
** @brief Limpa toda a área da imagem (buffer) com uma cor específica.
**
** Esta função é otimizada para preencher a imagem com uma cor arbitrária
** de forma eficiente, iterando sobre o buffer de imagem em blocos de 4 bytes.
**
** @param game Um ponteiro para a estrutura t_game, contendo os dados da imagem.
** @param color A cor para preencher a imagem (no formato 0xAARRGGBB).
*/
void	ft_clear_image(t_game *game, int color)
{
    // Esta é a maneira mais eficiente de preencher uma imagem de 32 bpp
    // com uma cor arbitrária, aproveitando que cada pixel é um unsigned int.
    unsigned int *img_buffer_int;
    int           total_pixels;
    int           i;

    img_buffer_int = (unsigned int *)game->data;
    // O total de pixels é (tamanho da linha em pixels) * HEIGHT
    // (game->size_line / (game->bpp / 8)) dá o número de pixels por linha
    total_pixels = (game->size_line / (game->bpp / 8)) * HEIGHT;
    i = 0;
    while (i < total_pixels)
    {
        img_buffer_int[i] = color;
        i++;
    }
}


/*
** ft_draw_filled_square
** --------------------------------------------------------------------------
** @brief Desenha um quadrado preenchido na imagem (buffer).
**
** @param game Um ponteiro para a estrutura t_game.
** @param x_start A coordenada X superior esquerda do quadrado.
** @param y_start A coordenada Y superior esquerda do quadrado.
** @param size O lado do quadrado em pixels.
** @param color A cor do quadrado no formato 0xAARRGGBB.
*/
void	ft_draw_filled_square(t_game *game, int x_start, int y_start, int size, int color)
{
    int	x;
    int	y;

    y = 0;
    while (y < size)
    {
        x = 0;
        while (x < size)
        {
            ft_put_pixel_to_img(game, x_start + x, y_start + y, color);
            x++;
        }
        y++;
    }
}

/*
** ft_draw_map
** --------------------------------------------------------------------------
** @brief Desenha o minimapa na imagem (buffer) com base na matriz do mapa.
**
** As paredes ('1') são desenhadas como quadrados preenchidos.
**
** @param game Um ponteiro para a estrutura t_game, contendo o mapa e os
**             dados da imagem.
*/
void	ft_draw_map(t_game *game)
{
    int	x;
    int	y;
    int	wall_color; // Cor para as paredes (formato 0xAARRGGBB)

    // Definindo a cor da parede: vermelho opaco (Alpha FF, Red FF, Green 00, Blue 00)
    // Usamos 0xFF000000 para vermelho opaco se o MiniLibX espera 0xAARRGGBB
    // (ex: FF 00 00 00 -> A R G B). Se ele espera 0xBBGGRRAA, isso seria diferente.
    // O valor 0xFF0000 é comum para vermelho (0x00RRGGBB). Vou manter a consistência.
    wall_color = 0x00FF0000; // Vermelho completo. O byte Alpha será tratado automaticamente por mlx_new_image ou estará em 0.

    y = 0;
    while (game->map[y]) // Itera pelas linhas do mapa
    {
        x = 0;
        while (game->map[y][x]) // Itera pelas colunas da linha atual
        {
            if (game->map[y][x] == '1')
            {
                // Desenha um quadrado preenchido para representar a parede
                ft_draw_filled_square(game, x * BLOCK, y * BLOCK, BLOCK, wall_color);
            }
            // Adicione outras condições aqui para desenhar jogador, chão, etc.
            x++;
        }
        y++;
    }
}