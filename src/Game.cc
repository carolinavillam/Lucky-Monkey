#include <time.h>
#include <stdlib.h>
#include "CommonHeaders.hh"
#include "Character.hh"
#include "Candle.hh"
#include "TileGroup.hh"
#include "ButtonElement.hh"

int badBanana = 0;
AudioManager* audioManager = new AudioManager();
Character* character1{};
Candle* chest1{};
Candle* chest2{};
Candle* chest3{};
Animation* candleIdle{};
TextAsset* text1{};

TileGroup* tileGroup{};

ButtonElement* buttonElement1{};
sf::View* view{};

Game::Game()
{
  window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_NAME);
  event = new sf::Event();
  gameClock = new sf::Clock();
  gravity = new b2Vec2(0.f, 0.f);
  world = new b2World(*gravity);
  drawPhysics = new DrawPhysics(window);
  view = new sf::View(sf::FloatRect(0.f, 0.f, WINDOW_WIDTH, WINDOW_HEIGHT));

  sf::Image* iconTexture{new sf::Image()};
  iconTexture->loadFromFile(ICON);
  window->setIcon(32, 32, iconTexture->getPixelsPtr());

  gameObjects = new std::vector<GameObject*>();
  gameObjectsDeleteList = new std::vector<GameObject*>();


  tileGroup = new TileGroup(window, ASSETS_TILES, 16, 16, GAME_SCALE, 11, 10, ASSETS_TILE_GROUP_1);

  contactEventManager = new ContactEventManager(gameObjectsDeleteList);

  character1 = new Character(ASSETS_SPRITES, sf::Vector2f(100.f, 100.f), GAME_SCALE,
  16, 16, 0, 5, 200.f, window, world);
  chest1 = new Candle(ASSETS_SPRITES, sf::Vector2(500.f, 200.f), GAME_SCALE, 16, 16, 6, 3, window, world);
  chest2 = new Candle(ASSETS_SPRITES, sf::Vector2(500.f, 300.f), GAME_SCALE, 16, 16, 6, 3, window, world);
  chest3 = new Candle(ASSETS_SPRITES, sf::Vector2(500.f, 400.f), GAME_SCALE, 16, 16, 6, 3, window, world);

  text1 = new TextAsset(window, ASSETS_FONT, "Selecciona una banana",
  14, sf::Color::White, sf::Vector2f(50.f, 50.f));

}

Game::~Game()
{
  delete world;
  delete gravity;
  delete window;
}

void Game::Start()
{
  srand(time(NULL));
  badBanana = 1+rand()%3;

  character1->SetTagtName("character");
  chest1->SetTagtName("chest");
  chest2->SetTagtName("chest2");
  chest3->SetTagtName("chest3");

  gameObjects->push_back(character1);
  gameObjects->push_back(chest1);
  gameObjects->push_back(chest2);
  gameObjects->push_back(chest3);

  uint32 flags{};
  flags += b2Draw::e_shapeBit;

  world->SetDebugDraw(drawPhysics);
  drawPhysics->SetFlags(flags);

  world->SetContactListener(contactEventManager);
}

void Game::Run()
{
  Start();
  MainLoop();
}

void Game::MainLoop()
{
  while (window->isOpen())
  {
    while (window->pollEvent(*event))
    {
      if(event->type == sf::Event::Closed)
      {
        window->close();
      }
    }

    deltaTime = gameClock->getElapsedTime().asSeconds();
    gameClock->restart();

    UpdatePhysics();
    InputHandle();
    Update();
    Render();
  }
}

  void Game::UpdatePhysics()
  {
    world->Step(deltaTime, 8, 8);
    world->ClearForces();
  }

  void Game::Update()
  {
    //view->setCenter(character1->GetPosition());
    for(auto& gameObject : *gameObjects)
    {
      gameObject->Update(deltaTime);
    }
  }

  void Game::Render()
  {
    int deletedItems = 0;
    bool lose = true;
    for(auto& gameObjectPendingDelete : *gameObjectsDeleteList)
    {
      deletedItems++;
      if(badBanana == 1 && gameObjectPendingDelete->GetTagName().compare("chest") == 0){
        lose = false;
      } else if(badBanana == 2 && gameObjectPendingDelete->GetTagName().compare("chest2") == 0){
        lose = false;
      } else if(badBanana == 3 && gameObjectPendingDelete->GetTagName().compare("chest3") == 0){
        lose = false;
      }

      if(lose){
        text1 = new TextAsset(window, ASSETS_FONT, "HAS PERDIDO",
          48, sf::Color::Red, sf::Vector2f(300.f, 300.f));
      } else {
        text1 = new TextAsset(window, ASSETS_FONT, "HAS GANADO!",
          48, sf::Color::Green, sf::Vector2f(300.f, 300.f));
      }

      gameObjects->erase(std::remove(gameObjects->begin(), gameObjects->end(), gameObjectPendingDelete), gameObjects->end());
      delete gameObjectPendingDelete;
    }
    if(deletedItems != 0){
      gameObjects->erase(std::remove(gameObjects->begin(), gameObjects->end(), character1), gameObjects->end());
    }

    gameObjectsDeleteList->clear();

    window->clear(sf::Color::Black);
    Draw();
    window->display();
  }

  void Game::Draw()
  {
    window->setView(*view);
    tileGroup->Draw();

    for(auto& gameObject : *gameObjects)
    {
      gameObject->Draw();
    }
    text1->Draw();
    world->DebugDraw();

  }

  void Game::InputHandle()
  {

  }