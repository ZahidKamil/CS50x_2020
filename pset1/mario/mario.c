# include<stdio.h>
# include<cs50.h>

void print_pyramid(int height);

int main(void){

    int height;

    do{
        height = get_int("Height: ");

    }while(height<1 || height>8);

    // printf("height: %i\n",height);
    print_pyramid(height);
}

void print_pyramid(int height){
    int n =1;
    // while(n<=height){

    //     for(int i=0;i<height;i++){

    //         for(int j=0;j<n;j++){

    //             printf("#");
    //         }
    //         printf("\n");
    //         n+=1;

    //     }
    // }

    while(n<=height){

        for(int i=0;i<height;i++){

            for(int j=0;j<height;j++){

                if(j<(height-i-1)){
                    printf(" ");
                }else{
                    printf("#");
                }
            }
            printf("\n");
            n+=1;
        }
    }

}