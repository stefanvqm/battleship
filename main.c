/* (author: Stefan Götz) */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


const int boatlength[] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
const char buchstaben[] = {'a','b','c','d','e','f','g','h','i','j'};
char boatfield1[10][10];    // [y][x]  field for player 1
char boatfield2[10][10];    // [y][x]  field for player 2

// 1. incompatible inputs

void deleteall() { 
    // deletes the terminal for changing user. //  # präprozessor anweisungen     
    #if defined _WIN32
	    system("CLS");
    #elif defined (__unix__)
	    system("clear");
    #endif
}

void clean_stdin(void)
{   // credits: Miron, thanks for helping!
    char c;
    do
    {
        c = getc(stdin);
    } while (c != '\n' && c != EOF);
}

void previewfield() {
    printf("   ");     
    for(int i=0; i<10; i++) {
        printf("%d ", i+1);
    }
    printf("\n");

    for(int i=0; i<10; i++) {
        printf("%c  ", buchstaben[i]);
        for(int j=0; j<10; j++) {
            printf("□ ");
        }
        printf("\n");
    }
}

void welcomeMessages() {
    printf("\n\n");
    printf("Welcome to Battleship!\n");
    printf("\nRules:\n");
    printf("1. the boats have to be placed vertical or horizontal.\n");
    printf("2. the boats are not allowed to touch each other.\n");
    printf("\nKeep in mind that you, as the player have to look if the boats are placed legally.\n");
    printf("\nYou have 10 boats:\n1x with the length of 4\n2x with the length of 3\n3x with the length of 2\n4x with the length of 1\n");
    printf("\nWhen placing a boat, at first give the y coordinate, then the x coordinate.");
    printf("\n\n");
    printf("The battlefield looks like that:\n\n");
    previewfield();
    printf("\nPress ENTER key to start.");
    //getchar();
    clean_stdin();
    deleteall();
}

// prints field of player 1
void fieldp1() {
    printf("\n\n   ");     
    for(int i=0; i<10; i++) {
        printf("%d ", i+1);
    }
    printf("\n");

    for(int i=0; i<10; i++) {
        printf("%c  ", buchstaben[i]);
        for(int j=0; j<10; j++) {
            printf("%c ", boatfield1[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void boatplacingplayer1() {
    // creates field without printing, otherwise error
    for(int i=0; i<10; i++) {
        for(int j=0; j<10; j++) {
            boatfield1[i][j] = '-';
        }
    }

    for(int p=0; p<10; p++) { //  p = 10 boats...
        int x = 0;
        int y = 0;
        int i, k, j;
        int direction;
        printf("y coordinate for boat no.%d with length %d: ", p+1, boatlength[p]);   // what if incompatible input
        scanf("%d", &y);
        printf("x coordinate for boat no.%d with length %d: ", p+1, boatlength[p]);   // what if incompatible input
        scanf("%d", &x);

        y--;
        x--;
        
        printf("\n\n   ");     
        for(j=0; j<10; j++) {
            printf("%d ", j+1);
        }
        printf("\n");
        for(i=0; i<10; i++) {
            printf("%c  ", buchstaben[i]);
            for(k=0; k<10; k++) {
                if( y == i && x == k) {
                    printf("O ");  // doesnt work with ■ hex = \x25A0
                }
                else {
                    if(((y == i) && ((k-x) < boatlength[p]) && ((x-k) < boatlength[p])) || ((x == k) && ((i-y) < boatlength[p]) && ((y-i) < boatlength[p])) ) {
                        printf("x ");
                    } 
                    else {
                        printf("- ");
                    }
                }
            }
            printf("\n");
        }
        
        printf("\nThe x's show you where your boat could be placed, depending on the base coordinates,\nboat left (1), right (2), up (3), down (4),  from the starting-point you chose?: ");
        scanf("%d", &direction);  // will be used later
        clean_stdin();
        int temp = boatlength[p];

        if(direction+48 == '1') {           // left
            for(int h=0; h<temp; h++) {
                boatfield1[y][x-h] = 'O'; 
            }
            fieldp1();
        }
        if(direction+48 == '2') {           // right
            for(int b=0; b<temp; b++) {
                boatfield1[y][x+b] = 'O'; 
            }
            fieldp1();
        }
        if(direction+48 == '3') {           // up
            for(int q=0; q<temp; q++) {
                boatfield1[y-q][x] = 'O'; 
            }
            fieldp1();
        }
        if(direction+48 == '4') {           // down
            for(int t=0; t<temp; t++) {
                boatfield1[y+t][x] = 'O'; 
            }
            fieldp1();
        }
    }
    printf("\nPlayer 1 placed every boat.\n");
    printf("\nPress ENTER key to remove your field from the screen.");
    clean_stdin();
    deleteall();
}

// prints field of player 2
void fieldp2() {
    printf("\n\n   ");     
    for(int i=0; i<10; i++) {
        printf("%d ", i+1);
    }
    printf("\n");

    for(int i=0; i<10; i++) {
        printf("%c  ", buchstaben[i]);
        for(int j=0; j<10; j++) {
            printf("%c ", boatfield2[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void boatplacingplayer2() {
    // creates field without printing, otherwise error
    for(int i=0; i<10; i++) {
        for(int j=0; j<10; j++) {
            boatfield2[i][j] = '-';
        }
    }

    for(int p=0; p<10; p++) { // p = 10 boats...
        int x = 0;
        int y = 0;
        int i, k, j;
        int direction;
        printf("y coordinate for boat no.%d with length %d: ", p+1, boatlength[p]);   // what if incompatible input
        scanf("%d", &y);
        printf("x coordinate for boat no.%d with length %d: ", p+1, boatlength[p]);   // what if incompatible input
        scanf("%d", &x);

        y--;
        x--;
        
        printf("\n\n   ");     
        for(j=0; j<10; j++) {
            printf("%d ", j+1);
        }
        printf("\n");
        for(i=0; i<10; i++) {
            printf("%c  ", buchstaben[i]);
            for(k=0; k<10; k++) {
                if( y == i && x == k) {
                    printf("O ");  // doesnt work with ■ hex = \x25A0
                }
                else {
                    if(((y == i) && ((k-x) < boatlength[p]) && ((x-k) < boatlength[p])) || ((x == k) && ((i-y) < boatlength[p]) && ((y-i) < boatlength[p])) ) {
                        printf("x ");
                    } 
                    else {
                        printf("- ");
                    }
                }
            }
            printf("\n");
        }
        

        printf("\nThe x's show you where your boat could be placed, depending on the base coordinates,\nboat left (1), right (2), up (3), down (4),  from the starting-point you chose?: ");
        scanf("%d", &direction);  // will be used later

        int temp = boatlength[p];

        if(direction+48 == '1') {           // left
            for(int h=0; h<temp; h++) {
                boatfield2[y][x-h] = 'O'; 
            }
            fieldp2();
        }
        if(direction+48 == '2') {           // right
            for(int b=0; b<temp; b++) {
                boatfield2[y][x+b] = 'O'; 
            }
            fieldp2();
        }
        if(direction+48 == '3') {           // up
            for(int q=0; q<temp; q++) {
                boatfield2[y-q][x] = 'O'; 
            }
            fieldp2();
        }
        if(direction+48 == '4') {           // down
            for(int t=0; t<temp; t++) {
                boatfield2[y+t][x] = 'O'; 
            }
            fieldp2();
        }
    }
    printf("Player 2 placed every boat, press [Enter] to remove your field from the screen.");
    printf("\nPress ENTER key to remove your field from the screen.");
    clean_stdin();
    deleteall();
}


int main() {
    welcomeMessages();
    boatplacingplayer1();
    boatplacingplayer2();
}
