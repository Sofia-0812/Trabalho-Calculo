#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int ler_quant_monomios();
void ler_coef_e_exp(int coeficientes[], int expoentes[], int n);
void derivar(int coef_derivada[], int exp_derivada[], int coeficientes[], int expoentes[], int n);
void escrever_funcao(int coeficientes[], int expoentes[], int n);
void escrever_derivada(int coef_derivada[], int exp_derivada[], int n);
bool deseja();
float calcula_valor_funcional(float a, int coef[], int exp[], int n);
void calcula_equacao_tangente(float a, int coeficientes[], int expoentes[], int n, int coef_derivada[], int exp_derivada[] );
void escreve_funcional(float resultadoF, float resultadoD, float a);

int main()
{
    bool repetir = false;
    do {
        system("cls");
        int numero_monomios = ler_quant_monomios();
        int coeficientes[numero_monomios];
        int expoentes[numero_monomios];
        ler_coef_e_exp(coeficientes, expoentes, numero_monomios);
        int coef_derivada[numero_monomios];
        int exp_derivada[numero_monomios];
        derivar(coef_derivada, exp_derivada, coeficientes, expoentes, numero_monomios);
        system("cls");// isso � pra limpar a tela em Windows, j� system("clear") � para limpar a tela em sistemas baseados em Unix (como Linux e macOS)
        escrever_funcao(coeficientes, expoentes, numero_monomios);
        escrever_derivada(coef_derivada, exp_derivada, numero_monomios);
        printf("\n\nDeseja calcular valor funcional?[S/N]: ");
        bool resposta = deseja();
        float a;
        float resultadoF;
        float resultadoD;
        bool fez = false;
        if(resposta)
        {
            printf("\nQual eh o valor de a?: ");
            scanf("%f", &a);
            resultadoF = calcula_valor_funcional(a, coeficientes, expoentes, numero_monomios);
            resultadoD = calcula_valor_funcional(a, coef_derivada, exp_derivada, numero_monomios);
            fez = true;
            system("cls");
            escrever_funcao(coeficientes, expoentes, numero_monomios);
            escrever_derivada(coef_derivada, exp_derivada, numero_monomios);
            escreve_funcional(resultadoF, resultadoD, a);
        }
        printf("\nDeseja calcular a equacao da reta tangente ao grafico de f no ponto P(a, f(a))?[S/N]: ");
        resposta = deseja();
        float a2;
        if(resposta)
        {
            printf("\nQual eh o valor de a?: ");
            scanf("%f", &a2);
            system("cls");
            escrever_funcao(coeficientes, expoentes, numero_monomios);
            escrever_derivada(coef_derivada, exp_derivada, numero_monomios);
            if(fez)escreve_funcional(resultadoF, resultadoD, a);
            calcula_equacao_tangente(a2, coeficientes, expoentes, numero_monomios, coef_derivada, exp_derivada);
        }
        repetir = false;
        printf("\nDeseja entrar com outra funcao polinomial?[S/N]: ");
        repetir = deseja();
    } while(repetir);
}
int ler_quant_monomios()
{
    int n;
    bool erro;
    do{
        printf("Digite quantos monomios tera seu polinomio: ");
        scanf("%d", &n);
        erro = n <= 0;
        if(erro) printf("\nValor invalido, digite um numero natural\n\n");
    }while(erro);
    return n;
}
void ler_coef_e_exp(int coeficientes[], int expoentes[], int n)
{
    bool erro;
    for(int i = 0; i < n; i++){
        do{
            printf("\nDigite o coeficiente do %d.o monomio: ", i+1);
            scanf("%d", &coeficientes[i]);
            erro = coeficientes[i] == 0;
            if(erro) printf("\nO coeficiente nao pode ser 0, pois nao existiria esse monomio. Tente novamente\n");
        }while(erro);
        printf("\nDigite o expoente do %d.o monomio: ", i+1);
        scanf("%d", &expoentes[i]);
    }
}
void derivar(int coef_derivada[], int exp_derivada[], int coeficientes[], int expoentes[], int n)
{
    for(int i = 0; i < n; i++){
        coef_derivada[i] = coeficientes[i] * expoentes[i];
        exp_derivada[i] = expoentes[i] - 1;
    }
}
void escrever_funcao(int coeficientes[], int expoentes[], int n)
{
    printf("\nf(x) = ");

    //escrever coeficiente i=0
    if(coeficientes[0] != 1)
    {
        if(coeficientes[0] == -1) printf("-");
        else printf("%d", coeficientes[0]);
    }

    //escrever expoente i = 0
    if(expoentes[0] == 1) printf("x ");
    else if(expoentes[0] == 0 && (coeficientes[0] == 1 || coeficientes[0] == -1)) printf("1 ");
    else if(expoentes[0] == 0)printf(" ");
    else printf("x^%d ", expoentes[0]);

    for(int i = 1; i < n; i++){
        //escrever coeficiente i > 0
        if(coeficientes[i] == 1) printf("+ ");
        else if(coeficientes[i] == -1) printf("- ");
        else if(coeficientes[i] < 0){
            printf("- %d", -coeficientes[i]);
        }
        else printf("+ %d", coeficientes[i]);

        //escrever expoente i > 0
        if(expoentes[i] == 1) printf("x ");
        else if(expoentes[i] == 0 && (coeficientes[i] == 1 || coeficientes[i] == -1)) printf("1 ");
        else if(expoentes[i] == 0)printf(" ");
        else printf("x^%d ", expoentes[i]);
    }
}
void escrever_derivada(int coef_derivada[], int exp_derivada[], int n)
{
    printf("\n\nf`(x) = ");
    if(coef_derivada[0] == 0 && n == 1) printf("0");
    else if (coef_derivada[0] != 0)
    {
        //escrever coeficiente i=0
        if(coef_derivada[0] != 1)
        {
            if(coef_derivada[0] == -1) printf("-");
            else printf("%d", coef_derivada[0]);
        }

        //escrever expoente i=0
        if(exp_derivada[0] == 1) printf("x ");
        else if(exp_derivada[0] == 0 && (coef_derivada[0] == 1 || coef_derivada[0] == -1)) printf("1 ");
        else if(exp_derivada[0] == 0)printf(" ");
        else printf("x^%d ", exp_derivada[0]);
    }

    for(int i = 1; i < n; i++)
    {
        bool todosAnterioresZero = true;
        for(int x = 1; x <= i; x++)
        {
            if(coef_derivada[i - x] != 0) todosAnterioresZero = false;
        }

        //escrever coeficientes i > 0
        if(coef_derivada[i] != 0)
        {
            if(todosAnterioresZero)
            {
                if(coef_derivada[i] != 1)
                {
                    if(coef_derivada[i] == -1) printf("-");
                    else printf("%d", coef_derivada[i]);
                }

            }
            else
            {
                if(coef_derivada[i] == 1) printf("+ ");
                else if(coef_derivada[i] == -1) printf("- ");
                else if(coef_derivada[i] < 0){
                    printf("- %d", -coef_derivada[i]);
                }
                else if (coef_derivada[i] > 0) printf("+ %d", coef_derivada[i]);

            }

            //escrever expoente i > 0
            if(exp_derivada[i] == 1) printf("x ");
            else if(exp_derivada[i] == 0 && (coef_derivada[i] == 1 || coef_derivada[i] == -1)) printf("1 ");
            else if(exp_derivada[i] == 0) printf(" ");
            else printf("x^%d ", exp_derivada[i]);
        }

    }
}
bool deseja()
{
    char desejo;
    bool resposta = false;
    bool erro;
    do
    {
        scanf(" %c", &desejo);
        erro = desejo != 'S' && desejo != 'N' && desejo != 's' && desejo != 'n';
        if(erro) printf("\nO valor digitado eh invalido, favor entrar com um valor valido [S/N]: ");
    }while(erro);
    if(desejo == 'S' || desejo == 's')
    {
        resposta = true;
    }
    return resposta;

}
float calcula_valor_funcional(float a, int coef[], int exp[], int n)
{
    float resultado = 0;
    for(int i = 0; i < n; i++)
    {
        resultado = resultado + (pow(a, exp[i]) * coef[i]);
    }

    return resultado;
}
void escreve_funcional(float resultadoF, float resultadoD, float a)
{
    printf("\n\na = %.2f   ",a);
    printf("f(%.2f) = %.2f   ",a, resultadoF);
    printf("f'(%.2f) = %.2f   ", a, resultadoD);
    printf("P(%.2f,%.2f)\n", a, resultadoF);
}
void calcula_equacao_tangente(float a, int coeficientes[], int expoentes[], int n, int coef_derivada[], int exp_derivada[] )
{
    float m = calcula_valor_funcional(a, coef_derivada, exp_derivada, n);
    float y = calcula_valor_funcional(a, coeficientes, expoentes, n);

    float b = y - m*a;

    printf("\n\nA equacao da reta tangente ao grafico de f no ponto P(%.2f, %.2f) eh y = ", a, y);

    if (m != 0) {
        if (m == 1) {
            printf("x");
        } else if (m == -1) {
            printf("-x");
        } else {
            printf("%.2fx", m);
        }

        if (b > 0) {
            printf(" + %.2f", b);
        } else if (b < 0) {
            printf(" - %.2f", -b);
        }
    } else {
        printf("%.2f", b);
    }

    printf("\n\n");
}



