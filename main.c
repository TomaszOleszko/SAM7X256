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


void print_obraz1(void) {
    //
}

void print_obraz2(void) {
    //
}

void print_animacja(void) {
    while (1) {
        print_obraz1();
        delay(500);
        print_obraz2();
        delay(500);
        if (!(PIOA_PDSR & left) {
            break;
        }
    }
}

void print_obrazItekst(void) {
    //
}

void print_okrag(void) {
    // LCDSetCircle(65,65,7,BLACK);
}

void print_kwadrat(void) {
    // LCDSetRect(43, 43, 88, 88, 1, BLACK);
}

void print_trojkat(void) {
    // LCDSetLine(95, 95, 95, 35, BLACK);
    // LCDSetLine(95, 35, 43, 65, BLACK);
    // LCDSetLine(43, 65, 95, 95, BLACK);
}

void print_trapez(void) {
    //  LCDSetLine(30, 20, 30, 110, BLACK);
    //  LCDSetLine(30, 20, 80, 5, BLACK);
    // LCDSetLine(80, 125, 30, 110, BLACK);
    //  LCDSetLine(80, 5, 80, 125, BLACK);
}

void show_author(void) {
    // LCDPutStr("Tomasz_Oleszko", 43, 11, MEDIUM, BLACK, GREEN);
    // LCDPutStr("GR 7.5", 64, 45, MEDIUM, BLACK, WHITE);
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
        print_obrazItekst
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
        show_author
};

menu_t sub_menu_1_1 = {
        "1. Obraz 1",
        &sub_menu_1_2,
        NULL,
        NULL,
        &menu_1,
        print_obraz1
};
menu_t sub_menu_1_2 = {
        "2. Obraz 2",
        &sub_menu_1_3,
        &sub_menu_1_1,
        NULL,
        &menu_1,
        print_obraz2
};
menu_t sub_menu_1_3 = {
        "3. Animacja",
        NULL,
        &sub_menu_1_2,
        NULL,
        &menu_1,
        print_animacja
};
menu_t sub_menu_3_1 = {
        "1. Okrag",
        &sub_menu_3_2,
        NULL,
        NULL,
        &menu_3,
        print_okrag
};
menu_t sub_menu_3_2 = {
        "2. Kwadrat",
        &sub_menu_3_3,
        &sub_menu_3_1,
        NULL,
        &menu_3,
        print_kwadrat
};
menu_t sub_menu_3_3 = {
        "3. Trojkat",
        &sub_menu_3_4,
        &sub_menu_3_2,
        NULL,
        &menu_3,
        print_trojkat
};
menu_t sub_menu_3_4 = {
        "4. Trapez",
        NULL,
        &sub_menu_3_3,
        NULL,
        &menu_3,
        print_trapez

};


void show_menu(int counter) {
    LCDClearScreen();
    switch (counter) {
        case 0:
            LCDPutStr("1. Obraz", 10, 5, MEDIUM, BLACK, GREEN);
            LCDPutStr("2. Tekst+obraz", 30, 5, MEDIUM, BLACK, WHITE);
            LCDPutStr("3. Figury", 50, 5, MEDIUM, BLACK, WHITE);
            LCDPutStr("4. O Autorze", 70, 5, MEDIUM, BLACK, WHITE);
            break;
        case 1:
            LCDPutStr("1. Obraz", 10, 5, MEDIUM, BLACK, WHITE);
            LCDPutStr("2. Tekst+obraz", 30, 5, MEDIUM, BLACK, GREEN);
            LCDPutStr("3. Figury", 50, 5, MEDIUM, BLACK, WHITE);
            LCDPutStr("4. O Autorze", 70, 5, MEDIUM, BLACK, WHITE);
            break;
        case 2:
            LCDPutStr("1. Obraz", 10, 5, MEDIUM, BLACK, WHITE);
            LCDPutStr("2. Tekst+obraz", 30, 5, MEDIUM, BLACK, WHITE);
            LCDPutStr("3. Figury", 50, 5, MEDIUM, BLACK, GREEN);
            LCDPutStr("4. O Autorze", 70, 5, MEDIUM, BLACK, WHITE);
            break;
        case 3:
            LCDPutStr("1. Obraz", 10, 5, MEDIUM, BLACK, WHITE);
            LCDPutStr("2. Tekst+obraz", 30, 5, MEDIUM, BLACK, WHITE);
            LCDPutStr("3. Figury", 50, 5, MEDIUM, BLACK, WHITE);
            LCDPutStr("4. O Autorze", 70, 5, MEDIUM, BLACK, GREEN);
            break;
    }

}

void displayName(menu_t *menu, menu_t *curr) {
    if (menu->name[0] == curr->name[0]) {
        printf("%s selected\n", menu->name);
        return;
    }
    printf("%s\n", menu->name);
}

void printMenu(menu_t *menu, menu_t *curr) {
    if (curr == NULL) {
        return;
    }
    while (menu != NULL) {
        displayName(menu, curr);
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
    menu_t *currentPointer = &menu_1;
    prinf_menu(currentPointer->name);
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