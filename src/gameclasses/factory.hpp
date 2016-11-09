#pragma once
#include "gameentity.hpp"
#include "gun.hpp"
#include <unordered_map>

// Factory templates
class Factory
{
public:
  template<typename T, typename... Args>
  std::unique_ptr<T> CreateNew(Args && ... args)
  {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
  }
};


// GameEntity factory (полиморфизм)
class GameEntityFactory
{
public:
  // Reg unreg new type in factory
  bool Register(std::unique_ptr<GameEntity2D> && entity)
  {
    if (m_templates.find(entity->GetEntityType()) != m_templates.end())
      return false;

    m_templates[entity->GetEntityType()] = std::move(entity);
    return true;
  }
  void Unregister(std::unique_ptr<GameEntity2D> const & entity)
  {
    m_templates[entity->GetEntityType()] = nullptr;
  }

  // create new unique_ptr for selected type
  std::unique_ptr<GameEntity2D> Create(EntitiesTypes type)
  {
    if (m_templates.find(type) == m_templates.end())
      return nullptr;

    return m_templates[type]->Create();
  }

  template <typename... Args>
  std::unique_ptr<GameEntity2D> Create(EntitiesTypes type, Args && ... args)
  {
    if (m_templates.find(type) == m_templates.end())
      return nullptr;

    return m_templates[type]->Create(std::forward<Args>(args)...);
  }

  // create new unique_ptr fro selected type, with initialization_list
  /*std::unique_ptr<GameEntity2D> Create(EntitiesTypes type, Point2D const & ld, Point2D const & rt, std::initializer_list<float> const & lst)
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
      return m_templates[type]->Create(ld, rt, *it, *(it+1)); // return nullptr;
  }*/

private:
  std::unordered_map<int, std::unique_ptr<GameEntity2D>> m_templates;
};

template <typename TDerived, typename TBase>
std::unique_ptr<TDerived> static_unique_ptr_cast(std::unique_ptr<TBase> && p)
{
  return std::unique_ptr<TDerived>(static_cast<TDerived *>(p.release()));
}
