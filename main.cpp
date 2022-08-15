#include "parse.cpp"
#include "stdafx.hpp"
#include <thread>

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("error");

    return 1;
  }

  char *text = read(argv[1]);

  Machine machine;

  input(&machine, text);

  bool ans = false;

  while (true) {
    P p = {machine.idx, machine.now->state};

    if (machine.rule.count(p) == 1) {
      int p0 = get<0>(machine.rule[p]);
      int p1 = get<1>(machine.rule[p]);
      int p2 = get<2>(machine.rule[p]);

      machine.idx = p0;

      if (p1 != '-') {
        machine.move(p2, p1);
      } else {
        machine.move(p2, -1);
      }
    }

    machine.print(16);

    if (machine.accept.count(machine.idx) == 1) {
      ans = true;
      break;
    }

    if (machine.reject.count(machine.idx) == 1) {
      ans = false;
      break;
    }

    chrono::milliseconds du(100);
    this_thread::sleep_for(du);
  }

  cout << yn(ans) << endl;

  return 0;
}
