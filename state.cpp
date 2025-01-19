#include <memory>
#include <stdio.h>

class Spa;

class SpaState
{
public:
  virtual ~SpaState() = default;
  virtual void SetContext(Spa* spa);
  virtual void Enter() = 0;
  virtual void Open() = 0;
protected:
  void ChangeState(Spa* spa, std::unique_ptr<SpaState> state);
  Spa* context_;
};

// this is the context, it's the interface used by the client
class Spa
{
public:
  // initializes the initial state
  Spa(std::unique_ptr<SpaState> state)
  : state_(nullptr)
  {
    // we can also create the default state here instead of passing it.
    this->ChangeState(std::move(state));
  }

  // the context delegates most of the requests to the underlying state
  void Enter()
  {
    state_->Enter();
  }

  void Open()
  {
    state_->Open();
  }

private:
  // friend relationship is not inherited...
  // one option then is to just set those methods public...
  friend class SpaState;
  friend class InFunctionSpaState;
  friend class OpenSpaState;
  friend class ClosedSpaState;
  // Spa state can call this private ChangeState method
  void ChangeState(std::unique_ptr<SpaState> state)
  {
    state_ = std::move(state);
    state_->SetContext(this);
  }

  // this is some context that the states might make use of
  int nb_customers_ = 0;
  std::unique_ptr<SpaState> state_;
};

// need to put this here because of circular dependency...
void SpaState::ChangeState(Spa* spa, std::unique_ptr<SpaState> state)
{
  // signal the context that the underlying state has changed
  spa->ChangeState(std::move(state));
}

void SpaState::SetContext(Spa* spa)
{
  context_ = spa;
}

class InFunctionSpaState : public SpaState
{
public:
  void Enter() override
  {
    printf("We are now %i customers!\n", ++context_->nb_customers_);
  }

  void Open() override
  {
    printf("Already open!\n");
  }
};

// concrete state implementations
class OpenSpaState : public SpaState
{
public:
  void Enter() override
  {
    printf("First Customer!\n");
    printf("We are now %i customers!\n", ++context_->nb_customers_);
    context_->ChangeState(std::make_unique<InFunctionSpaState>());
  }

  void Open() override
  {
    printf("Already open!\n");
  }
};

class ClosedSpaState : public SpaState
{
public:
  void Enter() override
  {
    printf("We are closed!\n");
  }

  void Open() override
  {
    printf("Openning!\n");
    context_->ChangeState(std::make_unique<OpenSpaState>());
  }
};

int main()
{
  auto close_state = std::make_unique<ClosedSpaState>();
  Spa spa(std::move(close_state));
  spa.Enter();
  spa.Open();
  spa.Open();
  spa.Enter();
  spa.Enter();
  spa.Enter();

  return 0;
}