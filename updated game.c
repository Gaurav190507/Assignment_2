#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

/* Faster screen redraw */
void clear_screen_fast() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {0, 0};
    SetConsoleCursorPosition(h, pos);
}

// Set console text color
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main() {

    srand(time(0));  // removed background color

    int x = 1;              // player lane
    int score = 0;
    int speed = 120;
    int lives = 3;

    int step1 = 0, step2 = -5;
    int obs1 = rand() % 3;
    int obs2 = rand() % 3;

    while (1) {

        // ---- INPUT (A/D + Arrow keys) ----
        if (_kbhit()) {
            int ch = getch();

            // Arrow keys give prefix (-32 or 224)
            if (ch == -32 || ch == 224) ch = getch();

            // A key or Left Arrow
            if ((ch == 'a' || ch == 'A' || ch == 75) && x > 0) x--;

            // D key or Right Arrow
            if ((ch == 'd' || ch == 'D' || ch == 77) && x < 2) x++;
        }

        // ---- DRAW FRAME ----
        clear_screen_fast();
        printf("|--- --- ---|   SCORE: %d   LIVES: %d\n\n", score, lives);

        // Draw obstacles
        for (int i = 0; i < 10; i++) {
            if (i == step1) {
                if (obs1 == 0) printf("| %c        |\n", 1);
                else if (obs1 == 1) printf("|     %c    |\n", 1);
                else printf("|        %c |\n", 1);
            }
            else if (i == step2) {
                if (obs2 == 0) printf("| %c        |\n", 1);
                else if (obs2 == 1) printf("|     %c    |\n", 1);
                else printf("|        %c |\n", 1);
            }
            else {
                printf("|           |\n");
            }
        }

        // ---- PLAYER (Blue) ----
        setColor(9); // Blue
        printf("|"); // left border
        for (int i = 0; i < 9; i++) {
            if (i == x * 5) printf("%c", 6); // player appears in correct lane
            else printf(" ");
        }
        printf("|\n");
        setColor(7); // Reset

        // ---- COLLISION ----
        int hit = 0;
        if (step1 == 10 && x == obs1) hit = 1;
        if (step2 == 10 && x == obs2) hit = 1;

        if (hit) {
            lives--;
            Beep(600, 120);

            if (lives == 0) {
                printf("\nGAME OVER! FINAL SCORE: %d\n", score);
                break;
            }
        }

        Sleep(speed);

        // Move obstacles
        step1++;
        step2++;

        // Reset + score
        if (step1 > 10) {
            step1 = 0;
            obs1 = rand() % 3;
            score++;
        }
        if (step2 > 10) {
            step2 = 0;
            obs2 = rand() % 3;
            score++;
        }

        // Speed up
        if (score > 0 && score % 5 == 0 && speed > 40) speed -= 5;
    }

    return 0;
}

