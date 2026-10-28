/*
 * 推箱子小游戏
 * levels.txt 中每关固定 10 行、每行 12 个字符，关卡之间用空行分隔。
 * 地图符号：# 墙、空格 地板、. 目标、$ 箱子、* 箱子在目标上、@ 玩家、+ 玩家在目标上
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#define ROW 10
#define COL 12
#define MAX_LEVELS 8
#define LEVEL_FILE "levels.txt"
#define SCORE_FILE "scores.txt"

char levels[MAX_LEVELS][ROW][COL + 1];
int levelCount = 0;

char board[ROW][COL];
int px, py;
int steps;
int boxCount;

bool readMap(FILE *fp, char map[ROW][COL + 1]) {
    char line[128];
    for (int y = 0; y < ROW; y++) {
        do {
            if (fgets(line, sizeof(line), fp) == NULL) {
                return false;
            }
            line[strcspn(line, "\r\n")] = '\0';
        } while (line[0] == '\0');
        if (strlen(line) != COL) {
            return false;
        }
        strcpy(map[y], line);
    }
    return true;
}

bool loadLevels(const char *fileName) {
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        return false;
    }
    levelCount = 0;
    while (levelCount < MAX_LEVELS && readMap(fp, levels[levelCount])) {
        levelCount++;
    }
    fclose(fp);
    return levelCount > 0;
}

void loadLevel(int index) {
    px = 0;
    py = 0;
    steps = 0;
    boxCount = 0;
    for (int y = 0; y < ROW; y++) {
        for (int x = 0; x < COL; x++) {
            char cell = levels[index][y][x];
            if (cell == '@' || cell == '+') {
                px = x;
                py = y;
                cell = (cell == '+') ? '.' : ' ';
            } else if (cell == '$' || cell == '*') {
                boxCount++;
            }
            board[y][x] = cell;
        }
    }
}

void draw(int index) {
    system("cls");
    printf("第 %d/%d 关    步数：%d\n", index + 1, levelCount, steps);
    for (int y = 0; y < ROW; y++) {
        for (int x = 0; x < COL; x++) {
            if (x == px && y == py) {
                printf("我");
            } else if (board[y][x] == '#') {
                printf("██");
            } else if (board[y][x] == '.') {
                printf("◎");
            } else if (board[y][x] == '$') {
                printf("箱");
            } else if (board[y][x] == '*') {
                printf("★");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
    printf("方向键移动，把全部箱子推到 ★ 上即可过关\n");
}

void tryMove(int dx, int dy) {
    int nx = px + dx;
    int ny = py + dy;
    if (nx < 0 || nx >= COL || ny < 0 || ny >= ROW) {
        return;
    }
    char next = board[ny][nx];
    if (next == '#') {
        return;
    }
    if (next == '$' || next == '*') {
        int bx = nx + dx;
        int by = ny + dy;
        if (bx < 0 || bx >= COL || by < 0 || by >= ROW) {
            return;
        }
        char beyond = board[by][bx];
        if (beyond == '#' || beyond == '$' || beyond == '*') {
            return;
        }
        board[by][bx] = (beyond == '.') ? '*' : '$';
        board[ny][nx] = (next == '*') ? '.' : ' ';
    }
    px = nx;
    py = ny;
    steps++;
}

bool isWin() {
    int onGoal = 0;
    for (int y = 0; y < ROW; y++) {
        for (int x = 0; x < COL; x++) {
            if (board[y][x] == '*') {
                onGoal++;
            }
        }
    }
    return boxCount > 0 && onGoal == boxCount;
}

void saveScore(int index, int stepCount) {
    FILE *fp = fopen(SCORE_FILE, "a");
    if (fp == NULL) {
        printf("无法写入成绩文件 %s\n", SCORE_FILE);
        return;
    }
    fprintf(fp, "第 %d 关    步数：%d\n", index + 1, stepCount);
    fclose(fp);
}

int main() {
    if (!loadLevels(LEVEL_FILE)) {
        printf("无法读取关卡文件 %s\n", LEVEL_FILE);
        return 1;
    }
    for (int i = 0; i < levelCount; i++) {
        loadLevel(i);
        while (true) {
            draw(i);
            if (isWin()) {
                break;
            }
            int ch = _getch();
            if (ch == 0xE0 || ch == 0x00) {
                ch = _getch();
            }
            int dx = 0;
            int dy = 0;
            switch (ch) {
                case 72: dy = -1; break;
                case 80: dy = 1; break;
                case 75: dx = -1; break;
                case 77: dx = 1; break;
                default: continue;
            }
            tryMove(dx, dy);
        }
        draw(i);
        printf("第 %d 关完成，步数：%d\n", i + 1, steps);
        saveScore(i, steps);
        if (i + 1 < levelCount) {
            printf("按任意键进入下一关...\n");
            _getch();
        }
    }
    printf("全部关卡通关！\n");
    return 0;
}
