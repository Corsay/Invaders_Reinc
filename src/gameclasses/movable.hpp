#pragma once

class Movable
{
public:
  // Default destructor.
  virtual ~Movable() = default;

  // Capabilities
  virtual void Move() = 0;
};
