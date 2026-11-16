#include "sys.h"
#include <unistd.h>

int isTerminal() {
    return isatty(STDOUT_FILENO);
}
