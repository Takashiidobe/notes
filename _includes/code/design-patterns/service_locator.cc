class Audio {
 public:
  virtual ~Audio() {}
  virtual void playSound(int soundID) = 0;
  virtual void stopSound(int soundID) = 0;
  virtual void stopAllSounds() = 0;
};

class ConsoleAudio : public Audio {
 public:
  virtual void playSound(int soundID) {
    // Play sound using console audio api...
  }

  virtual void stopSound(int soundID) {
    // Stop sound using console audio api...
  }

  virtual void stopAllSounds() {
    // Stop all sounds using console audio api...
  }
};

class Locator {
 public:
  static Audio* getAudio() { return service_; }

  static void provide(Audio* service) { service_ = service; }

 private:
  static Audio* service_;
};

int main() {
  ConsoleAudio* audio = new ConsoleAudio();
  Locator::provide(audio);
}
