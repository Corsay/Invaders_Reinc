#pragma once
#include <iostream>
#include <fstream>
#include <set>
#include <typeinfo>
#include "singleton.hpp"

typedef std::ostream & (*manip)(std::ostream &);

class SimpleLogger: public Singleton<SimpleLogger>
{
public:
  /*static SimpleLogger & GetLogger()
  {
    static SimpleLogger OnlyLogger;
    return OnlyLogger;
  }*/

  void SetOutput(std::ostream * os) { m_os = os; }
  void SetOutput(std::string const & fileName)
  {
    Close();

    m_os = new std::ofstream{fileName};
  }

  template<typename T>
  SimpleLogger & operator << (T const & obj)
  {
    if(m_loggerOn)
      (*m_os) << obj;
    return *this;
  }

  SimpleLogger & operator << (std::ostream & (*pf)(std::ostream &))
  {
    if(pf == static_cast<manip>(std::endl) && m_loggerOn)
      (*m_os) << std::endl;
    return *this;
  }

  template<typename T, template<typename, typename...> class C, typename... Args>
  SimpleLogger & operator << (C<T, Args...> const & objs)
  {
    if(m_loggerOn)
      for (auto const & obj : objs)
        (*this) << obj << "\n";
    return *this;
  }

  void On() { m_loggerOn = true; }
  void Off() { m_loggerOn = false; }

  //переключиться на вывод в консоль
  void Checkout()
  {
    if(m_thisFile == "")
      return;

    m_countJump++;
    *m_os << "*******Jump Number " << m_countJump << " in console" << std::endl;

    Close();
    m_os = &std::cout;
    *m_os << "*******Jump Number " << m_countJump << " from " << m_thisFile << std::endl;
    m_thisFile = "";
  }

  void Checkout(std::string const & fileName)
  {
    if(fileName == m_thisFile)
      return;

    m_countJump++;
    *m_os << "*******Jump Number " << m_countJump << " in " << fileName << std::endl;
    //если при этом запуске программы еще не было записи в этот файл, то очистить
    //и записывать в начало
    Close();
    if(m_files.find(fileName) == m_files.end())
    {
      m_os = new std::ofstream(fileName);
      m_files.insert(m_thisFile);
    }
    else
    {
      m_os = new std::ofstream(fileName, std::ios_base::app);
    }
    *m_os << "*******Jump Number " << m_countJump << " from " << ((m_thisFile == "") ? "concole" : m_thisFile) << std::endl;
    m_thisFile = fileName;
  }
private:
  friend class Singleton<SimpleLogger>;
  SimpleLogger() = default;
  ~SimpleLogger()
  {
    Close();
  }

  void Close()
  {
    if (m_os == nullptr)
      return;
    if (m_thisFile != "")
    {
      ((std::ofstream *)m_os)->close();   // закрытие файла
      delete m_os;                        // удаление ссылки
    }
    m_os = nullptr;
  }

  std::set<std::string> m_files;
  std::string m_thisFile = "log.txt";
  std::ostream * m_os = new std::ofstream(m_thisFile);
  bool m_loggerOn = true;  
  unsigned int m_countJump = 0;
};

