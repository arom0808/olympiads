import pygame

# colors used in game
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
GRAY = (128, 128, 128)

# game control variables
RECT_SIZE = 20
COLUMNS = int(800 / RECT_SIZE)
ROWS = int(600 / RECT_SIZE)
GAP_SIZE = 1
DELAY = 1000
VELOCITY = 20

# initial setup
pygame.init()
screen = pygame.display.set_mode([800, 600])
pygame.display.set_caption("Tetris")
clock = pygame.time.Clock()

# create an array to store x, y position for each piece
grid = [[(GAP_SIZE + RECT_SIZE * x + GAP_SIZE * x,
          GAP_SIZE + RECT_SIZE * y + GAP_SIZE * y)
         for x in range(COLUMNS)] for y in range(ROWS)]

# game loop
while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()

    # game logic goes here

    # draw game state
    for row in range(ROWS):
        for col in range(COLUMNS):
            pygame.draw.rect(screen, GRAY, grid[row][col] + (RECT_SIZE, RECT_SIZE))

    pygame.display.flip()
    clock.tick(VELOCITY)