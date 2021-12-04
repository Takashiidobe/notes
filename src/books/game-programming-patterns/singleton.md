---
title: singleton
---

# Singleton

Use the Singleton pattern sparingly; it tends to result in problems down
the road.

Singletons make it so there\'s only one instance of a class that manages
some state \-- this can be useful for operations that take a long time
and must be synchronized, like a file system API.

## Providing a global point of access

```cpp
class FileSystem {
public:
  static FileSystem& instance() {
    static FileSystem *instance = new FileSystem();
    return *instance_;
  }
  FileSystem(const FileSystem&) = delete; // remove the copy constructor
private:
  FileSystem() {}
};
```

## Why We Use it

- It saves memory by being lazily initialized
- It allows you to read information that the program has at runtime,
  since it\'s used at runtime unlike statics, which are compile time
  only
- You can subclass the singleton.

Here\'s the base class:

```cpp
class FileSystem {
public:
  virtual ~FileSystem() {}
  virtual char* readFile(char* path) = 0;
  virtual void  writeFile(char* path, char* contents) = 0;
};
```

Here are some implementations:

```cpp
class PS3FileSystem : public FileSystem
{
public:
  virtual char* readFile(char* path) {
    // Use Sony file IO API...
  }

  virtual void writeFile(char* path, char* contents) {
    // Use sony file IO API...
  }
};

class WiiFileSystem : public FileSystem
{
public:
  virtual char* readFile(char* path) {
    // Use Nintendo file IO API...
  }

  virtual void writeFile(char* path, char* contents) {
    // Use Nintendo file IO API...
  }
};
```

Then turn it into a singleton:

```cpp
class FileSystem {
public:
  static FileSystem& instance();

  virtual ~FileSystem() {}
  virtual char* readFile(char* path) = 0;
  virtual void  writeFile(char* path, char* contents) = 0;

protected:
  FileSystem() {}
};
```

And we can initialize it like so:

```cpp
FileSystem& FileSystem::instance()
{
  #if PLATFORM == PLAYSTATION3
    static FileSystem *instance = new PS3FileSystem();
  #elif PLATFORM == WII
    static FileSystem *instance = new WiiFileSystem();
  #endif

  return *instance;
}
```

This doesn\'t solve the fact that these are just glorified global vars:

Globals:

- Make it hard to reason about code. If a function is affected by or
  touches a global variable, your reasoning becomes non-local, you
  have to look at the function and at global state.

- They encourage coupling. Global variables are easy to entangle with
  other code even if you don\'t mean it \-- therefore they get bound
  into other code when you didn\'t mean to, turning your architecture
  into a ball of mud.

- They aren\'t concurrency-friendly: Games are multi-threaded now for
  maximum performance, and having globally readable and writable
  variables is one way to create race conditions.

## It solves two problems when you just have one

Convenient access is why we turn to the singleton, especially for cases
like logging. But when we do this, we can no longer create more than one
logger. What happens when we need to write to more than one log file? We
can\'t anymore. If we want to provide a filepath, every line of code
that uses it and the class itself must break.

## Lazy initialization takes control away from you

If you want to initialize everything at start time, you don\'t want lazy
instantiation. To do so, you might write this:

```cpp
class FileSystem {
public:
  static FileSystem& instance() { return instance_; }

private:
  FileSystem() {}

  static FileSystem instance_;
};
```

## What we can do instead

Do we really need the class?

A lot of singleton classes are \"managers\". Classes that babysit
another class.

Instead of doing this, allow the object to manage its own state.

```cpp
class Bulllet {
public:
  int getX() const { return x_; }
  int getY() const { return y_; }

  void setX(int x) { x_ = x; }
  void setY(int y) { y_ = y; }

private:
  int x_, y_;
};

class BulletManager {
public:
  Bullet* create(int x, int y) {
    Bullet* bullet = new Bullet();
    bullet->setX(x);
    bullet->setY(y);

    return bullet;
  }

  bool isOnScreen(Bullet& bullet) {
    return bullet.getX() >= 0 &&
           bullet.getX() < SCREEN_WIDTH &&
           bullet.getY() >= 0 &&
           bullet.getY() < SCREEN_HEIGHT;
  }

  void move(Bullet& bullet) {
    bullet.setX(bullet.getX() + 5);
  }
};
```

Have the class manage its own state and initialization:

```cpp
class Bullet {
public:
  Bullet(int x, int y) : x_(x), y_(y) {}

  bool isOnScreen() {
    return x_ >= 0 && x_ < SCREEN_WIDTH &&
           y_ >= 0 && y_ < SCREEN_HEIGHT;
  }

  void move(int x, int y) { x_ += x; y_ += y; }

private:
  int x_, y_;
};
```

## Only allowing one instance

We can try and find a way to support single instance instantiation:

```cpp
class FileSystem {
public:
  FileSystem() {
    assert(!instantiated_);
    instantiated_ = true;
  }

  ~FileSystem() { instantiated_ = false; }

private:
  static bool instantiated_;
};

bool FileSystem::instantiated_ = false;
```

## Providing convenient access to an instance

- Just pass it in. This adds more arguments to our functions, but
  gives us the most control.

- Get it from the base class. Most game architectures have shallow but
  wide inheritance hierarchies, so have the base GameObject class
  control the log and have objects derive from it.

```cpp
class GameObject {
protected:
  Log& getLog() { return log_; }

private:
  static Log& log_;
};

class Enemy : public GameObject {
  void doSomething() {
    getLog().write(;
  }
};
```

- Get it from something Global:

Assume there\'s already a singleton Game object:

```cpp
class Game {
public:
  static Game& instance() { return instance_; }

  // Functions to set log_, et. al. ...

  Log&         getLog()         { return *log_; }
  FileSystem&  getFileSystem()  { return *fileSystem_; }
  AudioPlayer& getAudioPlayer() { return *audioPlayer_; }

private:
  static Game instance_;

  Log         *log_;
  FileSystem  *fileSystem_;
  AudioPlayer *audioPlayer_;
};
```

You can get your audio through the game instance:

```cpp
Game::instance().getAudioPlayer().play(VERY_LOUD_BANG);
```

- Get it from a Service Locator:
  \[service-locator](service-locator.md)

Prev: \[prototype](prototype.md) Next:
\[state](state.md)
