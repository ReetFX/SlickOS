#include <stdio.h>
#include <kernel/tty.h>
#include <kernel/keyboard.h>

void kernel_main(void) {
    terminal_initialize();
    printf("SlickOS - Fast, Secure, Lightweight\n");
    printf("Click TAB key for program list\n");
    printf("root>$\n");
}
