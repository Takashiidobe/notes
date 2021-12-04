class FileSystem {
  private static instance_;
  static instance() {
    if (this.instance_) {
      return this.instance_;
    } else {
      this.instance_ = new FileSystem();
      return this.instance_;
    }
  }
  private constructor() {}

  getFile() {
    console.log(`get file was called`);
  }
}

const fs1 = FileSystem.instance();
const fs2 = FileSystem.instance();

class Dummy {
  constructor() {}
}

const dummy1 = new Dummy();
const dummy2 = new Dummy();

console.log(dummy1 === dummy2);

console.log(fs1 === fs2);

class Singleton {
  private static instance_ = new Singleton();

  static instance() {
    return this.instance_;
  }
}

Singleton.instance();
