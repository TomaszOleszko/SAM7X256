#include <stdio.h>
#include <targets\AT91SAM7.h>
#include "PCF8833U8_lcd.h"

#define up PIOA_SODR_P9
#define center_push PIOA_SODR_P15
#define left PIOA_SODR_P7
#define down PIOA_SODR_P8
#define right PIOA_SODR_P14

typedef struct menu_struct menu_t;

struct menu_struct {
    const char *name;
    menu_t *next; // Następny element
    menu_t *prev; // Poprzeni element
    menu_t *child; // Dziecko danego wskaźnika
    menu_t *parent; // Rodzic danego wskaźnika
    void ( *menu_function)(void);
};

__attribute__ ((section(".fast")))
void delay(int n) //procedura opoznienia
{
    volatile int i;
    for (i = 3000 * n; i > 0; i--) {
        __asm__("nop");
    }
}

void printImg1(void) {
    //
}

void printImg2(void) {
    //
}

void showAnimation(void) {
    while (1) {
        printImg1();
        delay(500);
        printImg2();
        delay(500);
        if (!(PIOA_PDSR & left) {
            break;
        }
    }
}

void showImgAndTxt(void) {
    //
}

void showCircle(void) {
    LCDSetCircle(65, 65, 7, BLACK);
}

void showSquare(void) {
    LCDSetRect(43, 43, 88, 88, 1, BLACK);
}

void showTriangle(void) {
    LCDSetLine(95, 95, 95, 35, BLACK);
    LCDSetLine(95, 35, 43, 65, BLACK);
    LCDSetLine(43, 65, 95, 95, BLACK);
}

void showTrapeze(void) {
    LCDSetLine(30, 20, 30, 110, BLACK);
    LCDSetLine(30, 20, 80, 5, BLACK);
    LCDSetLine(80, 125, 30, 110, BLACK);
    LCDSetLine(80, 5, 80, 125, BLACK);
}

void showAuthor(void) {
    LCDPutStr("Tomasz_Oleszko", 43, 11, MEDIUM, BLACK, GREEN);
    LCDPutStr("GR 7.5", 64, 45, MEDIUM, BLACK, GREEN);
}

menu_t menu_1, menu_2, menu_3, menu_4, sub_menu_1_1, sub_menu_1_2, sub_menu_1_3, sub_menu_3_1, sub_menu_3_2, sub_menu_3_3, sub_menu_3_4;
menu_t menu_1 = {
        "1. Obraz",
        &menu_2,
        NULL,
        &sub_menu_1_1,
        NULL,
        NULL
};
menu_t menu_2 = {
        "2. Tekst+obraz",
        &menu_3,
        &menu_1,
        NULL,
        NULL,
        showImgAndTxt
};
menu_t menu_3 = {
        "3. Figury",
        &menu_4,
        &menu_2,
        &sub_menu_3_1,
        NULL,
        NULL
};
menu_t menu_4 = {
        "4. O Autorze",
        NULL,
        &menu_3,
        NULL,
        NULL,
        showAuthor
};

menu_t sub_menu_1_1 = {
        "1. Obraz 1",
        &sub_menu_1_2,
        NULL,
        NULL,
        &menu_1,
        printImg1
};
menu_t sub_menu_1_2 = {
        "2. Obraz 2",
        &sub_menu_1_3,
        &sub_menu_1_1,
        NULL,
        &menu_1,
        printImg2
};
menu_t sub_menu_1_3 = {
        "3. Animacja",
        NULL,
        &sub_menu_1_2,
        NULL,
        &menu_1,
        showAnimation
};
menu_t sub_menu_3_1 = {
        "1. Okrag",
        &sub_menu_3_2,
        NULL,
        NULL,
        &menu_3,
        showCircle
};
menu_t sub_menu_3_2 = {
        "2. Kwadrat",
        &sub_menu_3_3,
        &sub_menu_3_1,
        NULL,
        &menu_3,
        showSquare
};
menu_t sub_menu_3_3 = {
        "3. Trojkat",
        &sub_menu_3_4,
        &sub_menu_3_2,
        NULL,
        &menu_3,
        showTriangle
};
menu_t sub_menu_3_4 = {
        "4. Trapez",
        NULL,
        &sub_menu_3_3,
        NULL,
        &menu_3,
        showTrapeze

};

void displayName(menu_t *menu, menu_t *curr, const unsigned char pos) {
    if (menu->name[0] == curr->name[0]) {
        LCDPutStr((char *) menu->name, pos, 5, MEDIUM, BLACK, GREEN);
        return;
    }
    LCDPutStr((char *) menu->name, pos, 5, MEDIUM, BLACK, WHITE);
}

void printMenu(menu_t *menu, menu_t *curr) {
    LCDClearScreen();
    if (curr == NULL) {
        return;
    }
    unsigned char pos = 10;
    while (menu != NULL) {
        displayName(menu, curr, pos);
        pos += 20;
        menu = menu->next;
    }
}

void changeSelect(menu_t **menu, menu_t *sel) {
    if (sel == NULL) {
        return;
    }
    *menu = sel;
}


int main() {
    PMC_PCER = PMC_PCER_PIOA;
    InitLCD();
    SetContrast(30);
    menu_t *currentPointer = &menu_1; // Aktualny wskaźnik
    menu_t *selected = currentPointer;
    printMenu(currentPointer, selected);
    char ismenu = 0;
    while (1) {
        if (!(PIOA_PDSR & up)) {
            changeSelect(&selected, selected->prev);
            printMenu(currentPointer, selected);
            while (!(PIOA_PDSR & up)) {
                continue;
            }
        }
        if (!(PIOA_PDSR & down)) {
            changeSelect(&selected, selected->next);
            printMenu(currentPointer, selected);
            while (!(PIOA_PDSR & down)) {
                continue;
            }
        }
        if (!(PIOA_PDSR & right)) {
            if (selected->menu_function != NULL) {
                selected->menu_function();
                ismenu = 1;
            }
            if (selected->child != NULL) {
                currentPointer = currentPointer->child;
                selected = currentPointer;
                printMenu(currentPointer, selected);
            }
            while (!(PIOA_PDSR & right)) {
                continue;
            }
        }
        if (!(PIOA_PDSR & left)) {
            if (currentPointer->parent != NULL && ismenu == 0) {
                currentPointer = currentPointer->parent;
                selected = currentPointer;
                printMenu(currentPointer, selected);
            }
            if (ismenu == 1) {
                ismenu = 0;
                printMenu(currentPointer, selected);
            }
            while (!(PIOA_PDSR & left)) {
                continue;
            }
        }
    }
}