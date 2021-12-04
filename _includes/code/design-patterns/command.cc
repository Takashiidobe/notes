enum BUTTON {
  BUTTON_X,
  BUTTON_Y,
  BUTTON_A,
  BUTTON_B
};

bool isPressed(BUTTON b) {
  if (b == BUTTON_A) return true;
  else return false;
}

void jump() {}
void fireGun() {}
void swapWeapon() {}
void lurchIneffectively() {}

class GameActor {
  public:
    void jump() {}
    void fireGun() {}
    void swapWeapon() {}
    void lurchIneffectively() {}
};

class Command {
  public:
    virtual ~Command() {}
    virtual Command* execute(GameActor& actor) = 0;
};

class JumpCommand : public Command {
  public:
    virtual void execute(GameActor& actor) { actor.jump(); }
};

class FireCommand : public Command {
  public:
    virtual void execute(GameActor& actor) { actor.fireGun(); }
};

class SwapCommand : public Command {
  public:
    virtual void execute(GameActor& actor) { actor.swapWeapon(); }
};

class LurchCommand : public Command {
  public:
    virtual void execute(GameActor& actor) { actor.lurchIneffectively(); }
};

class InputHandler {
  private:
    Command* buttonX_;
    Command* buttonY_;
    Command* buttonA_;
    Command* buttonB_;
  public:
    Command* handleInput();
};

GameActor actor;

Command* InputHandler::handleInput() {
  if (isPressed(BUTTON_X)) return buttonX_;
  if (isPressed(BUTTON_Y)) return buttonY_;
  if (isPressed(BUTTON_A)) return buttonA_;
  if (isPressed(BUTTON_B)) return buttonB_;

  return nullptr;
}

// void InputHandler::handleInput() {
//   if (isPressed(BUTTON_X)) buttonX_->execute(actor);
//   else if (isPressed(BUTTON_Y)) buttonY_->execute(actor);
//   else if (isPressed(BUTTON_A)) buttonA_->execute(actor);
//   else if (isPressed(BUTTON_B)) buttonB_->execute(actor);
// }
