#include "pimpl.h"

#include <memory>
#include <stdio.h>

namespace my_namespace {
class Pimpl::PimplImpl
{
public:
  void DoSomethingComplex()
  {
    // we have deps on complex thrid party libraries...
    printf("Hello!\n");
  }
private:
// here we might store a complex/big object

// changes here, even in the interface!, don't make pimpl_main.cpp recompile.
// only pimpl.cpp will recompile
int a;
// or changes to function names
};

Pimpl::Pimpl()
:impl_(std::make_unique<PimplImpl>())
{}

/*
You ensure that the complete definition of PimplImpl is available 
at the point where the std::unique_ptr destructor is instantiated.

Important to set it here.
*/
Pimpl::~Pimpl() = default;

void Pimpl::DoSomething()
{
  // the pimpl delegates to the implementation
  impl_->DoSomethingComplex();
  // changing implementation details here won't make the main recompile also
}

} // namespace my_namespace