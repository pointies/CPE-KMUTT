#include<stdio.h>
#include<time.h>
int main()
{
    int x, y, count;
    char name[20], ch;

    printf("\n******** PROGRAM RANDOM NUMBER ********\n");
    printf("Enter your name : ");
    scanf("%s",name);
    printf("Hello %s\n", name);
    printf("\n");

    do {
        srand(time(NULL));
        x = rand()%100+1;
        count = 0;
        printf("Cheat : %d\n\n", x);
        do {
            count = count+1;
            printf("--------Round %d--------",count);
            printf("\nYour number is ");
            scanf("%d", &y);

            if (y==x) {
                printf("\nYOU WIN!!!\n\n");
            }
            else {
                if (y<x) {
                    printf(" * Wrong!! Your number is Less than\n");
                }
                else {
                    printf(" * Wrong!! Your number is too much\n");
                }
                if (count==7) {
                    printf("\nYOU LOSE :((\n");
                    printf("The correct answer is %d\n\n", x);
                }
            }
        } while (count<7 && x!=y);

        do {
            printf("Enter y to play again or n to exit. ");
            scanf(" %c",&ch);
        } while(ch!='y' && ch!='n' && ch!='Y');
        printf("\n");
    } while (ch=='y' || ch=='Y');
    printf("End Program\n");
    return 0;
}
