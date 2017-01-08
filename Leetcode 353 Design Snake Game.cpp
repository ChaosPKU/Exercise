/*
Design a Snake game that is played on a device with screen size = width x height. Play the game online if you are not familiar with the game.

The snake is initially positioned at the top left corner (0,0) with length = 1 unit.

You are given a list of food's positions in row-column order. When a snake eats the food, its length and the game's score both increase by 1.

Each food appears one by one on the screen. For example, the second food will not appear until the first food was eaten by the snake.

When a food does appear on the screen, it is guaranteed that it will not appear on a block occupied by the snake.

Example:
Given width = 3, height = 2, and food = [[1,2],[0,1]].

Snake snake = new Snake(width, height, food);

Initially the snake appears at position (0,0) and the food at (1,2).

|S| | |
| | |F|

snake.move("R"); -> Returns 0

| |S| |
| | |F|

snake.move("D"); -> Returns 0

| | | |
| |S|F|

snake.move("R"); -> Returns 1 (Snake eats the first food and right after that, the second food appears at (0,1) )

| |F| |
| |S|S|

snake.move("U"); -> Returns 1

| |F|S|
| | |S|

snake.move("L"); -> Returns 2 (Snake eats the second food)

| |S|S|
| | |S|

snake.move("U"); -> Returns -1 (Game over because snake collides with border)

Credits:
Special thanks to @elmirap for adding this problem and creating all test cases.
*/

class SnakeGame {
public:
    int Width, Height, Score;
    vector<pair<int, int>> Foods;
    list<pair<int, int>> Body;
    pair<int, int> Head;
    /** Initialize your data structure here.
        @param width - screen width
        @param height - screen height 
        @param food - A list of food positions
        E.g food = [[1,1], [1,0]] means the first food is positioned at [1,1], the second is at [1,0]. */
    SnakeGame(int width, int height, vector<pair<int, int>> food) {
        Width = width;
        Height = height;
        Foods = food;
        Head = make_pair(0, 0);
        Score = 0;
        Body.push_back(Head);
    }
    
    /** Moves the snake.
        @param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down 
        @return The game's score after the move. Return -1 if game over. 
        Game over when snake crosses the screen boundary or bites its body. */
    int move(string direction) {
        pair<int, int> new_head = Head;
        switch(direction[0]){
            case 'U': new_head.first -= 1; break;
            case 'D': new_head.first += 1; break;
            case 'R': new_head.second += 1; break;
            case 'L': new_head.second -= 1; break;
        }
        if(new_head.first < 0 || new_head.second < 0 || new_head.first >= Height || new_head.second >= Width)
            return -1;
        for(auto itr = Body.begin(); itr != Body.end(); ++ itr)
            if(*itr == new_head) {
                if(*itr == Body.back()) continue;
                else return -1;
            }
        Body.push_front(new_head);
        Head = new_head;
        if(Score < Foods.size() && Head == Foods[Score])
            return ++ Score;
        Body.pop_back();
        return Score;
    }
};

/**
 * Your SnakeGame object will be instantiated and called as such:
 * SnakeGame obj = new SnakeGame(width, height, food);
 * int param_1 = obj.move(direction);
 */
