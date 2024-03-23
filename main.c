#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main()
{
    float e1[4] =  {0.0,0.0,1.0,1.0};
    float e2[4] =  {0.0,1.0,0.0,1.0};
    float tg[4] =  {0.0,1.0,1.0,0.0};

    float w1[3][3];
    float w2[3][3];
    float nw1[3][3];
    float nw2[3][3];
    float I[3][3];
    float O[3][3];
    float erroi;
    float erroj;
    float delta;
    float erro;
    int i, j, l;
    int cs;
    int n;

    srand(time(NULL));

    w1[0][0]= (rand()/32767.0*40.0-20.0);
    w1[1][0]= (rand()/32767.0*40.0-20.0);
    w1[2][0]= (rand()/32767.0*40.0-20.0);

    w1[0][1]= (rand()/32767.0*40.0-20.0);
    w1[1][1]= (rand()/32767.0*40.0-20.0);
    w1[2][1]= (rand()/32767.0*40.0-20.0);

    w2[0][0]= (rand()/32767.0*40.0-20.0);
    w2[1][0]= (rand()/32767.0*40.0-20.0);
    w2[2][0]= (rand()/32767.0*40.0-20.0);

    for(cs=0; cs<4;cs++){

            I[0][0] = e1[cs];
            I[0][1] = e2[cs];
            I[0][2] = 1.0;

            O[0][0] = I[0][0];
            O[0][1] = I[0][1];
            O[0][2] = I[0][2];

            for(j = 0; j < 2; j++){
                I[1][j]=0.0;
                for(i = 0; i < 3; i++){
                    I[1][j] += w1[i][j]*O[0][i];
                }
                    O[1][j] = 1.0 / (1.0 + exp(-I[1][j]));
            }

            I[1][2] = 1.0;
            O[1][2] = I[1][2];

            for(l = 0; l < 1; l++){
                I[2][l] = 0.0;
                for(j = 0; j < 3; j++){
                    I[2][l] += w2[j][l]*O[1][j];
                }
                O[2][l] = 1.0 / (1.0 + exp(-I[2][l]));
            }
            erroi += (tg[cs]-O[2][0])*(tg[cs]-O[2][0]);
            erroi = erroi / 4.0;
            printf("Resultado: %f \n", erroj);
        }//fim for de CS

    do{
        nw1[0][0] = w1[0][0] + ((rand()%3 - 10)/10.0);
        nw1[1][0] = w1[1][0] + ((rand()%3 - 10)/10.0);
        nw1[2][0] = w1[2][0] + ((rand()%3 - 10)/10.0);

        nw1[0][1] = w1[0][1] + ((rand()%3 - 10)/10.0);
        nw1[1][1] = w1[1][1] + ((rand()%3 - 10)/10.0);
        nw1[2][1] = w1[2][1] + ((rand()%3 - 10)/10.0);

        nw2[0][0] = w2[0][0] + ((rand()%3 - 10)/10.0);
        nw2[1][0] = w2[1][0] + ((rand()%3 - 10)/10.0);
        nw2[2][0] = w2[2][0] + ((rand()%3 - 10)/10.0);

        //erro = 0.0;

        for(cs=0; cs<4;cs++){

            I[0][0] = e1[cs];
            I[0][1] = e2[cs];
            I[0][2] = 1.0;

            O[0][0] = I[0][0];
            O[0][1] = I[0][1];
            O[0][2] = I[0][2];

            for(j = 0; j < 2; j++){
                I[1][j]=0.0;
                for(i = 0; i < 3; i++){
                    I[1][j] += nw1[i][j]*O[0][i];
                }
                    O[1][j] = 1.0 / (1.0 + exp(-I[1][j]));
            }

            I[1][2] = 1.0;
            O[1][2] = I[1][2];

            for(l = 0; l < 1; l++){
                I[2][l] = 0.0;
                for(j = 0; j < 3; j++){
                    I[2][l] += nw2[j][l]*O[1][j];
                }
                O[2][l] = 1.0 / (1.0 + exp(-I[2][l]));
            }
            erroj += (tg[cs]-O[2][0])*(tg[cs]-O[2][0]);
        }//fim for de CS

        erroj = erroj / 4.0;
        printf("Resultado: %f \n", erroj);

        delta = erroj - erroi;

        if(delta < 0){
            w1[0][0] = nw1[0][0];
            w1[1][0] = nw1[1][0];
            w1[2][0] = nw1[2][0];

            w1[0][1] = nw1[0][1];
            w1[1][1] = nw1[1][1];
            w1[2][1] = nw1[2][1];

            w2[0][0] = nw2[0][0];
            w2[1][0] = nw2[1][0];
            w2[2][0] = nw2[2][0];

            erroi = erroj;
        }
    }while(erro > 0.0001);

        for(j = 0; j < 2; j++){
            for(i = 0; i < 3; i++){
                printf("W1[%i][%i] = %f; \n", i, j, w1[i][j]);
            }
        }

        for(l = 0; l < 1; l++){
            for(j = 0; j < 3; j++){
                printf("W2[%i][%i] = %f; \n", j, l, w2[j][l]);
            }
        }

    return 0;
}
