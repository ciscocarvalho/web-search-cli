#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_error(char *message) { fprintf(stderr, "Error: %s", message); }

int main(int argc, char *argv[]) {
  char *query = argv[1];
  char *browser = getenv("BROWSER");
  char *base_url = "https://google.com/search?q=%s";
  const int STR_PLACEHOLDER_LEN = 2;

  if (query == NULL) {
    print_error("No search query provided\n");
    return 1;
  }

  if (browser == NULL) {
    print_error("$BROWSER is not set\n");
    return 1;
  }

  char *full_url =
      malloc(strlen(base_url) + strlen(query) - STR_PLACEHOLDER_LEN + 1);

  if (full_url == NULL) {
    print_error("Failed to allocate memory for url\n");
    return 1;
  }

  int url_written_chars_amount = sprintf(full_url, base_url, query);

  if (url_written_chars_amount < 0) {
    print_error("Failed to build url\n");
    free(full_url);
    return 1;
  }

  char *command_format = "%s '%s'";
  char *command = malloc(strlen(command_format) - 2 * STR_PLACEHOLDER_LEN +
                         strlen(browser) + strlen(full_url) + 1);

  if (command == NULL) {
    print_error("Failed to allocate memory for command\n");
    free(full_url);
    return 1;
  }

  int command_written_chars_amount =
      sprintf(command, command_format, browser, full_url);

  if (command_written_chars_amount < 0) {
    print_error("Failed to build command\n");
    free(full_url);
    free(command);
    return 1;
  }

  system(command);

  free(full_url);
  free(command);

  return 0;
}
