#include "stdafx.hpp"

State* createState(State *s, char t) {
  State *n = new State;

  if (t == 'L') {
    s->prev = n;
    n->next = s;
  }

  if (t == 'R') {
    n->prev = s;
    s->next = n;
  }

  return n;
}

void Machine::init(State *s) {
  State *t = s;

  // forward
  rep(i, 0, 16) { t = createState(t, 'R'); }
}

void Machine::move(char t, char c) {
  if (t == 'R') {
    if (now->next == nullptr) {
      createState(now, 'R');
    }

    if (c != -1) {
      now->state = c;
    }

    now = now->next;
  }

  if (t == 'L') {
    if (now->prev == nullptr) {
      createState(now, 'L');
    }

    if (c != -1) {
      now->state = c;
    }

    now = now->prev;
  }
}

void Machine::print(int r) {
  State *t = start;

  rep(i, 0, r) {
    if (t->next == nullptr) {
      t = createState(t, 'R');
    } else {
      t = t->next;
    }

    cout << (t->state) << " ";
  }

  cout << endl;

  t = start;

  while (t->next != now) {
    cout << "  ";

    t = t->next;
  }

  cout << "^" << endl;
}
