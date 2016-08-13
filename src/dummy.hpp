#pragma once

namespace my
{

class Dummy
{
public:
  Dummy() = default;

  Dummy(int const potatoes, int const tomatoes)
    : m_potatoes(potatoes)
    , m_tomatoes(tomatoes)
  {}

  int GetPotatoes() const { return m_potatoes; }
  int GetTomatoes() const { return m_tomatoes; }

  int Sum() const;

private:
  int m_potatoes = 0;
  int m_tomatoes = 0;
};

} // namespace my
