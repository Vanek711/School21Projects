#include <ctype.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  bool optionb;
  bool optione;
  bool optionn;
  bool options;
  bool optiont;
  bool optionv;
  bool warning;
} flags;

void processing(int argc, char *argv[], flags *flag, int *value_optind);
void print(int argc, char *argv[], flags flag, int value_optind);

int main(int argc, char *argv[]) {
  flags flag;
  int value_optind;
  processing(argc, argv, &flag, &value_optind);
  print(argc, argv, flag, value_optind);
  return 0;
}

void print(int argc, char *argv[], flags flag, int value_optind) {
  if (flag.optionn && flag.optionb) flag.optionn = false;
  while (value_optind < argc) {
    FILE *file;
    int ch;
    int lastch = 0;
    bool flagchignore = false, stemp = false, firststr = true;
    int line = 0;
    if ((file = fopen(argv[value_optind], "r")) == NULL) {
      exit(1);
    }
    while ((ch = getc(file)) != EOF) {
      if (lastch == '\n') {
        if (flag.options) {
          if (ch == '\n' && stemp)
            continue;
          else if (ch == '\n')
            stemp = true;
          else
            stemp = false;
        }
        if (flag.optionb && ch != '\n') printf("%6d\t", ++line);
      }
      if (firststr && ch != '\n' && flag.optionb) printf("%6d\t", ++line);
      if ((firststr || lastch == '\n') && flag.optionn) printf("%6d\t", ++line);
      if (flag.optione && ch == '\n') putchar('$');
      if (flag.optiont && ch == '\t') {
        putchar('^');
        putchar('I');
        flagchignore = false;
        firststr = false;
        lastch = ch;
        continue;
      }
      if (flag.optionv) {
        if (ch < 32) {
          flagchignore = true;
          if (ch == '\n' || ch == '\t')
            putchar(ch);
          else {
            putchar('^');
            ch += 64;
            putchar(ch);
          }
        } else if (ch == 127) {
          flagchignore = true;
          putchar('^');
          putchar('?');
        } else if (ch > 128) {
          flagchignore = true;
          putchar('M');
          putchar('-');
          if (ch >= 128 + 32) {
            if (ch < 128 + 127)
              putchar(ch - 128);
            else {
              putchar('^');
              putchar('?');
            }
          } else {
            putchar('^');
            putchar(ch - 128 + 64);
          }
        }
      }
      if (!flagchignore) putchar(ch);
      flagchignore = false;
      firststr = false;
      lastch = ch;
    }
    fclose(file);
    value_optind++;
  }
}

void processing(int argc, char *argv[], flags *flag, int *value_optind) {
  flag->optionb = false;
  flag->optionn = false;
  flag->options = false;
  flag->optiont = false;
  flag->optionv = false;
  flag->optione = false;
  flag->warning = false;
  while (1) {
    char option_symbol;
    int option_index = 0;
    static struct option options[] = {{"number-nonblank", 0, 0, 'b'},
                                      {"number", 0, 0, 'n'},
                                      {"squeeze-blank", 0, 0, 's'},
                                      {0, 0, 0, 0}};
    option_symbol = getopt_long(argc, argv, "bnsteETv", options, &option_index);
    if (option_symbol == -1) break;
    switch (option_symbol) {
      case 'b':
        flag->optionb = true;
        break;
      case 'e':
        flag->optione = true;
        flag->optionv = true;
        break;
      case 'n':
        flag->optionn = true;
        break;
      case 's':
        flag->options = true;
        break;
      case 't':
        flag->optiont = true;
        flag->optionv = true;
        break;
      case 'E':
        flag->optione = true;
        break;
      case 'v':
        flag->optionv = true;
        break;
      case 'T':
        flag->optiont = true;
        break;
      default:
        flag->warning = true;
        break;
    }
  }
  *value_optind = optind;
}
