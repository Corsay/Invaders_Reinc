#pragma once
#include <iostream>
#include <fstream>
#include <set>
#include <typeinfo>

typedef std::ostream & (*manip)(std::ostream &);

class SimpleLogger
{
public:
  static SimpleLogger & GetLogger()
  {
    static SimpleLogger OnlyLogger;
    return OnlyLogger;
  }

  ~SimpleLogger ()
  {
   Close();
  }

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

  SimpleLogger & operator << (std::string const & obj)
  {
    *m_os << obj;
    return *this;
  }

  template<typename T, template<typename, typename...> class C, typename... Args>
  SimpleLogger & operator << (C<T, Args...> const & objs)
  {
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
    *m_os << "*******Jump Number" << m_countJump << " in " << fileName << std::endl;
    //если при этом запуске программы еще не было записи в этот файл, то очистить
    //и записывать в начало
    if(m_files.find(fileName) == m_files.end())
    {
      Close();

      m_os = new std::ofstream(fileName);
      m_files.insert(m_thisFile);
    }
    else
    {
      Close();

      m_os = new std::ofstream(fileName, std::ios_base::app);
    }
    *m_os << "*******Jump Number " << m_countJump << " from " << ((m_thisFile == "")? "concole":m_thisFile) << std::endl;
    m_thisFile = fileName;
  }
private:

  void Close()
  {
    if (m_os == nullptr)
      return;
    ((std::ofstream *)m_os)->close();
    delete m_os;
    m_os = nullptr;
  }

  SimpleLogger() = default;
  SimpleLogger(const SimpleLogger & logger);
  SimpleLogger operator = (const SimpleLogger & logger);

  std::ostream * m_os = new std::ofstream("log.txt");
  bool m_loggerOn = true;
  std::set<std::string> m_files;
  std::string m_thisFile = "log.txt";
  unsigned int m_countJump = 0;
};

