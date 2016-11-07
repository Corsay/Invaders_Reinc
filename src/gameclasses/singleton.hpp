#pragma once

// не рекомендуется использовать singleton вложенный в singleton (из-за неопределенности порядка их удаления)
// рекомендация с лекции:
// использовать singleton для логгера и возможно для Space (если конечно не логировать то что будет в Space)

// First variant
template <typename T> class Singleton
{
public:
  static T & Instance()
  {
    static T inst;
    return inst;
  }

protected:
  Singleton() = default;
  virtual ~Singleton() = default;

  Singleton(Singleton const &) = delete;
  Singleton & operator= (Singleton const &) = delete;
  Singleton(Singleton &&) = delete;
  Singleton & operator= (Singleton &&) = delete;
};


// Second variant
// более определенный порядок вызова конструкторов и деструкторов(определяется вызовами create и destroy)
/*
template<typename T> class Singleton
{
public:
  static T * Instance();
  static void Create();
  static void Destroy();

protected:
  Singleton() = default; // прямой вызов конструктора закрыт
  virtual ~Singleton() = default;

  Singleton(Singleton const &) = delete;
  Singleton & operator = (Singleton const &) = delete;
  Singleton(Singleton &&) = delete;
  Singleton & operator= (Singleton &&) = delete;

  staticT * m_instance; // Обязаны определить в одном cpp-файле
};
*/
