#include <ctype.h>
#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  bool optione;
  bool optioni;
  bool optionv;
  bool optionc;
  bool optionl;
  bool optionn;
  bool optionh;
  bool options;
  bool optionf;
  bool optiono;
} flags;

void processing(int argc, char *argv[], flags *flag, int *value_optind,
                char ***eparam, char ***fparam, int *fcounter, int *ecounter);
void print(int argc, char *argv[], flags flag, int value_optind, char **eparam,
           char **fparam, int fcounter, int ecounter);
int stupidmatch(char *string, char *pattern, flags flag, int filecounter,
                char *argv[], int value_optind, int counterstringsN);
int printfEF(int ecounter, int fcounter, char *string, char **patterne,
             char **patternf, flags flag, char *argv[], int value_optind,
             int filecounter, int counterstringsN, int counterstringsC,
             int *newfile);
int printfE(int counterstringsC, int counterstringsN, int ecounter,
            char *string, char **patterne, flags flag, int filecounter,
            char *argv[], int value_optind, int *newfile);
int defaultprintf(char *string, char *pattern, flags flag, int filecounter,
                  char *argv[], int value_optind, int counterstringsN,
                  int counterstringsC, int *newfile);
int printfF(int counterstringsC, int counterstringsN, char *string,
            char **patternf, flags flag, int filecounter, char *argv[],
            int value_optind, int EFcounter, int *newfile);

int main(int argc, char *argv[]) {
  if (argc < 3) {
    return 0;
  }
  int ecounter = 0, fcounter = 0;
  flags flag;
  char **eparam = NULL;
  char **fparam = NULL;
  int value_optind;
  processing(argc, argv, &flag, &value_optind, &eparam, &fparam, &fcounter,
             &ecounter);
  if (flag.optionc && flag.optionl) flag.optionc = false;
  print(argc, argv, flag, value_optind, eparam, fparam, fcounter, ecounter);
  for (int i = 0; i < fcounter; i++) {
    free((fparam)[i]);
  }

  for (int i = 0; i < ecounter; i++) {
    free((eparam)[i]);
  }
  free(fparam);
  free(eparam);
  return 0;
}

void print(int argc, char *argv[], flags flag, int value_optind, char **eparam,
           char **fparam, int fcounter, int ecounter) {
  int EFcounter = 0;
  char *pattern = NULL;
  char **patterne = (char **)malloc(1024 * sizeof(char *));
  char **patternf = (char **)malloc(1024 * sizeof(char *));
  if (!(flag.optione || flag.optionf)) {
    pattern = argv[value_optind];
    value_optind++;
  } else {
    for (int i = 0; i < ecounter; i++) {
      patterne[i] = eparam[i];
    }
    for (int j = 0; j < fcounter; j++) {
      char str[1024];
      FILE *file;
      if ((file = fopen(fparam[j], "r")) == NULL) {
        fprintf(stderr, "grep: %s: No such file or directory\n", fparam[j]);
        exit(1);
      }
      while (!feof(file)) {
        if (fgets(str, sizeof(str), file)) {
          size_t strlength = strlen(str);
          if (str[strlength - 1] == '\n') str[strlength - 1] = '\0';
          patternf[EFcounter] = (char *)malloc((strlength + 1) * sizeof(char));
          strcpy(patternf[EFcounter], str);
          EFcounter++;
        }
      }
      fclose(file);
    }
  }
  int filecounter = argc - value_optind;

  while (value_optind < argc) {
    int newfile = 0;
    int counterstringsN = 0;
    int counterstringsC = 0;
    FILE *fp;
    size_t len = 0;
    size_t read;
    if ((fp = fopen(argv[value_optind], "r")) == NULL) {
      if (!flag.options)
        fprintf(stderr, "grep: %s: No such file or directory\n",
                argv[value_optind]);
      value_optind++;
      continue;
    }
    char *string = NULL;
    while ((int)(read = getline(&string, &len, fp)) != -1) {
      counterstringsN++;
      if (flag.optione && flag.optionf) {
        counterstringsC =
            printfEF(ecounter, EFcounter, string, patterne, patternf, flag,
                     argv, value_optind, filecounter, counterstringsN,
                     counterstringsC, &newfile);
      } else if (flag.optione) {
        counterstringsC =
            printfE(counterstringsC, counterstringsN, ecounter, string,
                    patterne, flag, filecounter, argv, value_optind, &newfile);
      } else if (flag.optionf) {
        counterstringsC =
            printfF(counterstringsC, counterstringsN, string, patternf, flag,
                    filecounter, argv, value_optind, EFcounter, &newfile);
      } else {
        counterstringsC = defaultprintf(string, pattern, flag, filecounter,
                                        argv, value_optind, counterstringsN,
                                        counterstringsC, &newfile);
      }
    }
    fclose(fp);
    if (flag.optionc) {
      if (filecounter > 1 && !flag.optionh) printf("%s:", argv[value_optind]);
      if (flag.optionv && flag.optionf)
        printf("%d\n", counterstringsN - counterstringsC);
      else
        printf("%d\n", counterstringsC);
    }
    value_optind++;
    free(string);
  }
  for (int i = 0; i < EFcounter; i++) {
    free(patternf[i]);
  }
  free(patternf);
  free(patterne);
}

void processing(int argc, char *argv[], flags *flag, int *value_optind,
                char ***eparam, char ***fparam, int *fcounter, int *ecounter) {
  *eparam = (char **)malloc(256 * sizeof(char *));
  *fparam = (char **)malloc(256 * sizeof(char *));
  flag->optione = false;
  flag->optioni = false;
  flag->optionv = false;
  flag->optionc = false;
  flag->optionl = false;
  flag->optionn = false;
  flag->options = false;
  flag->optionf = false;
  flag->optiono = false;
  while (1) {
    int option_symbol;
    option_symbol = getopt(argc, argv, "e:ivclnhsf:o");
    if (option_symbol == -1) break;
    switch (option_symbol) {
      case 'e':
        (*eparam)[*ecounter] =
            (char *)malloc((strlen(optarg) + 1) * sizeof(char));
        strcpy((*eparam)[*ecounter], optarg);
        *ecounter += 1;
        flag->optione = true;
        break;
      case 'i':
        flag->optioni = true;
        break;
      case 'v':
        flag->optionv = true;
        break;
      case 'c':
        flag->optionc = true;
        break;
      case 'l':
        flag->optionl = true;
        break;
      case 'n':
        flag->optionn = true;
        break;
      case 'h':
        flag->optionh = true;
        break;
      case 's':
        flag->options = true;
        break;
      case 'f':
        (*fparam)[*fcounter] =
            (char *)malloc((strlen(optarg) + 1) * sizeof(char));
        strcpy((*fparam)[*fcounter], optarg);
        *fcounter += 1;
        flag->optionf = true;
        break;
      case 'o':
        flag->optiono = true;
        break;
      default:
        break;
    }
  }
  *value_optind = optind;
}

int stupidmatch(char *string, char *pattern, flags flag, int filecounter,
                char *argv[], int value_optind, int counterstringsN) {
  regex_t re;
  regmatch_t pm[5];
  int offset = 0;
  int status;
  int temp = 1;
  char *newStr = (char *)malloc(strlen(string) + 1);
  char *newPat = (char *)malloc(strlen(pattern) + 1);
  strcpy(newStr, string);
  strcpy(newPat, pattern);
  if (flag.optioni) {
    for (int i = 0; newStr[i]; i++) {
      newStr[i] = tolower(newStr[i]);
    }
    for (int i = 0; newPat[i]; i++) {
      newPat[i] = tolower(newPat[i]);
    }
  }
  if ((status = regcomp(&re, newPat, REG_EXTENDED)) != 0) {
    free(newPat);
    free(newStr);
    regfree(&re);
    return (status);
  }
  if (flag.optiono && !flag.optionv) {
    while ((status = regexec(&re, string + offset, 1, pm, 0)) == 0) {
      if (filecounter > 1 && !flag.optionh) printf("%s:", argv[value_optind]);
      if (flag.optionn) {
        printf("%d:", counterstringsN);
      }
      temp = 0;
      if (!flag.optionc) {
        printf("%.*s\n", (int)(pm[0].rm_eo - pm[0].rm_so),
               string + offset + pm[0].rm_so);
      }
      offset += pm[0].rm_eo;
    }
  } else
    status = regexec(&re, newStr, 0, pm, 0);
  free(newPat);
  free(newStr);
  regfree(&re);
  if (flag.optiono) status = temp;
  return status;
}

int printfEF(int ecounter, int fcounter, char *string, char **patterne,
             char **patternf, flags flag, char *argv[], int value_optind,
             int filecounter, int counterstringsN, int counterstringsC,
             int *newfile) {
  int status = 1;
  int EFflag = 1;
  for (int j = 0; j < ecounter; j++) {
    status = stupidmatch(string, patterne[j], flag, filecounter, argv,
                         value_optind, counterstringsN);
    if (status == 0) {
      EFflag = 0;
      counterstringsC++;
    }
  }
  for (int j = 0; j < fcounter; j++) {
    status = stupidmatch(string, patternf[j], flag, filecounter, argv,
                         value_optind, counterstringsN);
    if (status == 0) {
      if (EFflag == 1) counterstringsC++;
      EFflag = 0;
    }
  }
  if (flag.optionv) EFflag = (EFflag == 0) ? 1 : 0;
  if (string[strlen(string) - 1] == '\n') string[strlen(string) - 1] = '\0';
  if (!(flag.optionc || flag.optionl || flag.optiono)) {
    if (EFflag == 0) {
      if (filecounter > 1 && !flag.optionh) printf("%s:", argv[value_optind]);
      if (flag.optionn) {
        printf("%d:%s\n", counterstringsN, string);
      } else
        printf("%s\n", string);
    }
  }
  if (flag.optionl && EFflag == 0 && *newfile == 0) {
    printf("%s\n", argv[value_optind]);
    *newfile = 1;
  }
  return counterstringsC;
}

int printfE(int counterstringsC, int counterstringsN, int ecounter,
            char *string, char **patterne, flags flag, int filecounter,
            char *argv[], int value_optind, int *newfile) {
  int eflag = 1;
  int status = 1;
  for (int j = 0; j < ecounter; j++) {
    status = stupidmatch(string, patterne[j], flag, filecounter, argv,
                         value_optind, counterstringsN);
    if (status == 0) {
      eflag = 0;
      counterstringsC++;
    }
  }
  if (flag.optionv) eflag = (eflag == 0) ? 1 : 0;
  size_t strlength = strlen(string);
  if (string[strlength - 1] == '\n') {
    string[strlength - 1] = '\0';
  }
  if (!(flag.optionc || flag.optionl || flag.optiono)) {
    if (eflag == 0) {
      if (filecounter > 1 && !flag.optionh) printf("%s:", argv[value_optind]);
      if (flag.optionn) {
        printf("%d:%s\n", counterstringsN, string);
      } else
        printf("%s\n", string);
    }
  }

  if (flag.optionl && eflag == 0 && *newfile == 0) {
    printf("%s\n", argv[value_optind]);
    *newfile = 1;
  }
  return counterstringsC;
}

int printfF(int counterstringsC, int counterstringsN, char *string,
            char **patternf, flags flag, int filecounter, char *argv[],
            int value_optind, int EFcounter, int *newfile) {
  int status = 1;
  int fflag = 1;
  for (int j = 0; j < EFcounter; j++) {
    status = stupidmatch(string, patternf[j], flag, filecounter, argv,
                         value_optind, counterstringsN);
    if (status == 0) {
      fflag = 0;
      counterstringsC++;
    }
  }
  if (flag.optionv) fflag = (fflag == 0) ? 1 : 0;
  if (!(flag.optionc || flag.optionl || flag.optiono)) {
    if (fflag == 0) {
      size_t strlength = strlen(string);
      if (string[strlength - 1] == '\n') {
        string[strlength - 1] = '\0';
      }
      if (filecounter > 1 && !flag.optionh) printf("%s:", argv[value_optind]);
      if (flag.optionn) {
        printf("%d:", counterstringsN);
      }
      printf("%s\n", string);
    }
  }
  if (flag.optionl && fflag == 0 && *newfile == 0) {
    printf("%s\n", argv[value_optind]);
    *newfile = 1;
  }
  return counterstringsC;
}

int defaultprintf(char *string, char *pattern, flags flag, int filecounter,
                  char *argv[], int value_optind, int counterstringsN,
                  int counterstringsC, int *newfile) {
  int status = 1;
  status = stupidmatch(string, pattern, flag, filecounter, argv, value_optind,
                       counterstringsN);
  if (flag.optionv) status = (status == 0) ? 1 : 0;
  if (string[strlen(string) - 1] == '\n') string[strlen(string) - 1] = '\0';
  if (status == 0) {
    if (!(flag.optionc || flag.optionl || flag.optiono)) {
      if (filecounter > 1 && !flag.optionh) printf("%s:", argv[value_optind]);
      if (flag.optionn) {
        printf("%d:", counterstringsN);
      }
      printf("%s\n", string);
    }
    counterstringsC++;
  }
  if (flag.optionl && status == 0 && *newfile == 0) {
    printf("%s\n", argv[value_optind]);
    *newfile = 1;
  }
  return counterstringsC;
}