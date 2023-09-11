class KeyboardController : public Component
{
public:
    TransformComponent* transform;
    SpriteComponent* sprite;

    float gravity = 0.5f;
    float maxFallSpeed = 3.0f;

    bool isJumping = false;
    float jumpSpeed = -3.5f;
    float jumpAcceleration = 0.05f; // Adjust this value for smoother jumps
    float jumpProgress = 0.0f;

    float jumpCooldown = 0.5f; // Adjust this value for the desired jump cooldown in seconds
    float jumpTimer = 0.0f;

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override
    {
        // Apply gravity
        transform->velocity.y += gravity;
        if (transform->velocity.y > maxFallSpeed)
        {
            transform->velocity.y = maxFallSpeed;
        }

        // Decrease the jump cooldown timer
        if (jumpTimer > 0.0f)
        {
            jumpTimer -= 0.01f; // Decrease the timer (adjust the time step as needed)
            if (jumpTimer < 0.0f)
            {
                jumpTimer = 0.0f; // Ensure the timer doesn't go negative
            }
        }

        if (SuperStory::event.type == SDL_KEYDOWN)
        {
            switch (SuperStory::event.key.keysym.sym)
            {
            case SDLK_w:
                if (!isJumping && jumpTimer <= 0.0f) // Check if not jumping and jump cooldown has elapsed
                {
                    isJumping = true;
                    jumpProgress = 0.0f;

                    // Start the jump cooldown timer
                    jumpTimer = jumpCooldown;
                    sprite->Play("Walk");
                }
                break;
            case SDLK_a:
                    transform->velocity.x = -1;
                    sprite->Play("Walk");
                    sprite->spriteFlip = SDL_FLIP_NONE;
                break;
            case SDLK_d:
                    transform->velocity.x = 1;
                    sprite->Play("Walk");
                    sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                break;
            case SDLK_s:
                    transform->velocity.y = 1;
                    sprite->Play("Walk");
                break;
            default:
                break;
            }
        }

        if (isJumping)
        {
            // Check if jumpAcceleration is not zero to avoid division by zero
            if (jumpAcceleration != 0.0f)
            {
                // Apply jump acceleration (smoother jump curve)
                jumpProgress += jumpAcceleration;
                if (jumpProgress >= 1.0f)
                {
                    jumpProgress = 1.0f;
                    isJumping = false;
                }

                // Calculate jump height based on a quadratic curve
                float jumpHeight = jumpSpeed * (1.0f - (jumpProgress * jumpProgress));
                transform->velocity.y = jumpHeight;

                sprite->Play("Walk");
            }
        }

        if (SuperStory::event.type == SDL_KEYUP)
        {
            switch (SuperStory::event.key.keysym.sym)
            {
            case SDLK_w:
                // Allow jumping again when releasing the jump key
                isJumping = false;
                sprite->Play("Idle");
                break;
            case SDLK_a:
                transform->velocity.x = 0;
                sprite->Play("Idle");
                break;
            case SDLK_d:
                transform->velocity.x = 0;
                sprite->Play("Idle");
                break;
            case SDLK_s:
                transform->velocity.y = 0;
                sprite->Play("Idle");
                break;
            case SDLK_ESCAPE:
                SuperStory::isRunning = false;
            default:
                break;
            }
        }
    }
};
