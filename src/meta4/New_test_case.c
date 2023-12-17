double a = 12.456;
int b = 14;
char z = 'n';

int par(int x){
    if( (x % 2) == 0)
        return 1;
    else
        return 0;
}

int main(void){
    int d;

    d = b + 51;

    int e = par(d);

    if(e)
        putchar('s');
    else
        putchar(z);
    
    putchar('\n');

    int x = 1, y = 0, z = 2;
    x = y - z;
    x = y / z;
    x = y * z;
    x = y + z;

    if(x || y){
        if(x && z){
            if(!y){
                putchar('y');
            }
        }
    }

    d, b, x;

    putchar('z');
    putchar('\n');
    return e;
}