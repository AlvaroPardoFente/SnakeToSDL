//#include <ncurses.h>
//#include <deque>
//#include <chrono>
//#include <thread>
//#include <iostream>
//#include <random>
//
//int screenWidth = 40;
//int screenHeight = 20;
//
//class Coordinates {
//    private:
//        int x;
//        int y;
//
//    public:
//        Coordinate() {}
//        Coordinate(int xVal, int yVal) : x(xVal), y(yVal) {
//            if (x < 0) x = screenWidth;
//            else if (x > screenWidth) x = 0;
//            if (y < 0) y = screenHeight;
//            else if (y > screenHeight) y = 0;
//        }
//
//        int getX() const {return x;}
//        int getY() const {return y;}
//
//};
//
//void renderScreen(const std::deque<Coordinate>& snake);
//
//enum Dir {up, down, left, right};
//
//Coordinate food;
//std::deque<Coordinate> snake;
//Dir lastDir;
//bool loopActive = true;
//int updateTime;
//
//void reduceTimer() {
//
//    if (updateTime > 50) updateTime -= 50;
//}
//
//Dir oppositeDir (Dir dir) {
//    switch (dir) {
//        case up:
//            return down;
//        case down:
//            return up;
//        case left:
//            return right;
//        case right:
//            return left;
//        default:
//            return up;
//    }
//}
//
//bool isValidCoord(int coordX, int coordY) {
//
//    for (const Coordinate& coord : snake) {
//
//        if (coord.getX() == coordX && coord.getY() == coordY) {
//            return false;
//        }
//
//    }
//    
//    return true;
//}
//
//Coordinate generateFood() {
//
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_int_distribution<int> distribX(0, screenWidth);
//    std::uniform_int_distribution<int> distribY(0, screenHeight);
//    bool isCoordTaken = false;
//    int randomX;
//    int randomY;
//
//    do {
//        randomX = distribX(gen);
//        randomY = distribY(gen);
//
//    } while (!isValidCoord(randomX, randomY));
//
//    return Coordinate(randomX, randomY);
//}
//
//void initGame() {
//
//    clear();
//
//    loopActive = true;
//    updateTime = 800;
//    lastDir = up;
//
//    snake.clear();
//    snake.push_front(Coordinate(screenWidth / 2, screenHeight / 2 + 6));
//    snake.push_front(Coordinate(screenWidth / 2, screenHeight / 2 + 5));
//    snake.push_front(Coordinate(screenWidth / 2, screenHeight / 2 + 4));
//    snake.push_front(Coordinate(screenWidth / 2, screenHeight / 2 + 3));
//    snake.push_front(Coordinate(screenWidth / 2, screenHeight / 2 + 2));
//    snake.push_front(Coordinate(screenWidth / 2, screenHeight / 2 + 1));
//    snake.push_front(Coordinate(screenWidth / 2, screenHeight / 2));
//
//    food = generateFood();
//}
//
//void loseGame() {
//
//    loopActive = false;
//    renderScreen(snake);
//    mvprintw(screenHeight / 2, screenWidth / 2 - 5, "GAME OVER");
//
//    mvprintw(screenHeight / 2 + 1, screenWidth / 2 - 12, "Press any key to exit...");
//
//    nodelay(stdscr, FALSE);
//
//    refresh();
//    getch();
//}
//
//bool isValidMove(int moveX,int moveY) {
//
//    for (const Coordinate& coord : snake) {
//        if (coord.getX() == moveX && coord.getY() == moveY) {
//            if (snake.back().getX() == moveX && snake.back().getY() == moveY) return true;
//            return false;
//        }
//    }
//
//    return true;
//}
//
//void moveSnake(Dir dir) {
//
//    int newHeadX = snake.front().getX();
//    int newHeadY = snake.front().getY(); 
//    if (dir == up) newHeadY--;
//    else if (dir == down) newHeadY++;
//    else if (dir == left) newHeadX--;
//    else if (dir == right) newHeadX++;
//    Coordinate newCoord = Coordinate(newHeadX, newHeadY);
//
//    if (!isValidMove(newCoord.getX(), newCoord.getY())) loseGame();
//    snake.push_front(newCoord);
//    if (newCoord.getX() == food.getX() && newCoord.getY() == food.getY()) {
//        food = generateFood();
//        reduceTimer();
//    } else snake.pop_back();
//}
//
//int readInput() {
//
//    int ch;
//    int nextInput = -1;
//    while ((ch = getch()) != ERR) {
//        if (ch == 27 || ch == KEY_UP || ch == KEY_DOWN || ch == KEY_LEFT || ch == KEY_RIGHT) {
//            nextInput = ch;
//        }
//    }
//    return nextInput;
//}
//
//void handleInput(int ch) {
//
//    if (ch == 27) loopActive = false;
//    else {
//        if (ch == KEY_UP) {if (up != oppositeDir(lastDir)) lastDir = up;}
//        else if (ch == KEY_DOWN) {if (down != oppositeDir(lastDir)) lastDir = down;}
//        else if (ch == KEY_LEFT) {if (left != oppositeDir(lastDir)) lastDir = left;}
//        else if (ch == KEY_RIGHT) {if (right != oppositeDir(lastDir)) lastDir = right;}
//        moveSnake(lastDir);
//    }
//}
//
//void renderScreen(const std::deque<Coordinate>& snake) {
//
//    for (const auto& segment : snake) {
//        mvprintw(segment.getY() + 1, segment.getX() + 1, "o");
//    } mvprintw(snake.front().getY() + 1, snake.front().getX() + 1, "@");
//
//    mvprintw(food.getY() + 1, food.getX() + 1, "$");
//
//    // Draw top border
//    mvhline(0, 0, '#', screenWidth + 2);
//    
//    // Draw bottom border
//    mvhline(screenHeight + 2, 0, '#', screenWidth + 2);
//    
//    // Draw left border
//    mvvline(0, 0, '#', screenHeight + 2);
//    
//    // Draw right border
//    mvvline(0, screenWidth + 2, '#', screenHeight + 2);
//
//    refresh();
//}
//
//void loop() {
//
//    while(loopActive)
//    {
//        clear();
//        handleInput(readInput());
//        if (!loopActive) break;
//        // update game logic
//
//        renderScreen(snake);
//
//        std::this_thread::sleep_for(std::chrono::milliseconds(updateTime));
//    }
//
//}
//
//int main() {
//
//    initscr();
//    raw();
//    keypad(stdscr, TRUE);
//    noecho();
//    curs_set(0);
//    nodelay(stdscr, TRUE);
//    resize_term(screenHeight+4, screenWidth+4);
//
//    initGame();
//
//    loop();
//
//    endwin();
//    return 0;
//}