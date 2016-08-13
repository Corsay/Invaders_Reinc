#pragma once

class Dummy
{
public:
  Dummy() = default;
  Dummy(int const potatoes, int const tomatoes)
    : m_potatoes(potatoes)
    , m_tomatoes(tomatoes)
  {}

  int Sum() const { return m_potatoes + m_tomatoes; }

private:
  int m_potatoes = 0;
  int m_tomatoes = 0;
};
