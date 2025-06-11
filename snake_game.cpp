#include <MD_MAX72xx.h>
#include <SPI.h>
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

#define MAX_DEVICES 1
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define CLK_PIN   18
#define DATA_PIN  23
#define CS_PIN    5
#define BUZZER    15

MD_MAX72XX matrix = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

#define MATRIX_SIZE 8

struct Point {
  int x, y;
};

Point snake[64]; // Max length 64 (8x8)
int snakeLength = 3;
Point food;
char direction = 'R'; // Initial: Right

// === Function Prototypes ===
void resetGame();
void generateFood();
void moveSnake();
void checkCollision();
bool isValidDirectionChange(char newDir);
void drawSnake();

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32Snake");  // Bluetooth device name

  matrix.begin();
  pinMode(BUZZER, OUTPUT);
  randomSeed(analogRead(0));  // Seed for food position
  resetGame();

  Serial.println("Snake Game Started | Connect via Bluetooth and send U/D/L/R");
}

void loop() {
  if (SerialBT.available()) {
    char cmd = SerialBT.read();
    if (isValidDirectionChange(cmd)) direction = cmd;
  }

  moveSnake();
  checkCollision();

  matrix.clear();
  drawSnake();
  matrix.setPoint(food.y, food.x, true); // Draw food
  matrix.update();

  delay(500); // Game speed
}

void resetGame() {
  snakeLength = 3;
  direction = 'R';
  for (int i = 0; i < snakeLength; i++) {
    snake[i] = {2 - i, 0};  // Horizontal snake starting from (2,0)
  }
  generateFood();
}

void generateFood() {
  while (true) {
    food.x = random(0, 8);
    food.y = random(0, 8);
    bool onSnake = false;
    for (int i = 0; i < snakeLength; i++) {
      if (snake[i].x == food.x && snake[i].y == food.y) {
        onSnake = true;
        break;
      }
    }
    if (!onSnake) break;
  }
}

void moveSnake() {
  Point newHead = snake[0];

  switch (direction) {
    case 'U': newHead.y--; break;
    case 'D': newHead.y++; break;
    case 'L': newHead.x--; break;
    case 'R': newHead.x++; break;
  }

  // Wrap-around behavior
  if (newHead.x < 0) newHead.x = 7;
  if (newHead.x > 7) newHead.x = 0;
  if (newHead.y < 0) newHead.y = 7;
  if (newHead.y > 7) newHead.y = 0;

  // If food is eaten
  if (newHead.x == food.x && newHead.y == food.y) {
    tone(BUZZER, 1000, 100);  // Short beep
    for (int i = snakeLength; i > 0; i--)
      snake[i] = snake[i - 1];
    snake[0] = newHead;
    snakeLength++;
    generateFood();
  } else {
    for (int i = snakeLength - 1; i > 0; i--)
      snake[i] = snake[i - 1];
    snake[0] = newHead;
  }
}

void checkCollision() {
  for (int i = 1; i < snakeLength; i++) {
    if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
      tone(BUZZER, 500, 500); // Long beep
      delay(1000);
      resetGame();
      return;
    }
  }
}

bool isValidDirectionChange(char newDir) {
  if ((direction == 'U' && newDir == 'D') ||
      (direction == 'D' && newDir == 'U') ||
      (direction == 'L' && newDir == 'R') ||
      (direction == 'R' && newDir == 'L'))
    return false;
  return (newDir == 'U' || newDir == 'D' || newDir == 'L' || newDir == 'R');
}

void drawSnake() {
  for (int i = 0; i < snakeLength; i++) {
    matrix.setPoint(snake[i].y, snake[i].x, true);
  }
}
