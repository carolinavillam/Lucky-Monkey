#include "Character.hh"
#include "InputSystem.hh"

//AudioClip* stepsAudioClip{new AudioClip("assets/audio/steps.ogg", 4.f)};

Character::Character(const char* textureUrl, sf::Vector2f position, float scale, float width,
float height, int col, int row, float moveSpeed, sf::RenderWindow*& window, b2World*& world) :
GameObject(textureUrl, position, scale, width, height, col, row, b2BodyType::b2_dynamicBody, window, world)
{
  animationsManager = new AnimationsManager();
  audioManager = new AudioManager();

  currentStepSFXTime = stepDelay;


  this->moveSpeed = moveSpeed;

  rigidbody->FreezeRotation(true);
  //audioManager->AddAudioClip("steps", new AudioClip("assets/audio/steps.ogg", 4.f));
}

Character::~Character()
{
}

void Character::Update(float& deltaTime)
{
  GameObject::Update(deltaTime);
  animationsManager->Update(deltaTime);
  Movement(deltaTime);
  FlipSprite();
  if(currentStepSFXTime < stepDelay)
  {
    currentStepSFXTime += deltaTime;
  }

  if(std::abs(InputSystem::GetAxis().x) > 0 || std::abs(InputSystem::GetAxis().y) > 0)
  {
    //animationsManager->Play("idle");
    /*animationsManager->Play("walk");
    if(currentStepSFXTime >= stepDelay)
    {
      audioManager->Play("steps");
      currentStepSFXTime = 0.f;
    }*/
  }
  else
  {
    //animationsManager->Play("idle");
  }
  
}

void Character::Movement(float& deltaTime)
{
  rigidbody->MoveBody(b2Vec2(InputSystem::GetAxis().x * moveSpeed,
  InputSystem::GetAxis().y * moveSpeed));
}

void Character::FlipSprite()
{
  drawable->GetSprite()->setScale(InputSystem::GetAxis().x < 0.f ? -drawable->GetScale() :
  InputSystem::GetAxis().x > 0.f ? drawable->GetScale() :
  drawable->GetSprite()->getScale().x, drawable->GetSprite()->getScale().y);
}