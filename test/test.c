int add(int a, int b);
int add(int a, int b) {
    return a + b;
}

struct A {};

void foo(struct A arg) {}

char* join(char* strs[]) {
    return *strs;
}
