#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #include "cMatrix.h"
#include <cmath>

Uint32 color = 0xffffffff;
Uint32 bgColor = 0x00000000;

const float WindowWidth = 640;
const float WindowHeight = 480;
const float COORDINATE_SYS_OFFSET_X = WindowWidth/2;
const float COORDINATE_SYS_OFFSET_Y = WindowHeight/2;

const int pixelWidth = 5;
const int pixelHeight = 5;
const int pixelCount = 240;

typedef struct Matrix {
    int R;
    int C;
    float* grid;
} Matrix;

void initMatrix(Matrix* mat) {
    if((mat->R > 0) || (mat->C > 0)) {
        return;
    }
    do {
        printf("Enter number of rows: ");
        scanf("%d",&(mat->R));
        printf("Enter number of columns: ");
        scanf("%d",&(mat->C));
    } while(!((mat->R > 0) && (mat->C > 0)));

    mat->grid = (float*)calloc(mat->R*mat->C, sizeof(float));
}

void killMatrix(Matrix* mat) {
    if(((mat->R > 0) && (mat->C > 0))) {
        mat->R = 0;
        mat->C = 0;
        free(mat->grid);
    }
    else {
        return;
    }
}

void printMatrix(Matrix* mat) {
    for(int i = 0;i < mat->R*mat->C; i++) {
        printf("%f ", mat->grid[i]);
        if(i%mat->C == mat->C-1) {
            printf("\n");
        }
    }
}

void matrixEntry(Matrix* mat) {
    for(int i = 0;i < mat->R*mat->C; i++) {
        printf("ROW%d, COLUMN%d = ", i/mat->C, i%mat->C);
        scanf("%f", &mat->grid[i]);
    }
}

void IdentityMat(Matrix* mat, __uint8_t size) {
    mat->R = size;
    mat->C = size;
    mat->grid = (float*)calloc(mat->R*mat->C, sizeof(float));
    for(int i = 0;i < mat->R*mat->C; i++) {
        mat->grid[i*mat->C + i] = 1;
    }
}

void scale_matrix(Matrix* matAns, float scalar, Matrix mat) {
    matAns->R = mat.R;
    matAns->C = mat.C;
    matAns->grid = (float*)calloc(mat.R*mat.C, sizeof(float));
    for(int i = 0; i < mat.R; i++) {
        for(int j = 0; j < mat.C; j++) {
            matAns->grid[i*mat.C + j] = scalar*mat.grid[i*mat.C + j];
        }
    }
}

void addMatrices(Matrix* matAns, Matrix* mat1, Matrix* mat2) {
    if((mat1-> R == mat2->R) && (mat1->C == mat2->C)) {
        matAns->R = mat1->R;
        matAns->C = mat1->C;
        matAns->grid = (float*)calloc(matAns->R*matAns->C, sizeof(float));
        for(int i = 0;i < matAns->R*matAns->C; i++) {
            matAns->grid[i] = mat1->grid[i] + mat2->grid[i];
        }
    }
    else if((mat1-> R == 0) || (mat1->C == 0)) {
        printf("mat1 not initialised.\n");
    }
    else if((mat2-> R == 0) || (mat2->C == 0)) {
        printf("mat2 not initialised.\n");
    }
    else {
        printf("Size mismatch.\n");
    }
}

void subtractMatrices(Matrix* matAns, Matrix* mat1, Matrix* mat2) {
    if((mat1-> R == mat2->R) && (mat1->C == mat2->C)) {
        matAns->R = mat1->R;
        matAns->C = mat1->C;
        matAns->grid = (float*)calloc(matAns->R*matAns->C, sizeof(float));
        for(int i = 0;i < matAns->R*matAns->C; i++) {
            matAns->grid[i] = mat1->grid[i] - mat2->grid[i];
        }
    }
    else if((mat1-> R == 0) || (mat1->C == 0)) {
        printf("mat1 not initialised.\n");
    }
    else if((mat2-> R == 0) || (mat2->C == 0)) {
        printf("mat2 not initialised.\n");
    }
    else {
        printf("Size mismatch.\n");
    }
}

void multiplyMatrices(Matrix* matAns, Matrix* mat1, Matrix* mat2) {
    if(mat1->C == mat2->R) {
        if((matAns->R != 0) && (matAns->C != 0)) {
            if((matAns->R != mat1->R) && (matAns->C != mat2->C)) {
                printf("Output matrix size doesn't match.");
                return;
            }
        }
        else {
            matAns->grid = (float*)calloc(matAns->R*matAns->C, sizeof(float));
        }
        matAns->R = mat1->R;
        matAns->C = mat2->C;
        Matrix mat3;
        mat3.R = mat1->R;
        mat3.C = mat2->C;
        mat3.grid = (float*)calloc(matAns->R*matAns->C, sizeof(float));
        for(int i = 0; i < mat3.R; i++) {
            for(int j = 0; j < mat3.C; j++) {
                for(int k = 0; k < mat1->C; k++) {
                    mat3.grid[(mat3.C)*i + j] += mat1->grid[k + (mat1->C)*i]*mat2->grid[(mat2->C)*k + j];
                }
                // printf("%f , %f*%f", mat3.grid[i*mat3.C + j], mat1->grid[i*mat3.C + j], mat2->grid[i*mat3.C + j]);
            }
            // printf("\n");
        }
        // printf("\nmat3:\n");
        // printMatrix(&mat3);
        for(int i = 0; i < mat3.R; i++) {
            for(int j = 0; j < mat3.C; j++) {
                matAns->grid[i*mat3.C + j] = mat3.grid[i*mat3.C + j];
            }
        }
        // printf("\nmatAns:\n");
        // printMatrix(matAns);
        killMatrix(&mat3);
    }
}

void rowEchleonUpper(Matrix* matAns, Matrix mat) {
    matAns->R = mat.R;
    matAns->C = mat.C;
    matAns->grid = (float*)calloc(mat.R*mat.C, sizeof(float));

    for(int i = 0; i < mat.R; i++) {
        for(int j = 0; j < mat.C; j++) {
            matAns->grid[i*mat.C + j] = mat.grid[i*mat.C + j];
        }
    }

    for(int i = 0; i < matAns->R; i++) {
        if(matAns->grid[i*matAns->C + i] == 0) {
            int rowExchangeFlag = 0;
            for(int j = i+1; j < matAns->R; j++) {
                if(matAns->grid[j*matAns->C + i] == 0) {
                    rowExchangeFlag = 0;
                    continue;
                }
                else {
                    for(int k = 0; k < matAns->C; k++) {
                        float temp = matAns->grid[j*matAns->C + k];
                        float temp2 = matAns->grid[i*matAns->C + k];
                        matAns->grid[j*matAns->C + k] = matAns->grid[i*matAns->C + k];
                        matAns->grid[i*matAns->C + k] = temp;
                    }
                    rowExchangeFlag = 1;
                    break;
                }
            }
            if(rowExchangeFlag == 0) {
                continue;
            }
            else {
                for(int j = i+1; j < matAns->R; j++) {
                    float ratio = matAns->grid[j*matAns->C + i]/matAns->grid[i*matAns->C + i];
                    for(int k = 0; k < matAns->C; k++) {
                        matAns->grid[j*matAns->C + k] = matAns->grid[j*matAns->C + k] - ratio*matAns->grid[i*matAns->C + k];
                    }
                }
            }
        }
        else {
            for(int j = i+1; j < matAns->R; j++) {
                float ratio = matAns->grid[j*matAns->C + i]/matAns->grid[i*matAns->C + i];
                for(int k = 0; k < matAns->C; k++) {
                    matAns->grid[j*matAns->C + k] = matAns->grid[j*matAns->C + k] - ratio*matAns->grid[i*matAns->C + k];
                }
            }
        }
    }
}

void rowEchleonLower(Matrix* matAns, Matrix mat) {
    matAns->R = mat.R;
    matAns->C = mat.C;
    matAns->grid = (float*)calloc(mat.R*mat.C, sizeof(float));
    
    for(int i = 0; i < mat.R; i++) {
        for(int j = 0; j < mat.C; j++) {
            matAns->grid[i*mat.C + j] = mat.grid[i*mat.C + j];
        }
    }

    for(int i = matAns->R - 1; i >= 0; i--) {
        if(matAns->grid[i*matAns->C + (matAns->C - (matAns->R - i))] == 0) {
            int rowExchangeFlag = 0;
            for(int j = i-1; j >= 0; j--) {
                if(matAns->grid[j*matAns->C + (matAns->C - (matAns->R - i))] == 0) {
                    rowExchangeFlag = 0;
                    continue;
                }
                else {
                    for(int k = 0; k < matAns->C; k++) {
                        float temp = matAns->grid[j*matAns->C + k];
                        float temp2 = matAns->grid[i*matAns->C + k];
                        matAns->grid[j*matAns->C + k] = matAns->grid[i*matAns->C + k];
                        matAns->grid[i*matAns->C + k] = temp;
                    }
                    rowExchangeFlag = 1;
                    break;
                }
            }
            if(rowExchangeFlag == 0) {
                continue;
            }
            else {
                for(int j = i-1; j >= 0; j--) {
                    float ratio = matAns->grid[j*matAns->C + (matAns->C - (matAns->R - i))]/matAns->grid[i*matAns->C + (matAns->C - (matAns->R - i))];
                    for(int k = 0; k < matAns->C; k++) {
                        matAns->grid[j*matAns->C + k] = matAns->grid[j*matAns->C + k] - ratio*matAns->grid[i*matAns->C + k];
                    }
                }
            }
        }
        else {
            for(int j = i-1; j >= 0; j--) {
                float ratio = matAns->grid[j*matAns->C + (matAns->C - (matAns->R - i))]/matAns->grid[i*matAns->C + (matAns->C - (matAns->R - i))];
                for(int k = 0; k < matAns->C; k++) {
                    printf("%f - %f*%f\n", matAns->grid[j*matAns->C + k], ratio, matAns->grid[i*matAns->C + k]);
                    matAns->grid[j*matAns->C + k] = matAns->grid[j*matAns->C + k] - ratio*matAns->grid[i*matAns->C + k];
                }
            }
        }
    }
}

int trace(float* sum, Matrix mat) {
    if((mat.R == mat.C ) && (mat.R > 0)) {
        *sum = 0;
        for(int i = 0; i < mat.R; i++) {
            *sum += mat.grid[i*mat.C + i];
        }
        return 1;
    }
    else {
        printf("Trace is not defined for non-sqaure matrices.\n");
        return 0;
    }
}

int determinant(float* det, Matrix mat) {
    if(mat.R == mat.C) {
        if(mat.R == 1) {
            *det = mat.grid[0];
            return 1;
        }
        else {
            Matrix matRowEchleon;
            rowEchleonLower(&matRowEchleon, mat);
            *det = 1;
            for(int i = 0; i < matRowEchleon.R; i++) {
                *det *= matRowEchleon.grid[i + i*matRowEchleon.C];
            }
            killMatrix(&matRowEchleon);
            return 1;
        }
    }
    else {
        printf("Determinant is not defined for non square matrix.\n");
        return 0;
    }
}

void inverse(Matrix* matAns, Matrix mat) {
    float det;
    if(determinant(&det, mat) && (det != 0)) {
        matAns->R = mat.R;
        matAns->C = mat.C;
        matAns->grid = (float*)calloc(mat.R*mat.C, sizeof(float));
        Matrix matAugmented;
        matAugmented.R = mat.R;
        matAugmented.C = mat.C*2;
        matAugmented.grid = (float*)calloc(2*mat.R*mat.C, sizeof(float));
        for(int i = 0; i < mat.R; i++) {
            for(int j = 0; j < 2*mat.C; j++) {
                if(j == i + mat.C) {
                    matAugmented.grid[i*2*mat.C + j] = 1;
                }
                else if(j < mat.C) {
                    matAugmented.grid[i*2*mat.C + j] = mat.grid[i*mat.C + j];
                }
            }
        }
        rowEchleonUpper(&matAugmented, matAugmented);
        for(int i = 0; i < matAugmented.R; i++) {
            for(int j = 0; j < mat.C; j++) {
                float temp = matAugmented.grid[i*2*mat.C + j];
                float temp2 = matAugmented.grid[i*2*mat.C + j + mat.C];
                matAugmented.grid[i*2*mat.C + j] = matAugmented.grid[i*2*mat.C + j + mat.C];
                matAugmented.grid[i*2*mat.C + j + mat.C] = temp;
            }
        }
        rowEchleonLower(&matAugmented, matAugmented);
        for(int i = 0; i < mat.R; i++) {
            for(int j = 0; j < matAugmented.C; j++) {
                matAugmented.grid[i*matAugmented.C + j] = matAugmented.grid[i*matAugmented.C + j]/matAugmented.grid[i*matAugmented.C + i + mat.C];
            }
        }
        for(int i = 0; i < matAns->R; i++) {
            for(int j = 0; j < matAns->C; j++) {
                matAns->grid[i*matAns->C + j] = matAugmented.grid[i*2*matAns->C + j];
            }
        }
        killMatrix(&matAugmented);
    }
    else {
        printf("Singular matrices are not invertible.\n");
    }
}

void char_poly(Matrix* matAns, Matrix mat) {
    if(mat.R == mat.C) {
        matAns->R = 1;
        matAns->C = mat.C + 1;
        matAns->grid = (float*)calloc(mat.C, sizeof(float));
        matAns->grid[0] = 1;
        Matrix Mi;
        Mi.R = mat.R;
        Mi.C = mat.C;
        Mi.grid = (float*)calloc(mat.R*mat.C, sizeof(float));
        for(int i = 0;i < Mi.R*Mi.C; i++) {
            printf("%f ", Mi.grid[i]);
            if(i%Mi.C == Mi.C-1) {
                printf("\n");
            }
        }
        Matrix In;
        IdentityMat(&In, mat.R);
        printf("\nIdentity matrix:\n");
        for(int i = 0;i < In.R*In.C; i++) {
            printf("%f ", In.grid[i]);
            if(i%In.C == In.C-1) {
                printf("\n");
            }
        }
        for(int i = 1; i < mat.C; i++) {
            Matrix product, product_trace;
            multiplyMatrices(&product, &Mi, &mat);
            printf("\nAMk-1:\n");
            for(int j = 0;j < product.R*product.C; j++) {
                printf("%f ", product.grid[j]);
                if(j%product.C == product.C-1) {
                    printf("\n");
                }
            }
            scale_matrix(&In, matAns->grid[i-1], In);
            printf("\nc(n-k+1)I:\n");
            for(int j = 0;j < In.R*In.C; j++) {
                printf("%f ", In.grid[j]);
                if(j%In.C == In.C-1) {
                    printf("\n");
                }
            }
            addMatrices(&Mi, &product, &In);
            printf("\nMk = AMk-1 + c(n-k+1)I:\n");
            for(int j = 0;j < Mi.R*Mi.C; j++) {
                printf("%f ", Mi.grid[j]);
                if(j%Mi.C == Mi.C-1) {
                    printf("\n");
                }
            }
            scale_matrix(&In, 1/matAns->grid[i-1], In);
            printf("\nc(n-k+1)I/c(n-k+1):\n");
            for(int j = 0;j < In.R*In.C; j++) {
                printf("%f ", In.grid[j]);
                if(j%In.C == In.C-1) {
                    printf("\n");
                }
            }
            printf("\nA:\n");
            for(int j = 0;j < mat.R*mat.C; j++) {
                printf("%f ", mat.grid[j]);
                if(j%mat.C == mat.C-1) {
                    printf("\n");
                }
            }
            printf("\nMk:\n");
            for(int j = 0;j < Mi.R*Mi.C; j++) {
                printf("%f ", Mi.grid[j]);
                if(j%Mi.C == Mi.C-1) {
                    printf("\n");
                }
            }
            multiplyMatrices(&product_trace, &Mi, &mat);
            printf("\nAMk:\n");
            for(int j = 0;j < Mi.R*Mi.C; j++) {
                printf("%f ", Mi.grid[j]);
                if(j%Mi.C == Mi.C-1) {
                    printf("\n");
                }
            }
            float trace_m;
            if(trace(&trace_m, product_trace) == 1) {
                matAns->grid[i] = (-1/((float)i))*(trace_m);
            };
            killMatrix(&product);
            killMatrix(&product_trace);
            printf("\ncn-k: %f\n", matAns->grid[i]);
        }
        // matAns->grid[matAns->C - 1]
        float det;
        determinant(&det, mat);
        matAns->grid[matAns->C - 1] = det;
    }
    else {
        printf("Characteristic polynomial is not defined for non-square matrices.\n");
    }
}

struct Point {
    Matrix Posvector;
};

struct Shape {
    Point* pointArray;
    int shapeX;
    int shapeY;
    int nEdges;
    float pitchAngle;
    float rollAngle;
    float yawAngle;
};

void init_shape(Shape* shape) {
    shape->shapeX = 0;
    shape->shapeY = 0;
    shape->pitchAngle = 0;
    shape->rollAngle = 0;
    shape->yawAngle = 0;
    shape->pointArray = (Point*)malloc(pixelCount*sizeof(Point));
    for(int i = 0; i < pixelCount; i++) {
        (shape->pointArray[i]).Posvector.R = 3;
        (shape->pointArray[i]).Posvector.C = 1;
        (shape->pointArray[i]).Posvector.grid = (float*)calloc(3, sizeof(float));
    }

    FILE* f;
    f = fopen("shape.txt","r");
    char shapeChar[10];
    int paramCount = 0;
    float* paramXmin;
    float* paramXmax;
    float* paramYmin;
    float* paramYmax;
    float* paramZmin;
    float* paramZmax;

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
            shape->nEdges = 0;
            for(int i = 0; shapeChar[i] != '\0'; i++) {
                shape->nEdges = shape->nEdges + ((int)shapeChar[i] - 48)*((int)pow(10, 2 - (i+1)));
            }
            paramCount++;
            c = fgetc(f);
            c = fgetc(f);
            paramXmin = (float*)calloc(shape->nEdges, sizeof(float));
            paramXmax = (float*)calloc(shape->nEdges, sizeof(float));

            paramYmin = (float*)calloc(shape->nEdges, sizeof(float));
            paramYmax = (float*)calloc(shape->nEdges, sizeof(float));

            paramZmin = (float*)calloc(shape->nEdges, sizeof(float));
            paramZmax = (float*)calloc(shape->nEdges, sizeof(float));
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
                    int param = 0;
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
    for(int i = 0; i < shape->nEdges; i++) {
        float xMin = paramXmin[i];
        float xMax = paramXmax[i];
        float yMin = paramYmin[i];
        float yMax = paramYmax[i];
        float zMin = paramZmin[i];
        float zMax = paramZmax[i];
        for(int j = 0; j < pixelCount/(shape->nEdges); j++) {
            shape->pointArray[i*(pixelCount/(shape->nEdges))+j].Posvector.grid[0] = xMin + ((xMax - xMin)/(pixelCount/(shape->nEdges)))*j;
            shape->pointArray[i*(pixelCount/(shape->nEdges))+j].Posvector.grid[1] = yMin + ((yMax - yMin)/(pixelCount/(shape->nEdges)))*j;
            shape->pointArray[i*(pixelCount/(shape->nEdges))+j].Posvector.grid[2] = zMin + ((zMax - zMin)/(pixelCount/(shape->nEdges)))*j;
            printf("Edge%d:\n",i+1);
            printf("Point%d: (%f, %f, %f)\n", i*(pixelCount/(shape->nEdges))+j, shape->pointArray[i*(pixelCount/(shape->nEdges))+j].Posvector.grid[0], shape->pointArray[i*(pixelCount/(shape->nEdges))+j].Posvector.grid[1], shape->pointArray[i*(pixelCount/(shape->nEdges))+j].Posvector.grid[2]);
        }
        // printf("\n");
    }
    free(paramXmin);
    free(paramXmax);
    free(paramYmin);
    free(paramYmax);
    free(paramZmin);
    free(paramZmax);
}


void DrawPixel(SDL_Surface* surface, float x, float y) {
    SDL_Rect rect = (SDL_Rect){(int)x , (int)y, pixelWidth, pixelHeight};
    SDL_FillRect(surface, &rect, color);
}

void DrawPoint(SDL_Surface* surface, struct Point point) {
    float x_2d = point.Posvector.grid[0] + COORDINATE_SYS_OFFSET_X;
    float y_2d = point.Posvector.grid[1] + COORDINATE_SYS_OFFSET_Y;
    DrawPixel(surface, x_2d, y_2d);
}

void DrawShape(SDL_Surface* surface, Shape* shape) {
    for(int i = 0; i < pixelCount; i++) {
        DrawPoint(surface, shape->pointArray[i]);
    }
}

void UpdateShape(Shape* shape, float pitch, float roll, float yaw) {
    Matrix pitchMatrix, rollMatrix, yawMatrix;
    pitchMatrix.R = 3;
    pitchMatrix.C = 3;
    pitchMatrix.grid = (float*)calloc(9, sizeof(float));
    pitchMatrix.grid[0] = 1;
    pitchMatrix.grid[4] = cos(pitch);
    pitchMatrix.grid[5] = -sin(pitch);
    pitchMatrix.grid[7] = sin(pitch);
    pitchMatrix.grid[8] = cos(pitch);
    // printf("\npitch matrix:\n");
    // printMatrix(&pitchMatrix);
    // printf("\n");

    rollMatrix.R = 3;
    rollMatrix.C = 3;
    rollMatrix.grid = (float*)calloc(9, sizeof(float));
    rollMatrix.grid[0] = cos(roll);
    rollMatrix.grid[2] = sin(roll);
    rollMatrix.grid[4] = 1;
    rollMatrix.grid[6] = -sin(roll);
    rollMatrix.grid[8] = cos(roll);

    yawMatrix.R = 3;
    yawMatrix.C = 3;
    yawMatrix.grid = (float*)calloc(9, sizeof(float));
    yawMatrix.grid[0] = cos(yaw);
    yawMatrix.grid[1] = -sin(yaw);
    yawMatrix.grid[3] = sin(yaw);
    yawMatrix.grid[4] = cos(yaw);
    yawMatrix.grid[8] = 1;

    // for(int i = 0; i < pixelCount; i++) {
    //     multiplyMatrices(&(shape->pointArray->Posvector), &pitchMatrix, &(shape->pointArray->Posvector));
    // }

    for(int i = 0; i < shape->nEdges; i++) {
        for(int j = 0; j < pixelCount/(shape->nEdges); j++) {
            // printf("Edge%d:\n",i+1);
            // printf("Point%d before: (%f, %f, %f)\n", i*(pixelCount/(shape->nEdges))+j, shape->pointArray[i*(pixelCount/(shape->nEdges))+j].Posvector.grid[0], shape->pointArray[i*(pixelCount/(shape->nEdges))+j].Posvector.grid[1], shape->pointArray[i*(pixelCount/(shape->nEdges))+j].Posvector.grid[2]);
            multiplyMatrices(&((shape->pointArray[i*(pixelCount/(shape->nEdges))+j]).Posvector), &pitchMatrix, &((shape->pointArray[i*(pixelCount/(shape->nEdges))+j]).Posvector));
            multiplyMatrices(&((shape->pointArray[i*(pixelCount/(shape->nEdges))+j]).Posvector), &rollMatrix, &((shape->pointArray[i*(pixelCount/(shape->nEdges))+j]).Posvector));
            multiplyMatrices(&((shape->pointArray[i*(pixelCount/(shape->nEdges))+j]).Posvector), &yawMatrix, &((shape->pointArray[i*(pixelCount/(shape->nEdges))+j]).Posvector));
            // printf("Point%d after: (%f, %f, %f)\n", i*(pixelCount/(shape->nEdges))+j, shape->pointArray[i*(pixelCount/(shape->nEdges))+j].Posvector.grid[0], shape->pointArray[i*(pixelCount/(shape->nEdges))+j].Posvector.grid[1], shape->pointArray[i*(pixelCount/(shape->nEdges))+j].Posvector.grid[2]);
        }
        // printf("\n");
    }
    printf("Roll angle: %f\n", shape->rollAngle);
    killMatrix(&pitchMatrix);
    killMatrix(&rollMatrix);
    killMatrix(&yawMatrix);
}

void killShape(Shape* shape) {
    for(int i = 0; i < pixelCount; i++) {
        killMatrix(&((shape->pointArray[i]).Posvector));
    }
    free(shape->pointArray);
}

int main() {
    // Matrix A;
    // A.R = 2;
    // A.C = 2;
    // A.grid = (float*)calloc(4, sizeof(float));
    // A.grid[0] = 1;
    // A.grid[1] = 2;
    // A.grid[2] = 3;
    // A.grid[3] = 4;
    // printf("A:\n");
    // printMatrix(&A);
    // printf("\n");
    // Matrix B;
    // B.R = 2;
    // B.C = 1;
    // B.grid = (float*)calloc(4, sizeof(float));
    // B.grid[0] = 1;
    // B.grid[1] = 2;
    // printf("B:\n");
    // printMatrix(&B);
    // printf("\n");
    // multiplyMatrices(&B, &A, &B);
    // printf("B:\n");
    // printMatrix(&B);
    // printf("\n");
    // killMatrix(&A);
    // killMatrix(&B);
    Uint32 t1,t2;
    float pitchRate = 0, rollRate = 0, yawRate = 0;
    Shape cube;
    init_shape(&cube);
    
    SDL_Window* window = SDL_CreateWindow("Cube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowWidth, WindowHeight, 0);
    if(window == NULL) {
        printf("Window not created. Error: %s.\n", SDL_GetError());
    }
    else {
        t1 = SDL_GetTicks();
        SDL_Surface* screen = SDL_GetWindowSurface(window);        
        DrawShape(screen, &cube);
        SDL_Event e;
        bool quit = false;
        while(!quit) {
            while(SDL_PollEvent(&e)) {
                if(e.type == SDL_QUIT) {
                    quit = true;
                }
            }
            UpdateShape(&cube, pitchRate, rollRate, yawRate);
            DrawShape(screen, &cube);
            SDL_UpdateWindowSurface(window);
            if(cube.pitchAngle < 1.57) {
                pitchRate = 0.01;
            }
            else {
                t2 = SDL_GetTicks();
                printf("time diff: %d\n", t2);
                pitchRate = 0;
                killShape(&cube);
                quit = true;
            }
            cube.pitchAngle += pitchRate;
            cube.rollAngle += rollRate;
            cube.yawAngle += yawRate;
            SDL_Delay(10);
            
            // printf("time diff: %ld\n", t2-t1);
            SDL_Rect rect = (SDL_Rect){0 , 0, (int)WindowWidth, (int)WindowHeight};
            SDL_FillRect(screen, &rect, bgColor);
        }
        killShape(&cube);
    }    
    SDL_Quit();
    return 0;
}