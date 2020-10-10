#include<string>

class Matrix_Term{
    friend S_Matrix;
    friend Block;
private:
        int row,col,val;  
};

class S_Matrix{
public:
    S_Matrix();
    ~S_Matrix();
    S_Matrix(int row,int col,int t);//t is number of nonzero terms
    S_Matrix Add(S_Matrix b);

private:
    int row,col,terms;
    Matrix_Term *term_arr;
};

class Game_board:private S_Matrix{
public:
    Game_board();
    int check_2();
    int check_walls();
    void print_board();
private:
    int lastempty[45];//only for the game matrix
    //int lastempty[] for every col
};

class Block{
public:
    Block();
    Block(string block_type,int init_col,int moves);
    Block move_down_max(Game_board*);//move to lastempty
    Block move_down_1(Game_board*);//move block and add to game board
    Block move_up_1(Game_board*);
    Block move_left(Game_board*);
    Block move_right(Game_board*);
private:
    int need_to_move;
    string block_type;
    int init_col,terms;//terms=4
    Matrix_Term *term_arr;

};
