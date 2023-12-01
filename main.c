#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BOARD_SIZE 4  // Definieer de grootte van het bord

typedef struct {
    int value;
    int is_visible;
} Piece;  // Definieer de struct voor een stukje op het bord

// Functie om het bord dynamisch te initialiseren
Piece **createBoard() {
    Piece **board = malloc(BOARD_SIZE * BOARD_SIZE * sizeof(Piece *)); // Maak een array van pointers naar stukjes piece, eigl 1 dimensionaal array
    if (board == NULL) {
        exit(1);
    }

    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        board[i] = NULL;
    }
    return board;
}

// Functie om een stukje te creëren
Piece *create_piece(int value, int is_visible) {
    Piece *new_piece = (Piece *) malloc(sizeof(Piece));
    if (new_piece == NULL) {
        exit(1);  // Foutafhandeling als malloc faalt
    }
    new_piece->value = value;
    new_piece->is_visible = is_visible;
    return new_piece;
}

int random_num() {
    return rand() % 10 + 1;  // Genereer een willekeurig getal tussen 1 en 10
}

void fillBoard(Piece **board) {
    board[3 * BOARD_SIZE + 1] = create_piece(random_num(), 1);
    board[3 * BOARD_SIZE + 2] = create_piece(random_num(), 1);
    board[0 * BOARD_SIZE + 1] = create_piece(random_num(), 0);
    board[0 * BOARD_SIZE + 2] = create_piece(random_num(), 0);
}

void display_board(Piece **board) {
    printf("  0 1 2 3 X\n");
    for (int i = 0; i < BOARD_SIZE; i++) { // loop door de y-coördinaten
        printf("%d ", i);  // Toon Y-coördinaten
        for (int j = 0; j < BOARD_SIZE; j++) { //loop door ehle bord en kijken of er een stukje is of niet
            Piece *current_piece = board[i * BOARD_SIZE + j]; //krijg het stukje op de huidige locatie
            if (current_piece == NULL) {
                printf("0 ");
            } else if (current_piece->is_visible) {
                printf("%d ", current_piece->value);
            } else {
                printf("* ");
            }
        }
        printf("\n");
    }
    printf("Y\n");
}

// De move_piece, get_piece_to_move, en get_direction functies blijven onveranderd

void freeBoard(Piece **board) {
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        free(board[i]);  // Maak elk stukje vrij
    }
    free(board);  // Maak het bord vrij
}

void move_piece(Piece *board[BOARD_SIZE][BOARD_SIZE], int x, int y, char *direction) {
    int target_x = x, target_y = y; // initieer de target x en y op de x en y van het stuk dat je wilt verplaatsen
    //In de code ga je eigenlijk de de target aanpassen op basis van de string die je geeft. Als je bijvoorbeeld boven geeft dan ga je de target_y aanpassen zodat deze 1 lager is dan de y van het stuk dat je wilt verplaatsen. Als je dan de target_x en target_y gebruikt om het stuk te verplaatsen dan verplaats je het stuk naar de locatie die je wilt.

    if (strcmp(direction, "boven") == 0 && y > 0)
        target_y--; //kijkt of de string direction gelijk is aan boven en of de y groter is dan 0
    else if (strcmp(direction, "onder") == 0 && y < BOARD_SIZE - 1)
        target_y++;  //kijkt of de string direction gelijk is aan onder en of de y kleiner is dan de board size - 1
    else if (strcmp(direction, "links") == 0 && x > 0)
        target_x--; //kijkt of de string direction gelijk is aan links en of de x groter is dan 0
    else if (strcmp(direction, "rechts") == 0 && x < BOARD_SIZE - 1)
        target_x++; //kijkt of de string direction gelijk is aan rechts en of de x kleiner is dan de board size - 1
    else {
        printf("Ongeldige richting, probeer opnieuw.\n");
        return;
    }

    if (board[target_y][target_x] != NULL) {
        if (board[target_y][target_x]->is_visible ==
            0) {
            if (board[y][x]->value >
                board[target_y][target_x]->value) { // je iegen stuk is waarde is groter dan het stuk waar je heen wilt gaan
                free(board[target_y][target_x]); // Remove opponent piece
                board[target_y][target_x] = board[y][x]; // Move your piece
                printf("Je hebt een stuk van de tegenstander verslagen!\n");
                board[y][x] = NULL;
            } else if (board[y][x]->value <
                       board[target_y][target_x]->value) { // je iegen stuk is waarde is kleiner dan het stuk waar je heen wilt gaan
                printf("Verslagen, tegenstander is sterker. met een waarde van %d\n", board[target_y][target_x]->value);
                free(board[y][x]); // Remove your piece
                board[y][x] = NULL;
            } else { //Als het stuk dat je wilt verplaatsen dezelfde waarde heeft als het stuk waar je heen wilt gaan dan worden beide stukken verwijderd.
                free(board[target_y][target_x]);
                free(board[y][x]);
                board[target_y][target_x] = NULL;
                board[y][x] = NULL;
            }
        } else {
            printf("Kan niet bewegen, eigen stuk op doellocatie.\n");
            return;
        }
    } else {
        // Move to empty cell
        board[target_y][target_x] = board[y][x];
        board[y][x] = NULL;
    }
}

void get_piece_to_move(int *x, int *y) {
    printf("Selecteer een stuk (x y): ");
    scanf("%d %d", x, y);
}

void get_direction(const char *direction) {
    printf("Geef richting (boven, onder, links, rechts): ");
    scanf("%s", direction);
}

int main() {
    srand(time(NULL));  // Zorg dat random niet steeds dezelfde getallen genereert

    Piece **board = createBoard();
    fillBoard(board);

    int x, y;
    char direction[10];

    while (1) {
        display_board(board);
        get_piece_to_move(&x, &y);
        if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE || board[y * BOARD_SIZE + x] == NULL) {
            printf("Ongeldige selectie, probeer opnieuw.\n");
            continue;
        }
        get_direction(direction);
        move_piece(board, x, y, direction);
    }

    freeBoard(board);

    return 0;
}


