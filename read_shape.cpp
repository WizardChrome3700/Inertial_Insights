#include <stdio.h>
#include <stdlib.h>
#include <cmath>

int main() {
    FILE* f;
    f = fopen("shape.txt","r");
    char shapeChar[10];
    int edgeCount;
    int paramCount = 0;
    int* paramXmin;
    int* paramXmax;

    int* paramYmin;
    int* paramYmax;

    int* paramZmin;
    int* paramZmax;

    int axisCount = 0;
    for(char c = fgetc(f); !feof(f);) {
        if(paramCount == 0) {
            int count = 0;
            while(c!=';') {
                shapeChar[count] = c;
                count++;
                c = fgetc(f);
            }
            shapeChar[count] = '\0';
            edgeCount = 0;
            for(int i = 0; shapeChar[i] != '\0'; i++) {
                edgeCount = edgeCount + ((int)shapeChar[i] - 48)*((int)pow(10, 2 - (i+1)));
            }
            paramCount++;
            c = fgetc(f);
            c = fgetc(f);
            paramXmin = (int*)calloc(edgeCount, sizeof(int));
            paramXmax = (int*)calloc(edgeCount, sizeof(int));

            paramYmin = (int*)calloc(edgeCount, sizeof(int));
            paramYmax = (int*)calloc(edgeCount, sizeof(int));

            paramZmin = (int*)calloc(edgeCount, sizeof(int));
            paramZmax = (int*)calloc(edgeCount, sizeof(int));
        }
        else {
            int eleCount = 0;
            while(eleCount != 2) {
                int count = 0;
                c = fgetc(f);
                if(c == '\n') {
                    c = fgetc(f);
                    axisCount++;
                    if(axisCount > 2) {
                        axisCount = 0;
                    }
                }
                if(c == '\n') {
                    axisCount++;
                    if(axisCount > 2) {
                        axisCount = 0;
                    }
                }
                count = 0;
                while(c!=';') {
                    shapeChar[count] = c;
                    count++;
                    c = fgetc(f);
                }
                shapeChar[count] = '\0';
                if(shapeChar[0] == '-') {
                    int param = 0;c = fgetc(f);
                    count = 1;
                    while(shapeChar[count] != '\0') {
                        param -= ((int)shapeChar[count] - 48)*((int)pow(10, 3 - (count + 1)));
                        count++;
                    }
                    if(axisCount == 0) {
                        if(eleCount == 0) {
                            paramXmin[paramCount-1] = param;
                        }
                        else {
                            paramXmax[paramCount-1] = param;
                        }
                    }
                    if(axisCount == 1) {
                        if(eleCount == 0) {
                            paramYmin[paramCount-1] = param;
                        }
                        else {
                            paramYmax[paramCount-1] = param;
                        }
                    }
                    if(axisCount == 2) {
                        if(eleCount == 0) {
                            paramZmin[paramCount-1] = param;
                        }
                        else {
                            paramZmax[paramCount-1] = param;
                        }
                    }
                }
                else {
                    int param = 0;
                    count = 0;
                    while(shapeChar[count] != '\0') {
                        param += ((int)shapeChar[count] - 48)*((int)pow(10, 2 - (count + 1)));
                        count++;
                    }
                    if(axisCount == 0) {
                        if(eleCount == 0) {
                            paramXmin[paramCount-1] = param;
                        }
                        else {
                            paramXmax[paramCount-1] = param;
                        }
                    }
                    if(axisCount == 1) {
                        if(eleCount == 0) {
                            paramYmin[paramCount-1] = param;
                        }
                        else {
                            paramYmax[paramCount-1] = param;
                        }
                    }
                    if(axisCount == 2) {
                        if(eleCount == 0) {
                            paramZmin[paramCount-1] = param;
                        }
                        else {
                            paramZmax[paramCount-1] = param;
                        }
                    }
                }
                eleCount++;
            }
            axisCount++;
            if(axisCount == 3) {
                axisCount = 0;
                paramCount++;
                c = fgetc(f);
                c = fgetc(f);
            }
            else {
                c = fgetc(f);
            }
        }
    }
    fclose(f);
    printf("nEdges:\n%d\n", edgeCount);
    printf("xmax:\n");
    for(int i = 0; i < 12; i++) {
        printf("%d ", paramXmax[i]);
    }
    printf("\nxmin:\n");
    for(int i = 0; i < 12; i++) {
        printf("%d ", paramXmin[i]);
    }
    printf("\nymax:\n");
    for(int i = 0; i < 12; i++) {
        printf("%d ", paramYmax[i]);
    }
    printf("\nymin:\n");
    for(int i = 0; i < 12; i++) {
        printf("%d ", paramYmin[i]);
    }
    printf("\nzmax:\n");
    for(int i = 0; i < 12; i++) {
        printf("%d ", paramZmax[i]);
    }
    printf("\nzmin:\n");
    for(int i = 0; i < 12; i++) {
        printf("%d ", paramZmin[i]);
    }
    printf("\n");
    free(paramXmin);
    free(paramXmax);
    free(paramYmin);
    free(paramYmax);
    free(paramZmin);
    free(paramZmax);
    return 0;
}