//Kacper Zimmer
#include <iostream>

using namespace std;





void Intersection(int set1[], int set2[], int result[]) {
    int i = 0;
    int j = 0;
    int pos = 0;
    bool check;

    while (set1[i] != -1) {
        j = 0;
        while (set2[j] != -1) {
            if (set1[i] == set2[j]) {
                check = true;
                break;
            }
            j++;
        }
        if (check) {
            result[pos] = set1[i];
            pos++;
            check = false;
        }
        i++;
    }

    result[pos] = -1;

    
    for (int v = 0; v < pos; v++) {
        for (int n = 0; n < pos; n++) {
            if (result[v] < result[n]) {
                int temp = result[n];
                result[n] = result[v];
                result[v] = temp;
            }
        }
    }
}

void Symmetric(int set1[], int set2[], int result[]) {
    int i = 0, j = 0, pos = 0;
    bool check;
    
    while (set1[i] != -1) {
        check = false;
        j = 0;
        while (set2[j] != -1) {
            if (set1[i] == set2[j]) {
                check = true;
                break;
            }
            j++;
        }
        if (!check) {
            result[pos] = set1[i];
            pos++;
        }
        i++;
    }
    
    i = 0;
    while (set2[i] != -1) {
        check = false;
        j = 0;
        while (set1[j] != -1) {
            if (set2[i] == set1[j]) {
                check = true;
                break;
            }
            j++;
        }
        if (!check) {
            result[pos] = set2[i];
            pos++;
        }
        i++;
    }
    result[pos] = -1;
}


void Complement(int set[], int result[]){
    int i = 0;
    bool check;
    int pos = 0;
    const int universeEnd = 4095;
    int universeLim = universeEnd;

    
    while(set[i] != -1){
        i++;
    }

    
    while(universeLim >= 0){
        check = false;
        for(int j = 0; j < i; j++){
            if(set[j] == universeLim){
                check = true;
                break;
            }
        }
        if(!check){
            result[pos] = universeLim;
            pos++;
        }
        universeLim--;
    }

  

    
    result[universeEnd - i] = -1;
    
    for(int x = 0; x < universeEnd - i; x++){
        for(int j = 0; j < universeEnd - i; j++){
            if(result[x] < result[j]){
                int temp = result[x];
                result[x] = result[j];
                result[j] = temp;
            }
        }
    }
}


void Difference(int set1[], int set2[], int result[]) {
    // odjemna --> odjemnik [1,2,3,4,5] - [1,2,3] - > [4,5] +[-1]
    int x = 0;
    while (set2[x] != -1) {
        x++;
    }
    int pos = 0;
    bool check;
    for (int i = 0; set1[i] != -1; i++) {
        check = false;
        for (int j = 0; j < x; j++) {
            if (set2[j] == set1[i]) {
                check = true;
                break;
            }
        }
        if (!check) {
            result[pos] = set1[i];
            pos++;
        }
    }
   
    result[pos] = -1;
    
    for(int m = 0; m < pos; m++){
        for(int z = 0; z < pos; z++){
            if(result[m] < result[z]){
                int temp = result[z];
                result[z] = result[m];
                result[m] = temp;
                
            }
        }
    }
}


void Union(int set1[],int set2[],int result[]){
    bool check = true;
    int i = 0;
    while(set1[i] != -1){
        i++;
    }
    int j = 0;
    int pos = 0;
    
    for(int z = 0; z < i; z++){
        result[z] = set1[z];
    }
    
    
while(set2[j] != -1){
        
    for(int z = 0; z < i; z++){
        if(result[z] != set2[j]){
            check = true;
        } else {
            check = false;
            break;
        }
    }
        
    if(check){
        result[i + pos] = set2[j];
            pos++;
    }
        

    j++;
}
    int totalLength = pos + i;
    result[totalLength] = -1;
    
    
    for(int z = 0; z < totalLength ; z++){
        for(int x = 0; x < totalLength; x++){
            if(result[x] > result[z]){
                int temp = result[x];
                result[x] = result[z];
                result[z] = temp;
            }
        }
    }
    

}



void Create(int length, int set[], int finalSet[]){
    int counter = 0;
    bool check;
    for(int i = 0; i < length; i++){
        check = true;
        if(set[i] >= 1 && set[i] <= 4095){
            for(int j = 0; j < counter; j++){
                if(set[i] == finalSet[j]){
                    check = false;
                    break;
                }
            }
            if(check){
                finalSet[counter] = set[i];
                counter ++;
            }
        }
    }
    finalSet[counter] = -1;
    int len = 0;
    while(finalSet[len] != -1){
        len++;
    }
    
    for(int i = 0; i < len; i++){
        for(int j = 0; j < len; j++){
            if(finalSet[i] < finalSet[j]){
                int temp = finalSet[j];
                finalSet[j] = finalSet[i];
                finalSet[i] = temp;
                
            }
        }
    }
  
  
}




bool Subset(int set1[], int set2[]){
    
    //zawierany - > zawierajacy
    int i = 0;
    int j = 0;
    while(set1[i] != -1){
        i++;
    }

    while(set2[j] != -1){
        j++;
    }
    
    if(i > j){
        return false;
    }
     
    int counter = 0;
    
    for(int c = 0; c < i; c++){
        for(int z = 0; z < j; z++){
            if(set2[z] == set1[c]){
                counter ++;
            }
        }
    }
    
    if(counter == i){
        return true;
    }else{
        return false;
    }
    
    
}
bool Equal(int set1[],int set2[]){
    int i = 0;
    int j = 0;
    while(set1[i] != -1){
        i++;
    }
    while(set2[j] != -1){
        j++;
    }
    if(j != i){
        return false;
    }else{
        return Subset(set1,set2);
    }
    
    return true;
    
}


void MinMax(int tab[], int* min, int& max ){
    if(tab[0] != -1){
        int i = 0;
        
        while(tab[i] != -1){
            i++;
        }
        *min = tab[0];
        max = tab[0];
        for(int j = 0; j < i; j++){
            if(*min > tab[j]){
                *min = tab[j];
            }
            if(max < tab[j]){
                max = tab[j];
            }
        }
    }
}


void Cardinality(int tab[], int *powerSet){
    int i = 0;
    while(tab[i] != -1){
        i++;
    }
    *powerSet = i;
     
}

void Add(int value, int tab[]) {
    if(value >= 1 && value <= 4095){
        int i = 0;
        while (tab[i] != -1) {
            i++;
        }
        
        for (int j = 0; j < i; j++) {
            if (tab[j] == value) {
                return;
            }
        }
        
        tab[i] = value;
        tab[i + 1] = -1;
        i++;
        
        for(int l = 0; l < i; l++){
            for(int z = 0; z < i; z++){
                if(tab[l] < tab[z]){
                    int temp = tab[z];
                    tab[z] = tab[l];
                    tab[l] = temp;
                    
                }
            }
            
        }
    }

}

bool Element(int value, int tab[]){
    int i = 0;
    bool isThereValue = false;
    while(tab[i] != -1){
        i++;
    }
    for(int j = 0; j < i; j++){
        if(tab[j] == value){
            isThereValue = true;
        }
    }
    return isThereValue;
}

double Harmonic(int tab[]){
    if(tab[0] == -1){
        return 1;
    }
    double sum = 0.0;
    int i = 0;
    
    while(tab[i] != -1){
        i++;
    }
    
    for(int j = 0; j < i; j++){
        sum += 1.0 / tab[j];
    }
    return i / sum;
}


double Arithmetic(int tab[]){
    double result;;
    double sum = 0;
    int i = 0;
    if(tab[0] == -1){
        return 0;
    }
    while(tab[i] != -1){
        i += 1;
    }
    
    for(int j = 0; j < i; j++){
        sum += tab[j];
    }
    
    result = sum / i;
    return result;
}



bool Empty(int tab[]){
    if(tab[0] == - 1){
     return true;
    }else{
        return false;
    }
}


bool Nonempty(int tab[]){
    if(tab[0] == - 1){
     return false;
    }else{
        return true;
    }
}


void Properties(int set[],char operations[], double &avgValue,double* harmonicValue, int &minValue,int* maxValue,int &setPower){
    int i = 0;
    //void MinMax(int tab[], int* min, int& max ){
    while(operations[i] !=  '\0'){
        if(operations[i] == 'a'){
            avgValue = Arithmetic(set);
        }else if(operations[i] == 'h'){
            *harmonicValue = Harmonic(set);
        } else if (operations[i] == 'm'){
            MinMax(set,&minValue, *maxValue);
        } else if(operations[i] == 'c'){
           Cardinality(set, &setPower);
        }
        i++;
    }
    
    
}
