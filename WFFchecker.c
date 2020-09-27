#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

int defType(char *Char)
{

    if (isupper(Char[0]))
        return 0;

    if (Char[0] == '^')
        return 1;

    if (Char[0] == '<')
    {
        if (Char[1] == '>')
            return 11;
        return -11;
    }

    if (Char[0] == '|')
    {
        if (Char[1] == '|')
            return 12;
        return -12;
    }

    if (Char[0] == '&')
    {
        if (Char[1] == '&')
            return 13;
        return -14;
    }

    if (Char[0] == '-')
    {
        if (Char[1] == '>')
            return 14;
        return -14;
    }

    if (Char[0] == '!')
        return 2;

    if (Char[0] == '0' || Char[0] == '1')
        return 3;

    if (Char[0] == '(')
        return 4;

    if (Char[0] == ')')
        return 5;

    return -2;
}

int verification(char *entrada)
{
    /*
    -1 = initial
    0 = P
    1 = -> <> && ||
    2 = ! 
    3 = 0 1
    4 = (
    5 = )
    */
    //char Char;
    int Pstate = -1;
    int state;
    int i = 0;
    int ParenCounter = 0;
    do
    {

        state = defType(&entrada[i]);
        //caso de conectivos incompletos ou invalidos
        if (state < -10)
        {
            printf("Conectivo incompleto ou inválido\n-->pos=%d caractere=%c%c\n", i, entrada[i], entrada[i + 1]);
            return 1;
        }
        //caso de conectivos
        if (state > 10)
        {
            i ++;
            state = 1;
        }
        

        switch (Pstate)
        {

        case -1: //Primeiro caractere
            if (state == 2 || state == 0 || state == 3)
                break;
            printf("Primeiro caractere invalido\n-->pos=%d caractere=%c\n", i, entrada[i]);
            return 0;
            //break;

        case 0: //caso de Símbolos proposicionais
            if (state == 1 || state == 5)
                break;
            printf("Não é um conectivo proposicional \n-->pos=%d caractere=%c\n", i, entrada[i]);
            return 0;
            //break;

        case 1: //caso de Conectivos proposicionais
            if (state == 4 || state == 0 || state == 1 || state == 3 || state == 2)
                break;
            printf("Esse caractere não é valido apos um conectivo \n-->pos=%d caractere=%c\n", i, entrada[i]);
            return 0;
            //break;

        case 2: //caso negação
            if (state == 0 || state == 4 || state == 2 || state == 3)
                break;
            printf("Esse caractere não é válido após uma negação \n-->pos=%d caractere=%c\n", i, entrada[i]);
            return 0;
            //break;

        case 3: //caso de true/false
            if (state == 1)
                break;
            printf("Não é um conectivo proposicional\n-->pos=%d caractere=%c\n", i, entrada[i]);
            return 0;
            //break;

        case 4: //abrir parenteses
            if (state == 0 || state == 2 || state == 4 || state == 3)
                break;
            printf("Esse caractere não é válido após parenteses\n-->pos=%d caractere=%c\n", i, entrada[i]);
            return 0;
            //break;

        case 5: //fechar parenteses
            if (state == 1 || state == 5)
                break;
            printf("Esse caractere não é válido após fechamentos de parentese\n-->pos=%d caractere=%c\n", i, entrada[i]);
            return 0;
            //break;

        default:
            break;
        }
        if(state == 5)
            ParenCounter--;
        if(state == 4)
            ParenCounter++;
        Pstate = state;
        i++;
    } while (entrada[i]);
    if (ParenCounter > 0)
    {
        if (ParenCounter == 1)
        {
            printf("existe um parentese aberto sem estar fechado\n");
            return 0;
        }
        printf("existem parenteses abertos sem estarem fechados\n");
        return 0;
    }

    return 1;
}

int main()
{
    
    char entrada[100];
    
    printf("Insira a expressão:\n--> ");
    scanf("%s", entrada);
    if (verification(entrada))
        printf("\nSua expressão é uma expressão lógica\n");

    printf("\n--> %s", entrada);
    return 0;
}
