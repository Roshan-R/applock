#include <ctype.h>
#include <libconfig.h>
#include <openssl/sha.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "util.h"

int compare_hash(const unsigned char *input_password, char *config_sha) {
  unsigned char sha1[1024];
  SHA1(input_password, strlen((const char *)input_password), sha1);
  char tmp[1024];
  for (int i = 0, j = 0; i < 20; i++, j += 2)
    sprintf(&tmp[j], "%02x", (unsigned int)sha1[i]);
  printf("[calculate_hash] Calculated hash is : %s \n", tmp);
  return !strcmp(config_sha, tmp);
}

void read_config_file(struct Config *c) {
  config_t cfg;
  config_setting_t *setting;
  const char *str;

  config_init(&cfg);

  /* Read the file. If there is an error, report it and exit. */
  if (!config_read_file(&cfg, "/opt/applock/config")) {
    fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
            config_error_line(&cfg), config_error_text(&cfg));
    config_destroy(&cfg);
    return;
  }

  /* Get the password_hash string */
  if (config_lookup_string(&cfg, "password_hash", &str)) {
    strcpy(c->password_hash, str);
    printf("[config] Password hash: %s\n", c->password_hash);

  } else {
    fprintf(stderr, "No 'password_hash' setting in configuration file.\n");
  }
  /* get programs into Config struct varaible c */
  setting = config_lookup(&cfg, "programs");
  if (setting != NULL) {
    int count = config_setting_length(setting);
    printf("[config] Number of progams on config file : %d\n", count);
    int i;
    c->no_of_programs = count;
    for (i = 0; i < count; ++i) {
      strcpy(c->programs[i], config_setting_get_string_elem(setting, i));
      printf("[config] Program %d : %s\n", i, c->programs[i]);
    }

  } else {
    fprintf(stderr, "No 'programs' setting in configuration file.\n");
  }
}

int is_in_blocklist(char *cmdline, struct Config *c) {
  /* check whether the program is in the blocklist */

  char *program_name;
  program_name = (char *)malloc((100) * sizeof(char));
  program_name = strtok(cmdline, " ");
  for (int i = 0; i < c->no_of_programs; i++) {
    if (program_name) {
      if (strcmp(c->programs[i], program_name) == 0) {
        return 1;
      }
    }
  }
  return 0;
}

void lock_app(int pid, char *password_hash) {
  FILE *zenity;
  char answer[getpagesize()];

  printf("[lock_app] new process pid : %d\n", pid);

  kill(pid, SIGSTOP);

  if ((zenity = popen("zenity --title='applock' --password", "r")) != NULL) {

    fgets(answer, sizeof(answer), zenity);
    printf("[lock_app] entered password : %s", answer);

    // remove trailing newline charecter
    // https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input

    answer[strcspn(answer, "\n")] = 0;

    if (compare_hash(answer, password_hash)) {
      printf("[lock_app] authenticated successfully\n");
      kill(pid, SIGCONT);
    } else {
      printf("[lock_app] password_hash is wrong\n");
      kill(pid, SIGTERM);
    }
  }
}
