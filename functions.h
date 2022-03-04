#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include<ctype.h>
#include<string.h>
#include<time.h>
int check_input(char inp[4],int gridsize){
    int row;
    int col;
    char temp1,temp2;
    if((strlen(inp) < 2) || (strlen(inp) > 3)){
        return 0;
    }
    else if((gridsize < 10) && (strlen(inp) == 3)){
        return 0;
    }
    else{
     for(int i = 0;inp[i] != '\0';i++){
         if (strlen(inp) == 2){
            if (((isalpha(inp[0]) == 0) && (isalpha(inp[1]) == 0))||((isalpha(inp[0]) != 0) && (isalpha(inp[1]) != 0))){
                return 0;
            }
            else{
                if(isalpha(inp[i]) != 0){
                    col = (tolower(inp[i]) - '0') - 49;
                    if (col > gridsize){
                        return 0;
                    }
                }
                else if(isdigit(inp[i]) != 0){
                    row = (inp[i] - '0');
                    if (row > gridsize){
                        return 0;
                    }
                }
        }
        }
        else{
            if ((isalpha(inp[0]) == 0) && (isalpha(inp[1]) == 0) && (isalpha(inp[2]) == 0)){
                return 0;
            }
            else{
                if(isalpha(inp[i]) != 0){
                    col = (tolower(inp[i]) - '0') - 49;
                    if (col > gridsize){
                        return 0;
                    }
                }
                else if(isdigit(inp[i]) != 0){
                    if (inp[i+1] != '\0'){
                        temp1 = (inp[i+1] - '0');
                    }
                    temp2 = (inp[i] - '0') * 10;
                    temp2 += temp1;
                    if (temp2 > gridsize){
                        return 0;
                    }
                    }
                }
            }
        }
}

    return 1;
}

int update_myboard(char inp[4],char** compmatrix,char** mymatrix,int *carrier,int *battleship,int *frigate,char *ship_destroyed){
    int row_pos;
    int col_pos;
    char c,r;
    char ship_type;
    int temp1;
    if (strlen(inp) == 2){
    for(int i = 0;inp[i] != '\0';i++){
        if (isdigit(inp[i]) != 0){
            r = inp[i];
            row_pos = (r - '0') - 1;
        }
        else if(isalpha(inp[i]) != 0){
            c = tolower(inp[i]);
            col_pos = (c - '0') - 49;
            c = toupper(c);
        }
    }
    }
    else{
    for(int i = 0;inp[i+1] != '\0';i++){
        if(isalpha(inp[i]) != 0){
            c = tolower(inp[i]);
            col_pos = (c - '0') - 49;
            c = toupper(c);
        }
        else if(isdigit(inp[i]) != 0){
            if (inp[i+1] != '\0'){
            temp1 = (inp[i+1] - '0');
            }
            row_pos = (inp[i] - '0') * 10;
            row_pos += temp1;
            row_pos -= 1;
}
}

}
    if (compmatrix[row_pos][col_pos] != '_') {
        if(mymatrix[row_pos][col_pos] != 'h'){
            mymatrix[row_pos][col_pos] = 'h';
            ship_type = compmatrix[row_pos][col_pos];
            printf("%c%c",c,r);
            printf(" is a hit!");
            if(ship_type == 'c'){
                *carrier += 1;
                if (*carrier == 4){
                    *ship_destroyed = 'c';
                    *carrier = 0;
                    return 1;
                }
            }else if(ship_type == 'b'){
                *battleship += 1;
                if (*battleship == 3){
                    *ship_destroyed = 'b';
                    *battleship = 0;
                    return 1;
                }
            }else{
                *frigate += 1;
                if(*frigate == 2){
                    *ship_destroyed = 'f';
                    *frigate = 0;
                     return 1;
                }
            }
        }
    }
    else{
        mymatrix[row_pos][col_pos] = 'm';
        //compmatrix[row_pos][col_pos] = 'm';
        printf("%c%c",c,r);
        printf(" is a miss!");
    }
    printf("\n");
    return 0;
}


void display_myboard(char** mymatrix,char** compmatrix, int height,int width,int ship_status,char ship_destroyed){
    if(ship_status == 1){
        printf("\n");
        printf(" ");
        for (int j = 0;j < width;j++){
        printf("%*s", 1,  "");
        printf("%c",j+65);
        }
        printf("\n");
        for(int i = 0;i < height;i++){ //printing the underscores.
            printf("%d",i + 1);
            printf("%*s", 1, "");
            for(int j = 0;j < width;j++){
                if ((mymatrix[i][j] == 'h') && (compmatrix[i][j] == ship_destroyed)){
                    printf("%c",compmatrix[i][j]);
                    printf("%*s", 1, "");
                    }

                else{
                    printf("%c", mymatrix[i][j]);
                    printf("%*s", 1, "");
                }
            }
            printf("\n");
        }

    }

    else{
    printf(" ");
    for (int j = 0;j < width;j++){
        printf("%*s", 1,  "");
        printf("%c",j+65);

    }
    printf("\n");
    for(int i = 0;i < height;i++){ //printing the underscores.
        printf("%d",i + 1);
        printf("%*s", 1, "");
        for(int j = 0;j < width;j++){
            printf("%c", mymatrix[i][j]);
            printf("%*s", 1, "");
        }

        printf("\n");

    }
}
}

void display_compboard(char** compmatrix,int height,int width){
    printf(" ");
    for (int j = 0;j < width;j++){
        printf("%*s", 1,  "");
        printf("%c",j+65);

    }
    printf("\n");
    for(int i = 0;i < height;i++){ //displaying the computer board.
        printf("%d",i + 1);
        printf("%*s", 1, "");
        for(int j = 0;j < width;j++){
            printf("%c", compmatrix[i][j]);
            printf("%*s", 1, "");
        }
        printf("\n");
    }
}
void generate_random(int *row,int *col,int gridsize, int shipsize){
    srand(time(0));
    *row = (rand() % ((gridsize - shipsize) - 0 + 1)) + 0;
    *col = (rand() % ((gridsize - shipsize)- 0 + 1)) + 0;
}

int check_compmatrix(int row,int col,char** compmatrix,char ori,int shipsize){
    int sc,sr;
    if (ori == 'r'){
        sr = row;
        while(row < shipsize + sr){
            if (compmatrix[row][col] != '_'){
                return 0;
            }
            row += 1;
        }
    }else{
        sc = col;
        while(col < shipsize + sc){
            if(compmatrix[row][col] != '_'){
                return 0;
            }
            col += 1;
        }
    }
    return 1;


}

void deleteArray(char** myArray, int rows) {
  for (int i = 0; i < rows; i++) {
    free(myArray[i]);
  }
  free(myArray);

  return;
}
#endif // FUNCTIONS_H_INCLUDED
