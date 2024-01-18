//Kacper Zimmer
#include <iostream>
using namespace std;

long long int determinant(int A[][32], bool isOut[32], int n, int apexL)
{
    if (n == 1)
    {
        for (int i = 0; i < apexL; i++)
        {
            if (!isOut[i])
            {
                return A[0][i];
            }
        }
    }

    long long int sum = 0;
    int k = 0;
    if (n > 1)
    {
        for (int i = 0; i < apexL && k < n; i++)
        {
            if (isOut[i])
            {
                continue;
            }

            if (A[0][i] != 0)
            {
                isOut[i] = true;


                sum += A[0][i] * determinant(A + 1, isOut, n - 1, apexL) * (k % 2 == 0 ? 1 : -1);
                isOut[i] = false;
            }
            k++;
        }
    }
    return sum;
}

long long int bareiss(int matrix[][32], int size) {
    if (size <= 0) {
        return 0;
    }
    int sign = 1;

    for (int k = 0; k < size - 1; k++) {
        if (matrix[k][k] == 0) {
            long long int z = 0;
            for (z = k + 1; z < size; z++) {
                if (matrix[z][k] != 0) {
                    for (int j = 0; j < size; j++) {
                        int temp = matrix[z][j];
                        matrix[z][j] = matrix[k][j];
                        matrix[k][j] = temp;
                    }
                    sign = -sign;
                    break;
                }
            }
            if (z == size) {
                return 0;
            }
        }
        for (int i = k + 1; i < size; i++) {
            for (int j = k + 1; j < size; j++) {
                matrix[i][j] = matrix[k][k] * matrix[i][j] - matrix[i][k] * matrix[k][j];
                if (k != 0) {
                    matrix[i][j] /= matrix[k - 1][k - 1];
                }
            }
        }
    }

    long long int wyznacznik = sign * matrix[size - 1][size - 1];
    return wyznacznik;
}




int main(){
    int apexLenght = 0;
    int depth = 32;

    int dataCube[32][32][32];
    char choice = ' ';


    cin >> apexLenght;

    for(int i = 0; i < apexLenght; i++){
        for(int j = 0; j < apexLenght; j++){
            for(int c = 0; c < apexLenght; c++){
                cin >> dataCube[i][j][c];
            }
        }
    }


    while(choice != 'E'){
        cin >> choice;


        if(choice == 'C') {

            int suma = 0;
            int l = 0;
            int v = 0;
            int p = 0;
            int h = 0;
            int w = 0;
            int d = 0;

            cin >> l >> v >> p >> h >> w >> d;

            int newHeight = 0;
            int newWidth = 0;
            int newDepth = 0;

            if(v < (apexLenght /2)){
                newWidth = v;
                newWidth += w;


            }else {
                newWidth = v;
                newWidth -= w;
            }
            if(v > newWidth){
                int cur = v;
                v = newWidth;
                newWidth = cur;
            }

            if(l < (apexLenght / 2)){
                newHeight = l;
                newHeight += h;


            }
            else {
                newHeight = l;
                newHeight -= h;
            }
            if(l > newHeight){
                int cur = l;
                l = newHeight;
                newHeight = cur;
            }
            if(p < (apexLenght / 2) ){

                newDepth = p;
                newDepth += d;

            }else {
                newDepth = p;
                newDepth -= d;
            }
            if (p > newDepth) {
                int cur = p;
                p = newDepth;
                newDepth = cur;
            }







            for (int i = p; i <= newDepth; i++) {
                for (int j = l; j <= newHeight; j++) {
                    for (int c = v; c <= newWidth; c++) {
                        if (i >= 0 && i < apexLenght && j >= 0 && j < apexLenght && c >= 0 && c < apexLenght) {
                            suma += dataCube[i][j][c];
                        }
                    }
                }
            }


            cout << suma << endl;




        }else if(choice == 'T') {
            int l = 0;
            int v = 0;
            int p = 0;
            int e = 0;
            cin >> l >> v >> p >> e;

            int newHeight = 0;
            int newWidth = 0;
            int newDepth = 0;

            if (l < (apexLenght / 2)) {
                newHeight = l;
                newHeight += e;
            } else {
                newHeight = l;
                newHeight -= e;
            }

            if (l > newHeight) {
                int cur = l;
                l = newHeight;
                newHeight = cur;
            }

            if (v < (apexLenght / 2)) {
                newWidth = v;
                newWidth += e;
            } else {
                newWidth = v;
                newWidth -= e;
            }
            if (v > newWidth) {
                int cur = v;
                v = newWidth;
                newWidth = cur;
            }

            if (p < (apexLenght / 2)) {
                newDepth = p;
                newDepth += e;
            } else {
                newDepth = p;
                newDepth -= e;
            }
            if (p > newDepth) {
                int cur = p;
                p = newDepth;
                newDepth = cur;
            }


            int suma = 0;
            for (int i = p; i <= newDepth; i++) {
                for (int j = l; j <= newHeight; j++) {
                    for (int c = v; c <= newWidth; c++) {
                        if (i >= 0 && i < apexLenght && j >= 0 && j < apexLenght && c >= 0 && c < apexLenght) {
                            if ((i - p) + (j - l) + (c - v) <= e){
                                suma += dataCube[i][j][c];
                            }

                        }
                    }
                }
            }
            cout << suma << endl;




        }else if(choice == 'D') {
            int subMatrix[32][32];

            char where;

            int i = 0;

            cin >> where >> i;

            if(where == 'E'){
                break;
            }


            if (where == 'l') {
                for (int x = 0; x < apexLenght;  x++) {
                    for (int j = 0; j < apexLenght; j++) {
                        subMatrix[x][j] = dataCube[x][i][j];
                    }
                }

            } else if (where == 'v') {
                for (int x = 0; x < apexLenght; x++) {
                    for (int j = 0; j < apexLenght; j++) {
                        subMatrix[x][j] = dataCube[x][j][i];
                    }
                }
            } else if (where == 'p') {
                for (int x = 0; x < apexLenght; x++) {
                    for (int j = 0; j < apexLenght; j++) {
                        subMatrix[x][j] = dataCube[i][x][j];
                    }
                }
            } else if(where == 'E'){
                break;
            }
            bool isOut[32] = {};
            if(apexLenght > 10) {
                cout << bareiss(subMatrix, apexLenght) << endl;
            }else{
                cout << determinant(subMatrix, isOut, apexLenght, apexLenght) << endl;
            }

        }else if(choice == 'O'){
            int suma = 0;
            int l = 0;
            int v = 0;
            int p = 0;
            int r = 0;
            cin >> l >> v >> p >> r;
            int newHeight = 0;
            int newDepth = 0;
            int newWidth = 0;

            if(l < (apexLenght / 2)){
                newHeight = l;
                newHeight += r;
            }else{
                newHeight = l;
                newHeight -= r;
            }
            if (l > newHeight) {
                int cur = l;
                l = newHeight;
                newHeight = cur;
            }

            if(v < (apexLenght / 2)){
                newWidth = v;
                newWidth += r;

            }else{
                newWidth = v;
                newWidth -= r;
            }
            if (v > newWidth) {
                int cur = v;
                v = newWidth;
                newWidth = cur;
            }

            if(p < (apexLenght / 2)){
                newDepth = p;
                newDepth += r;

            }else{
                newDepth = p;
                newDepth -= r;
            }
            if (p > newDepth) {
                int cur = p;
                p = newDepth;
                newDepth = cur;
            }

            int sum = 0;


            for (int i = p; i <= newDepth; i++) {
                for (int j = l; j <= newHeight; j++) {
                    for (int c = v; c <= newWidth; c++) {
                        //sqrt((x2 - x1)^2 + (y2 - y1)^2 + (z2 - z1)^2) // wzor na odleglosc
                        if (i >= 0 && i < apexLenght && j >= 0 && j < apexLenght && c >= 0 && c < apexLenght) {
                            int distance = (i - p) * (i - p) + (j - l) * (j - l) + (c - v) * (c - v);


                            if (distance <= (r * r)) {
                                sum += dataCube[i][j][c];
                            }
                        }
                    }
                }
            }


            cout << sum << endl;

        }


    }


    return 0;
}