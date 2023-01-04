#include<stdio.h>

void stage1(){
    printf("--\n");
}

void stage2(){
    for (int i = 0; i < 4; i++)
    {
        printf("|\n");
    }
    
    printf("--\n");
}

void stage3(){
    for (int i = 0; i < 6; i++)
    {
        printf("_");
    }
    printf("\n");

    for (int i = 0; i < 4; i++)
    {
        printf("|\n");
    }
    
    printf("--\n");
}

void stage4(){
    for (int i = 0; i < 6; i++)
    {
        printf("_");
    }
    printf("\n");
    
    printf("|/\n");
    for (int i = 0; i < 3; i++)
    {
        printf("|\n");
    }
    
    printf("--\n");
}

void stage5(){
    for (int i = 0; i < 6; i++)
    {
        printf("_");
    }
    printf("\n");
    
    printf("|/   |\n");
    for (int i = 0; i < 3; i++)
    {
        printf("|\n");
    }
    
    printf("--\n");
}

void stage6(){
    for (int i = 0; i < 6; i++)
    {
        printf("_");
    }
    printf("\n");
    
    printf("|/   |\n");
    printf("|    o\n");
    for (int i = 0; i < 2; i++)
    {
        printf("|\n");
    }
    
    printf("--\n");
}

void stage7(){
    for (int i = 0; i < 6; i++)
    {
        printf("_");
    }
    printf("\n");
    
    printf("|/   |\n");
    printf("|    o\n");
    printf("|    |\n");
    printf("|\n");

    
    printf("--\n");
}

void stage8(){
    for (int i = 0; i < 6; i++)
    {
        printf("_");
    }
    printf("\n");
    
    printf("|/   |\n");
    printf("|    o\n");
    printf("|   /|\n");
    printf("|\n");

    printf("--\n");
}

void stage9(){
    for (int i = 0; i < 6; i++)
    {
        printf("_");
    }
    printf("\n");
    
    printf("|/   |\n");
    printf("|    o\n");
    printf("|   /|\\\n");

    printf("|\n");
    printf("--\n");
}

void stage10(){
    for (int i = 0; i < 6; i++)
    {
        printf("_");
    }
    printf("\n");
    
    printf("|/   |\n");
    printf("|    o\n");
    printf("|   /|\\\n");
    printf("|   /\n");
    
    printf("--\n");
}

void stage11(){
    for (int i = 0; i < 6; i++)
    {
        printf("_");
    }
    printf("\n");
    
    printf("|/   |\n");
    printf("|    o\n");
    printf("|   /|\\\n");
    printf("|   / \\\n");
    
    printf("--\n");
}

void draw(int i){
    switch (i)
    {
    case 1:
        stage1();
        break;
    case 2:
        stage2();
        break;
    case 3:
        stage3();
        break;
    case 4:
        stage4();
        break;
    case 5:
        stage5();
        break;
    case 6:
        stage6();
        break;
    case 7:
        stage7();
        break;
    case 8:
        stage8();
        break;
    case 9:
        stage9();
        break;
    case 10:
        stage10();
        break;
    case 11:
        stage11();
        break;
    default:
        printf("No instructions for stage %d\n", i);
        break;
    }
}