#include "DrawPhysics.hh"

DrawPhysics::DrawPhysics(sf::RenderWindow*& window)
{
  this->window = window;
}

DrawPhysics::~DrawPhysics()
{
}

sf::Color DrawPhysics::GLColorToSFML(const b2Color &color, sf::Uint8 alpha)
{
  return sf::Color(static_cast<sf::Uint8>(color.r * 255), static_cast<sf::Uint8>(color.g * 255), static_cast<sf::Uint8>(color.b * 255), alpha);
}

sf::Vector2f DrawPhysics::B2VecToSFVec(const b2Vec2 &vector)
{
  return sf::Vector2f(std::floor(vector.x), std::floor(vector.y));
}

void DrawPhysics::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color)
{
  sf::ConvexShape polygon{sf::ConvexShape(vertexCount)};
  for(int i{}; i < vertexCount; i++)
  {
    polygon.setPoint(i, B2VecToSFVec(vertices[i]));
  }

  polygon.setFillColor(sf::Color::Transparent);
  polygon.setOutlineColor(GLColorToSFML(color));
  polygon.setOutlineThickness(-2.f);

  window->draw(polygon);
}

void DrawPhysics::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color)
{
  sf::ConvexShape polygon{sf::ConvexShape(vertexCount)};
  for(int i{}; i < vertexCount; i++)
  {
    polygon.setPoint(i, B2VecToSFVec(vertices[i]));
  }

  polygon.setFillColor(GLColorToSFML(color, 60));
  polygon.setOutlineColor(GLColorToSFML(color));
  polygon.setOutlineThickness(-2.f);

  window->draw(polygon);
}

void DrawPhysics::DrawCircle(const b2Vec2 &center, float radius, const b2Color &color)
{

}

void DrawPhysics::DrawSolidCircle(const b2Vec2 &center, float radius, const b2Vec2 &axis, const b2Color &color)
{

}

void DrawPhysics::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color)
{

}

void DrawPhysics::DrawTransform(const b2Transform &xf)
{

}

void DrawPhysics::DrawPoint(const b2Vec2 &p, float size, const b2Color &color)
{

}