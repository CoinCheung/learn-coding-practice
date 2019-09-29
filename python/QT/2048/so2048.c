#include "so2048.h"


/*init the status of the game */
void initGame(){ 

    printf(" in the so2048 C method init()\n");
    currentScore = 0;

    initPanel();

    printf("leave the so2048 C method init()\n");

} 

/* init the numbers of the panel */
void initPanel(){
    char row1, colomn1, row2, colomn2;
    char i,j;

    row1 = randInt()%4;
    colomn1 = randInt()%4;
    do {
    row2 = randInt()%4;
    colomn2 = randInt()%4;
    }while(row1 == row2 && colomn1 == colomn2);

    //printf("the generated locations are %d,%d,%d,%d \n",row1,colomn1,row2,colomn2);
    for(i = 0; i < 4; i++)
        for(j = 0; j<4 ;j++)
            fields[i][j] = 0;
    
    fields[row1][colomn1] = (randInt()%2 + 1)<<1;
    fields[row2][colomn2] = (randInt()%2 + 1)<<1;

    /*
    printf("the initialization is done, the layout is like: \n");
    for(i = 0;i <4 ;i++){
        for(j = 0;j < 4; j++)
           printf("%d,  ",fields[i][j]); 
        printf("\n");
    }*/
}

int randInt(){ // generate an random Integer
    srand((unsigned)time(NULL));
    return rand();
}


/* entrance of the program if debug is implemented */
void main(){
    initGame();
}
