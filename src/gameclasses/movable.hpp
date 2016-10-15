#pragma once

// testing multi-inheritance
class Movable
{
public:
  // Default destructor.
  virtual ~Movable() = default;

  // Capabilities
  virtual void Move() = 0;
};
