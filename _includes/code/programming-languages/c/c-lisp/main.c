#include <ctype.h>
#include <math.h>
#include <stdio.h>

typedef enum Symbol {
  L_PAREN,
  R_PAREN,
  SIGN,
  NUM,
} Symbol;

typedef enum Sign {
  ADD,
  SUB,
  MUL,
  DIV,
  NONE,
} Sign;

void eval(Sign s, int nums[1024], int i);
void parse(char c);
void print(int i);
Sign s = NONE;
int nums[1024];
int i = 0;
int left_parens = 0;
int right_parens = 0;
int curr = 0;

int main() {
  char c;
  while ((c = getchar()) != EOF) {
    parse(c);
  }
}

void eval(Sign s, int nums[1024], int i) {
  int total = 0;
  switch (s) {
  case ADD:
    total = 0;
    for (int j = 0; j < i; j++)
      total += nums[j];
    break;
  case SUB:
    total = nums[0];
    for (int j = 1; j < i; j++)
      total -= nums[j];
    break;
  case MUL:
    total = 1;
    for (int j = 0; j < i; j++)
      total *= nums[j];
    break;
  case DIV:
    total = nums[0];
    for (int j = 1; j < i; j++)
      total /= nums[j];
    break;
  default:
    puts("No sign was provided");
    break;
  }
  printf("=> %d\n", total);
}

void parse(char c) {
  switch (c) {
    case '+':
      s = ADD;
      break;
    case '-':
      s = SUB;
      break;
    case '*':
      s = MUL;
      break;
    case '/':
      s = DIV;
      break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      curr = c - '0';
      while ((c = getchar()) != EOF) {
        if (c == ' ')
          break;
        if (c == ')') {
          right_parens++;
          break;
        }
        if (isdigit(c)) {
          if (c == '0')
            curr *= 10;
          else
            curr = (curr * 10) + (c - '0');
        }
      }
      nums[i] = curr;
      i++;
      curr = 0;
      break;
    case '(':
      left_parens++;
      break;
    case ')':
      right_parens++;
      break;
    case '\n':
      if ((left_parens && right_parens) && (left_parens == right_parens))
        eval(s, nums, i);
      else
        puts("You did not provide balanced parens.");
      s = NONE;
      left_parens = 0;
      right_parens = 0;
      i = 0;
      break;
    default:
      break;
    }
}
