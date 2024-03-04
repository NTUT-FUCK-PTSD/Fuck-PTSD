#include "App.hpp"

#include "Core/Context.hpp"

int main(int, char **) {
  auto context = Core::Context::GetInstance();
  App  app;

  while (!context->GetExit()) {
    switch (app.GetCurrentState()) {
      case App::State::START:
        app.InitStart();
        app.Start();
        app.FinishStart();
        break;

      case App::State::UPDATE:
        app.InitUpdate();
        app.Update();
        app.FinishUpdate();
        break;

      case App::State::END:
        app.End();
        context->SetExit(true);
        break;
    }
    context->Update();
  }
  return 0;
}
