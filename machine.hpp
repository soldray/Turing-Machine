#pragma once

struct State {
  State *next = nullptr, *prev = nullptr;
  char state = '-';
};

class Machine {
public:
  State *start;
  State *now;
  int idx;
  map<P, T> rule;
  set<int> accept, reject;

  Machine() {
    now = new State;
    start = now;

    idx = 0;

    init(now);
  }

  void init(State *s);
  void print(int r);
  void move(char t, char c);
};
