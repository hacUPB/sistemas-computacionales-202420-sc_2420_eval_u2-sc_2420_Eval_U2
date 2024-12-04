#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <math.h> // Necesario para las funciones sin() y cos()

///////////////////////////////////////////////////////////////////////////////
// Global variables
///////////////////////////////////////////////////////////////////////////////
bool game_is_running = false;
int last_frame_time = 0;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

///////////////////////////////////////////////////////////////////////////////
// Declare two game objects for the ball and the paddle
///////////////////////////////////////////////////////////////////////////////
struct game_object {
    float x;
    float y;
    float width;
    float height;
    float vel_x;
    float vel_y;
    float angle; // New field for rotation
} ball;

///////////////////////////////////////////////////////////////////////////////
// Declare variables for additional shapes
///////////////////////////////////////////////////////////////////////////////
SDL_Rect rect = { 100, 100, 200, 150 }; // Initial position and size of the rectangle
int rect_vel_x = 100; // Velocity for the rectangle
float rect_scale = 1.0f; // Scale factor for resizing
float rect_scale_rate = 0.5f; // Rate of scaling

int circle_x = 600; // Initial x position for the circle
int circle_y = 200; // Initial y position for the circle
int circle_radius = 50; // Radius of the circle
int circle_vel_x = 100; // Velocity for the circle
float circle_scale = 1.0f; // Scale factor for resizing
float circle_scale_rate = 0.5f; // Rate of scaling

// Line variables
int line_start_x = 400;
int line_start_y = 300;
int line_end_x = 700;
int line_end_y = 500;
int line_vel_x = 100; // Velocity for the line movement
int line_vel_y = 50;  // Velocity for the line movement
float line_angle = 0.0f; // Angle of rotation for the line
float line_rotation_rate = 0.02f; // Rate of rotation for the line

// Color variables
Uint8 rect_color_r = 255;
Uint8 rect_color_g = 0;
Uint8 rect_color_b = 0;
Uint8 rect_color_a = 255;

Uint8 circle_color_r = 0;
Uint8 circle_color_g = 255;
Uint8 circle_color_b = 0;
Uint8 circle_color_a = 255;

Uint8 line_color_r = 0;
Uint8 line_color_g = 0;
Uint8 line_color_b = 255;
Uint8 line_color_a = 255;

int color_change_interval = 500; // Milliseconds to change color
Uint32 last_color_change_time = 0;

///////////////////////////////////////////////////////////////////////////////
// Function to initialize our SDL window
///////////////////////////////////////////////////////////////////////////////
int initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }
    window = SDL_CreateWindow(
        "A simple game loop using C & SDL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, // WINDOW_WIDTH
        600, // WINDOW_HEIGHT
        0
    );
    if (!window) {
        fprintf(stderr, "Error creating SDL Window.\n");
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Error creating SDL Renderer.\n");
        return false;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////////
// Function to poll SDL events and process keyboard input
///////////////////////////////////////////////////////////////////////////////
void process_input(void) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            game_is_running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                game_is_running = false;
            }
            break;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Function to draw a circle using SDL_RenderDrawPoint
///////////////////////////////////////////////////////////////////////////////
void draw_circle(int center_x, int center_y, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, center_x + dx, center_y + dy);
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Check for collision between circle and rectangle
///////////////////////////////////////////////////////////////////////////////
bool check_circle_rect_collision(int circle_x, int circle_y, int circle_radius, SDL_Rect rect) {
    int closest_x = circle_x;
    int closest_y = circle_y;

    if (circle_x < rect.x) closest_x = rect.x;
    else if (circle_x > rect.x + rect.w) closest_x = rect.x + rect.w;

    if (circle_y < rect.y) closest_y = rect.y;
    else if (circle_y > rect.y + rect.h) closest_y = rect.y + rect.h;

    int dx = circle_x - closest_x;
    int dy = circle_y - closest_y;
    return (dx * dx + dy * dy) <= (circle_radius * circle_radius);
}

///////////////////////////////////////////////////////////////////////////////
// Setup function that runs once at the beginning of our program
///////////////////////////////////////////////////////////////////////////////
void setup(void) {
    ball.x = 10;
    ball.y = 20;
    ball.width = 20;
    ball.height = 20;
    ball.vel_x = 180;
    ball.vel_y = 140;
    ball.angle = 0.0f; // Initial angle for rotation
}

///////////////////////////////////////////////////////////////////////////////
// Update function with a fixed time step
///////////////////////////////////////////////////////////////////////////////
void update(void) {
    Uint32 update_start_time = SDL_GetTicks();
    printf("update()\n");

    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
    last_frame_time = SDL_GetTicks();

    // Update the scale of the rectangle and the circle
    rect_scale += rect_scale_rate * delta_time;
    circle_scale += circle_scale_rate * delta_time;

    if (rect_scale < 0.5f || rect_scale > 2.0f) {
        rect_scale_rate = -rect_scale_rate;
    }
    if (circle_scale < 0.5f || circle_scale > 2.0f) {
        circle_scale_rate = -circle_scale_rate;
    }

    line_angle += line_rotation_rate * delta_time;

    ball.x += ball.vel_x * delta_time;
    ball.y += ball.vel_y * delta_time;

    rect.x += rect_vel_x * delta_time;
    circle_x += circle_vel_x * delta_time;

    line_start_x += line_vel_x * delta_time;
    line_start_y += line_vel_y * delta_time;
    line_end_x += line_vel_x * delta_time;
    line_end_y += line_vel_y * delta_time;

    if (ball.x < 0) {
        ball.x = 0;
        ball.vel_x = -ball.vel_x;
    }
    if (ball.x + ball.width > 800) {
        ball.x = 800 - ball.width;
        ball.vel_x = -ball.vel_x;
    }
    if (ball.y < 0) {
        ball.y = 0;
        ball.vel_y = -ball.vel_y;
    }
    if (ball.y + ball.height > 600) {
        ball.y = 600 - ball.height;
        ball.vel_y = -ball.vel_y;
    }

    if (rect.x < 0 || rect.x + rect.w * rect_scale > 800) {
        rect_vel_x = -rect_vel_x;
    }

    if (circle_x < 0 || circle_x + circle_radius * circle_scale * 2 > 800) {
        circle_vel_x = -circle_vel_x;
    }

    if (line_start_x < 0 || line_end_x > 800) {
        line_vel_x = -line_vel_x;
    }
    if (line_start_y < 0 || line_end_y > 600) {
        line_vel_y = -line_vel_y;
    }

    if (check_circle_rect_collision(circle_x, circle_y, circle_radius * circle_scale, rect)) {
        circle_vel_x = -circle_vel_x;
        rect_vel_x = -rect_vel_x;
    }

    Uint32 current_time = SDL_GetTicks();
    if (current_time - last_color_change_time > color_change_interval) {
        last_color_change_time = current_time;

        // Update color for the rectangle
        if (rect_color_r == 255 && rect_color_g == 0 && rect_color_b == 0) {
            rect_color_r = 0; rect_color_g = 255; rect_color_b = 0;
        }
        else if (rect_color_r == 0 && rect_color_g == 255 && rect_color_b == 0) {
            rect_color_r = 0; rect_color_g = 0; rect_color_b = 255;
        }
        else if (rect_color_r == 0 && rect_color_g == 0 && rect_color_b == 255) {
            rect_color_r = 255; rect_color_g = 0; rect_color_b = 0;
        }

        // Update color for the circle
        if (circle_color_r == 0 && circle_color_g == 255 && circle_color_b == 0) {
            circle_color_r = 0; circle_color_g = 0; circle_color_b = 255;
        }
        else if (circle_color_r == 0 && circle_color_g == 0 && circle_color_b == 255) {
            circle_color_r = 255; circle_color_g = 0; circle_color_b = 0;
        }
        else if (circle_color_r == 255 && circle_color_g == 0 && circle_color_b == 0) {
            circle_color_r = 0; circle_color_g = 255; circle_color_b = 0;
        }

        // Update color for the line
        if (line_color_r == 0 && line_color_g == 0 && line_color_b == 255) {
            line_color_r = 255; line_color_g = 0; line_color_b = 0;
        }
        else if (line_color_r == 255 && line_color_g == 0 && line_color_b == 0) {
            line_color_r = 0; line_color_g = 255; line_color_b = 0;
        }
        else if (line_color_r == 0 && line_color_g == 255 && line_color_b == 0) {
            line_color_r = 0; line_color_g = 0; line_color_b = 255;
        }
    }

    Uint32 update_end_time = SDL_GetTicks();
    Uint32 update_duration = update_end_time - update_start_time;
    printf("Update duration: %u ms\n", update_duration);
}

///////////////////////////////////////////////////////////////////////////////
// Render function to draw game objects in the SDL window
///////////////////////////////////////////////////////////////////////////////
void render(void) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw the ball
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect ball_rect = { ball.x, ball.y, ball.width, ball.height };
    SDL_RenderFillRect(renderer, &ball_rect);

    // Draw the rectangle
    SDL_SetRenderDrawColor(renderer, rect_color_r, rect_color_g, rect_color_b, rect_color_a);
    SDL_Rect scaled_rect = { rect.x, rect.y, rect.w * rect_scale, rect.h * rect_scale };
    SDL_RenderFillRect(renderer, &scaled_rect);

    // Draw the circle
    SDL_SetRenderDrawColor(renderer, circle_color_r, circle_color_g, circle_color_b, circle_color_a);
    draw_circle(circle_x, circle_y, circle_radius * circle_scale);

    // Draw the line
    SDL_SetRenderDrawColor(renderer, line_color_r, line_color_g, line_color_b, line_color_a);
    int line_end_x_rot = line_start_x + (int)((line_end_x - line_start_x) * cos(line_angle) - (line_end_y - line_start_y) * sin(line_angle));
    int line_end_y_rot = line_start_y + (int)((line_end_x - line_start_x) * sin(line_angle) + (line_end_y - line_start_y) * cos(line_angle));
    SDL_RenderDrawLine(renderer, line_start_x, line_start_y, line_end_x_rot, line_end_y_rot);

    SDL_RenderPresent(renderer);
}

///////////////////////////////////////////////////////////////////////////////
// Main loop
///////////////////////////////////////////////////////////////////////////////
void loop(void) {
    Uint32 frame_start_time;
    Uint32 frame_duration;
    Uint32 frame_time = 1000 / 60; // Target frame time for 60 FPS

    while (game_is_running) {
        frame_start_time = SDL_GetTicks();
        process_input();
        update();
        render();
        frame_duration = SDL_GetTicks() - frame_start_time;

        if (frame_duration < frame_time) {
            SDL_Delay(frame_time - frame_duration);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Main function
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {
    if (!initialize_window()) {
        return -1;
    }
    setup();
    game_is_running = true;
    loop();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
