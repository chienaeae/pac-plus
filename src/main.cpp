#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "game/Core.h"
#include "game/FPS.h"
#include "game/LTexture.h"
#include "game/GameObject.h"
#include "game/SceneStateMachine.h"
#include "game/LTimer.h"
#include "SceneTest.h"
#include "Square.h"

using namespace std;

const int GAME_FRAME = 60;

const int SECOND = 1000;
const int TICKS_PER_GAME_FRAME = SECOND / GAME_FRAME;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;
SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;
TTF_Font *gFont = nullptr;


class Game {
public:
    bool init();

    void run();

    static void close();

private:
    void update();

    void eventUpdate(SDL_Event* e);

    void renderUpdate();

    FPS fps;

    SceneStateMachine sceneStateMachine;

    LTimer clock;
    // deltaTime records the last game loop update as seconds
    float deltaTime;
};

bool Game::init() {
    bool success = true;

    // Init SDL SubSystems (Video)
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialized! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Init SDL_image for PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image count not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    // Init SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    // Init SDL_ttf
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }
    gFont = TTF_OpenFont("assets/font/lazy.ttf", 28);
    if(gFont == nullptr){
        printf("Global Font could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Init SDL Window
    gWindow = SDL_CreateWindow(
            "Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Init SDL Renderer
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    std::shared_ptr<SceneTest> testScene = std::make_shared<SceneTest>(sceneStateMachine);

    unsigned int testSceneID = sceneStateMachine.Add(testScene);

    sceneStateMachine.SwitchTo(testSceneID);

    clock.start();

    return success;
}

void Game::run() {
    bool quit = false;
    Uint64 previous = clock.getTicks();
    Uint64 lag = 0;
    fps.init();

    float time;
    while(!quit){
        Uint64 current = clock.getTicks();
        Uint64 elapsed = current - previous;

        lag += elapsed;

        // Event Loop
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            eventUpdate(&e);
        }

        // Logic Loop
        while (lag >= TICKS_PER_GAME_FRAME){
            update();
            lag -= TICKS_PER_GAME_FRAME;
        }

        // Render Loop
        renderUpdate();

        deltaTime = (float)(current - previous) / SECOND;
        previous = current;
    }
}

void Game::close() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = nullptr;
    gWindow = nullptr;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::update(){
    sceneStateMachine.Update();
}

void Game::eventUpdate(SDL_Event* e){
    sceneStateMachine.EventUpdate(e);
}

void Game::renderUpdate(){
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    // FPS handle each render update
    fps.update();

    // test object handle each render update
    sceneStateMachine.RenderUpdate();

    SDL_RenderPresent(gRenderer);
}


int main(int argc, char *argv[])
{
    Game game;
    if (!game.init())
    {
        printf("Failed to initialize!\n");
        game.close();
        return EXIT_FAILURE;
    }

    game.run();
    game.close();
    return EXIT_SUCCESS;
}


void GameObject::init(int x, int y, int a, LTexture *texture, SDL_Rect *clip){
    this->texture = texture;
    this->clip = clip;

    this->x = x;
    this->y = y;
    this->a = a;

    this->velX = 0;
    this->velY = 0;
    this->velA = 0;
}

void GameObject::render() {
    this->texture->render(this->x, this->y, clip, this->a);
}

void GameObject::update() {
    this->x += this->velX;
    this->y += this->velY;
    this->a += this->velA;

}

void GameObject::eventUpdate(SDL_Event* e) {
    if (e->type == SDL_KEYDOWN) {
        switch (e->key.keysym.sym) {
            case SDLK_RIGHT:
                velX = 3;
                break;
            case SDLK_LEFT:
                velX = -3;
                break;
            case SDLK_UP:
                velY = -3;
                break;
            case SDLK_DOWN:
                velY = 3;
                break;
            case SDLK_z:
                velA = -3;
                break;
            case SDLK_x:
                velA = 3;
                break;
        }
    }
    else if (e->type == SDL_KEYUP) {
        switch (e->key.keysym.sym) {
            case SDLK_RIGHT:
                velX = 0;
                break;
            case SDLK_LEFT:
                velX = 0;
                break;
            case SDLK_UP:
                velY = 0;
                break;
            case SDLK_DOWN:
                velY = 0;
                break;
            case SDLK_z:
                velA = 0;
                break;
            case SDLK_x:
                velA = 0;
                break;
        }
    }
}
