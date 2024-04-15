import pygame
import random
import sys

WIDTH, HEIGHT = 800, 600

WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)

FPS = 20


def update_screen(screen, font, array, colors, swaps, comparisons):
    screen.fill(WHITE)
    for i, height in enumerate(array):
        pygame.draw.rect(screen, colors[i], (10 + i * 15, HEIGHT - height, 10, height))
    # Show comparisons and swaps
    text = font.render("Comparisons: " + str(comparisons), True, BLACK)
    screen.blit(text, (20, 20))
    text = font.render("Swaps: " + str(swaps), True, BLACK)
    screen.blit(text, (20, 50))
    pygame.display.flip()


def main():
    pygame.init()
    clock = pygame.time.Clock()
    screen = pygame.display.set_mode((WIDTH, HEIGHT))
    pygame.display.set_caption("Insertion Sort with Binary Search")
    font = pygame.font.SysFont(None, 30)
    array = [random.randint(50, 550) for _ in range(50)]  # Generate random array
    colors = [BLACK for _ in range(50)]
    swaps, comparisons = 0, 0
    cond, i, j, l, r, j = 0, 1, 0, 0, 0, 0
    running = True
    while running:
        clock.tick(FPS)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
        if cond == 0:
            if i >= len(array):
                cond = 3
                continue
            colors[i] = RED
            l, r = 0, i
            cond = 1
            while l != r:
                m = (l + r) // 2
                if array[m] < array[i]:
                    l = m + 1
                elif array[m] > array[i]:
                    r = m
                else:
                    l = r = m
                comparisons += 1
            j = i
        elif cond == 1:
            if j > l:
                array[j], array[j - 1] = array[j - 1], array[j]
                colors[j], colors[j - 1] = colors[j - 1], colors[j]
                j -= 1
                swaps += 1
            else:
                colors[j] = BLACK
                i += 1
                cond = 0
        update_screen(screen, font, array, colors, swaps, comparisons)
    pygame.quit()
    sys.exit()


main()
