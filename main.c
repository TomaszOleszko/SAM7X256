#include <stdio.h>
//#include <targets\AT91SAM7.h>
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

/*
__attribute__ ((section(".fast")))
void delay(int n) //procedura opoznienia
{
    volatile int i;
    for(i=3000*n;i>0;i--)
    {
        __asm__("nop");
    }
}
*/

void print_obraz1(void) {
    printf("Obraz 1 :DDD\n");
}

void print_obraz2(void) {
    printf("Obraz 2 :DDD\n");
}

void print_animacja(void) {
    while (1) {
        print_obraz1();
        // delay(500);
        print_obraz2();
        // delay(500);
    }
}

void print_obrazItekst(void) {
    printf("Obraz i tekst\n");
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
        "ObrazX\nTekst+obraz\nFigury\nO Autorze\n",
        &menu_2,
        &menu_1,
        &sub_menu_1_1,
        NULL,
        NULL
};
menu_t sub_menu_1_1 = {
        "Obraz 1X\nObraz 2\nAnimacja\n",
        &sub_menu_1_2,
        &sub_menu_1_1,
        NULL,
        &menu_1,
        print_obraz1
};
menu_t sub_menu_1_2 = {
        "Obraz 1\nObraz 2X\nAnimacja\n",
        &sub_menu_1_3,
        &sub_menu_1_1,
        NULL,
        &menu_1,
        print_obraz2
};
menu_t sub_menu_1_3 = {
        "Obraz 1\nObraz 2\nAnimacjaX\n",
        &sub_menu_1_3,
        &sub_menu_1_2,
        NULL,
        &menu_1,
        print_animacja
};
menu_t menu_2 = {
        "Obraz\nTekst+obrazX\nFigury\nO Autorze\n",
        &menu_3,
        &menu_1,
        NULL,
        NULL,
        print_obrazItekst
};
menu_t menu_3 = {
        "Obraz\nTekst+obraz\nFiguryX\nO Autorze\n",
        &menu_4,
        &menu_2,
        &sub_menu_3_1,
        NULL,
        NULL
};
menu_t sub_menu_3_1 = {
        "OkragX\nKwadrat\nTrojkat\nTrapez\n",
        &sub_menu_3_2,
        &sub_menu_3_1,
        NULL,
        &menu_3,
        print_okrag
};
menu_t sub_menu_3_2 = {
        "Okrag\nKwadratX\nTrojkat\nTrapez\n",
        &sub_menu_3_3,
        &sub_menu_3_1,
        NULL,
        &menu_3,
        print_kwadrat
};
menu_t sub_menu_3_3 = {
        "Okrag\nKwadrat\nTrojkatX\nTrapez\n",
        &sub_menu_3_4,
        &sub_menu_3_2,
        NULL,
        &menu_3,
        print_trojkat
};
menu_t sub_menu_3_4 = {
        "Okrag\nKwadrat\nTrojkat\nTrapezX\n",
        &sub_menu_3_4,
        &sub_menu_3_3,
        NULL,
        &menu_3,
        print_trapez

};
menu_t menu_4 = {
        "Obraz\nTekst+obraz\nFigury\nO AutorzeX\n",
        &menu_4,
        &menu_3,
        NULL,
        NULL,
        show_author
};


void prinf_menu(const char *text) {
    //LCDClearScreen();
    unsigned char counter = 0;
    unsigned lcd = 10;
    char tab[25];
    unsigned char t_c = 3;
    unsigned l_c = 1;

    tab[24] = '\0';
    while (text[counter] != '\0') {
        // dodawac chary str_talk
        if (text[counter] != '\n') {
            tab[t_c] = text[counter];
            t_c++;
        } else {
            unsigned char green = 0;
            if (tab[t_c - 1] == 'X') {
                green = 1;
                tab[t_c - 1] = ' ';
            }
            while (t_c != 24) {
                tab[t_c] = ' ';
                t_c++;
            }
            tab[0] = l_c++ + '0';
            tab[1] = '.';
            tab[2] = ' ';
            t_c = 3;
            if (green) {
                printf("XXXXX%s\n", tab);
                //LCDPutStr(tab, lcd, 5, MEDIUM, BLACK, GREEN);
            } else {
                printf("%s\n", tab);
                //LCDPutStr(tab, lcd, 5, MEDIUM, BLACK, WHITE);
            }
            lcd += 20;
        }
        counter++;
    }
}

int main() {
    menu_t *currentPointer = &menu_1; // Aktualny wskaźnik
    char a = 0;
    prinf_menu(currentPointer->name);
    while (1) {
        scanf("%c", &a);
        switch (a) {
            case 'w':
                currentPointer = currentPointer->prev;
                prinf_menu(currentPointer->name);
                break;
            case 's':
                currentPointer = currentPointer->next;
                prinf_menu(currentPointer->name);
                break;
            case 'd':
                if (currentPointer->child == NULL) {
                    currentPointer->menu_function();
                    // while nie wcisniesz 'a' wyswietlaj menu func
                    while (a != 'a') {
                        scanf("%c", &a);
                    }
                    prinf_menu(currentPointer->name);
                } else {
                    currentPointer = currentPointer->child;
                    prinf_menu(currentPointer->name);
                }
                break;
            case 'a':
                if (currentPointer->parent == NULL) {
                    prinf_menu(currentPointer->name);
                } else {
                    currentPointer = currentPointer->parent;
                    prinf_menu(currentPointer->name);
                }
                break;
        }
    }
}