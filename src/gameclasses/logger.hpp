#pragma once
#include <iostream>
#include <fstream>
#include <set>
typedef std::ostream& (*manip)(std::ostream&);


class SimpleLogger
{
public:
  static SimpleLogger& GetLogger(){
      static SimpleLogger OnlyLogger;
      return OnlyLogger;
  }
  SetOutput(std::ostream* os) { m_os = os; }
  SetOutput(std::string const & fileName) { m_os = new std::ofstream{fileName}; }

  template<typename T>
  SimpleLogger & operator << (T const & obj)
  {
    if(m_loggerOn)
      (*m_os) << obj;
    return *this;
  }
  SimpleLogger& operator << (std::ostream& (*pf)(std::ostream&)){
    if(pf == static_cast<manip>(std::endl) && m_loggerOn)
      (*m_os) << std::endl;
    return *this;
  }
  void On() { m_loggerOn=true; }
  void Off() { m_loggerOn=false; }

  //переключиться на вывод в консоль
  void Checkout() { m_os = &std::cout; }
  void Checkout(std::string const & fileName)
  {
    //если при этом запуске программы еще не было записи в этот файл, то очистить
    //и записывать в начало
    if(m_files.find(fileName) == m_files.end())
    {
      m_os = new std::ofstream(fileName);
      m_files.insert(fileName);
    }
    else
      m_os = new std::ofstream(fileName, std::ios_base::app);
  }
private:
  SimpleLogger()=default;
  SimpleLogger(const SimpleLogger & logger);
  SimpleLogger operator =(const SimpleLogger & logger);

  std::ostream* m_os = new std::ofstream("log.txt");
  //std::ostream* m_os = &std::cout;
  bool m_loggerOn = true;
  std::set<std::string> m_files{"log.txt"};
};
