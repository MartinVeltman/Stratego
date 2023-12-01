#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//er is een 2 dimensionale array gemaakt waar of een null value staat of een pointer naar een stukje geheugen waar een Piece in zit. Dit is gedaan omdat je anders een 3 dimensionale array zou moeten maken om de value en is_visible van een Piece te kunnen veranderen. Dit zou veel meer geheugen gebruiken en het zou ook veel moeilijker zijn om door het bord heen te loopen.

// set the board size
#define BOARD_SIZE 4

// Dit defineert een stukje geheugen dat je kan gebruiken om een stukje van het bord te representeren
typedef struct {
    int value;
    int is_visible;
} Piece;


void initializeBoardCellsToNull(Piece *board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = NULL; // Initialize all cells to NULL
        }
    }
}
//Deze functie zorgt ervoor dat alle cellen van het bord geinitialiseerd worden naar NULL. Dit is nodig omdat je anders niet kan checken of een cel leeg is of niet.

Piece *create_piece(int value, int is_visible) {
    Piece *new_piece = (Piece *) malloc(
            sizeof(Piece)); //Je maakt een nieuw stukje geheugen aan dat groot genoeg is om een Piece te bevatten. Dit stukje geheugen wordt dan toegewezen aan de pointer new_piece.
    new_piece->value = value; //Je stelt de value van het stukje geheugen in op de waarde die je meegeeft aan de functie.
    new_piece->is_visible = is_visible; //Je stelt de is_visible van het stukje geheugen in op de waarde die je meegeeft aan de functie.
    return new_piece; //Je geeft de pointer terug zodat je het stukje geheugen kan gebruiken.
}

int random() {
    // Generate a random number between 1 and 10
    return rand() % 10 + 1;

}

void createBoard(Piece *board[BOARD_SIZE][BOARD_SIZE]) {
    initializeBoardCellsToNull(board);

    board[3][1] = create_piece(random(),
                               1); // je plaatst een pointer naar een stukje geheugen op het bord. Dit stukje geheugen bevat een Piece met een value en een is_visible. zo set je dus niet een heel opject op het bord maar alleen een pointer naar een stukje geheugen waar een Piece in zit. zo blijft je array 2d en kan je makkelijk door het bord heen loopen en gebruikt het minder geheugen.
    board[3][2] = create_piece(random(), 1);


    board[0][1] = create_piece(random(), 0);
    board[0][2] = create_piece(random(), 0);
}

void display_board(Piece *board[BOARD_SIZE][BOARD_SIZE]) {
    printf("  0 1 2 3 X\n"); // Displaying X-coordinates
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d ", i); // Displaying Y-coordinates
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == NULL) {
                printf("0 ");
            } else if (board[i][j]->is_visible) {
                printf("%d ", board[i][j]->value);
            } else {
                printf("* ");
            }
        }
        printf("\n");
    }
    printf("Y\n");
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

    // Check if target cell is occupied, if so do iets anders beweeg het stuk er gewoon heen
    if (board[target_y][target_x] != NULL) {
        // Collision with opponent piece
        if (board[target_y][target_x]->is_visible ==
            0) { //kijkt of het stuk waar je heen wilt gaan niet bezet is door een eigen stuk
            if (board[y][x]->value > board[target_y][target_x]->value) { // je iegen stuk is waarde is groter dan het stuk waar je heen wilt gaan
                free(board[target_y][target_x]); // Remove opponent piece
                board[target_y][target_x] = board[y][x]; // Move your piece
                printf("Je hebt een stuk van de tegenstander verslagen!\n");
                board[y][x] = NULL;
            } else if (board[y][x]->value < board[target_y][target_x]->value) { // je iegen stuk is waarde is kleiner dan het stuk waar je heen wilt gaan
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
    srand(time(NULL));  // zorg dat random niet steedd dezelfde getallen genereert



    Piece *board[BOARD_SIZE][BOARD_SIZE];
    createBoard(board);
    display_board(board);

    int x, y;
    char direction[10];

    while (1) {
        display_board(board);

        get_piece_to_move(&x, &y);
        if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE || board[y][x] == NULL) {
            printf("Ongeldige selectie, probeer opnieuw.\n");
            continue;
        }

        get_direction(direction);

        move_piece(board, x, y, direction);
    }

    return 0;
}



