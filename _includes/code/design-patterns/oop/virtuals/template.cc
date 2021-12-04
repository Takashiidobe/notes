#include <fmt/core.h>
#include <string>

struct Logger {
  void log(const char *msg) { log(msg); }
  virtual ~Logger() = default;

private:
  virtual void logMsg(const char *msg) = 0;
};

struct StdoutLogger : private Logger {
  void log(const char *msg) { logMsg(msg); }
  virtual ~StdoutLogger() = default;

private:
  void logMsg(const char *msg) { fmt::print("{}", msg) }
};

struct StderrLogger : private Logger {
  void log(const char *msg) { logMsg(msg); }
  virtual ~StderrLogger() = default;

private:
  void logMsg(const char *msg) { std::cerr << msg << std::endl; }
};

int main() {
  StdoutLogger stdoutlogger = StdoutLogger();
  stdoutlogger.log("Msg");
  StderrLogger stderrlogger = StderrLogger();
  stderrlogger.log("Err");
}
