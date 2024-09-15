[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/C5iNLRra)
# Documentación del Proyecto
### Unidad 2

## Estudiante:  Tomas Mejia
## Id:  000466315
### Ejercicio 1: Reconociendo las Partes del Game Loop
Setup ()

![image](https://github.com/user-attachments/assets/578a4471-a6bd-4968-a28f-86da13fc5412)
Se utiliza para inicializar los objetos del juego. Aquí se configura la bola, asignándole una posición inicial (x, y) y una velocidad (vel_x, vel_y). Esta función solo se ejecuta una vez al comienzo del juego, y es el punto donde defines el estado inicial de tus objetos de juego.

Update ()

![image](https://github.com/user-attachments/assets/84922f26-f485-4c3f-a234-9c05770731d9)
Actualiza la lógica del juego, es decir, los movimientos y colisiones. Aquí calculas el tiempo transcurrido entre los fotogramas (delta_time) y ajustas la posición de la bola según su velocidad y tiempo transcurrido. También puedes maneja las colisiones de la bola con los bordes de la ventana.

Render ()

![image](https://github.com/user-attachments/assets/154e60f0-a14b-4ae3-8c02-bca20812370b)
Dibuja los objetos en la ventana. Esta función limpia la pantalla y luego dibuja los objetos del juego (como la bola) en sus posiciones actuales.

Insertar un printf()

![image](https://github.com/user-attachments/assets/a282d89a-5003-4716-8ab9-9050a5d8c2a9)

![image](https://github.com/user-attachments/assets/e4ec2930-73b6-4f51-a98a-551341420997)

se imprimio (printf)
- printf ("setup()\n")
- printf("update()\n")
- printf("render()\n")
  
### Ejercicio 2: Calculando el Tiempo de Ejecución

![image](https://github.com/user-attachments/assets/b672e5a0-2ae3-4a58-9b69-2f9270f04d76)

Terminal

![image](https://github.com/user-attachments/assets/7aa68365-9601-43f5-ab51-efd62c39f543)



Los tiempos de ejecución de las funciones update() y render() determinan cuántos ciclos del Game Loop se completan por segundo, lo que impacta la tasa de cuadros por segundo (FPS). Si estos tiempos son bajos y constantes, el juego corre fluidamente con una alta tasa de FPS. Sin embargo, si los tiempos aumentan o varían mucho, la tasa de FPS disminuye, lo que genera tirones o retrasos visibles en el juego.

Mantener una frecuencia de actualización constante es muy importante para garantizar una experiencia de juego fluida y evitar fluctuaciones perceptibles en el rendimiento.

### Ejercicio 3: Creación de Figuras Geométricas


```c
#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <math.h> // Necesario para la función sin() y cos()

///////////////////////////////////////////////////////////////////////////////
// Global variables
///////////////////////////////////////////////////////////////////////////////
int game_is_running = false;
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
} ball, paddle;

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
// Setup function that runs once at the beginning of our program
///////////////////////////////////////////////////////////////////////////////
void setup(void) {
    // Initialize the ball object moving down at a constant velocity
    ball.x = 10;
    ball.y = 20;
    ball.width = 20;
    ball.height = 20;
    ball.vel_x = 180;
    ball.vel_y = 140;
}

///////////////////////////////////////////////////////////////////////////////
// Update function with a fixed time step
///////////////////////////////////////////////////////////////////////////////
void update(void) {
    // Marcar el inicio del cronometraje para la función update()
    Uint32 update_start_time = SDL_GetTicks();

    printf("update()\n");

    // Obtener delta_time convertido a segundos
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0;

    // Almacenar el tiempo del frame actual
    last_frame_time = SDL_GetTicks();

    // Mover la bola usando delta_time
    ball.x += ball.vel_x * delta_time;
    ball.y += ball.vel_y * delta_time;

    // Comprobar la colisión de la bola con los bordes de la ventana
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

    // Marcar el final del cronometraje para la función update()
    Uint32 update_end_time = SDL_GetTicks();

    // Calcular el tiempo transcurrido y mostrarlo en la consola
    Uint32 update_duration = update_end_time - update_start_time;
    printf("Update duration: %u ms\n", update_duration);
}

///////////////////////////////////////////////////////////////////////////////
// Render function to draw game objects in the SDL window
///////////////////////////////////////////////////////////////////////////////
void render(void) {
    printf("render()\n");

    // Set background color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw a rectangle
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect = { 100, 100, 200, 150 }; // x, y, width, height
    SDL_RenderFillRect(renderer, &rect);

    // Draw a line
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawLine(renderer, 400, 300, 700, 500); // Start (x, y), End (x, y)

    // Draw a circle
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    draw_circle(600, 200, 50); // Center (x, y), Radius

    // Present everything on the screen
    SDL_RenderPresent(renderer);
}

///////////////////////////////////////////////////////////////////////////////
// Function to destroy SDL window and renderer
///////////////////////////////////////////////////////////////////////////////
void destroy_window(void) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

///////////////////////////////////////////////////////////////////////////////
// Main function
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* args[]) {
    game_is_running = initialize_window();

    setup();

    while (game_is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}
```

terminal 

![image](https://github.com/user-attachments/assets/adda7857-108c-4c2c-a91d-0566b41c6330)

### Ejercicio 4: Movimiento de Figuras en Pantalla
```c
#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <math.h> // Necesario para la función sin() y cos()

///////////////////////////////////////////////////////////////////////////////
// Global variables
///////////////////////////////////////////////////////////////////////////////
int game_is_running = false;
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
} ball;

///////////////////////////////////////////////////////////////////////////////
// Declare variables for additional shapes
///////////////////////////////////////////////////////////////////////////////
SDL_Rect rect = { 100, 100, 200, 150 }; // Initial position and size of the rectangle
int rect_vel_x = 100; // Velocity for the rectangle

int circle_x = 600; // Initial x position for the circle
int circle_y = 200; // Initial y position for the circle
int circle_radius = 50; // Radius of the circle
int circle_vel_x = 100; // Velocity for the circle

// Line variables
int line_start_x = 400;
int line_start_y = 300;
int line_end_x = 700;
int line_end_y = 500;
int line_vel_x = 100; // Velocity for the line movement
int line_vel_y = 50;  // Velocity for the line movement

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
// Setup function that runs once at the beginning of our program
///////////////////////////////////////////////////////////////////////////////
void setup(void) {
    // Initialize the ball object moving down at a constant velocity
    ball.x = 10;
    ball.y = 20;
    ball.width = 20;
    ball.height = 20;
    ball.vel_x = 180;
    ball.vel_y = 140;
}

///////////////////////////////////////////////////////////////////////////////
// Update function with a fixed time step
///////////////////////////////////////////////////////////////////////////////
void update(void) {
    // Mark the start of timing for the update() function
    Uint32 update_start_time = SDL_GetTicks();

    printf("update()\n");

    // Get delta_time converted to seconds
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

    // Store the current frame time
    last_frame_time = SDL_GetTicks();

    // Move the ball using delta_time
    ball.x += ball.vel_x * delta_time;
    ball.y += ball.vel_y * delta_time;

    // Move the rectangle and the circle
    rect.x += rect_vel_x * delta_time; // Move the rectangle to the right
    circle_x += circle_vel_x * delta_time; // Move the circle to the right

    // Move the line
    line_start_x += line_vel_x * delta_time;
    line_start_y += line_vel_y * delta_time;
    line_end_x += line_vel_x * delta_time;
    line_end_y += line_vel_y * delta_time;

    // Check for collision of the ball with window edges
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

    // Check boundary conditions for the rectangle
    if (rect.x < 0 || rect.x + rect.w > 800) {
        rect_vel_x = -rect_vel_x; // Reverse direction
    }

    // Check boundary conditions for the circle
    if (circle_x < 0 || circle_x + circle_radius * 2 > 800) {
        circle_vel_x = -circle_vel_x; // Reverse direction
    }

    // Check boundary conditions for the line
    if (line_start_x < 0 || line_end_x > 800) {
        line_vel_x = -line_vel_x; // Reverse direction
    }
    if (line_start_y < 0 || line_end_y > 600) {
        line_vel_y = -line_vel_y; // Reverse direction
    }

    // Mark the end of timing for the update() function
    Uint32 update_end_time = SDL_GetTicks();

    // Calculate the elapsed time and display it in the console
    Uint32 update_duration = update_end_time - update_start_time;
    printf("Update duration: %u ms\n", update_duration);
}

///////////////////////////////////////////////////////////////////////////////
// Render function to draw game objects in the SDL window
///////////////////////////////////////////////////////////////////////////////
void render(void) {
    printf("render()\n");

    // Set background color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw the rectangle at the updated position
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    // Draw the line
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawLine(renderer, line_start_x, line_start_y, line_end_x, line_end_y); // Start (x, y), End (x, y)

    // Draw the circle at the updated position
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    draw_circle(circle_x, circle_y, circle_radius);

    // Present everything on the screen
    SDL_RenderPresent(renderer);
}

///////////////////////////////////////////////////////////////////////////////
// Function to destroy SDL window and renderer
///////////////////////////////////////////////////////////////////////////////
void destroy_window(void) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

///////////////////////////////////////////////////////////////////////////////
// Main function
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* args[]) {
    game_is_running = initialize_window();

    setup();

    while (game_is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}
```

terminal 

![image](https://github.com/user-attachments/assets/a96db0ec-722d-451a-baec-dd97cf2308d8)

Un problema que me ocurrio es que la linea verde no salia al comeinzo, y depues de buscar logre que saliera pero ahora esta cuando se movia se salia de la panatalla

### Ejercicio 5: Modificación de Tamaño, Orientación y Color

modifique en el render para que dibujen las figuras con los cambios de tamaño, orientación y color.

![image](https://github.com/user-attachments/assets/9d2d7f63-20e2-4a9e-b3f3-8f059394fff5)

Función updat Modificada se actualizan los tamaños, la orientación y el color de las figuras, y se restaura el cronómetro.
```c
void update(void) {
    // Mark the start of timing for the update() function
    Uint32 update_start_time = SDL_GetTicks();

    printf("update()\n");

    // Get delta_time converted to seconds
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

    // Store the current frame time
    last_frame_time = SDL_GetTicks();

    // Update the scale of the rectangle and the circle
    rect_scale += rect_scale_rate * delta_time;
    circle_scale += circle_scale_rate * delta_time;

    // Reverse scaling direction if limits are exceeded
    if (rect_scale < 0.5f || rect_scale > 2.0f) {
        rect_scale_rate = -rect_scale_rate;
    }
    if (circle_scale < 0.5f || circle_scale > 2.0f) {
        circle_scale_rate = -circle_scale_rate;
    }

    // Update the angle of the line for rotation
    line_angle += line_rotation_rate * delta_time;

    // Move the ball using delta_time
    ball.x += ball.vel_x * delta_time;
    ball.y += ball.vel_y * delta_time;

    // Move the rectangle and the circle
    rect.x += rect_vel_x * delta_time; // Move the rectangle to the right
    circle_x += circle_vel_x * delta_time; // Move the circle to the right

    // Move the line
    line_start_x += line_vel_x * delta_time;
    line_start_y += line_vel_y * delta_time;
    line_end_x += line_vel_x * delta_time;
    line_end_y += line_vel_y * delta_time;

    // Check for collision of the ball with window edges
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

    // Check boundary conditions for the rectangle
    if (rect.x < 0 || rect.x + rect.w * rect_scale > 800) {
        rect_vel_x = -rect_vel_x; // Reverse direction
    }

    // Check boundary conditions for the circle
    if (circle_x < 0 || circle_x + circle_radius * circle_scale * 2 > 800) {
        circle_vel_x = -circle_vel_x; // Reverse direction
    }

    // Check boundary conditions for the line
    if (line_start_x < 0 || line_end_x > 800) {
        line_vel_x = -line_vel_x; // Reverse direction
    }
    if (line_start_y < 0 || line_end_y > 600) {
        line_vel_y = -line_vel_y; // Reverse direction
    }

    // Update color based on elapsed time
    Uint32 current_time = SDL_GetTicks();
    if (current_time - last_color_change_time > color_change_interval) {
        last_color_change_time = current_time;
        // Cycle through colors
        if (color_r == 255 && color_g == 0 && color_b == 0) {
            color_r = 0; color_g = 255; color_b = 0;
        } else if (color_r == 0 && color_g == 255 && color_b == 0) {
            color_r = 0; color_g = 0; color_b = 255;
        } else if (color_r == 0 && color_g == 0 && color_b == 255) {
            color_r = 255; color_g = 0; color_b = 0;
        }
    }

    // Mark the end of timing for the update() function
    Uint32 update_end_time = SDL_GetTicks();

    // Calculate the elapsed time and display it in the console
    Uint32 update_duration = update_end_time - update_start_time;
    printf("Update duration: %u ms\n", update_duration);
}
```

vista en Termina

![af1e5e9f-ceaa-4c7e-a2df-3edff2d083c8](https://github.com/user-attachments/assets/4eef1b74-91c7-41ee-b079-b339ba9d7618)

![264cc8ca-e96e-4286-88a3-62904093f6ec](https://github.com/user-attachments/assets/b33b6576-87cf-48ae-9b30-79782e53c392)

![bfc4be98-048d-4f2f-8427-3968418a4b08](https://github.com/user-attachments/assets/b5281142-69ad-47e8-b47f-40f98c8377f3)


- el circulo y la esfera se movieron rapidamente al comeinzo mientras que la linea se movia lentamente
-  la linea tubo cambio de tama;o muy lento mientras que el circulo y el cuadrado cambiaban de tamaño rapidamnete 

### Ejercicio 6: Rebote de Figuras
se agrego función para detectar si dos figuras colisionan.
- las figuras no rebotaban apenas chocarse si no como cuando cada una tocaba el centro de la otra 
![image](https://github.com/user-attachments/assets/0d47a359-a58c-4f0a-a9c4-00d7eebcf91d)

final 
```c
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
```
## Proyecto Juego esquivar circulos
### Juego
El juego consiste en un cuadrado verde que se mueve de derecha a izquierda en la pantalla. El objetivo es esquivar obstáculos (círculos rojos) que caen desde la parte superior de la pantalla. Estos círculos serán de distintos tamaños y velocidades, y a medida que pase el tiempo, la cantidad de círculos que caen aumentará. Si el cuadrado toca uno de estos círculos, perderás el juego y aparecerá un mensaje que dirá: "¡Has perdido!"

Personajes
He comenzado con los objetos principales: el cuadrado (jugador) y los círculos (obstáculos).
![image](https://github.com/user-attachments/assets/32a15d67-6629-4452-be10-ea5de7fe3c38)

## Obstáculos
Los círculos comienzan desde la parte superior de la pantalla y tienen una velocidad y un tamaño asignados. Inicialmente, todos eran iguales, pero ahora la velocidad y el tamaño son aleatorios. Además, el juego comienza con un círculo, que se incrementa hasta un máximo de 25 círculos.

![image](https://github.com/user-attachments/assets/71773e31-3927-4ba9-9c8c-78baca9b2607)

![image](https://github.com/user-attachments/assets/df2a5d7f-15e1-40d0-8ce1-0e9ef2578d83)

Cada 5 segundos, se añaden más círculos para incrementar la dificultad.

![image](https://github.com/user-attachments/assets/9849a938-7490-4038-956a-6cb9ee7f4b20)

Para gestionar las colisiones, se ha implementado un sistema que detecta cuándo el cuadrado choca con un círculo. Si ocurre una colisión, se pierde el juego.

```c
bool detect_collision(Player* player, Circle* circle) {
    int dist_x = player->x + player->width / 2 - circle->x;
    int dist_y = player->y + player->height / 2 - circle->y;
    int distance = dist_x * dist_x + dist_y * dist_y;
    int radius_squared = circle->radius * circle->radius;

    return distance < radius_squared;
}
```
## Juego principal 
Aquí ya se ha agregado todo: cómo iniciar SDL, el renderizado, la ventana del juego y el bucle del juego. También se implementó la funcionalidad para dibujar los objetos y generar las esferas, y para que la cantidad de esferas aumentara con el tiempo. Al final, se colocó un print para mostrar un mensaje de "Has perdido!" cuando el jugador colisiona con un círculo.

- La pantalla

![image](https://github.com/user-attachments/assets/cbd67c91-c6b3-428e-b446-d1696e576865)

lo que se dibujo en ella

![image](https://github.com/user-attachments/assets/0e4e8fda-afa6-4398-bdd4-a91d74f54323)

![image](https://github.com/user-attachments/assets/04ca0bdc-a6d8-412c-a337-c16f955e8734)

- Renderizacion

![image](https://github.com/user-attachments/assets/767c65c8-4e21-4a71-b32b-f37ca9743d6c)

- el bucle del juego
  
![image](https://github.com/user-attachments/assets/6c47942f-16c1-4b65-830a-e32dd7d6431c)

- Los obstaculos
- 
![image](https://github.com/user-attachments/assets/584811a0-57a7-49c6-8acd-b7c4401d6a5d)



- Finalizar juego
  

![image](https://github.com/user-attachments/assets/cd51ac87-bdbd-442f-ba6f-8a7636c98b2b)


## Final 

```c
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define MAX_CIRCLES 25 // Incrementado a 25 círculos máximos

typedef struct {
    int x, y;
    int radius;
    int vel_y;
    bool active;
} Circle;

typedef struct {
    int x, y;
    int width, height;
    int vel_x;
} Player;

bool game_over = false;
Player player;
Circle circles[MAX_CIRCLES]; // Array para almacenar los círculos
int active_circles = 1;      // Número de círculos activos (comienza con 1)
Uint32 last_add_time = 0;   // Tiempo del último aumento de círculos

void initialize_player(Player* player) {
    player->x = WINDOW_WIDTH / 2;
    player->y = WINDOW_HEIGHT - 50;
    player->width = 40;
    player->height = 40;
    player->vel_x = 0;
}

void initialize_circle(Circle* circle) {
    circle->x = rand() % (WINDOW_WIDTH - circle->radius * 2) + circle->radius;
    circle->y = 0; // Empieza desde arriba
    circle->vel_y = 4 + rand() % 3; // Velocidad aleatoria 
    circle->radius = 20 + rand() % 30; // Tamaño aleatorio 
    circle->active = true;
}

void draw_circle(SDL_Renderer* renderer, int center_x, int center_y, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, center_x + dx, center_y + dy);
            }
        }
    }
}

bool detect_collision(Player* player, Circle* circle) {
    int dist_x = player->x + player->width / 2 - circle->x;
    int dist_y = player->y + player->height / 2 - circle->y;
    int distance = dist_x * dist_x + dist_y * dist_y;
    int radius_squared = circle->radius * circle->radius;

    return distance < radius_squared;
}

void increase_difficulty(Uint32 current_time) {
    if ((current_time - last_add_time) > 5000 && active_circles < MAX_CIRCLES) {
        initialize_circle(&circles[active_circles]);
        active_circles++;
        last_add_time = current_time; // Reiniciar el temporizador
    }
}

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Error al inicializar SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Juego de esquivar ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!window) {
        fprintf(stderr, "Error al crear la ventana: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Error al crear el renderizador: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    srand(time(0)); //  aleatorios
    initialize_player(&player);
    initialize_circle(&circles[0]);

    last_add_time = SDL_GetTicks(); 
    bool game_running = true;
    SDL_Event event;

    while (game_running && !game_over) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                game_running = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_a) {
                    player.vel_x = -5;
                }
                else if (event.key.keysym.sym == SDLK_d) {
                    player.vel_x = 5;
                }
            }
            else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_d) {
                    player.vel_x = 0;
                }
            }
        }

 
        player.x += player.vel_x;


        if (player.x < 0) player.x = 0;
        if (player.x + player.width > WINDOW_WIDTH) player.x = WINDOW_WIDTH - player.width;

        for (int i = 0; i < active_circles; i++) {
            if (circles[i].active) {
                circles[i].y += circles[i].vel_y;
                if (circles[i].y - circles[i].radius > WINDOW_HEIGHT) {
                    initialize_circle(&circles[i]);
                }

                // Comprobar colisiones
                if (detect_collision(&player, &circles[i])) {
                    game_over = true;
                }
            }
        }

        Uint32 current_time = SDL_GetTicks();
        increase_difficulty(current_time);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Fondo negro
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Color verde para el jugador
        SDL_Rect player_rect = { player.x, player.y, player.width, player.height };
        SDL_RenderFillRect(renderer, &player_rect);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Color rojo para los círculos
        for (int i = 0; i < active_circles; i++) {
            if (circles[i].active) {
                draw_circle(renderer, circles[i].x, circles[i].y, circles[i].radius);
            }
        }

        SDL_RenderPresent(renderer); // Mostrar todo en la pantalla

        SDL_Delay(16); // Pausar para mantener 60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    if (game_over) {
        printf("Has perdido!.\n");
    }

    return 0;
}
```
## Problemas 
- Tuve algunos problemas al inicio para que el cuadrado apareciera y se mantuviera dentro de la pantalla cuando se presionaban las teclas 'A' y 'D'. 
- También tuve problemas al tratar de aleatorizar el tamaño y la velocidad de los círculos. Al principio, estos cambiaban a mitad de camino, pero yo quería que salieran con un tamaño  y que permanecieran así hasta que se fueran. Al final, pedí ayuda a una IA.

- Otro problema que encontré es que la colisión no se detecta cuando el borde del cuadrado toca el círculo, sino cuando sus centros se tocan.
- También hice la pantalla un poco más pequeña porque antes tenía que usar como 50 círculos para que el juego tuviera un nivel de dificultad adecuado. Sin embargo, al generar tantas esferas, a veces el juego sufría caídas en los FPS. No sé si era más un problema del computador, pero preferí reducir el tamaño y la cantidad de circulos que se generaban.

---
