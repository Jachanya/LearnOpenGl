#ifndef _IDENTITY_TRANSITION_H_
#define _IDENTITY_TRANSITION_H_

#include "transition.hpp"
#include "game_object.hpp"
#include "sprite_renderer.hpp"

namespace jachan
{
    class IdentityTransition : public Transition
    {
    public:
        IdentityTransition(GameObject& gameObject);
        ~IdentityTransition() = default;
        GameObject& transform(SpriteRenderer &renderer);
    private:
        GameObject& gameObject;
    };
}
#endif