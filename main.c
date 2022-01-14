#include <stdio.h>
#include <string.h>
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

void show_author(void) {
    printf("Tomasz_Oleszko\n");
}

void print_obraz1(void) {
    printf("Obraz 1 :DDD\n");
}

void print_obraz2(void) {
    printf("Obraz 2 :DDD\n");
}

void print_animacja(void) {
    printf("Animacja :DDD\n");
}

void print_obrazItekst(void) {
    printf("Obraz i tekst\n");
}

void print_okrag(void) {
    printf("print_okrag\n");
}

void print_kwadrat(void) {
    printf("print_kwadratD\n");
}

void print_trojkat(void) {
    printf("print_trojkat\n");
}

void print_trapez(void) {
    printf("print_trapez\n");
}

menu_t menu_1, menu_2, menu_3, menu_4, sub_menu_1_1, sub_menu_1_2, sub_menu_1_3, sub_menu_2_1, sub_menu_3_1, sub_menu_3_2, sub_menu_3_3, sub_menu_3_4;
menu_t menu_1 = {
        "XObraz\nTekst+obraz\nFigury\nO Autorze\n",
        &menu_2,
        &menu_1,
        &sub_menu_1_1,
        NULL,
        NULL
};
menu_t sub_menu_1_1 = {
        "XObraz 1\nObraz 2\nAnimacja\n",
        &sub_menu_1_2,
        &sub_menu_1_1,
        NULL,
        &menu_1,
        print_obraz1
};
menu_t sub_menu_1_2 = {
        "Obraz 1\nXObraz 2\nAnimacja\n",
        &sub_menu_1_3,
        &sub_menu_1_1,
        NULL,
        &menu_1,
        print_obraz2
};
menu_t sub_menu_1_3 = {
        "Obraz 1\nObraz 2\nXAnimacja\n",
        &sub_menu_1_3,
        &sub_menu_1_2,
        NULL,
        &menu_1,
        print_animacja
};
menu_t menu_2 = {
        "Obraz\nXTekst+obraz\nFigury\nO Autorze\n",
        &menu_3,
        &menu_1,
        NULL,
        NULL,
        print_obrazItekst
};
menu_t menu_3 = {
        "Obraz\nTekst+obraz\nXFigury\nO Autorze\n",
        &menu_4,
        &menu_2,
        &sub_menu_3_1,
        NULL,
        NULL
};
menu_t sub_menu_3_1 = {
        "XOkrag\nKwadrat\nTrojkat\nTrapez\n",
        &sub_menu_3_2,
        &sub_menu_3_1,
        NULL,
        &menu_3,
        print_okrag
};
menu_t sub_menu_3_2 = {
        "Okrag\nXKwadrat\nTrojkat\nTrapez\n",
        &sub_menu_3_3,
        &sub_menu_3_1,
        NULL,
        &menu_3,
        print_kwadrat
};
menu_t sub_menu_3_3 = {
        "Okrag\nKwadrat\nXTrojkat\nTrapez\n",
        &sub_menu_3_4,
        &sub_menu_3_2,
        NULL,
        &menu_3,
        print_trojkat
};
menu_t sub_menu_3_4 = {
        "Okrag\nKwadrat\nTrojkat\nXTrapez\n",
        &sub_menu_3_4,
        &sub_menu_3_3,
        NULL,
        &menu_3,
        print_trapez

};
menu_t menu_4 = {
        "Obraz\nTekst+obraz\nFigury\nXO Autorze\n",
        &menu_4,
        &menu_3,
        NULL,
        NULL,
        show_author
};


void prinf_menu(const char *text) {
    //LCDClearScreen();
    unsigned char counter = 0;
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
            while (t_c != 24) {
                tab[t_c] = ' ';
                t_c++;
            }
            tab[0] = l_c++ + '0';
            tab[1] = '.';
            tab[2] = ' ';
            t_c = 3;
            printf("%s\n", tab);
            //LCDPutStr(tab, 10, 5, MEDIUM, BLACK, WHITE);
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


/*
1. Obraz
- 1. Obraz1
- 2. Obraz2
- 3. Animacja 0.5s obraz1 -> 0.5s obraz2
2. Tekst+obraz -> Dowolny tekst (tłoTekstu - transparentne) na obrazie
3. Figury
- okrąg
- kwadrat
- trójkąt
- trapez -> trapez musimy narysowac sami. Wiele mozliwości (nie obraz!) pojedyncze piksele lub narysowac 4 linie
4. Autor albo O Autorze
Imię_Nazwisko
Nr. grupy
 */