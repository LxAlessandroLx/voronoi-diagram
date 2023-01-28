# Voronoi diagram
A single source file program to draw Voronoi diagrams written in C using SDL2

## Requirements
- a C compiler
- [SDL2](https://www.libsdl.org/)

## How to compile
You can use the Makefile running ```$ make``` or compile it manually with you compiler.

Here is an example with gcc:

    gcc -o VoronoiDiagram  src/main.c  -Wall -Wextra `sdl2-config --cflags` -lm `sdl2-config --libs`

## Usage
    ./VoronoiDiagram [norm] [window windth] [window height]

## Examples
Voronoi diagram using Euclidean norm
![euclidean](/screenshots/euclidean.png)
Voronoi diagram using Manhattan distance
![euclidean](/screenshots/manhattan.png)
Voronoi diagram using -1 norm
![euclidean](/screenshots/minusone.png)

---
Copyright (C) 2022 Alessandro Chiozza - chiozzalessandro@gmail.com
