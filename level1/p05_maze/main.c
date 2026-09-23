#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <conio.h>

#define ROW 20
#define COL 20

char mapStr[ROW][COL + 1] = {
    "####################",
    "#S#.......#........#",
    "#.#.#####.#.######.#",
    "#...#...#.#.#....#.#",
    "###.#.#.#.#.#.##.#.#",
    "#...#.#...#.#.#..#.#",
    "#.###.#####.#.#.##.#",
    "#.....#.....#.#....#",
    "#####.#######.####.#",
    "#.....#.......#....#",
    "#.###.#.#####.#.##.#",
    "#.#...#.#...#.#.#..#",
    "#.#.###.#.#.#.#.#.##",
    "#.#.....#.#.#.#.#..#",
    "#.#######.#.#.#.##.#",
    "#.........#...#....#",
    "##########.######.##",
    "#...............#E.#",
    "#.###############..#",
    "####################"
};

bool wall[ROW][COL];
int px, py;
int ex, ey;

void initMap() {
    for (int y = 0; y < ROW; y++) {
        for (int x = 0; x < COL; x++) {
            char c = mapStr[y][x];
            wall[y][x] = (c == '#');
            if (c == 'S') { px = x; py = y; }
            if (c == 'E') { ex = x; ey = y; }
        }
    }
}

void draw() {
    system("cls");
    for (int y = 0; y < ROW; y++) {
        for (int x = 0; x < COL; x++) {
            if (x == px && y == py) {
                printf("♥");
            } else if (wall[y][x]) {
                printf("█");
            } else if (x == ex && y == ey) {
                printf("★");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("方向键移动，到达 ★ 胜利\n");
}

int main() {
    initMap();
    while (true) {
        draw();
        if (px == ex && py == ey) {
            printf("恭喜你赢了！\n");
            break;
        }
        int ch = _getch();
        if (ch == 0xE0 || ch == 0x00) {
            ch = _getch();
        }
        int nx = px, ny = py;
        switch (ch) {
            case 72: ny--; break;
            case 80: ny++; break;
            case 75: nx--; break;
            case 77: nx++; break;
            default: continue;
        }
        if (nx < 0 || nx >= COL || ny < 0 || ny >= ROW) continue;
        if (wall[ny][nx]) continue;
        px = nx;
        py = ny;
    }
    return 0;
}
