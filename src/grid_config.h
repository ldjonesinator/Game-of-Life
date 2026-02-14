#define ROWS 90
#define COLS 160
#define TILES (ROWS * COLS)

#define INDICES 6
#define VERTICES 4

#define MAX_VERT (TILES * VERTICES)
#define MAX_INDX (TILES * INDICES)

#define SQR_SIZE 20
#define SQR_SPACE 2

#define WORLD_X (SQR_SIZE + SQR_SPACE) * COLS
#define WORLD_Y (SQR_SIZE + SQR_SPACE) * ROWS