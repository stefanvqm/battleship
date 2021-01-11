
#include <stdio.h>
#include <stdlib.h>

const char boatspecifier[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}; // gives every boat an unique number, used in numberedfield 1 & 2
const int boatlength[] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
const int rownumbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // used for the field rows

char boatfield1[10][10];      // field of player 1, format: [y][x]
char boatfield2[10][10];      // field of player 2, format: [y][x]
char shootingresult1[10][10]; // result of p1's shootings
char shootingresult2[10][10]; // result of p2's shootings
char numberedfield1[10][10];  // for function destroyedboat
char numberedfield2[10][10];  // for function destroyedboat

int whoseturn = 0; // used to decide whose shooting

// deletes the terminal for changing user
void deleteall(void)
{
//  source: https://stackoverflow.com/questions/142508/how-do-i-check-os-with-a-preprocessor-directive
#if defined _WIN32
    system("CLS");
#elif defined(__unix__)
    system("clear");
#endif
}

// cleans buffer of standard input, for preventing error
void clean_stdin(void)
{ // credits: "Miron", thanks for helping!
    char c;
    do
    {
        c = (char)getc(stdin);
    } while (c != '\n' && c != EOF);
}

// prints the numbers for the x-axis of the battlefield
void printcolumnnumbers(void)
{
    printf("   ");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", i + 1);
    }
    printf("\n");
}

// prints preview field for the start screen. used in welcome messages
void previewfield(void)
{
    printcolumnnumbers();
    for (int i = 0; i < 10; i++)
    {
        if (rownumbers[i] != 10)
        {
            printf("%d  ", rownumbers[i]);
        }
        else
        {
            printf("%d ", rownumbers[i]);
        }
        for (int j = 0; j < 10; j++)
        {
            printf("- ");
        }
        printf("\n");
    }
}

// prints a specified field, depending what parameter is used
void printfield(char *fieldarray)
{
    printcolumnnumbers();
    for (int i = 0; i < 10; i++)
    {
        if (rownumbers[i] != 10)
        {
            printf("%d  ", rownumbers[i]);
        }
        else
        {
            printf("%d ", rownumbers[i]);
        }

        for (int j = 0; j < 10; j++)
        {
            printf("%c ", *(fieldarray + ((i * 10) + j)));
        }
        printf("\n");
    }
    printf("\n\n");
}

// transforms characters of completely destroyed boats from x to S
// boats that are just one field won't be transformed here, see: shooting function
// format:              your results, opponents numbered arrray
void destroyedboat(char *resultarray, char *numberarray)
{

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            // horizontal 4x boat
            if ((*(numberarray + ((10 * i) + j)) == '0' && *(numberarray + ((10 * i) + j + 1)) == '0' && *(numberarray + ((10 * i) + j + 2)) == '0' && *(numberarray + ((10 * i) + j + 3)) == '0') &&
                (*(resultarray + ((10 * i) + j)) == 'x' && *(resultarray + ((10 * i) + j + 1)) == 'x' && *(resultarray + ((10 * i) + j + 2)) == 'x' && *(resultarray + ((10 * i) + j + 3)) == 'x'))
            {

                *(resultarray + ((10 * i) + j)) = 'S';
                *(resultarray + ((10 * i) + j + 1)) = 'S';
                *(resultarray + ((10 * i) + j + 2)) = 'S';
                *(resultarray + ((10 * i) + j + 3)) = 'S';

                printf("\nYou smashed a boat to the ocean floor!\n");
            }
            // vertical 4x boat
            if ((*(numberarray + ((10 * i) + j)) == '0' && *(numberarray + ((10 * (i + 1)) + j)) == '0' && *(numberarray + ((10 * (i + 2)) + j)) == '0' && *(numberarray + ((10 * (i + 3)) + j)) == '0') &&
                (*(resultarray + ((10 * i) + j)) == 'x' && *(resultarray + ((10 * (i + 1)) + j)) == 'x' && *(resultarray + ((10 * (i + 2)) + j)) == 'x' && *(resultarray + ((10 * (i + 3)) + j)) == 'x'))
            {

                *(resultarray + ((10 * i) + j)) = 'S';
                *(resultarray + ((10 * (i + 1)) + j)) = 'S';
                *(resultarray + ((10 * (i + 2)) + j)) = 'S';
                *(resultarray + ((10 * (i + 3)) + j)) = 'S';

                printf("\nYou smashed a boat to the ocean floor!\n");
            }
            // horizontal 3x boat
            if (((*(numberarray + ((10 * i) + j)) == '1' && *(numberarray + ((10 * i) + j + 1)) == '1' && *(numberarray + ((10 * i) + j + 2)) == '1') || (*(numberarray + ((10 * i) + j)) == '2' && *(numberarray + ((10 * i) + j + 1)) == '2' && *(numberarray + ((10 * i) + j + 2)) == '2')) &&
                (*(resultarray + ((10 * i) + j)) == 'x' && *(resultarray + ((10 * i) + j + 1)) == 'x' && *(resultarray + ((10 * i) + j + 2)) == 'x'))
            {

                *(resultarray + ((10 * i) + j)) = 'S';
                *(resultarray + ((10 * i) + j + 1)) = 'S';
                *(resultarray + ((10 * i) + j + 2)) = 'S';

                printf("\nYou smashed a boat to the ocean floor!\n");
            }
            // vertical 3x boat
            if (((*(numberarray + ((10 * i) + j)) == '1' && *(numberarray + ((10 * (i + 1)) + j)) == '1' && *(numberarray + ((10 * (i + 2)) + j)) == '1') || (*(numberarray + ((10 * i) + j)) == '2' && *(numberarray + ((10 * (i + 1)) + j)) == '2' && *(numberarray + ((10 * (i + 2)) + j)) == '2')) &&
                (*(resultarray + ((10 * i) + j)) == 'x' && *(resultarray + ((10 * (i + 1)) + j)) == 'x' && *(resultarray + ((10 * (i + 2)) + j)) == 'x'))
            {

                *(resultarray + ((10 * i) + j)) = 'S';
                *(resultarray + ((10 * (i + 1)) + j)) = 'S';
                *(resultarray + ((10 * (i + 2)) + j)) = 'S';

                printf("\nYou smashed a boat to the ocean floor!\n");
            }
            // horizontal 2x boat
            if (((*(numberarray + ((10 * i) + j)) == '3' && *(numberarray + ((10 * i) + j + 1)) == '3') || (*(numberarray + ((10 * i) + j)) == '4' && *(numberarray + ((10 * i) + j + 1)) == '4') || (*(numberarray + ((10 * i) + j)) == '5' && *(numberarray + ((10 * i) + j + 1)) == '5')) &&
                (*(resultarray + ((10 * i) + j)) == 'x' && *(resultarray + ((10 * i) + j + 1)) == 'x'))
            {

                *(resultarray + ((10 * i) + j)) = 'S';
                *(resultarray + ((10 * i) + j + 1)) = 'S';

                printf("\nYou smashed a boat to the ocean floor!\n");
            }
            // vertical 2x boat
            if (((*(numberarray + ((10 * i) + j)) == '3' && *(numberarray + ((10 * (i + 1)) + j)) == '3') || (*(numberarray + ((10 * i) + j)) == '4' && *(numberarray + ((10 * (i + 1)) + j)) == '4') || (*(numberarray + ((10 * i) + j)) == '5' && *(numberarray + ((10 * (i + 1)) + j)) == '5')) &&
                (*(resultarray + ((10 * i) + j)) == 'x' && *(resultarray + ((10 * (i + 1)) + j)) == 'x'))
            {

                *(resultarray + ((10 * i) + j)) = 'S';
                *(resultarray + ((10 * (i + 1)) + j)) = 'S';

                printf("\nYou smashed a boat to the ocean floor!\n");
            }
        }
    }
}

// welcome screen and its messages
void welcomeMessages(void)
{
    printf("\n\nPress ENTER key to start.");
    clean_stdin();
    deleteall();
    printf("Welcome to Battleship!\n");
    printf("\nRules:\n");
    printf("1. the boats have to be placed vertical or horizontal.\n");
    printf("2. the boats are not allowed to touch each other.\n");
    printf("\nKeep in mind that you, as the player have to look if the boats are placed legally.\n");
    printf("\nYou have 10 boats:\n\n   1x with the length of 4\n   2x with the length of 3\n   3x with the length of 2\n   4x with the length of 1\n");
    printf("\nWhen placing a boat, at first give the y coordinate, then the x coordinate.\n");
    printf("\nLegend:\n\n   -  unknown\n   O  boat\n   x  destroyed part of boat\n   S  part of fully destroyed boat\n   w  water");
    printf("\n\n");
    printf("The battlefield looks like that:\n\n");
    previewfield();
    printf("\nPress ENTER key to start.");
    clean_stdin();
    deleteall();
}

// allocates '-' to the specified array, otherwise error
void arrayallocating(char *array)
{
    for (int i = 0; i < 100; i++)
    {
        *(array + i) = '-';
    }
}

// delares in the numbered array for every boat a unique number
void boatsToNumbers(char *array, char *numberarray, int p)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {   
            if (*(numberarray + ((i * 10) + j)) == '-' && *(array + ((i * 10) + j)) == 'O') // first condition checks if not already a number, means already a boat
            { 
                *(numberarray + ((i * 10) + j)) = boatspecifier[p];
            }
        }
    }
}

// checks for correct inputs in boatplacing for the coordiantes and the direction and in shooting for the coordiantes
int checkinput(int x, int g)
{
    do
    {
        if (x <= g && x >= 1)
        {
            return x;
        }
        else
        {
            printf("\nwrong input, try again: ");
            scanf("%d", &x);
        }
    } while (1);
}

// boat placing
void boatplacing(char *array, int playernumber, char *resultarray, char *numberarray)
{

    // allocates - to the main array, otherwise error
    arrayallocating(array);

    // allocates ? to the result array, otherwise error
    arrayallocating(resultarray);

    // allocates ? to the numbered array, otherwise error
    arrayallocating(numberarray);

    printf("Player %d:\n\n", playernumber);

    for (int p = 0; p < 10; p++)
    { //  p = 10 because there are 10 boats to be placed
        int x = 0;
        int y = 0;
        int direction;
        printf("\ny coordinate for boat no.%d with length %d: ", p + 1, boatlength[p]);
        scanf("%d", &y);
        y = checkinput(y, 10);
        clean_stdin();

        printf("\nx coordinate for boat no.%d with length %d: ", p + 1, boatlength[p]);
        scanf("%d", &x);
        x = checkinput(x, 10);
        clean_stdin();

        y--; // array is from 0 to 9, player gives input from 1 to 10
        x--; // array is from 0 to 9, player gives input from 1 to 10

        printf("\n\n");
        printcolumnnumbers();

        // prints a temporary field, it wont be saved here because the x's shouldn't be in the field
        for (int i = 0; i < 10; i++)
        {
            if (rownumbers[i] != 10)
            {
                printf("%d  ", rownumbers[i]);
            }
            else
            {
                printf("%d ", rownumbers[i]);
            }
            for (int k = 0; k < 10; k++)
            {
                if (y == i && x == k)
                {
                    printf("O ");
                }
                else
                {
                    // possible directions for placing the boat
                    if (((y == i) && ((k - x) < boatlength[p]) && ((x - k) < boatlength[p])) || ((x == k) && ((i - y) < boatlength[p]) && ((y - i) < boatlength[p])))
                    {
                        printf("x ");
                    }
                    else
                    {
                        printf("- ");
                    }
                }
            }
            printf("\n");
        }

        if (boatlength[p] != 1)
        { // boats with a length bigger than 1 need a direction. 1x1 boats have no direction
            printf("\nThe x's show you where your boat could be placed, depending on the base coordinates.\nPlease check if there is enough space for your boat, considering the boat length.\nBoat left (1), right (2), up (3), down (4),  from the starting-point you chose?: ");
            scanf("%d", &direction);
            direction = checkinput(direction, 4);
            clean_stdin();
            int temp = boatlength[p];

            if (direction + 48 == '1')
            { // if player decides left
                for (int h = 0; h < temp; h++)
                {
                    *(array + ((y * 10 + x) - h)) = 'O';
                }

                printf("\n\n");
                printfield(array);
            }
            if (direction + 48 == '2')
            { // if player decides right
                for (int b = 0; b < temp; b++)
                {
                    *(array + ((y * 10 + x) + b)) = 'O';
                }

                printf("\n\n");
                printfield(array);
            }
            if (direction + 48 == '3')
            { // if player decides up
                for (int q = 0; q < temp; q++)
                {
                    *(array + ((y - q) * 10 + x)) = 'O';
                }

                printf("\n\n");
                printfield(array);
            }
            if (direction + 48 == '4')
            { // if player decides down
                for (int t = 0; t < temp; t++)
                {
                    *(array + ((y + t) * 10 + x)) = 'O';
                }

                printf("\n\n");
                printfield(array);
            }
        }
        else
        {

            *(array + (((y)*10) + x)) = 'O'; // for boats with length 1
            printf("\n\n");
            printfield(array);
        }

        // specifies the boats in an all knowing field (numberedfield) which nobody will see
        boatsToNumbers(array, numberarray, p);
    }

    printf("\nPlayer %d placed every boat.\n", playernumber);
    printf("\nPress ENTER key to remove your field from the screen.");
    clean_stdin();
    deleteall();
}

// int because points will be returned for score
int shooting(int player, char *playerarray, char *resultarray, char *numberarray)
{

    int sx, sy;

    printf("Player %d:\n\n", player);

    printf("y coordinate of shot: ");
    scanf("%d", &sy);
    sy = checkinput(sy, 10);
    clean_stdin();
    printf("x coordinate of shot: ");
    scanf("%d", &sx);
    sx = checkinput(sx, 10);
    clean_stdin();

    sx--;
    sy--;

    if (*(resultarray + ((sy * 10) + sx)) == '-')
    { // checks if field can be attacked or is already known

        if (*(playerarray + ((sy * 10) + sx)) == 'O')
        {
            printf("\nboat hit! check the fields and go on!\n\n");
            // boats with the length of 1 have in the numbered field the specified numbers 6, 7, 8 and 9. a boat with length 1 will be instantly marked as a S
            if (*(numberarray + ((sy * 10) + sx)) == '6' || *(numberarray + ((sy * 10) + sx)) == '7' || *(numberarray + ((sy * 10) + sx)) == '8' || *(numberarray + ((sy * 10) + sx)) == '9')
            {
                *(resultarray + ((sy * 10) + sx)) = 'S';
            }
            else
            {
                *(resultarray + ((sy * 10) + sx)) = 'x';
            }
            return 1; // returns 1 point because shot hit boat
        }
        if (*(playerarray + ((sy * 10) + sx)) == '-')
        {
            printf("\nwater...your opponent will shoot next.\n\n");
            *(resultarray + ((sy * 10) + sx)) = 'w';
            whoseturn++; // adds 1 to whoseturn, this makes the switch to the other player.
            return 0;    // returns 0 point because shot hit water
        }
    }
    else
    {
        printf("\n\nthe field on which you tried to shoot doesnt exist or is know as water/boat.\nTry again to shoot a field where you dont know its identity.\n\n");
    }
    return 0; // returns 0 point because shot hit water
}

//                   my shootingresult,     player,  opponent b.field,      opponent n.field,   my b.field, 
int gameProcess(char *shootingresult_m, int player, char *boatfield_o, char *numberedfield_o, char *boatfield_m)
{

    int temp = 0; // temporary to mangage the points given from the shooting function to counterofplayer

    printf("before shooting:\n\n");

    printf("Your shooting results\n\n");
    printfield(shootingresult_m);

    printf("\n");
    //        attacker,   defender ,  attacker result,  attacked numbers
    temp = shooting(player, boatfield_o, shootingresult_m, numberedfield_o);

    //                 your result,  opponents n.field
    destroyedboat(shootingresult_m, numberedfield_o);

    printf("Your field\n\n");
    printfield(boatfield_m);

    printf("\nAfter shooting.\n\n");

    printf("Your shooting results\n\n");
    printfield(shootingresult_m);

    return temp;
}

int checkIfWon(int counterofplayer_m, int player)
{

    if (counterofplayer_m == 20)
    { // 20 points because the boats have in total 20 parts to hit

        printf("\n\n");
        for (int i = 0; i < 3; i++)
        {
            printf("Player %d won! congratulations!\n", player);
        }
        printf("\n\n");

        return 0;
    }
    else
    {
        printf("\nPress ENTER key to continue.");
        clean_stdin();
        deleteall();

        return 1;
    }
}

int main(void)
{

    welcomeMessages();
    boatplacing(*boatfield1, 1, *shootingresult1, *numberedfield1); // format: player array , player number, shooting result, numbered field
    boatplacing(*boatfield2, 2, *shootingresult2, *numberedfield2); // format: player array , player number, shooting result, numbered field

    int counterofplayer1 = 0; // points to decide who won
    int counterofplayer2 = 0; // points to decide who won

    int stop = 1; // used to make the do-while loop infinite until one player wins and turns it to 0

    printf("Player 1 starts attacking!\n\n");
    printf("\nPress ENTER key to continue.");
    clean_stdin();
    deleteall();

    do
    {
        if (whoseturn % 2 == 0)
        {

            // the game process
            counterofplayer1 = counterofplayer1 + gameProcess(*shootingresult1, 1, *boatfield2, *numberedfield2, *boatfield1);

            printf("\nYour points (1 point equals 1 boat part): %d/20\n", counterofplayer1);

            // if won, checkIfWon returns 0 which causes to stop the do-while-loop
            stop = checkIfWon(counterofplayer1, 1);
        }

        if (whoseturn % 2 == 1)
        {

            // the game process
            counterofplayer2 = counterofplayer2 + gameProcess(*shootingresult2, 2, *boatfield1, *numberedfield1, *boatfield2);
            printf("\nYour points (1 point equals 1 boat part): %d/20\n", counterofplayer2);

            // if won, checkIfWon returns 0 which causes to stop the do-while-loop
            stop = checkIfWon(counterofplayer2, 2);
        }
    } while (stop);
}
