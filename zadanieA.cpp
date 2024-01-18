//Kacper Zimmer
//Kacper Zimmer
#include <iostream>
using namespace std;



int main() {
    int size;
    int sesNum;
    char userChoice;
    int fragmentSize;
    int startingIndex;
    int shift;
    cin >> sesNum;
   
    while(sesNum > 0){
        cin >> size;
        
        if(size <= 0) return 0;
        int arr[size];
        
        int i = 0;
        while(i < size){
            cin >> arr[i];
            cout << arr[i] << " ";
            i++;
        }
        cout << endl;
        
        userChoice = ' ';
        while(userChoice != 'F'){
            cin >> userChoice;
            if(userChoice == 'S'){
                cin >> startingIndex >> fragmentSize;
        
                if (size != 0 && size != 1) {
                    
                    
                    if (fragmentSize == 0){
                        fragmentSize = 1;
                    }
                    
                    int TotalnumFragments = size / fragmentSize;
                    bool isPositive = true;
                    
                    
                    if (fragmentSize < 0) {
                        TotalnumFragments *= -1;
                        fragmentSize *= -1;
                        isPositive = false;
                    }
                    
                    
                    int remainingSize = size - TotalnumFragments * fragmentSize;
                    
                    if (startingIndex < 0) {
                        startingIndex = ((startingIndex + size) % size);
                        if (startingIndex < 0) {
                            startingIndex += size;
                        }
                    }
                    
                    
                    
                    int i = 0;
                    while (i < TotalnumFragments) {
                        int circularPosition = (startingIndex) % size;
                        int end = circularPosition + fragmentSize;
                                            
                        int j = circularPosition;
                        while (j < end) {
                            int z = circularPosition;
                            while (z < end) {
                                if (arr[j % size] < arr[z % size] && isPositive) {
                                    int temp = arr[j % size];
                                    arr[j % size] = arr[z % size];
                                    arr[z % size] = temp;
                                }
                                else if (arr[j % size] > arr[z % size] && !isPositive) {
                                    int temp = arr[j % size];
                                    arr[j % size] = arr[z % size];
                                    arr[z % size] = temp;
                                }
                                z++;
                            }
                            j++;
                        }
                        startingIndex += fragmentSize;
                        i++;
                    }

                    if (remainingSize > 0) {
                        int circularPosition = (startingIndex) % size;
                        int end = circularPosition + remainingSize;
                                            
                        int j = circularPosition;
                        while (j < end) {
                            int z = circularPosition;
                            while (z < end) {
                                if (arr[j % size] < arr[z % size] && isPositive) {
                                    int temp = arr[j % size];
                                    arr[j % size] = arr[z % size];
                                    arr[z % size] = temp;
                                }
                                else if (arr[j % size] > arr[z % size] && !isPositive) {
                                    int temp = arr[j % size];
                                    arr[j % size] = arr[z % size];
                                    arr[z % size] = temp;
                                }
                                z++;
                            }
                            j++;
                        }
                    }

                }
       
            }
            
            else if(userChoice == 'R'){
                cin >> startingIndex >> fragmentSize;
                   if (fragmentSize == 0){
        fragmentSize ++;
    }
    int numOfFragments = size / fragmentSize;
    int aslong = 0;
    int i = 0;
        
        
    if (startingIndex < 0) {
        startingIndex = ((startingIndex + size) % size);
        if (startingIndex < 0) {
            startingIndex += size;
        }
    }
        
    while (i < numOfFragments) {
        int circular_position = startingIndex % size;
        int limit = circular_position + fragmentSize;
        int curPos = 0;
            
        while (aslong < ((limit - circular_position) / 2)) {
            aslong++;
            int index1 = 0;
            int index2 = 0;
            if (size > 0) {
                index1 = (circular_position + curPos) % size;
                index2 = ((circular_position + fragmentSize) - curPos - 1) % size;
            }
            if (index1 < 0) index1 += size;
            if (index2 < 0) index2 += size;
                        
            if (index1 >= size || index2 >= size) {
                return 0 ;
            }
                        
            int temp = arr[index1];
            arr[index1] = arr[index2];
            arr[index2] = temp;
            curPos++;
        }

        aslong = 0;
        startingIndex += fragmentSize;
        i++;
    }







            }
            else if(userChoice == 'C'){
                cin >> startingIndex >> fragmentSize;
                 if(fragmentSize > 0){
        if (startingIndex < 0) {
            startingIndex = ((startingIndex + size) % size);
            if (startingIndex < 0) {
                startingIndex += size;
            }
        }
        

        int totalFragments = (size / fragmentSize) / 2;
        
        int i = 0;
        
        while(i < totalFragments){
            int end = startingIndex + fragmentSize;
            
            int j = startingIndex;
            while (j < end) {
                int index1 = j % size;
                int index2 = ((j % size) + fragmentSize) % size;
                if (index1 >= 0 && index1 < size && index2 >= 0 && index2 < size) {
                    int temp = arr[index1];
                    arr[index1] = arr[index2];
                    arr[index2] = temp;
                }
                j++;
            }
            
            if (size > 0) {
                startingIndex += ((fragmentSize * 2) )% size;
            }
            i++;

        }
        
    }
                
            }
            else if(userChoice == 'F'){
                int i = 0;
                while(i < size){
                    cout << arr[i] << " ";
                    i++;
                }
                cout << endl;
            }
            
            else if(userChoice == 'M'){
                cin >> startingIndex >> fragmentSize >> shift;
         if (size != 0 && fragmentSize != 0 && fragmentSize <= size){

while (startingIndex < 0)
    startingIndex += size;
startingIndex %= size;

int currentShift = -shift;
while (currentShift < 0)
    currentShift += fragmentSize;
    currentShift %= fragmentSize;

int cycleNumber = 0;
while ((cycleNumber + 1) * fragmentSize < size)
{
    int tmp;
    int cycleStart = startingIndex + cycleNumber * fragmentSize;
    int shiftCounter = 0;
    while (shiftCounter < currentShift)
    {
        int i = 0;
        tmp = arr[cycleStart % size];
        while (i < fragmentSize - 1)
        {
            arr[(cycleStart + i) % size] = arr[(cycleStart + (i + 1) % fragmentSize) % size];
            i++;
        }
        arr[(cycleStart + fragmentSize - 1) % size] = tmp;;
        shiftCounter++;
    }
    cycleNumber++;
}
if (size - cycleNumber * fragmentSize > 0)
{
    int newFragmentSize = size - cycleNumber * fragmentSize;
    int cycleStart = (startingIndex + cycleNumber * fragmentSize) % size;

    int currentShift = -shift;
    while (currentShift < 0)
        currentShift += newFragmentSize;
    currentShift %= newFragmentSize;

    int shiftCounter = 0;
    while (shiftCounter < currentShift)
    {
        int i = 0;
        int tmp = arr[cycleStart % size];
        while (i < newFragmentSize - 1)
        {
            arr[(cycleStart + i) % size] = arr[(cycleStart + (i + 1) % newFragmentSize) % size];
            i++;
        }
        arr[(cycleStart + newFragmentSize - 1) % size] = tmp;
        shiftCounter++;
    }
} 
   }
            }

        }
        
        sesNum--;
    }
    
    return 0;
}
