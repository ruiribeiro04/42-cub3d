- Se o teu ft_error chama ft_free_game, vais ter o mesmo crash (Segfault) se o raycasting falhar, porque estás a limpar memória dentro do loop.

```c
int	ft_draw_loop(t_game *game)
{
    // ...
    if (ft_raycasting(game) == 1)
        ft_error(game, "Raycasting failed!"); // <--- PERIGO
    // ...
}
```

Solução recomendada para erros dentro do loop:
Cria uma flag de erro ou usa o mlx_loop_end também no erro, e deixa o main limpar.

No entanto, para resolver o erro do Valgrind que mostraste (que acontece ao sair com ESC), a alteração no passo 1 é a solução.

---

- Rewrite do codigo das texturas, para ficar mais simples e menos jank
- norminette
- testar se compila nos PCs da 42

---

# Comecar a trabalhar no `bonus`

- Implementar sistema de mouse aim
    - potencialmente mudar os keycodes, mas nao sei
- sistema de portas que abre e fecha
    - Reconhecer simbolo de porta no mapa
    - dar draw a uma textura de porta
    - implementar logica de close e open
        Colisao do player fica on e off, conforme o estado da porta
- minimapa
    - nao faco a minima
    - seria interessante carregar no tab e surgir o mapa
- sprites animados
    - meter so para ter 125!
    - potencialmente fazer animacao das paredes, com fogo ou algo do genero

---

## Tracked TODOs

- [cub3D-#TBD] srcs/textures/ft_textures.c: refactor texture column rendering — see Epic 5 S5.2
- [cub3D-#TBD] srcs_bonus/textures/ft_textures.c: refactor texture column rendering — see Epic 5 S5.2
