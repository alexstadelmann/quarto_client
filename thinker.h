int free_squares[16];

bool is_winning_move(int, int, int[][4]);
bool is_winning_move_helper(int, int, int[][4]);

int free_squares_search(int[]);

//Function from thinker.c
void calculateMove();
void chooseNextOpponentPiece();

void convert_coordinates(int, char[]);
void insertNextMove(char[], char[]);
