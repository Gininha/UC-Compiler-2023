int variavel_global_memo_a_bacans = 30;

void funcao_bueda_fixe(void) {
    int i = 0;

    while (i < 10) {
        if (i == 10) {
            putchar('s');
        }
        if (i >= 9) {
            putchar('k');
        }
        if (i > 8) {
            putchar('l');
        }
        if (i != 7) {
            putchar('p');
        }
        if (i < 6) {
            putchar('u');
        }
        if (i <= 5) {
            putchar('l');
        }
        i = i + 1;
    }
    putchar('\n');
}

void testezito(void) {
    char b = 'b';
    putchar(b);
    char d = b + 10;
    putchar(d);
    putchar('\n');
}

int teste_c(int x, int y) {
    int res = x + y;

    return res;
}

int somaarg(int x) {
    x = x + 1;

    return x;
}

int sus(int x) {
    return x + 1;
}

int main(void) {

    int a = 10;
    int b = 0;

    funcao_bueda_fixe();
    testezito();
    b = teste_c(a, 10);

    putchar(sus(50));

    putchar(b);
}