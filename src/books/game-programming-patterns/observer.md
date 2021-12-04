---
title: observer
---

# Observer

## Achievement Unlocked

Let's add achievements to our game -- We'll do so with the Observer
pattern.

Observers let one piece of code announce that something interesting
happened, and letting listeners subscribe to it.

Let's implement an observer that notifies anything at all when our
character falls off a bridge.

```cpp
void Physics::updateEntity(Entity& entity) {
    bool wasOnSurface = entity.isOnSurface();
    entity.accelerate(GRAVITY);
    entity.update();
    if (wasOnSurface && !entity.isOnSurface()) {
        notify(entity, EVENT_START_FALL);
    }
}
```

## How it Works

Let's create an `Observer` interface:

```cpp
class Observer {
public:
    virtual ~Observer() {}
    virtual void onNotify(const Entity& entity, Event event) = 0;
};
```

Now we'll have our achievements class implement things:

```cpp
class Achievements : public Observer {
public:
    virtual void onNotify(const Entity& entity, Event event) {
        switch(event) {
            case EVENT_ENTITY_FELL:
                if (entity.isHerO() && heroIsOnBridge_) {
                    unlock(ACHIEVEMENT_FELL_OFF_BRIDGE);
                }
                break;
            // other events here
        }
    }
private:
    void unlock(Achievement achievement) { /* Unlock if not unlcoked */}
    bool heroIsOnBridge;
};
```

## The Subject

The notification method is invoked by the object being observed. This is
the subject.

We'll keep a list that lets us store observers.

Next, send notifications.

```cpp
class Subject {
public:
    void addObserver(Observer* observer) { /* Add observer */ }
    void removeObserver(Observer* observer) { /* Remove observer */ }
protected:
    void notify(const Entity& entity, Event event) {
        for (int i = 0; i < numObservers_; i++)
            observers_[i]->onNotify(entity, event);
    }
private:
    Observer* observers_[MAX_OBSERVERS];
    int numObservers_;
};
```

Now, for our physics engine, we just have to inherit from Subject.

```cpp
class Physics : public Subject {
public:
    void updateEntity(Entity& entity);
};
```

Prev: [flyweight](flyweight.md) Next:
[prototype](prototype.md)
