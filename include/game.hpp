#ifndef GAME_HPP
#define GAME_HPP

#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <glm/ext.hpp>

#include <iostream>

const uint32_t WIDTH = 800, HEIGHT = 600;
const uint32_t WINDOW_FLAGS = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
const uint32_t KEYS_MAX_LENGTH = 500;
const char * TITLE = "OpenGL Hello Triangle";

const uint32_t GL_CLEAR_ARGS = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;

class Game {
    public:
        void Run();
        void Cleanup();
    private:
        bool running;
        SDL_Window * window;
        SDL_GLContext ctx;
        bool keys[KEYS_MAX_LENGTH];

        bool initSDL();
        bool initWindow();
        bool initContext();
        bool initGL();
        void init();
        void pollEvents();
        void pollKeyEvents();
        void update();
        void render();
        void mainLoop();
};

void Game::Run() {
    init();
    mainLoop();
}

bool Game::initSDL() {
    return SDL_Init(SDL_INIT_EVERYTHING) <= 0;
}

bool Game::initWindow() {
    window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, WINDOW_FLAGS);
    return window != nullptr;
}

bool Game::initContext() {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    ctx = SDL_GL_CreateContext(window);
    if(ctx)
        SDL_GL_MakeCurrent(window, ctx);

    return ctx;
}

bool Game::initGL() {
    bool success = gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
    if(success) {
        glClearColor(0.2f, 0.5f, 0.8f, 1.0f);
        glViewport(0, 0, WIDTH, HEIGHT);
    }
    return success;
}

void Game::init() {
    std::cout << "Initalizing Game\n";
    if(!initSDL()) {
        Cleanup();
        throw std::runtime_error("Error initializing SDL2\n");
    } else {
        std::cout << "\tInitalized SDL\n";
    }
    if(!initWindow()) {
        Cleanup();
        throw std::runtime_error("Error creating window\n");
    } else {
        std::cout << "\tCreated window\n";
    }
    if(!initContext()) {
        Cleanup();
        throw std::runtime_error("Error initalzing the OpenGL context\n");
    } else {
        std::cout << "\tInitalized context\n";
    }
    if(!initGL()) {
        Cleanup();
        throw std::runtime_error("Error initializing OpenGL\n");
    } else {
        std::cout << "\tInitalized OpenGL\n";
    }

    std::fill_n(keys, KEYS_MAX_LENGTH, false);
    running = true;
}

void Game::pollEvents() {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        switch(e.type) {
            case SDL_QUIT:
                running = false;
                break;
        }
    }
}

void Game::pollKeyEvents() {
    if(keys[SDLK_ESCAPE])
        running = false;
}

void Game::update() {

}

void Game::render() {
    glClear(GL_CLEAR_ARGS);



    SDL_GL_SwapWindow(window);
}

void Game::mainLoop() {
    while(running) {
        pollEvents();
        pollKeyEvents();
        update();
        render();
    }
}

void Game::Cleanup() {
    if(ctx)
        SDL_GL_DeleteContext(ctx);
    if(window != nullptr)
        SDL_DestroyWindow(window);
    SDL_Quit();
}

#endif