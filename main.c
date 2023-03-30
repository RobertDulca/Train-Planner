#include <stdio.h>
#include <stdlib.h>

enum type {passenger, sleeper, diner};

struct carriage{
    enum type carriageType;
    int capacity;
};

struct train{
    struct carriage arr_train[10];
    int length;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Funktionen für die Ausgabe

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void printCarriage (struct carriage carriage){
    if (carriage.carriageType == 0){
        printf("[P:%03d]", carriage.capacity);
    }
    else if (carriage.carriageType == 1){
        printf("[S:%03d]", carriage.capacity);
    }
    else if (carriage.carriageType == 2){
        printf("[D:%03d]", carriage.capacity);
    }
}

void printTrain(struct train *train){
    if(train->length > 0){
        printf("\nTrain: ");
        int size = 0;
        for (int i = 0; i < train->length; i++){
            printf("%d:", i);
            printCarriage(train-> arr_train[i]);
            size++;
            if (i < train->length-1){
                printf("-");
            }
        }
        printf(" Length: %d", size);
    }
    else{
        printf("\nTrain: No Carriages!");
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Funktionen für die Eingabe

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char getMenu(){

    char menuEingabe ;
    printf("\nChoose Action: print train (p), new carriage (n), print stats (s) or exit (x):");
    while(1){
        scanf(" %c", &menuEingabe);
        if(menuEingabe == 'p' || menuEingabe == 'n' || menuEingabe == 's'|| menuEingabe == 'x'){
            return menuEingabe;
            break;
        }
        else {
            printf("\nInput invalid! Try again:");
        }
    }
}

struct carriage getCarriage(){
    struct carriage newCarriage;
    char typeEingabe;
    int capacityInput;
    printf("\nChoose type of carriage: passenger (p), sleeper (s) or diner (d):");
    while(1){
        scanf(" %c", &typeEingabe);
        if(typeEingabe == 'p'){
            newCarriage.carriageType = passenger;
            printf ("\nChoose capacity (20 - 130):");
            while (1){
                scanf (" %d", &capacityInput);
                if(capacityInput <= 130 && capacityInput >= 20){
                    newCarriage.capacity = capacityInput;
                    return newCarriage;
                }
                else{
                    printf("\nInput invalid! Try again:");
                }
            }
        }
        else if(typeEingabe == 's'){
            newCarriage.carriageType = sleeper;
            printf ("\nChoose capacity (20 - 130):");
            while (1){
                scanf (" %d", &capacityInput);
                if(capacityInput <= 130 && capacityInput >= 20){
                    newCarriage.capacity = capacityInput;
                    return newCarriage;
                }
                else{
                    printf("\nInput invalid! Try again:");
                }
            }
        }
        else if(typeEingabe == 'd'){
            newCarriage.carriageType = diner;
            printf ("\nChoose capacity (20 - 130):");
            while (1){
                scanf (" %d", &capacityInput);
                if(capacityInput <= 130 && capacityInput >= 20){
                    newCarriage.capacity = capacityInput;
                    return newCarriage;
                }
                else{
                    printf("\nInput invalid! Try again:");
                }
            }
        }
        else {
            printf("\nInput invalid! Try again:");
        }
    }
};

int getPosition(int length){
    int eingabe;
    printf("\nChoose position for the new carriage (0-%d):", length);
    while(1){
        scanf(" %d", &eingabe);
        if (eingabe>=0 && eingabe<=length){
            return eingabe;
        }
        else {
            printf("\nInput invalid! Try again:");
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Einfügen eines Waggons in den Zug

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int insertCarriage(struct train *trainComplete, int position, struct carriage newCarriage){
    int lengthTrain = trainComplete -> length;

    if (lengthTrain>9){
        return -1;
    }

    if (trainComplete -> arr_train[position].carriageType == 1 && newCarriage.carriageType == 1){
        return -3;
    }

    if (position < lengthTrain-1 && newCarriage.carriageType == 1){
        if(trainComplete -> arr_train[position+1].carriageType == passenger && trainComplete -> arr_train[position+2].carriageType == passenger){
            if(position >= lengthTrain && position < 10){
                trainComplete -> arr_train[position] = newCarriage;
                return 0;
            }
            else{
                for(int i = lengthTrain; i > position; i--){
                    trainComplete -> arr_train[i] = trainComplete -> arr_train[i-1];
                }
                trainComplete -> arr_train[position]= newCarriage;
                return 0;
            }
        }
        if(trainComplete -> arr_train[position].carriageType == passenger && trainComplete -> arr_train[position+1].carriageType == passenger){
            if(position >= lengthTrain && position < 10){
                trainComplete -> arr_train[position] = newCarriage;
                return 0;
            }
            else{
                for(int i = lengthTrain; i > position; i--){
                    trainComplete -> arr_train[i] = trainComplete -> arr_train[i-1];
                }
                trainComplete -> arr_train[position]= newCarriage;
                return 0;
            }
        }
        else{
            return -3;
        }
    }

    if(newCarriage.carriageType == 1){
        return -3;
    }


    if (position < 0 || position > lengthTrain){
        return -2;
    }
    if (newCarriage.carriageType == 0 || newCarriage.carriageType == 2){
        if(position >= lengthTrain && position < 10){
            trainComplete -> arr_train[position] = newCarriage;
            return 0;
        }
        else{
            for(int i = lengthTrain; i > position; i--){
                trainComplete -> arr_train[i] = trainComplete -> arr_train[i-1];
            }
            trainComplete -> arr_train[position]= newCarriage;
            return 0;
        }
    }
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Ermittlung der Kapazität und Ausgabe der Statistik

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int sumCapacity(struct train *trainComplete, enum type carriage){
    int sumType = 0;

    if(carriage == 0){
        for(int i=0; i < trainComplete->length; i++){
            if(trainComplete->arr_train[i].carriageType == passenger){
                sumType += trainComplete->arr_train[i].capacity;
            }
        }
        if(sumType < 65){
            printf("\n  Passenger: %d - invalid", sumType);
        }
        else{
            printf("\n  Passenger: %d", sumType);
        }
    }
    else if (carriage == 1){
        for(int i=0; i < trainComplete->length; i++){
            if(trainComplete->arr_train[i].carriageType == sleeper){
                sumType += trainComplete->arr_train[i].capacity;
            }
        }
        printf("\n  Sleeper: %d", sumType);
    }
    else if (carriage == 2){
        for(int i=0; i < trainComplete->length; i++){
            if(trainComplete->arr_train[i].carriageType == diner){
                sumType += trainComplete->arr_train[i].capacity;
            }
        }
        printf("\n  Diner: %d", sumType);
    }
    return 0;
}

void printTrainStats(struct train *trainComplete){
    struct train trainGanz;
    for (int i=0; i<trainComplete->length; i++){
        trainGanz.arr_train[i] = trainComplete -> arr_train[i];
    }
    trainGanz.length = trainComplete -> length;

    printTrain(&trainGanz);
    printf("\nCapacities:");
    sumCapacity(&trainGanz, 0);
    sumCapacity(&trainGanz, 1);
    sumCapacity(&trainGanz, 2);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Main Function

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){

    struct train trainComplete;
    struct carriage newCarriage;
    int carriageCount = 0;
    int position;
    int returnInsert;

    trainComplete.length = 0;

    while(1){
        char eingabe = getMenu();
        if (eingabe == 'x'){
            break;
        }
        if (eingabe == 'n'){
            newCarriage = getCarriage();
            position = getPosition(trainComplete.length);
            returnInsert = insertCarriage(&trainComplete, position, newCarriage);
            if (returnInsert == 0){
                ++carriageCount;
                trainComplete.length = carriageCount;
            }
            else if (returnInsert == -1){
                printf("\nError: Train too long!");
            }
            else if (returnInsert == -2){
                printf("\nError: Position not possible!");
            }
            else if (returnInsert == -3){
                printf("\nError: Sleeper only possible directly before two passenger carriages!");
            }
        }
        if (eingabe == 'p'){
            printTrain(&trainComplete);
        }
        if (eingabe == 's'){
            printTrainStats(&trainComplete);
        }
    }

    return 0;
}
