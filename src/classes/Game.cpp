//
// Created by wm200618 on 2020/11/5.
//
#include <game/Game.h>
#include <game/sprite.h>
#include <game/ResourceManager.h>
#include <game/GameLevel.h>

// Game-related State data
SpriteRenderer *Renderer;
GameObject *Player;

Game::Game(GLuint width, GLuint height) : State(GAME_ACTIVE), Keys(), Width(width), Height(height) {

}

Game::~Game() {
    delete Renderer;
    delete Player;
}

void Game::Init() {
    // Load shaders
    ResourceManager::LoadShader("../src/classes/base/sprite/sprite.vs", "../src/classes/base/sprite/sprite.fs", nullptr,
                                "sprite");
    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f,
                                      -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // Load textures
    ResourceManager::LoadTexture("../resources/texture/background.jpg", GL_FALSE, "background");
    ResourceManager::LoadTexture("../resources/texture/awesomeFace.png", GL_TRUE, "face");
    ResourceManager::LoadTexture("../resources/texture/block.png", GL_FALSE, "block");
    ResourceManager::LoadTexture("../resources/texture/block_solid.png", GL_FALSE, "block_solid");
    // Set render-specific controls
    Shader shader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(shader);

    // 加载关卡
    GameLevel one;
    one.Load("../resources/levels/one.lvl", this->Width, this->Height * 0.5);
    GameLevel two;
    two.Load("../resources/levels/two.lvl", this->Width, this->Height * 0.5);
    GameLevel three;
    three.Load("../resources/levels/three.lvl", this->Width, this->Height * 0.5);
    GameLevel four;
    four.Load("../resources/levels/four.lvl", this->Width, this->Height * 0.5);
    this->Levels.push_back(one);
    this->Levels.push_back(two);
    this->Levels.push_back(three);
    this->Levels.push_back(four);
    this->Level = 1;

    ResourceManager::LoadTexture("../resources/texture/paddle.png", true, "paddle");
    glm::vec2 playerPos = glm::vec2(
            this->Width / 2 - PLAYER_SIZE.x / 2,
            this->Height - PLAYER_SIZE.y
    );
    Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
}

void Game::ProcessInput(GLfloat dt) {
    if (this->State == GAME_ACTIVE)
    {
        GLfloat velocity = PLAYER_VELOCITY * dt;
        // 移动挡板
        if (this->Keys[GLFW_KEY_A])
        {
            if (Player->Position.x >= 0)
                Player->Position.x -= velocity;
        }
        if (this->Keys[GLFW_KEY_D])
        {
            if (Player->Position.x <= this->Width - Player->Size.x)
                Player->Position.x += velocity;
        }
    }
}

void Game::Update(GLfloat dt) {

}

void Game::Render() {
    if (this->State == GAME_ACTIVE) {
        // 绘制背景
        Texture2D texture2D = ResourceManager::GetTexture("background");
        Renderer->DrawSprite(texture2D,glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);
        // 绘制关卡
        this->Levels[this->Level].Draw(*Renderer);
        Player->Draw(*Renderer);
    }
}
