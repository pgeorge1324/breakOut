//
// Created by wm200618 on 2020/11/5.
//
#include <game/Game.h>
#include <game/sprite.h>
#include <game/ResourceManager.h>

// Game-related State data
SpriteRenderer  *Renderer;

Game::Game(GLuint width, GLuint height):State(GAME_ACTIVE), Keys(), Width(width), Height(height)  {

}

Game::~Game() {
    delete Renderer;
}

void Game::Init() {
    // Load shaders
    ResourceManager::LoadShader("../src/classes/base/sprite/sprite.vs", "../src/classes/base/sprite/sprite.fs", nullptr, "sprite");
    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // Load textures
    ResourceManager::LoadTexture("../resources/texture/awesomeFace.png", GL_TRUE, "face");
    // Set render-specific controls
    Shader shader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(shader);
}

void Game::ProcessInput(GLfloat dt) {

}

void Game::Update(GLfloat dt) {

}

void Game::Render() {
    Texture2D texture2D = ResourceManager::GetTexture("face");
    Renderer->DrawSprite(texture2D, glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
