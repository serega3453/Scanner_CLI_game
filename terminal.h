#ifndef TERMINAL_H
#define TERMINAL_H

void terminal_init(void);
void terminal_restore(void);
int terminal_getch(void);
void terminal_clear(void);

#endif