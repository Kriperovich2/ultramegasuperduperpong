#include <switch.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24

#define PADDLE_HEIGHT 6
#define BALL_CHAR 'O'
#define PADDLE_CHAR '|'

typedef enum { MENU, GAME } GameState;
typedef enum { SINGLE, TWO_PLAYER } GameMode;

GameState state = MENU;
GameMode mode = SINGLE;

int ballX, ballY;
int ballVX = 1, ballVY = 1;

int paddle1Y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
int paddle2Y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;

int score1 = 0, score2 = 0;

int frameCount = 0;
int ballMoveCounter = 0;
int cpuMoveCounter = 0;
int cpuDirection = 1;

void resetBall() {
    ballX = SCREEN_WIDTH / 2;
    ballY = SCREEN_HEIGHT / 2;
    ballVX = (rand() % 2 == 0) ? 1 : -1;
    ballVY = (rand() % 2 == 0) ? 1 : -1;
    ballMoveCounter = 0;
}

void resetGame() {
    paddle1Y = paddle2Y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    score1 = score2 = 0;
    cpuDirection = 1;
    resetBall();
}

void drawPaddle(int x, int y) {
    for (int i = 0; i < PADDLE_HEIGHT; i++) {
        if (y + i >= 1 && y + i < SCREEN_HEIGHT)
            printf("\x1b[%d;%dH%c", y + i + 1, x + 1, PADDLE_CHAR);
    }
}

void drawScreen() {
    consoleClear();

    // Верх и низ — белые полосы
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        printf("\x1b[1;%dH-", x + 1);
        printf("\x1b[%d;%dH-", SCREEN_HEIGHT, x + 1);
    }

    // Ракетки
    drawPaddle(2, paddle1Y);
    drawPaddle(SCREEN_WIDTH - 3, paddle2Y);

    // Мяч
    printf("\x1b[%d;%dH%c", ballY + 1, ballX + 1, BALL_CHAR);

    // Счёт
    printf("\x1b[1;1HPlayer1: %d", score1);
    if (mode == SINGLE)
        printf("  CPU: %d", score2);
    else
        printf("  Player2: %d", score2);
}

void drawMenu() {
    consoleClear();
    printf("\x1b[10;30HPING PONG (Switch)");
    printf("\x1b[12;28HMode: %s", mode == SINGLE ? "Single Player" : "Two Player");
    printf("\x1b[14;28HPress A to toggle mode");
    printf("\x1b[16;28HPress + to start");
    printf("\x1b[18;28HPress - to exit");
}

int main(int argc, char* argv[]) {
    consoleInit(NULL);
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);
    PadState pad;
    padInitializeDefault(&pad);

    resetGame();

    while (appletMainLoop()) {
        padUpdate(&pad);
        u64 kDown = padGetButtonsDown(&pad);
        u64 kHeld = padGetButtons(&pad);

        if (kDown & HidNpadButton_Minus) break;

        if (state == MENU) {
            if (kDown & HidNpadButton_A)
                mode = (mode == SINGLE) ? TWO_PLAYER : SINGLE;

            if (kDown & HidNpadButton_Plus) {
                resetGame();
                state = GAME;
            }

            drawMenu();
        } else {
            // Платформа 1 — вверх/вниз
            if (frameCount % 3 == 0) {
                if (kHeld & HidNpadButton_Up) paddle1Y--;
                if (kHeld & HidNpadButton_Down) paddle1Y++;
            }

            if (paddle1Y < 1) paddle1Y = 1;
            if (paddle1Y + PADDLE_HEIGHT > SCREEN_HEIGHT - 1)
                paddle1Y = SCREEN_HEIGHT - PADDLE_HEIGHT - 1;

            // Платформа 2
            if (mode == SINGLE) {
                if (cpuMoveCounter++ >= 6) {
                    paddle2Y += cpuDirection;
                    if (paddle2Y <= 1 || paddle2Y + PADDLE_HEIGHT >= SCREEN_HEIGHT - 1)
                        cpuDirection *= -1;
                    cpuMoveCounter = 0;
                }
            } else {
                if (frameCount % 3 == 0) {
                    if (kHeld & HidNpadButton_X) paddle2Y--;
                    if (kHeld & HidNpadButton_A) paddle2Y++;
                }
            }

            if (paddle2Y < 1) paddle2Y = 1;
            if (paddle2Y + PADDLE_HEIGHT > SCREEN_HEIGHT - 1)
                paddle2Y = SCREEN_HEIGHT - PADDLE_HEIGHT - 1;

            // Движение мяча — замедленное
            if (ballMoveCounter++ >= 3) {
                ballX += ballVX;
                ballY += ballVY;

                if (ballY <= 1 || ballY >= SCREEN_HEIGHT - 2)
                    ballVY *= -1;

                if (ballX == 3 &&
                    ballY >= paddle1Y && ballY < paddle1Y + PADDLE_HEIGHT)
                    ballVX *= -1;

                if (ballX == SCREEN_WIDTH - 4 &&
                    ballY >= paddle2Y && ballY < paddle2Y + PADDLE_HEIGHT)
                    ballVX *= -1;

                if (ballX <= 0) { score2++; resetBall(); }
                if (ballX >= SCREEN_WIDTH - 1) { score1++; resetBall(); }

                ballMoveCounter = 0;
            }

            drawScreen();
        }

        frameCount++;
        consoleUpdate(NULL);
    }

    consoleExit(NULL);
    return 0;
}
