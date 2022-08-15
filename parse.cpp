#include "stdafx.hpp"

enum TokenKind {
  TOKEN_MAP,
  TOKEN_PAIR,
  TOKEN_TUPLE,
  TOKEN_NUM,
  TOKEN_EOF,
};

struct Token {
  TokenKind kind;
  Token *parent;

  vector<Token *> child;
  int val;
};

char *read(char *path) {
  FILE *fp = fopen(path, "r");

  if (!fp) {
    printf("cannot open %s: %s", path, strerror(errno));
  }

  if (fseek(fp, 0, SEEK_END) == -1) {
    printf("%s: fseek: %s", path, strerror(errno));
  }

  size_t size = ftell(fp);

  if (fseek(fp, 0, SEEK_SET) == -1) {
    printf("%s: fseek: %s", path, strerror(errno));
  }

  // Load a file.
  char *buf = (char *)calloc(1, size + 2);

  fread(buf, size, 1, fp);

  if (size == 0 || buf[size - 1] != '\n') {
    buf[size] = '\n';
    size++;
  }

  buf[size] = '\0';
  fclose(fp);

  return buf;
}

Token *createToken(TokenKind kind, Token *cur) {
  Token *token = new Token;

  token->kind = kind;
  token->parent = cur;

  if (kind == TOKEN_PAIR || kind == TOKEN_MAP) {
    token->child.resize(2);
  }

  if (kind == TOKEN_TUPLE) {
    token->child.resize(3);
  }

  return token;
}

bool expect(char *p, char op) {
  if (*p != op) {
    printf("%c を期待しています\n", op);
    return false;
  }

  return true;
}

void dfs(Token *ptr) {
  cout << ptr->kind << " ";

  if (ptr->kind == 3) {
    cout << ptr->val << endl;
  } else {
    cout << endl;
  }

  rep(i, 0, ptr->child.size()) { dfs(ptr->child[i]); }
}

// (s,   a   ) -> (s,   a,    dir )
// (int, char) -> (int, char, char)

void input(Machine *m, char *p) {
  while (*p != ';') {

    if (*p != '\n') {
      m->now->state = *p;
      m->now = m->now->next;
    }

    p++;
  }

  p++;

  while (*p != ';') {
    if (isdigit(*p)) {
      m->accept.insert(strtol(p, &p, 10));
    }

    p++;
  }

  while (*p != '(') {
    p++;
  }

  m->now = m->start;

  // rules
  Token *root = createToken(TOKEN_MAP, nullptr);

  int s = 0;

  vector<Token *> res;

  cout << p << endl;

  while (*p) {
    if (isspace(*p)) {
      p++;

      continue;
    }

    if (expect(&p[0], '(')) {
      p++;

      if (s == 0) {
        Token *l = createToken(TOKEN_PAIR, root);
        root->child[0] = l;

        rep(i, 0, 2) {
          Token *t = createToken(TOKEN_NUM, l);
          if (i == 0 && isdigit(*p)) {
            t->val = strtol(p, &p, 10);
          }

          if (i == 1) {
            t->val = *p;
	    p++;
          }

          l->child[i] = t;

          if (i < 1) {
            expect(p, ',');
          } else {
            expect(p, ')');
          }

          p++;
        }
      }

      if (s == 1) {
        Token *r = createToken(TOKEN_TUPLE, root);
        root->child[1] = r;

        rep(i, 0, 3) {
          Token *t = createToken(TOKEN_NUM, r);

          if (i == 0 && isdigit(*p)) {
            t->val = strtol(p, &p, 10);
          }

	  if (i > 0) {
	    t->val = *p;
	    p++;
	  }

          r->child[i] = t;

          if (i < 2) {
            expect(p, ',');
          } else {
            expect(p, ')');
          }

          p++;
        }

        res.push_back(root);

        root = createToken(TOKEN_MAP, nullptr);
      }

      s = (s + 1) & 1;
    } else {
      break;
    }
  }

  rep(i, 0, res.size()) {
    P p;

    p.first = res[i]->child[0]->child[0]->val;
    p.second = res[i]->child[0]->child[1]->val;

    T t;

    get<0>(t) = res[i]->child[1]->child[0]->val;
    get<1>(t) = res[i]->child[1]->child[1]->val;
    get<2>(t) = res[i]->child[1]->child[2]->val;

    m->rule[p] = t;
  }
}
