//
// Created by wm200618 on 2020/11/6.
//

#ifndef BREAKOUT_BALLOBJECT_H
#define BREAKOUT_BALLOBJECT_H

#include <game/GameObject.h>

class BallObject : public GameObject {
public:
    // 球的状态
    GLfloat Radius;
    GLboolean Stuck;

    BallObject();

    BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite);

    glm::vec2 Move(GLfloat dt, GLuint window_width);

    void Reset(glm::vec2 position, glm::vec2 velocity);
};


#endif //BREAKOUT_BALLOBJECT_H
