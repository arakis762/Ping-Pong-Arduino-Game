#include <GyverOLED.h>

const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;

GyverOLED<SSH1106_128x64> screen;

// Define button pins
const int buttonUpPin = 2;    // Pin for the up button
const int buttonDownPin = 3;  // Pin for the down button

class Paddle {
protected:
  void LimitMovement() {
    if (y < 0) {
      y = 0;
    }
    if (y + height >= screen_height) {
      y = screen_height - height;
    }
  }

public:
  int x, y;
  int width, height;
  int speed;
  int screen_height;

  void Draw() {
    screen.rect(x, y, x + width, y + height, OLED_FILL);
  }

  void Update(int ball_speed, int ball_y) {
    if (ball_y > y && ball_speed < 0) {
      y += speed;
    }
    if (ball_y < y + height && ball_speed < 0) {
      y -= speed;
    }
    LimitMovement();
  }
};

class LeftPaddle : public Paddle {
public:
  void Update(int buttonUpState, int buttonDownState) {
    if (buttonUpState == LOW) {  // If the up button is pressed
      y -= speed;
    }
    if (buttonDownState == LOW) {  // If the down button is pressed
      y += speed;
    }
    LimitMovement();
  }
};

class Ball {
public:
  int x, y;
  int radius;
  int speed_x;
  int speed_y;

  void Draw() {
    screen.circle(x, y, radius, 1);
  }

  void Update(Paddle &player, Paddle &cpu) {
    x += speed_x;
    y += speed_y;

    if (y + radius >= SCREEN_HEIGHT - 1) {
      speed_y *= -1;
      y = SCREEN_HEIGHT - 1 - radius;
    }

    if (y - radius <= 1) {
      speed_y *= -1;
    }

    if (x + radius >= SCREEN_WIDTH - 1) {
      ResetBall();
    }

    if (x - radius <= 1) {
      ResetBall();
    }

    if ((x - radius <= player.x + player.width) && (y + radius > player.y) && (y - radius < player.y + player.height)) {
      speed_x *= -1;
    }

    if ((x + radius >= cpu.x) && (y + radius > cpu.y) && (y - radius < cpu.y + cpu.height)) {
      speed_x *= -1;
    }
  }

  void ResetBall() {
    x = SCREEN_WIDTH / 2;
    y = SCREEN_HEIGHT / 2;
  }
};

Ball ball;
Paddle player;
LeftPaddle cpu;

void setup(void) {
  initDisplay();
  Wire.setClock(800000L);

  ball.x = SCREEN_WIDTH / 2;
  ball.y = SCREEN_HEIGHT / 2;
  ball.radius = 3;
  ball.speed_x = 2;
  ball.speed_y = 2;

  screen.clear();

  player.width = 4;
  player.height = 18;
  player.x = 3;
  player.y = (SCREEN_HEIGHT - 1) / 2 - player.height / 2;
  player.speed = 2;
  player.screen_height = SCREEN_HEIGHT;

  cpu.width = 4;
  cpu.height = 18;
  cpu.x = (SCREEN_WIDTH - 1) - cpu.width - 3;
  cpu.y = (SCREEN_HEIGHT - 1) / 2 - cpu.height / 2;
  cpu.speed = 2;
  cpu.screen_height = SCREEN_HEIGHT;

  // Initialize button pins
  pinMode(buttonUpPin, INPUT_PULLUP);
  pinMode(buttonDownPin, INPUT_PULLUP);
}

void loop() {
  screen.clear();

  // Read button states
  int buttonUpState = digitalRead(buttonUpPin);
  int buttonDownState = digitalRead(buttonDownPin);

  ball.Update(cpu, player);  // Note the swapped order
  cpu.Update(buttonUpState, buttonDownState);  // Note the swapped role

  player.Update(ball.speed_x, ball.y);

  ball.Draw();
  player.Draw();
  cpu.Draw();

  screen.update();
}

void initDisplay() {
  screen.init();
  screen.clear();
  screen.update();
}
