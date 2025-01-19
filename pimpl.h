# pragma once

#include <memory>

namespace my_namespace {
class Pimpl
{
public:
  Pimpl();
  ~Pimpl();
  void DoSomething();
private:
  class PimplImpl;
  std::unique_ptr<PimplImpl> impl_;
};

} // namespace my_namespace