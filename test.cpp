#include <stdio.h>
#include <stdlib.h>
#include <string>

char* tainted_str() {
    char *buf = (char*)malloc(32);
    // gets(buf);
    return buf;
}

int tainted_int() {
    return strtoul(tainted_str(), NULL, 10);
}

void int_overflow() {
    int a = tainted_int();
    int b = 0;
    int c = a + b;

    a = 0;
    b = tainted_int();
    int d = a + b;
}

void int_truncation() {
    int a = tainted_int();
    short b = a;

    int c = tainted_int();
    int d = 0;
    short e = c + d;
}

void int_overflow_loop() {
    int a = 1;
    int i = 40;
    while (i--) {
        a += a;
    }
}

char* stack_return() {
    char foo[10];
    return foo;
}

void uncontrolled_malloc() {
    malloc(tainted_int());
}

void format_string() {
    char* format = "%x";
    printf(format);
}

void sprintf_return_val() {
    char buf[10];
    snprintf(buf, 5, "%s", "ABCDEFG");

    sprintf(buf, "%s", "ABCDEFG");
}

void my_system(std::string cmd) {
    system(cmd.c_str());
}

void my_system_char(const char* cmd) {
    system(cmd);
}

std::string get_user_input() {
    return "world'; ls -la; echo 'goodbye";
}

const char* get_user_input_char() {
    return "world'; ls -la; echo 'goodbye";
}

template<typename T>
void my_prop(T cmd) {
    my_system(cmd);
}

void my_prop_char(const char* cmd) {
    my_system_char(cmd);
}

int main() {
    // Not sure if this actually needs to be called to be detected?
    stack_return()[0];

    auto cmd = get_user_input();
    my_prop(cmd);

    auto cmd_char = get_user_input_char();
    my_prop(cmd_char);
    my_prop_char(cmd_char);
    // my_system_char(cmd_char);
}
