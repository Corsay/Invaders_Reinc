#pragma once

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

