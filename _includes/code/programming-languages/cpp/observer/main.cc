#include <fmt/core.h>
#include <list>
#include <string>

class ObserverInterface {
public:
  virtual ~ObserverInterface(){};
  virtual void update(const std::string &message) = 0;
};

class SubjectInterface {
public:
  virtual ~SubjectInterface(){};
  virtual void attach(ObserverInterface *observer) = 0;
  virtual void detach(ObserverInterface *observer) = 0;
  virtual void notify() = 0;
};

class Subject : public SubjectInterface {
public:
  Subject() = default;
  ~Subject() = default;
  void attach(ObserverInterface *observer) override {
    observers.push_back(observer);
  }
  void detach(ObserverInterface *observer) override {
    observers.remove(observer);
  }
  void notify() override {
    for (const auto observer : observers) {
      observer->update(message);
    }
  }

private:
  std::list<ObserverInterface *> observers = {};
  std::string message = "Notification";
};

class Observer : public ObserverInterface {
public:
  Observer(Subject &subject) : subject_(subject) {
    this->subject_.attach(this);
  }
  ~Observer() = default;

  void update(const std::string &message) override {
    fmt::print("{}\n", message);
  }

private:
  Subject &subject_;
};

int main() {
  Subject *subject = new Subject();
  Observer *obs1 = new Observer(*subject);
  fmt::print("Notifying Obs 1 twice\n");
  subject->notify();
  subject->notify();
  Observer *obs2 = new Observer(*subject);
  Observer *obs3 = new Observer(*subject);
  fmt::print("Notifying Obs 1, 2, 3 once\n");
  subject->notify();
}
