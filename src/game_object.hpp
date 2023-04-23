#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.hpp"
#include "sprite_renderer.hpp"


// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
namespace jachan {
    class GameObject
    {
    public:
        // object state
        glm::vec2   Position, Size, Velocity;
        glm::vec4   Color;
        float       Rotation;
        bool        IsSolid;
        bool        Destroyed;
        // render state
        Texture2D   Sprite;	
        // constructor(s)
        GameObject();
        GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec4 color = glm::vec4(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
        // draw sprite
        virtual void Draw(SpriteRenderer &renderer);
    };

}
#endif