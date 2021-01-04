
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

const char boatspecifier[] = {'0','1','2','3','4','5','6','7','8','9'};
const int boatlength[] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
const int rownumbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

char boatfield1[10][10];        // [y][x]  field of player 1
char boatfield2[10][10];        // [y][x]  field of player 2
char shootingresult1[10][10];   //     result of p1's shootings
char shootingresult2[10][10];   //     result of p2's shootings
char numberedfield1[10][10];   // for function destroyedboat
char numberedfield2[10][10];   // for function destroyedboat

int whoseturn = 0;
int whichplayerisnow = 0;


void deleteall() { 
    // deletes the terminal for changing user. //  # präprozessor anweisungen     
    #if defined _WIN32
	    system("CLS");
    #elif defined (__unix__)
	    system("clear");
    #endif
}

void clean_stdin(void)
{   // credits: "Miron", thanks for helping!
    char c;
    do
    {
        c = getc(stdin);
    } while (c != '\n' && c != EOF);
}

void printcolumnnumbers() {
    printf("   ");     
    for(int i=0; i<10; i++) {
        printf("%d ", i+1);
    }
    printf("\n");
}

void previewfield() {

    printcolumnnumbers();

    for(int i=0; i<10; i++) {
        if(rownumbers[i] != 10) {
            printf("%d  ", rownumbers[i]);
        }
        else {
            printf("%d ", rownumbers[i]);
        }
        for(int j=0; j<10; j++) {
            printf("- ");
        }
        printf("\n");
    }
}

void printplayerfield(char *fieldarray) {

    printf("Your field\n\n");
    printcolumnnumbers();

    for(int i=0; i<10; i++) {
        printf("%c  ", rownumbers[i]);
            for(int j=0; j<10; j++) {
                printf("%c ", *(fieldarray+((i*10)+j))); 
            }
        printf("\n");
    }
}

void printresultfield(char *fieldarray) {

    printf("Your shooting results\n\n");
    printcolumnnumbers();

    for(int i=0; i<10; i++) {
        printf("%c  ", rownumbers[i]);
            for(int j=0; j<10; j++) {
                printf("%c ", *(fieldarray+((i*10)+j))); 
            }
        printf("\n");
    }
}

//                       your result,   opponent arrray
void destroyedboat(char *resultarray, char *numberarray) {

    for(int i=0; i<10; i++) {
        for(int j=0; j<10; j++) {
// horizontal 4x boat
            if((*(numberarray+((10*i)+j)) == '0' && *(numberarray+((10*i)+j+1)) == '0' && *(numberarray+((10*i)+j+2)) == '0' && *(numberarray+((10*i)+j+3)) == '0') &&
               (*(resultarray+((10*i)+j)) == 'x' && *(resultarray+((10*i)+j+1)) == 'x' && *(resultarray+((10*i)+j+2)) == 'x' && *(resultarray+((10*i)+j+3)) == 'x')) {

                *(resultarray+((10*i)+j)) = 'S';
                *(resultarray+((10*i)+j+1)) = 'S';
                *(resultarray+((10*i)+j+2)) = 'S';
                *(resultarray+((10*i)+j+3)) = 'S';
            }
// vertical 4x boat
            if((*(numberarray+((10*i)+j)) == '0' && *(numberarray+((10*(i+1))+j)) == '0' && *(numberarray+((10*(i+2))+j)) == '0' && *(numberarray+((10*(i+3))+j)) == '0') &&
               (*(resultarray+((10*i)+j)) == 'x' && *(resultarray+((10*(i+1))+j)) == 'x' && *(resultarray+((10*(i+2))+j)) == 'x' && *(resultarray+((10*(i+3))+j)) == 'x')) {

                *(resultarray+((10*i)+j)) = 'S';
                *(resultarray+((10*(i+1))+j)) = 'S';
                *(resultarray+((10*(i+2))+j)) = 'S';
                *(resultarray+((10*(i+3))+j)) = 'S';
            }
// horizontal 3x boat
            if(((*(numberarray+((10*i)+j)) == '1' && *(numberarray+((10*i)+j+1)) == '1' && *(numberarray+((10*i)+j+2)) == '1') || (*(numberarray+((10*i)+j)) == '2' && *(numberarray+((10*i)+j+1)) == '2' && *(numberarray+((10*i)+j+2)) == '2')) &&
               (*(resultarray+((10*i)+j)) == 'x' && *(resultarray+((10*i)+j+1)) == 'x' && *(resultarray+((10*i)+j+2)) == 'x')) {

                *(resultarray+((10*i)+j)) = 'S';
                *(resultarray+((10*i)+j+1)) = 'S';
                *(resultarray+((10*i)+j+2)) = 'S';
            }
// vertical 3x boat
            if(((*(numberarray+((10*i)+j)) == '1' && *(numberarray+((10*(i+1))+j)) == '1' && *(numberarray+((10*(i+2))+j)) == '1') || (*(numberarray+((10*i)+j)) == '2' && *(numberarray+((10*(i+1))+j)) == '2' && *(numberarray+((10*(i+2))+j)) == '2')) &&
               (*(resultarray+((10*i)+j)) == 'x' && *(resultarray+((10*(i+1))+j)) == 'x' && *(resultarray+((10*(i+2))+j)) == 'x')) {

                *(resultarray+((10*i)+j)) = 'S';
                *(resultarray+((10*(i+1))+j)) = 'S';
                *(resultarray+((10*(i+2))+j)) = 'S';
            }
// horizontal 2x boat
            if(((*(numberarray+((10*i)+j)) == '3' && *(numberarray+((10*i)+j+1)) == '3') || (*(numberarray+((10*i)+j)) == '4' && *(numberarray+((10*i)+j+1)) == '4') || (*(numberarray+((10*i)+j)) == '5' && *(numberarray+((10*i)+j+1)) == '5')) &&
               (*(resultarray+((10*i)+j)) == 'x' && *(resultarray+((10*i)+j+1)) == 'x')) {

                *(resultarray+((10*i)+j)) = 'S';
                *(resultarray+((10*i)+j+1)) = 'S';
            }
// vertical 2x boat
            if(((*(numberarray+((10*i)+j)) == '3' && *(numberarray+((10*(i+1))+j)) == '3') || (*(numberarray+((10*i)+j)) == '4' && *(numberarray+((10*(i+1))+j)) == '4') || (*(numberarray+((10*i)+j)) == '5' && *(numberarray+((10*(i+1))+j)) == '5')) &&
               (*(resultarray+((10*i)+j)) == 'x' && *(resultarray+((10*(i+1))+j)) == 'x')) {

                *(resultarray+((10*i)+j)) = 'S';
                *(resultarray+((10*(i+1))+j)) = 'S';
            }            
        }
    }
    
}

void welcomeMessages() {
    printf("\n");
    printf("\nPress ENTER key to start.");
    clean_stdin();
    deleteall();
    printf("Welcome to Battleship!\n");
    printf("\nRules:\n");
    printf("1. the boats have to be placed vertical or horizontal.\n");
    printf("2. the boats are not allowed to touch each other.\n");
    printf("\nKeep in mind that you, as the player have to look if the boats are placed legally.\n");
    printf("\nYou have 10 boats:\n\n   1x with the length of 4\n   2x with the length of 3\n   3x with the length of 2\n   4x with the length of 1\n");
    printf("\nWhen placing a boat, at first give the y coordinate, then the x coordinate.\n");
    printf("\nLegende: \n\n   -  unknown\n   O  boat\n   x  destroyed part of boat\n   S  part of fully destroyed boat\n   w  water");
    printf("\n\n");
    printf("The battlefield looks like that:\n\n");
    previewfield();
    printf("\nPress ENTER key to start.");
    clean_stdin();
    deleteall();
}

//char to void
char boatplacing(char *array, int playernumber, char *resultarray, char *numberarray) {  
    
    // format: player array , player number

    // allocates - to the main array, otherwise error
    for(int i=0; i<100; i++) {
        *(array+i) = '-';
    }

    // allocates ? to the result array, otherwise error
    for(int i=0; i<100; i++) {
        *(resultarray+i) = '-';
    }

    // allocates ? to the numbered array, otherwise error
    for(int i=0; i<100; i++) {
        *(numberarray+i) = '-';
    }

    printf("Player %d:\n\n", playernumber);

    for(int p=0; p<10; p++) { //  p = 10 boats...    // !!!!!
        int x = 0;
        int y = 0;
        int i, k, j;
        int direction;
        printf("y coordinate for boat no.%d with length %d: ", p+1, boatlength[p]);   // what if incompatible input
        scanf("%d", &y);
        clean_stdin();
        printf("x coordinate for boat no.%d with length %d: ", p+1, boatlength[p]);   // what if incompatible input
        scanf("%d", &x);
        clean_stdin();

        y--;
        x--;
        
        printf("\n\n");
        printcolumnnumbers();
        for(i=0; i<10; i++) {
            printf("%c  ", rownumbers[i]);
            for(k=0; k<10; k++) {
                if( y == i && x == k) {
                    printf("O ");
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
        
        if(boatlength[p] != 1) {
            printf("\nThe x's show you where your boat could be placed, depending on the base coordinates,\nboat left (1), right (2), up (3), down (4),  from the starting-point you chose?: ");
            scanf("%d", &direction);  // will be used later
            clean_stdin();
            int temp = boatlength[p];

            if(direction+48 == '1') {           // left
                for(int h=0; h<temp; h++) {
                    *(array+((y*10+x)-h)) = 'O'; 
                }

                printf("\n\n");
                printcolumnnumbers();
                
                for(int i=0; i<10; i++) {
                    printf("%c  ", rownumbers[i]);

                    for(int j=0; j<10; j++) {
                        printf("%c ", *(array+((i*10)+j)));
                    }
                    printf("\n");
                }
                printf("\n");
            }
            if(direction+48 == '2') {           // right
                for(int b=0; b<temp; b++) {
                    *(array+((y*10+x)+b)) = 'O'; 
                }

                printf("\n\n");
                printcolumnnumbers();
                
                for(int i=0; i<10; i++) {
                    printf("%c  ", rownumbers[i]);

                    for(int j=0; j<10; j++) {
                        printf("%c ", *(array+((i*10)+j)));
                    }
                    printf("\n");
                }
                printf("\n");
            }
            if(direction+48 == '3') {           // up
                for(int q=0; q<temp; q++) {
                    *(array+((y-q)*10+x)) = 'O'; 
                    // array[y-q][x] = 'O'; 
                }

                printf("\n\n");
                printcolumnnumbers();
                
                for(int i=0; i<10; i++) {
                    printf("%c  ", rownumbers[i]);

                    for(int j=0; j<10; j++) {
                        printf("%c ", *(array+((i*10)+j)));
                    }
                    printf("\n");
                }
                printf("\n");
            }
            if(direction+48 == '4') {           // down
                for(int t=0; t<temp; t++) {
                    *(array+((y+t)*10+x)) = 'O';
                    //array[y+t][x] = 'O'; 
                }

                printf("\n\n");
                printcolumnnumbers();
                
                printf("\n");
                for(int i=0; i<10; i++) {
                    printf("%c  ", rownumbers[i]);

                    for(int j=0; j<10; j++) {
                        printf("%c ", *(array+((i*10)+j)));
                    }
                    printf("\n");
                }
                printf("\n");
            }
        } 
        else {

        *(array+(((y)*10)+x)) = 'O';


                printf("\n\n");
                printcolumnnumbers();
                
                for(int i=0; i<10; i++) {
                    printf("%c  ", rownumbers[i]);

                    for(int j=0; j<10; j++) {
                        printf("%c ", *(array+((i*10)+j)));
                    }
                    printf("\n");
                }
                printf("\n");
        }

        // specifies the boats in an all knowing field which nobody will see
        switch(boatlength[p]) {
            case 4:
 
                for(int i=0; i<10; i++) {
                    for(int j=0; j<10; j++) {
                        if(*(numberarray+((i*10)+j)) == '-' && *(array+((i*10)+j)) == 'O') { // first condition checks if not already a number
                            *(numberarray+((i*10)+j)) = boatspecifier[p];
                        }
                    }
                }

            break;
            case 3:

                for(int i=0; i<10; i++) {
                    for(int j=0; j<10; j++) {
                        if(*(numberarray+((i*10)+j)) == '-' && *(array+((i*10)+j)) == 'O') { // first condition checks if not already a number
                            *(numberarray+((i*10)+j)) = boatspecifier[p];
                        }
                    }
                }

            break;
            case 2:

                for(int i=0; i<10; i++) {
                    for(int j=0; j<10; j++) {
                        if(*(numberarray+((i*10)+j)) == '-' && *(array+((i*10)+j)) == 'O') { // first condition checks if not already a number
                            *(numberarray+((i*10)+j)) = boatspecifier[p];
                        }
                    }
                }

            break;
            case 1:

                for(int i=0; i<10; i++) {
                    for(int j=0; j<10; j++) {
                        if(*(numberarray+((i*10)+j)) == '-' && *(array+((i*10)+j)) == 'O') { // first condition checks if not already a number
                            *(numberarray+((i*10)+j)) = boatspecifier[p];
                        }
                    }
                }

            break;

        }
    
    }

    printf("\nPlayer %d placed every boat.\n", playernumber);
    printf("\nPress ENTER key to remove your field from the screen.");
    clean_stdin();
    deleteall();
}

// int bc points will be returned
int shooting(int player, char *playerarray, char *resultarray, char *numberarray) {

    int stop = 1;
    int sx, sy;

    do {
        
        printf("Player %d:\n\n", player);

        printf("y coordinate of shot nr %d: ", whichplayerisnow);   // what if incompatible input
        scanf("%d", &sy);
        clean_stdin();
        printf("x coordinate of shot nr %d: ", whichplayerisnow);   // what if incompatible input
        scanf("%d", &sx);
        clean_stdin();

        sx--;
        sy--;

        if(*(resultarray+((sy*10)+sx)) == '-') {

            if(*(playerarray+((sy*10)+sx)) == 'O') {
                printf("\nboat hit! check the fields and go on!\n\n");

                if(*(numberarray+((sy*10)+sx)) == '6' || *(numberarray+((sy*10)+sx)) == '7' || *(numberarray+((sy*10)+sx)) == '8' || *(numberarray+((sy*10)+sx)) == '9') {
                    *(resultarray+((sy*10)+sx)) = 'S';
                }
                else{
                    *(resultarray+((sy*10)+sx)) = 'x';
                }
                return 1;
            }
            if(*(playerarray+((sy*10)+sx)) == '-') {
                printf("\nwater...your opponent will shoot next.\n\n");
                *(resultarray+((sy*10)+sx)) = 'w';
                whoseturn++;
                return 0;
            }
            
            stop = 0;
        }
        else {
            printf("\n\nthe field on which you tried to shoot doesnt exist or is know as water/boat.\nTry again to shoot a field where you dont know its identity.\n\n");
        }

    } while(stop);

}

int main() {

    welcomeMessages();
    boatplacing(*boatfield1, 1, *shootingresult1, *numberedfield1); // format: player array , player number, shooting result
    boatplacing(*boatfield2, 2, *shootingresult2, *numberedfield2); // format: player array , player number, shooting result


///////////////////////////////////////////
    printf("number field1\n\n");
    printf("   ");     
    for(int i=0; i<10; i++) {
        printf("%d ", i+1);
    }
    printf("\n");

    for(int i=0; i<10; i++) {
        printf("%c  ", rownumbers[i]);
            for(int j=0; j<10; j++) {
                printf("%c ", numberedfield1[i][j]); 
            }
        printf("\n");
    }

    printf("number field2\n\n");
    printf("   ");     
    for(int i=0; i<10; i++) {
        printf("%d ", i+1);
    }
    printf("\n");

    for(int i=0; i<10; i++) {
        printf("%c  ", rownumbers[i]);
            for(int j=0; j<10; j++) {
                printf("%c ", numberedfield2[i][j]); 
            }
        printf("\n");
    }
///////////////////////////////////////////

    int counterofplayer1 = 0;
    int counterofplayer2 = 0;

    int temp1;
    int temp2;

    int stop = 1;

    printf("Player 1 starts attacking!\n\n");
    printf("\nPress ENTER key to continue.");
    clean_stdin();
    deleteall();

    do {
        if (whoseturn%2 == 0) {
            printf("before shooting:\n\n");
            printresultfield(*shootingresult1);
            printf("\n");
            //        attacker,   defender ,  attacker result,  attacked numbers
            temp1 = shooting(1, *boatfield2, *shootingresult1, *numberedfield2);
            counterofplayer1 = counterofplayer1 + temp1;

            //            your result,  opponent arrray
            destroyedboat(*shootingresult1, *numberedfield2);

            printplayerfield(*boatfield1);
            printf("\nAfter shooting.\n\n");
            printresultfield(*shootingresult1);
            printf("\nYour points (1 point equals 1 boat part): %d\n", counterofplayer1);

            if(counterofplayer1 >= 20) {               // !!!!!
                stop = 0;

                printf("\n\n");
                for(int i=0; i<3; i++) {
                    printf("Player 1 won! congratulations!\n");
                }
                printf("\n\n");
            }   
            else {
                printf("\nPress ENTER key to continue.");
                clean_stdin();
                deleteall();
            }
            
        }

        if (whoseturn%2 == 1) {
            printf("before shooting:\n\n");
            printresultfield(*shootingresult2);
            printf("\n");
            //        attacker,   defender ,  attacker result, attacked numbers
            temp2 = shooting(2, *boatfield1, *shootingresult2, *numberedfield1);
            counterofplayer2 = counterofplayer2 + temp2;

            //            your result,  opponent arrray
            destroyedboat(*shootingresult2, *numberedfield1);

            printplayerfield(*boatfield2);
            printf("\nAfter shooting.\n\n");
            printresultfield(*shootingresult2);
            printf("\nYour points (1 point equals 1 boat part): %d\n", counterofplayer2);
            
            if(counterofplayer2 >= 20) {               // !!!!!
                stop = 0;

                printf("\n\n");
                for(int i=0; i<3; i++) {
                    printf("Player 2 won! congratulations!\n");
                }
                printf("\n\n");
            }   
            else {
                printf("\nPress ENTER key to continue.");
                clean_stdin();
                deleteall();
            }
        }

    } while(stop); 

}


/////// NOTES ///////

// 10 boat places  && 20 points to win

/////// TO DO /////// 

// boat placing !

// printplayerfield & printresultfield als eine fkt

// z 176 bis 189 3 for schleifen

// 236 und 3x noch

// switch case in boatplacing ist useless

// whoseturn fixen 

// vlt main kürzer

/////// FIXED /////// 

// single boat will be instantly a S

// destroyed boat xxxx to SSSS, xxx to SSS, xx to SS

// 1x boats NO DIRECTION 

// check what field before shooting, allowed to shoot in fields with - 

// error check for destroyedboat function, same row etc.

// abc am rand

// printf("   ");     
//   for(int i=0; i<10; i++) {
//        printf("%d ", i+1);
//   }
// als funktion