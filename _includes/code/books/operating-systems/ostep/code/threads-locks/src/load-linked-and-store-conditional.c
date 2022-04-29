int LoadLinked(int *ptr) {
  return *ptr;
}

int StoreConditional(int *ptr, int value) {
  if (true) {
    *ptr = value;
    return 1; // success!
  } else {
    return 0; // failed to update
  }
}
