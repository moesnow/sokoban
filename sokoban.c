#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define MAP_SIZE 6
#define PLAYER 'P'
#define BOX 'B'
#define TARGET 'T'
#define WALL '#'
#define EMPTY ' '

void printMap(char map[][MAP_SIZE]) {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
}

int getch() {
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}

int main() {
    char map[MAP_SIZE][MAP_SIZE] = {
        {WALL, WALL, WALL, WALL, WALL, WALL},
        {WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL},
        {WALL, EMPTY, TARGET, BOX, EMPTY, WALL},
        {WALL, EMPTY, EMPTY, PLAYER, EMPTY, WALL},
        {WALL, EMPTY, EMPTY, EMPTY, EMPTY, WALL},
        {WALL, WALL, WALL, WALL, WALL, WALL}};

    int playerX = 3;  // 初始玩家位置
    int playerY = 3;

    int win = 0;  // 胜利标志

    while (!win) {
        system("clear");  // 清屏

        printMap(map);

        char move = getch();  // 获取键盘输入

        int targetX, targetY;  // 目标位置

        switch (move) {
            case 'w':  // 上
                targetX = playerX - 1;
                targetY = playerY;
                break;
            case 's':  // 下
                targetX = playerX + 1;
                targetY = playerY;
                break;
            case 'a':  // 左
                targetX = playerX;
                targetY = playerY - 1;
                break;
            case 'd':  // 右
                targetX = playerX;
                targetY = playerY + 1;
                break;
            default:  // 非移动键
                continue;
        }

        if (map[targetX][targetY] == EMPTY) {  // 空格
            map[playerX][playerY] = EMPTY;
            map[targetX][targetY] = PLAYER;
            playerX = targetX;
            playerY = targetY;
        } else if (map[targetX][targetY] == BOX) {  // 箱子
            int boxTargetX = targetX + (targetX - playerX);
            int boxTargetY = targetY + (targetY - playerY);

            if (map[boxTargetX][boxTargetY] == EMPTY || map[boxTargetX][boxTargetY] == TARGET) {
                map[playerX][playerY] = EMPTY;
                map[targetX][targetY] = PLAYER;
                map[boxTargetX][boxTargetY] = BOX;
                playerX = targetX;
                playerY = targetY;
            }
        }

        // 检查是否胜利
        win = 1;
        for (int i = 0; i < MAP_SIZE; i++) {
            for (int j = 0; j < MAP_SIZE; j++) {
                if (map[i][j] == TARGET) {
                    win = 0;
                    break;
                }
            }
        }
    }

    system("clear");  // 清屏
    printMap(map);    // 最终画面
    printf("\nCongratulations! You won the game.\n");

    return 0;
}
