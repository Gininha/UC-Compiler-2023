double kek = 0, kek_1 = 1.2;
int kappa = 75;
char u_know = 'p';
short w = 40;

void funcao_vazia(void){

}

double funcao_double(void){
    return 64.5;
}
int funcao_int(void){
    return 0;
}
char funcao_char(void){
    return 1;
}
short funcao_short(void){
    return 2;
}

void funcao_com_globais(void){
    putchar(w);
    putchar(u_know);
    putchar(kappa);
    int res_1 = kappa + w, res_2 = u_know + w-100, res_3 = kappa + u_know-100;
    putchar(res_1);
    putchar(res_2);
    putchar(res_3);

    double ala_u_akbar = kek + kek_1;
    putchar('\n');
}


int recursion(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * recursion(n - 1);
}

int main(void){
    double a = 0;
    double b = 0.2;

    double c;
    int d, e = 0;
    
    d = e+10;
    
    if(d < e)
        putchar('c');
    else{
        c = a + b;
        while(d){
            e = d +50;
            putchar(e);
            d = d-1;
        }
    }

    putchar('\n');

    funcao_com_globais();
    funcao_vazia();
    funcao_double();
    funcao_int();
    funcao_char();
    funcao_short();

    return  recursion(5);
}
