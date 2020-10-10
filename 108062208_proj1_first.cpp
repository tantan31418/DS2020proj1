#include<iostream>
#include<string>
#include<vector>
#include <fstream>


using namespace std;

class Matrix_Term{
public:
    Matrix_Term(int r,int c,int v);
    int row,col,val;  
};

class Game_board{
public:
    Game_board();
    Game_board(int r,int c);
    // int check_2();
    // int check_walls();
    void print_board();

    int row,col;
    int board[20][45];
    // int lastempty[45];//only for the game matrix
    //int lastempty[] for every col
};

class Block{
public:
    Block();
    Block(string b_type,int init_c,int mvs);
    // void move_down_max(Game_board*);//move to lastempty
    void move(Game_board*);
    void move_down_1();//move block and add to game board
    void move_down(Game_board*);
    void move_lr(Game_board*);
    void move_up_1();
    void move_left();
    void move_right();
    int check_slot(Game_board*);
    void create_block();
    void add_to_board(Game_board*);
    int hit_ground(Game_board*);
    //data
    int need_to_move;
    string block_type;
    int init_col,terms;//terms=4
    vector<Matrix_Term> term_arr;
};


//main
int main(int argc,char* argv[]){
    /*file in*/
    int r, c;
    ifstream infile;
    infile.open(argv[1]);
    cout << "Reading from the file" << endl;
    infile >> r >> c;
    cout <<"Init Board " <<r <<" "<< c << endl;
    /*Init board*/
    Game_board game(r,c);
    game.print_board();
    string b_ty;
    while (1)
    {
        int init_c, mvs;
        infile >> b_ty;
        if (b_ty == "End")
            break;
        infile >> init_c >> mvs;
        cout <<"Block "<< b_ty <<" " <<init_c<< " "<< mvs << endl;
        Block bl(b_ty,init_c,mvs);
        bl.move(&game);
        game.print_board();
    }
    infile.close();
    /*file in */

    return 0;
}

//impl


Game_board::Game_board(int r,int c){
    row = r;
    col = c;
    for (int i=1;i<=r;i++){
        for (int j=1;j<=c;j++){
            board[i][j]=0;
        }
    }
    // for (int i=1;i<=c;i++){
    //     lastempty[i] = r;
    // }
}


Block::Block(string b_type,int init_c,int mvs){
    block_type = b_type;
    init_col = init_c;
    need_to_move = mvs;
    create_block();
}

Matrix_Term::Matrix_Term(int r,int c,int v){
    row=r;
    col=c;
    val=v;
}
// int Game_board::check_2(){}
void Game_board::print_board(){
    printf("Game Status:\n");
    for (int i=1;i<=row;i++){
        for (int j=1;j<=col;j++){
            printf("%d ",board[i][j]);
        }
        printf("\n");
    }
}

int Block::check_slot(Game_board* gb){
    for (int i=0;i<4;i++){
        if(gb->board[term_arr[i].row][term_arr[i].col]!=0){
            return 1;//slot already in use
        }
    }
    return 0;//available
}
void Block::add_to_board(Game_board* gb){
    for (int i=0;i<4;i++){
        gb->board[term_arr[i].row][term_arr[i].col]+=1;
    }
}
int Block::hit_ground(Game_board* gb){
    for (int i=0;i<4;i++){
        if (term_arr[i].row==(gb->row)+1){
            printf("Block arrive bottom wall!\n");
            return 1;
        }
        else if(term_arr[i].row==0){
            printf("Block arrive top wall!\n");
            return 1;
        }
        else if(term_arr[i].col==0){
            printf("Block arrive left wall!\n");
            return 1;
        }
        else if(term_arr[i].col==(gb->col)+1){
            printf("Block arrive right wall!\n");
            return 1;
        }
    }
    return 0;
}
// void Block::move_down_max(Game_board* gb){
//     int max_ls_em=0;
//     for (int i=0;i<4;i++){
//         int temp_em = gb->lastempty[term_arr[i].row];
//         max_ls_em = (temp_em>max_ls_em) ? temp_em : max_ls_em;
//     }
// }//move to lastempty
void Block::move_down(Game_board* gb){
    while (1){
        move_down_1();
        //for deb
        gb->print_board();
        if (check_slot(gb)==1){//hit below
            move_up_1();
            break;
        }
        if(hit_ground(gb)==1){
            move_up_1();//move up
            break;
        } 
    }
}
void Block::move_lr(Game_board* gb){
    if (need_to_move>0){
        //right
        while (need_to_move!=0){
            move_right();
            //for deb
            gb->print_board();
            if (check_slot(gb)==1){
                printf("Invalid!\n");
                printf("Game Over!\n");
            }
            need_to_move--;
        }
    }
    else if(need_to_move<0){
        //left
        while (need_to_move!=0){
            move_left();
            //for deb
            gb->print_board();
            if (check_slot(gb)==1){
                printf("Invalid!\n");
                printf("Game Over!\n");
            }
            need_to_move++;
        }
    }
    else {
        move_down(gb);
    }
}
void Block::move(Game_board* gb){
    move_down(gb);
    move_lr(gb);
    add_to_board(gb);
}
void Block::move_down_1(){
    for (int i=0;i<4;i++){
        term_arr[i].row++;
    }
}//move block and add to game board
void Block::move_up_1(){
    for (int i=0;i<4;i++){
        term_arr[i].row--;
    }
}
void Block::move_left(){
    for (int i=0;i<4;i++){
        term_arr[i].col--;
    }
}
void Block::move_right(){
    for (int i=0;i<4;i++){
        term_arr[i].col++;
    }
}


void Block::create_block(){
    if (block_type == "T1"){
        Matrix_Term temp1(1,init_col,1);
        Matrix_Term temp2(1,init_col+1,1);
        Matrix_Term temp3(1,init_col+2,1);
        Matrix_Term temp4(2,init_col+1,1);
        term_arr.push_back(temp1);
        term_arr.push_back(temp2);
        term_arr.push_back(temp3);
        term_arr.push_back(temp4);
    }
    else if (block_type == "T2"){
        Matrix_Term temp1(1,init_col+1,1);
        Matrix_Term temp2(2,init_col,1);
        Matrix_Term temp3(2,init_col+1,1);
        Matrix_Term temp4(3,init_col+1,1);
        term_arr.push_back(temp1);
        term_arr.push_back(temp2);
        term_arr.push_back(temp3);
        term_arr.push_back(temp4);
    }
    else if (block_type == "T3"){
        Matrix_Term temp1(1,init_col+1,1);
        Matrix_Term temp2(2,init_col,1);
        Matrix_Term temp3(2,init_col+1,1);
        Matrix_Term temp4(2,init_col+2,1);
        term_arr.push_back(temp1);
        term_arr.push_back(temp2);
        term_arr.push_back(temp3);
        term_arr.push_back(temp4);
    }
    else if (block_type == "T4"){
        Matrix_Term temp1(1,init_col,1);
        Matrix_Term temp2(2,init_col,1);
        Matrix_Term temp3(2,init_col+1,1);
        Matrix_Term temp4(3,init_col,1);
        term_arr.push_back(temp1);
        term_arr.push_back(temp2);
        term_arr.push_back(temp3);
        term_arr.push_back(temp4);
    }
    else if (block_type == "L1"){
        Matrix_Term temp1(1,init_col,1);
        Matrix_Term temp2(2,init_col,1);
        Matrix_Term temp3(3,init_col,1);
        Matrix_Term temp4(3,init_col+1,1);
        term_arr.push_back(temp1);
        term_arr.push_back(temp2);
        term_arr.push_back(temp3);
        term_arr.push_back(temp4);
    }
    else if (block_type == "L2"){
        Matrix_Term temp1(1,init_col,1);
        Matrix_Term temp2(1,init_col+1,1);
        Matrix_Term temp3(1,init_col+2,1);
        Matrix_Term temp4(2,init_col,1);
        term_arr.push_back(temp1);
        term_arr.push_back(temp2);
        term_arr.push_back(temp3);
        term_arr.push_back(temp4);
    }
    else if (block_type == "L3"){
        Matrix_Term temp1(1,init_col,1);
        Matrix_Term temp2(1,init_col+1,1);
        Matrix_Term temp3(2,init_col+1,1);
        Matrix_Term temp4(3,init_col+1,1);
        term_arr.push_back(temp1);
        term_arr.push_back(temp2);
        term_arr.push_back(temp3);
        term_arr.push_back(temp4);
    }
    else if (block_type == "L4"){
        Matrix_Term temp1(1,init_col+2,1);
        Matrix_Term temp2(2,init_col,1);
        Matrix_Term temp3(2,init_col+1,1);
        Matrix_Term temp4(2,init_col+2,1);
        term_arr.push_back(temp1);
        term_arr.push_back(temp2);
        term_arr.push_back(temp3);
        term_arr.push_back(temp4);
    }
    else if (block_type == "J1"){
        Matrix_Term temp1(1,init_col+1,1);
        Matrix_Term temp2(2,init_col+1,1);
        Matrix_Term temp3(3,init_col,1);
        Matrix_Term temp4(3,init_col+1,1);
        term_arr.push_back(temp1);
        term_arr.push_back(temp2);
        term_arr.push_back(temp3);
        term_arr.push_back(temp4);
    }
    else if (block_type == "J2"){
        Matrix_Term temp1(1,init_col,1);
        Matrix_Term temp2(2,init_col,1);
        Matrix_Term temp3(2,init_col+1,1);
        Matrix_Term temp4(2,init_col+1,1);
        term_arr.push_back(temp1);
        term_arr.push_back(temp2);
        term_arr.push_back(temp3);
        term_arr.push_back(temp4);
    }
    else if (block_type == "J3"){
        Matrix_Term temp1(1,init_col,1);
        Matrix_Term temp2(1,init_col+1,1);
        Matrix_Term temp3(2,init_col,1);
        Matrix_Term temp4(3,init_col,1);
        term_arr.push_back(temp1);
        term_arr.push_back(temp2);
        term_arr.push_back(temp3);
        term_arr.push_back(temp4);
    }
    else if (block_type == "J4"){
        Matrix_Term temp1(1,init_col,1);
        Matrix_Term temp2(1,init_col+1,1);
        Matrix_Term temp3(1,init_col+2,1);
        Matrix_Term temp4(2,init_col+2,1);
        term_arr.push_back(temp1);
        term_arr.push_back(temp2);
        term_arr.push_back(temp3);
        term_arr.push_back(temp4);
    }
    else if (block_type == "S1"){
        Matrix_Term temp1(1,init_col+1,1);
        Matrix_Term temp2(1,init_col+2,1);
        Matrix_Term temp3(2,init_col,1);
        Matrix_Term temp4(2,init_col+1,1);
        term_arr.push_back(temp1);
        term_arr.push_back(temp2);
        term_arr.push_back(temp3);
        term_arr.push_back(temp4);
    }
    else if (block_type == "S2"){
        Matrix_Term temp1(1,init_col,1);
        Matrix_Term temp2(2,init_col,1);
        Matrix_Term temp3(2,init_col+1,1);
        Matrix_Term temp4(3,init_col+1,1);
        term_arr.push_back(temp1);
        term_arr.push_back(temp2);
        term_arr.push_back(temp3);
        term_arr.push_back(temp4);
    }
    else if (block_type == "Z1"){
        Matrix_Term temp1(1,init_col,1);
        Matrix_Term temp2(1,init_col+1,1);
        Matrix_Term temp3(2,init_col+1,1);
        Matrix_Term temp4(2,init_col+2,1);
        term_arr.push_back(temp1);
        term_arr.push_back(temp2);
        term_arr.push_back(temp3);
        term_arr.push_back(temp4);
    }
    else if (block_type == "Z2"){
        Matrix_Term temp1(1,init_col+1,1);
        Matrix_Term temp2(2,init_col,1);
        Matrix_Term temp3(2,init_col+1,1);
        Matrix_Term temp4(3,init_col,1);
        term_arr.push_back(temp1);
        term_arr.push_back(temp2);
        term_arr.push_back(temp3);
        term_arr.push_back(temp4);
    }
    else if (block_type == "I1"){
        Matrix_Term temp1(1,init_col,1);
        Matrix_Term temp2(2,init_col,1);
        Matrix_Term temp3(3,init_col,1);
        Matrix_Term temp4(4,init_col,1);
        term_arr.push_back(temp1);
        term_arr.push_back(temp2);
        term_arr.push_back(temp3);
        term_arr.push_back(temp4);
    }
    else if (block_type == "I2"){
        Matrix_Term temp1(1,init_col,1);
        Matrix_Term temp2(1,init_col+1,1);
        Matrix_Term temp3(1,init_col+2,1);
        Matrix_Term temp4(1,init_col+3,1);
        term_arr.push_back(temp1);
        term_arr.push_back(temp2);
        term_arr.push_back(temp3);
        term_arr.push_back(temp4);
    }
    else if (block_type == "O"){
        Matrix_Term temp1(1,init_col,1);
        Matrix_Term temp2(1,init_col+1,1);
        Matrix_Term temp3(2,init_col,1);
        Matrix_Term temp4(2,init_col+1,1);
        term_arr.push_back(temp1);
        term_arr.push_back(temp2);
        term_arr.push_back(temp3);
        term_arr.push_back(temp4);
    }
    else {
        printf("error");
    }
}
