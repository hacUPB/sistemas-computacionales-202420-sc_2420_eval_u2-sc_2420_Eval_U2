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

![image](https://github.com/user-attachments/assets/952d7ca7-059a-4ce7-8ee4-824ce2e4de24)


Los tiempos de ejecución de las funciones update() y render() determinan cuántos ciclos del Game Loop se completan por segundo, lo que impacta la tasa de cuadros por segundo (FPS). Si estos tiempos son bajos y constantes, el juego corre fluidamente con una alta tasa de FPS. Sin embargo, si los tiempos aumentan o varían mucho, la tasa de FPS disminuye, lo que genera tirones o retrasos visibles en el juego.

Mantener una frecuencia de actualización constante es muy importante para garantizar una experiencia de juego fluida y evitar fluctuaciones perceptibles en el rendimiento.

### Ejercicio 3: Creación de Figuras Geométricas
# Juego Simple con C y SDL2

Este proyecto es un juego simple utilizando la biblioteca SDL2 en C. A continuación, se muestra el código fuente completo del juego.


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

---
