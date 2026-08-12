#include <math.h>
#include <raylib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIN_WIDTH  900
#define WIN_HEIGHT 600
#define N_COLORS   7
#define G          (10.0)
#define SOFTNESS   (10.0)

typedef struct { // Vector2 struct with double
  double x, y;
} Vector2D;

typedef struct {
  Vector2D pos;
  Vector2D vel;
  Vector2D acc;  // acceleration
  Vector2D frce; // force
  double radius;
  double mass;
  Color color;
  uint8_t active; // 0 or 1
} Body;

typedef struct {
  double minR;
  double maxR;
  double initVel;
  double dt;
  size_t activeBodies; // num of active bodies
} Configuration;

double getRandomD(double min, double max) {
  return min + ((double)rand() / RAND_MAX) * (max - min);
}

Color getBodyColor(Color colors[N_COLORS], size_t i) {
  return colors[i];
}

/**
 * @brief define a single body's properties
 *
 * @param b         holds properties of a body
 * @param colors    random color for every body
 * @param N_COLORS  number of colors in colors[]
 * @param cfg       configuration of each body
 */
void generateBody(Body *b, Color colors[N_COLORS], Configuration *cfg) {
  b->pos.x = getRandomD(0, WIN_WIDTH);
  b->pos.y = getRandomD(0, WIN_HEIGHT);
  b->vel.x = getRandomD(-cfg->initVel, cfg->initVel);
  b->vel.y = getRandomD(-cfg->initVel, cfg->initVel);

  b->acc.x = 0;
  b->acc.y = 0;
  b->frce.x = 0;
  b->frce.y = 0;

  b->radius = getRandomD(cfg->minR, cfg->maxR);
  b->color = getBodyColor(colors, getRandomD(0, N_COLORS - 1)); // random color
  b->mass = getRandomD(b->radius * b->radius, b->radius * b->radius * 10);

  b->active = 1; // is active
}

// @brief generate `n` number of bodies with set color and configurations
void setBodies(Body *b, size_t n, Color colors[N_COLORS], Configuration *cfg) {
  for (size_t i = 0; i < n; i++) generateBody(&b[i], colors, cfg);
}

double hypotenuse(Body *b1, Body *b2) {
  double x = b1->pos.x - b2->pos.x;
  double y = b1->pos.y - b2->pos.y;
  return sqrt(x * x + y * y);
}

double calNetwon(Body *b1, Body *b2) {
  double distance = hypotenuse(b1, b2);
  return G * b1->mass * b2->mass / (distance * distance + SOFTNESS * SOFTNESS);
}

void resetForce(Body *b) {
  b->frce.x = 0;
  b->frce.y = 0;
}

void updateForce(Body *b1, Body *b2) {
  if (b1->active && b2->active && b1 != b2) {
    double force = calNetwon(b1, b2);
    double dx = b2->pos.x - b1->pos.x;
    double dy = b2->pos.y - b1->pos.y;

    double r = hypotenuse(b1, b2);
    double fx = force * dx / r;
    double fy = force * dy / r;

    // Fa = -Fb
    b1->frce.x += fx;
    b1->frce.y += fy;
    b2->frce.x -= fx;
    b2->frce.y -= fy;
  }
}

void updateAcc(Body *b) {
  if (b->active) {
    b->acc.x = b->frce.x / b->mass;
    b->acc.y = b->frce.y / b->mass;
  }
}
void updateVel(Body *b, double dt) {
  if (b->active) {
    b->vel.x += b->acc.x * dt;
    b->vel.y += b->acc.y * dt;
  }
}
void updatePos(Body *b, double dt) {
  if (b->active) {
    b->pos.x += b->vel.x * dt;
    b->pos.y += b->vel.y * dt;
  }
}

/**
 * @brief update the active body count after collisions
 *
 * @param b referece to Body, checks their active status
 * @param n number of active bodies
 * @param cfg reference to Configuration
 */
void updateActiveBod(Body *b, size_t n, Configuration *cfg) {
  size_t num = 0;
  for (size_t i = 0; i < n; i++)
    if (b[i].active) num++;
  cfg->activeBodies = num;
}

int isColliding(Body *b1, Body *b2) {
  if (b1->active && b2->active && b1 != b2) {
    double centerDist = hypotenuse(b1, b2);
    if (centerDist <= (b1->radius + b2->radius)) return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
void merge(Body *b1, Body *b2) {
  if (!b1->active || !b2->active) return;
  if (isColliding(b1, b2)) {
    uint8_t activity = b1->radius > b2->radius ? 1 : 0;
    b1->active = activity;
    b2->active = !activity;

    double newMass = b1->mass + b2->mass; // note: updating radius w/ mass -> BAD IDEA!!
    // TraceLog(LOG_INFO, "previous mass: %f and %f", b1->mass, b2->mass);
    // TraceLog(LOG_INFO, "new mass: %f", newMass);
    (b1->active ? b1 : b2)->mass = newMass;
    // if (b1->active) b1->mass = newMass; else b2->mass = newMass;
  }
}

// @brief render active bodies in raylib window
void renderBodies(Body *b, size_t n) {
  for (size_t i = 0; i < n; i++) {
    if (b[i].active)
      DrawCircle((float)b[i].pos.x, (float)b[i].pos.y, (float)b[i].radius, b[i].color);
  }
}

int main(void) {
  InitWindow(WIN_WIDTH, WIN_HEIGHT, "nbody simulation");
  SetTargetFPS(60);

  srand(time(NULL));
  Color colors[N_COLORS] = {VIOLET, WHITE, BLUE, GREEN, YELLOW, ORANGE, RED};

  size_t n = 100; // number of active bodies
  Body *bodies = malloc(n * sizeof(Body));
  Configuration cfg = {.minR = 1, .maxR = 9, .initVel = 15, .activeBodies = n};
  setBodies(bodies, n, colors, &cfg);

  while (!WindowShouldClose()) {
    cfg.dt = GetFrameTime();
    for (size_t i = 0; i < n; i++) resetForce(&bodies[i]);
    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < n; j++) {
        updateForce(&bodies[i], &bodies[j]);
        merge(&bodies[i], &bodies[j]);
      }
    }
    updateActiveBod(bodies, n, &cfg); // after collision
    for (size_t i = 0; i < n; i++) {
      updateAcc(&bodies[i]);
      updateVel(&bodies[i], cfg.dt);
      updatePos(&bodies[i], cfg.dt);
    }

    BeginDrawing();
    ClearBackground(BLACK);
    renderBodies(bodies, n); // entry point
    DrawText(TextFormat("active bodies: %zu", cfg.activeBodies), 10, 10, 30, WHITE);
    EndDrawing();
  }
  CloseWindow();
  free(bodies);
  return 0;
}
