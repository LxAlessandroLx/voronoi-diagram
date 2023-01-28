#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#define MANHATTAN_DISTANCE  1
#define EUCLIDEAN_NORM      2
#define NORM                1

typedef struct Vector2
{
    int x, y;
} Vector2;

typedef struct Points
{
    Vector2 points[1024];
    size_t capacity;
} Points;

SDL_Color colors[1024];

void generateColors()
{
    for (int i = 0; i < 1024; i++)
    {
        colors[i].r = rand()%256;
        colors[i].g = rand()%256;
        colors[i].b = rand()%256;
        colors[i].a = 255;
    }
}

void draw(SDL_Renderer *renderer, Vector2 size, Points *points)
{
    for (int i = 0; i < size.x*size.y; i++)
    {
        int index = 0;

        for (size_t j = 1; j < points->capacity; j++)
        {
            if (pow(pow(abs(i%size.x - points->points[j].x),NORM) + pow(abs(i/size.x - points->points[j].y),NORM), 1.f/NORM) < 
                pow(pow(abs(i%size.x - points->points[index].x),NORM) + pow(abs(i/size.x - points->points[index].y),NORM), 1.f/NORM))
            {
                index = j;
            }
        }

        SDL_SetRenderDrawColor(renderer, colors[index].r, colors[index].g, colors[index].b, colors[index].a);
        SDL_RenderDrawPoint(renderer, i%size.x, i/size.x);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (size_t i = 0; i < points->capacity; i++)
        drawCyrcle(renderer, points->points[i], 5);
    
    
    SDL_RenderPresent(renderer);
}

void drawCyrcle(SDL_Renderer *renderer, Vector2 center, int radius)
{
    for (int x = center.x - radius; x <= center.x + radius; x++)
    {
        for (int y = center.y - radius; y <= center.y + radius; y++)
        {
            int dx = center.x - x;
            int dy = center.y - y;
            if (dx*dx + dy*dy < radius*radius)
                SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}

int main(void)
{
    srand(time(NULL));
    
    SDL_Window *window;
    SDL_WindowFlags flags = SDL_WINDOW_RESIZABLE;
    SDL_Renderer *renderer;
    SDL_RendererFlags renderer_flags = SDL_RENDERER_ACCELERATED;
    SDL_Event event;

    Points points;
    points.capacity = 0;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Voronoi Diagram", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, flags);
    renderer = SDL_CreateRenderer(window, -1, renderer_flags);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    bool fullscreen = false;

    generateColors();

    bool isOpen = true;

    while (isOpen)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isOpen = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.scancode == SDL_SCANCODE_F)
                {
                    if (fullscreen)
                        SDL_SetWindowFullscreen(window, 0);
                    else
                        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

                    fullscreen = !fullscreen;

                    int w, h;
                    SDL_GetWindowSize(window, &w, &h);
                    draw(renderer, (Vector2){w, h}, &points);
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_BACKSPACE)
                {
                    if (points.capacity > 0)
                        points.capacity--;

                    int w, h;
                    SDL_GetWindowSize(window, &w, &h);
                    draw(renderer, (Vector2){w, h}, &points);
                }
                break;
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    draw(renderer, (Vector2){event.window.data1, event.window.data2}, &points);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                points.points[points.capacity++] = (Vector2){event.button.x, event.button.y};

                int w, h;
                SDL_GetWindowSize(window, &w, &h);
                draw(renderer, (Vector2){w, h}, &points);

                break;
            default:
                break;
            }
        }

        SDL_Delay(100); 
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
