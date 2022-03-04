#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include <time.h>
struct board{
    char **matrix;
    int height;
    int width;
};
struct ship{
    char type;
    int size;
};


int main(int argc, char *argv[ ]) {
      char *filename;
      srand(time(0));
      char orientation,start_col,start_row;
      int row,col,s_r,s_c;
      char user_input[4];
      int grid_size,num_shorts;
      int carrier = 0;
      int battleship = 0;
      int frigate = 0;
      int ship_status = 0;
      int ships_destroyed = 0;
      int end_game = 0;
      char ships[5] = "cbff";
      char location[3] = "rc";
      char ship_destroyed;
      int temp;
      struct ship compship;

    if (argc == 2){
      filename = argv[1];
}
      FILE *ptr_file;
      char buf[1000];
      //ptr_file = fopen("demo_file.txt","r");
      ptr_file = fopen(filename,"r");
            //return 1;

      printf("\n");
      printf("Welcome to Frigate!\n");
      printf("How large should I make the grid? ");
      scanf("%d",&grid_size);
      //printf("%d",grid_size);
      if ((grid_size < 7) || (grid_size > 20)){
        grid_size = 7;
        printf("The minimum grid size is 7... I'll create one that size.\n");
      }

      num_shorts = ((grid_size * grid_size) / 2);
      printf("\n");

      struct board myboard;
      myboard.matrix = NULL;
      myboard.height = grid_size;
      myboard.width = grid_size;

      struct board compboard;
      compboard.matrix = NULL;
      compboard.height = grid_size;
      compboard.width = grid_size;

      myboard.matrix = (char **)malloc(sizeof(char *)*myboard.height);
      for(int i = 0;i < myboard.height;i++){
        myboard.matrix[i] = (char*)malloc(sizeof(char)*myboard.width);
      }

      compboard.matrix = (char **)malloc(sizeof(char *)*compboard.height);
      for(int i = 0;i < compboard.height;i++){
        compboard.matrix[i] = (char*)malloc(sizeof(char)*compboard.width);
      }


    for(int i = 0;i < myboard.height;i++){ // filling with underscores.
        for(int j = 0;j < myboard.width;j++){
            myboard.matrix[i][j] = '_';
        }
    }


    for(int i = 0;i < compboard.height;i++){ // filling with underscores.
        for(int j = 0;j < compboard.width;j++){
            compboard.matrix[i][j] = '_';
        }
    }


if(ptr_file != NULL){
    while(!feof(ptr_file)){ //file reading part.
        fgets(buf,1000,ptr_file);
        if (buf[0] == '#'){

        }
        else{

            if (buf[0] == 'c'){
                compship.type = 'c';
                compship.size = 5;
                orientation = buf[2];
                start_col = buf[4];
                start_row = buf[5];
            }
            else if (buf[0] == 'b'){
                compship.type = 'b';
                compship.size = 4;
                orientation = buf[2];
                start_col = buf[4];
                start_row = buf[5];
            }
            else{
                compship.type = 'f';
                compship.size = 2;
                orientation = buf[2];
                start_col = buf[4];
                start_row = buf[5];
            }
            row = (start_row - '0') - 1;
            col = (start_col - '0') - 49;
            if (orientation == 'r'){
                s_r = row;
                while (row < compship.size+s_r){
                    compboard.matrix[row][col] = compship.type;
                    row += 1;
                }

            }
            else{
                s_c = col;
                while(col < compship.size+s_c){
                    compboard.matrix[row][col] = compship.type;
                    col += 1;
                }

            }
        }

    }

}

else{
for(int i = 0;ships[i] != '\0';i++){
    if (ships[i] == 'c'){
        compship.type = 'c';
        compship.size = 5;
    }
    else if(ships[i] == 'b'){
        compship.type = 'b';
        compship.size = 4;
    }else{
        compship.type = 'f';
        compship.size = 2;
    }
    orientation = location[(rand() % (1 - 0 + 1)) + 0];
    generate_random(&row,&col,grid_size,compship.size);
    temp = check_compmatrix(row,col,compboard.matrix,orientation,compship.size);
    while (temp!= 1){
        generate_random(&row,&col,grid_size,compship.size);
        temp = check_compmatrix(row,col,compboard.matrix,orientation,compship.size);
    }

    if (orientation == 'r'){
        s_r = row;
        while (row < compship.size+s_r){
        compboard.matrix[row][col] = compship.type;
        row += 1;
}
}
    else{
        s_c = col;
        while(col < compship.size+s_c){
        compboard.matrix[row][col] = compship.type;
        col += 1;
}
}
}
}

    display_myboard(myboard.matrix,compboard.matrix,myboard.height,myboard.width,ship_status,ship_destroyed);
    while ((num_shorts > 0) && (end_game != 1)){
        printf("Enter the coordinate for your short ");
        printf("%d",num_shorts);
        printf(" shorts remaining: ");
        scanf("%s",user_input);
        if (check_input(user_input,grid_size) == 1){
            printf("user input is valid.");
            printf("\n");
            ship_status = update_myboard(user_input,compboard.matrix,myboard.matrix,&carrier,&battleship,&frigate,&ship_destroyed);
            if(ship_status == 1){
                ships_destroyed += 1;
            }
            display_myboard(myboard.matrix,compboard.matrix,myboard.height,myboard.width,ship_status,ship_destroyed);
            num_shorts = num_shorts - 1;
            if (ships_destroyed == 4){
                printf("\n");
                printf("You Won! All Ships Destroyed!!!...\n");
                end_game = 1;
            }
        }
        else{
            printf("user input invalid.");
            printf("\n");
        }
    }
    if (num_shorts == 0){
    printf("\n");
    printf("You do not have enough shells left to sink the remaining ships.\n");
    printf("Here is the original ship locations.\n");
    }
    display_compboard(compboard.matrix,compboard.height,compboard.width);
    printf("You sunk %d ships.\n", ships_destroyed);
    printf("PlayAgain (Y/N) ? \n");
    printf("Thank you for playing.");

    deleteArray(myboard.matrix,myboard.height);
    deleteArray(compboard.matrix,compboard.height);

}
