#define PIN_ROW1 13 // defining our 8x8 Matrix
#define PIN_ROW2 12
#define PIN_ROW3 11
#define PIN_ROW4 10
#define PIN_ROW5 9
#define PIN_ROW6 8
#define PIN_ROW7 7
#define PIN_ROW8 6

#define PIN_COL1 16
#define PIN_COL2 17
#define PIN_COL3 18
#define PIN_COL4 19
#define PIN_COL5 2
#define PIN_COL6 3
#define PIN_COL7 4
#define PIN_COL8 5

#define PIN_INPUT_LEFT 15
#define PIN_INPUT_RIGHT 14

#define MAX_BODY_LENGTH 12
#define GAME_AREA_WIDTH 8
#define GAME_AREA_HEIGHT 8
#define GAME_OVER_TIME 3000

typedef struct p
{
  int x;
  int y;
} Position;

Position body[MAX_BODY_LENGTH];
int lastInput;
int head;
int tail;
int bodyLength;
int direction;
Position food;
int gameover;
int score;
int elapsedTime;
bool readInput;
unsigned long previousTime;

void setup()
{    
    pinMode(PIN_ROW1, OUTPUT); // setting up our rows and columns of LEDs
    pinMode(PIN_ROW2, OUTPUT);
    pinMode(PIN_ROW3, OUTPUT);
    pinMode(PIN_ROW4, OUTPUT);
    pinMode(PIN_ROW5, OUTPUT);
    pinMode(PIN_ROW6, OUTPUT);
    pinMode(PIN_ROW7, OUTPUT);
    pinMode(PIN_ROW8, OUTPUT);
    pinMode(PIN_COL1, OUTPUT);
    pinMode(PIN_COL2, OUTPUT);
    pinMode(PIN_COL3, OUTPUT);
    pinMode(PIN_COL4, OUTPUT);
    pinMode(PIN_COL5, OUTPUT);
    pinMode(PIN_COL6, OUTPUT);
    pinMode(PIN_COL7, OUTPUT);
    pinMode(PIN_COL8, OUTPUT);
    pinMode(PIN_INPUT_LEFT, INPUT);
    pinMode(PIN_INPUT_RIGHT, INPUT);
    
    reset(); 
}

void move()
{
  Position prevHead = body[head]; // initialising our struct
  if(direction == DIRECTION_LEFT)
  {
    prevHead.x = prevHead.x -1;
  }
  else
  {
    if(direction == DIRECTION_RIGHT)
    {
      prevHead.x = prevHead.x + 1;
    }
    else
    {
      prevHead.x = prevHead.x;
    }
  }
}


void eat()
{
    if (body[head].x == food.x && body[head].y == food.y) // registers if food has been eaten
    {
        if (bodyLength < MAX_BODY_LENGTH) // if it has then the body length increases
        {
            bodyLength++;
            tail--; // body length increasing makes the tail longer
            if(tail < 0) 
              tail = MAX_BODY_LENGTH - 1;
        }
        score++; // score is then increase
        food = { -1, -1 };
        spawnFood(); // this function creates another piece of food for the snake
    }
}

void draw() // sets the snake to its starting position
{
    body[0] = { 3,3 };
    body[1] = { 3,4 };
    body[2] = { 3,5 };
    bodyLength = 3; // sets the rest of the variables too
    head = 2;
    tail = 0;
    direction = DIRECTION_DOWN;
    food = {-1, -1};
    gameover = 0;
    elapsedTime = 0;
    score = 0;
    spawnFood();
    readInput = true;
}

void checkGameover()
{
  if(head > tail) // game over if the snake runs into itself
    for (int i = tail; i <= head - 1; i++)
    {
        if(body[head].x == body[i].x && body[head].y == body[i].y) 
        {
            gameover = GAME_OVER_TIME; 
            return;
        }
  }
 if(head < tail)
    for(int j = tail; j <= MAX_BODY_LENGTH - 1; j++)
    {
      if(body[head].x == body[j].x && body[head].y == body[j].y)
        {
            gameover = GAME_OVER_TIME;
            return;
        }
    }
}


void loop()
{   
    unsigned long currentTime = millis(); 

    if(!gameover) // checks if the game is over, if it's not we run though this if statement
    {
        draw(); // draw() function creates snake (turns on the correct LEDs)
        elapsedTime += currentTime - previousTime;
        if(elapsedTime > 100)
        {
            move(); // move function allows the snake to move around the matrix
            eat();
            checkGameover();
            elapsedTime = 0;
            readInput = true;
        }
     }
}
