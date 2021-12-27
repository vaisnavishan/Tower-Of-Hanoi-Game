#include <stdio.h> 
#include <string.h>
#include <unistd.h>


// This function, addon_to_peg, will add a new disk on top of the targeted peg 
void addon_to_peg(int peg[],int size_of_disk){ 
    int i = 0;
    for( i = 0; i < 9;i++){
        if( peg[i] == 0){
            peg[i] = size_of_disk;
            break;
        }
    }
}

// This function, remove_from_peg, will remove the topmost disk from the intended peg 
void remove_from_peg(int peg[],int size_of_disk){
    int i = 0;
    for( i = 0; i < 9;i++){
        if( peg[i] == size_of_disk){
            peg[i] = 0;
            break;
        }
    }
}

//This function, display_seg, will display the segment according to its' corresponding number
void display_seg(int number) {
    if (number == 0){
        printf("          |               ");
    }
    else if (number == 1){
        printf("         +|+              ");
    }
    else if (number == 2){
        printf("        ++|++             ");

    }
    else if (number == 3){
        printf("       +++|+++            ");
    }
    else if (number == 4){
        printf("      ++++|++++           ");    
    }
    else if (number == 5){
        printf("     +++++|+++++          ");   
    }
    else if (number == 6){
        printf("    ++++++|++++++         ");   
        
    }
    else if (number == 7){
        printf("   +++++++|+++++++        ");   
        
    }
    else if (number == 8){
        printf("  ++++++++|++++++++       "); 
        
    }
    else if (number == 9){
        printf(" +++++++++|+++++++++      "); 
        
    }
}

// This function, display_pegs, will display the pegs every single time a move is made 
void display_pegs(int A[], int B[],int C[]){
    int i = 0;
    for(i = 8; i >=0;i--){
        display_seg(A[i]);
        display_seg(B[i]);
        display_seg(C[i]);
        printf("\n");
    }
    printf("XXXXXXXXXXXXXXXXXXXXX     XXXXXXXXXXXXXXXXXXXXX     XXXXXXXXXXXXXXXXXXXXX \n");
    printf(" \n");
    printf(" \n");
    sleep(1);

}

// This function, print_pegs, will print all the pegs at each move, in order
void print_pegs(char from_rod, char to_rod, char middle_rod, int from_peg[], int to_peg[], int middle_peg[]){
    if (to_rod == 'A'){
        if(middle_rod == 'B'){
            display_pegs(to_peg,middle_peg,from_peg);
        }
        else {
            display_pegs(to_peg,from_peg,middle_peg);
        }
    }
    else if (middle_rod == 'A'){
        if (to_rod == 'B'){
            display_pegs(middle_peg,to_peg,from_peg);
        }
        else {
            display_pegs(middle_peg,from_peg,to_peg);
        }
    }
    else if (from_rod == 'A'){
        if (to_rod == 'B'){
            display_pegs(from_peg,to_peg,middle_peg);
        }
        else {
            display_pegs(from_peg,middle_peg,to_peg);
        }
    }
}

//This function, tower_of_hanoi, will utilize all of the previously created functions to create the tower of hanoi
void tower_of_hanoi(int number_of_disks, char from_rod, char to_rod, char middle_rod, int from_peg[], int to_peg[], int middle_peg[]){ 
    
    if (number_of_disks == 1){ 
        addon_to_peg(to_peg,number_of_disks);
        remove_from_peg(from_peg,number_of_disks);
        print_pegs(from_rod, to_rod, middle_rod, from_peg, to_peg, middle_peg);
        return; 
    }
    
    tower_of_hanoi(number_of_disks-1, from_rod, middle_rod, to_rod, from_peg, middle_peg, to_peg); 
    addon_to_peg(to_peg,number_of_disks);
    remove_from_peg(from_peg,number_of_disks);
    print_pegs(from_rod, to_rod, middle_rod, from_peg, to_peg, middle_peg);
    tower_of_hanoi(number_of_disks-1, middle_rod, to_rod, from_rod, middle_peg, to_peg, from_peg); 
} 

//This function, main, is the main function and will allow our program to execute
int main(int argc, char *argv[]){ 
    
    if (argc != 2){
        printf("There is an incorrect number of command line arguments. The program is terminating.\n");
        return 0;
    }
    
    if (strlen(argv[1]) != 1){
        printf("Incorrect argument. The program is terminating.\n");
        return 0;
    }

    if( argv[1][0]-'0' < 1 || argv[1][0]-'0' > 9){
        printf("This is an incorrect value of argv[1][0]. The program is terminating.\n");
        return 0;
    }

    int number_of_disks = argv[1][0]-'0';
    
    int peg_A[] = {0,0,0,0,0,0,0,0,0};
    int peg_B[] = {0,0,0,0,0,0,0,0,0};
    int peg_C[] = {0,0,0,0,0,0,0,0,0};
    
    
    int i = number_of_disks;
    
    //Note: Here, we are initializing peg 1 with the appropriate disks 
    for(int j = 0; j < 9; j++){
        peg_A[j]=i;
        i--;
        if (i == 0){
            break;
        }
    }

    display_pegs(peg_A,peg_B,peg_C);
    
    tower_of_hanoi(number_of_disks, 'A', 'B', 'C', peg_A, peg_B, peg_C);  //Note: Here, A, B and C are the names of the rods 
    printf("done\n");
    return 0; 
}
