/*
 * 简单进销存
 * 库存文件 stock.txt 每行格式：型号 数量
 */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ITEMS 100
#define MODEL_LEN 32
#define STOCK_FILE "stock.txt"

typedef struct {
    char model[MODEL_LEN];
    int quantity;
} Item;

Item items[MAX_ITEMS];
int itemCount = 0;

int findItem(const char *model) {
    for (int i = 0; i < itemCount; i++) {
        if (strcmp(items[i].model, model) == 0) {
            return i;
        }
    }
    return -1;
}

void loadStock(const char *fileName) {
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        return;
    }
    itemCount = 0;
    while (itemCount < MAX_ITEMS &&
           fscanf(fp, "%31s %d", items[itemCount].model, &items[itemCount].quantity) == 2) {
        itemCount++;
    }
    fclose(fp);
}

void saveStock(const char *fileName) {
    FILE *fp = fopen(fileName, "w");
    if (fp == NULL) {
        printf("无法保存库存文件 %s\n", fileName);
        return;
    }
    for (int i = 0; i < itemCount; i++) {
        fprintf(fp, "%s %d\n", items[i].model, items[i].quantity);
    }
    fclose(fp);
}

void showItems() {
    if (itemCount == 0) {
        printf("库存为空。\n");
        return;
    }
    printf("序号\t型号\t数量\n");
    int total = 0;
    for (int i = 0; i < itemCount; i++) {
        printf("%d\t%s\t%d\n", i + 1, items[i].model, items[i].quantity);
        total += items[i].quantity;
    }
    printf("共 %d 种货物，总数量：%d\n", itemCount, total);
}

void clearInput() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

void stockIn() {
    char model[MODEL_LEN];
    int quantity;
    printf("请输入入库型号和数量（例如 A-1001 10）：");
    if (scanf("%31s %d", model, &quantity) != 2 || quantity <= 0) {
        printf("输入无效。\n");
        clearInput();
        return;
    }
    int index = findItem(model);
    if (index == -1) {
        if (itemCount >= MAX_ITEMS) {
            printf("库存已满，无法新增货物。\n");
            return;
        }
        index = itemCount;
        itemCount++;
        strcpy(items[index].model, model);
        items[index].quantity = 0;
    }
    items[index].quantity += quantity;
    printf("入库成功，%s 当前数量：%d\n", items[index].model, items[index].quantity);
}

void stockOut() {
    char model[MODEL_LEN];
    int quantity;
    printf("请输入出库型号和数量（例如 A-1001 3）：");
    if (scanf("%31s %d", model, &quantity) != 2 || quantity <= 0) {
        printf("输入无效。\n");
        clearInput();
        return;
    }
    int index = findItem(model);
    if (index == -1) {
        printf("没有型号为 %s 的货物。\n", model);
        return;
    }
    if (items[index].quantity < quantity) {
        printf("库存不足，%s 当前数量：%d\n", model, items[index].quantity);
        return;
    }
    items[index].quantity -= quantity;
    printf("出库成功，%s 剩余数量：%d\n", model, items[index].quantity);
}

void showMenu() {
    printf("\n===== 简单进销存 =====\n");
    printf("1. 显示存货列表\n");
    printf("2. 入库\n");
    printf("3. 出库\n");
    printf("0. 退出程序\n");
    printf("请选择：");
}

int main() {
    loadStock(STOCK_FILE);
    while (true) {
        showMenu();
        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("输入无效，请重新选择。\n");
            clearInput();
            continue;
        }
        switch (choice) {
            case 1:
                showItems();
                break;
            case 2:
                stockIn();
                break;
            case 3:
                stockOut();
                break;
            case 0:
                saveStock(STOCK_FILE);
                printf("库存已保存，程序退出。\n");
                return 0;
            default:
                printf("没有这个选项，请重新选择。\n");
                break;
        }
    }
}
