#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <set>
#include <map>
#include <tuple>

using namespace std;
using P = pair<int, char>;
using T = tuple<int, char, char>;

#define rep(i, n, m) for (int i = (n); i < (m); i++)
#define rrep(i, n, m) for (int i = (n); i > m; i--)

#define yn(ans) (ans ? "Accepted." : "Rejected.")

#include "machine.hpp"
