#pragma once
#include "movedgameentity.hpp"
#include <unordered_map>


// Factory через шаблон, но думаю можем реализовать вариант полиморфизма, так как нумератор уже есть(в GameEntity)
class Factory
{
public:
  template<typename T, typename... Args>
  std::unique_ptr<T> Create(Args && ... args)
  {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
  }
};
// Вариант на рассмотрение для обновления GameEntity фабрики (полиморфизм)




class GameEntityFactory
{
public:
  bool Register(std::unique_ptr<MovedGameEntity2D> && entity)
  {
    if (m_templates.find(entity->GetEntityType()) != m_templates.end())
      return false;

    m_templates[entity->GetEntityType()] = std::move(entity);
    return true;
  }
  void Unregister(std::unique_ptr<MovedGameEntity2D> const & entity)
  { m_templates[entity->GetEntityType()] = nullptr; }

  std::unique_ptr<MovedGameEntity2D> Create(EntitiesTypes type)
  {
    if (m_templates.find(type) == m_templates.end())
      return nullptr;

      return m_templates[type]->Create();
  }
  std::unique_ptr<MovedGameEntity2D> Create(EntitiesTypes type,Point2D & ld, Point2D & rt,
                                        std::initializer_list<float> const & lst)
  {
    if (m_templates.find(type) == m_templates.end())
      return nullptr;
    short l = lst.size();
    auto it = lst.begin();
    if(l < 2)
      return m_templates[type]->Create(ld, rt);
    else if((l > 4) && (type != EntitiesTypes::GunType))
      return m_templates[type]->Create(ld, rt, *it, *(it+1), *(it+2) );
    else
      return m_templates[type]->Create(ld, rt, *it, *(it+1));// return nullptr;
  }
private:
  std::unordered_map<int, std::unique_ptr<MovedGameEntity2D>> m_templates;
};

