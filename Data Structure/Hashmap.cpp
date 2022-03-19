#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>

using namespace std;

string wordGenerator(){
    string letters[] = {"a", "b","c","d", "e", "f", "g","h","i","j" ,"k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
    string result = "";
    for(int i=0;i<7;i++){
        result.append(letters[rand()%26]);
    }
    return result;

}

class tableValue{
public:
    string key;
    int value;
    tableValue *next = nullptr;
    tableValue *prev = nullptr;
};



class hashTable{
private:
    tableValue *table;
    int tableSize;
    int insertedWord = 0;
    int uniqueHashValue = 0;

    int doubleHashCollision = 0;
    int doubleHashProbes = 0;

    int customHashCollision = 0;
    int customHashProbes = 0;

    int chainingCollision = 0;
    int chainingProbes = 0;
public:
    hashTable(int s){
        table = new tableValue[s];
        tableSize = s;
        for(int i=0;i<s;i++){
            table[i].value = -1;
            table[i].key = "";
        }
    }

    unsigned long int hash1(string key){
        unsigned long hashValue = 0;
        int l = key.length();
        for(int i=0;i<l;i++){
            hashValue = (int)key[i] + (hashValue << 6) + (hashValue << 16) - hashValue;
        }
        return hashValue;
    }

    unsigned long int hash2(string key){
        unsigned long hashValue = 5381;
        int l = key.length();
        for(int i=0;i<l;i++){
            hashValue = ((hashValue << 5) + hashValue) + (int)key[i];
        }

        return hashValue;
    }

    unsigned long int auxHash(string key){
        unsigned int hashValue = 7;
        int l = key.length();
        for(int i=0;i<l;i++){
            hashValue += (hashValue*31 + (int)key[i]);
        }

        return hashValue;
    }

    long int doubleHash(string key, int i){
        int hashValue = (hash2(key) + i*auxHash(key))%tableSize;
        return hashValue;
    }

    long int customHash(string key, int i){
        int hashValue = (hash2(key) + 2153*i*auxHash(key) + 4987*i*i) % tableSize;
        return hashValue;
    }

    long int chainingMethodIndex(string key){
        int hashValue = hash2(key)%tableSize;
        return hashValue;
    }

    void insertDoubleHash(string key, int value){
        for(int i=0;i<tableSize;i++){
            int index = doubleHash(key, i);
            if(table[index].value == -1){
                table[index].value = value;
                table[index].key = key;
                insertedWord++;
                if(i==0) uniqueHashValue++;
                break;
            }
            else{
                doubleHashCollision++;
            }
        }
    }
    int searchDoubleHash(string key, bool avgProbe = false){
        for(int i=0;i<tableSize;i++){
            int index = doubleHash(key,i);
            if(table[index].key == key){
                if(avgProbe) doubleHashProbes++;
                return index;
            }
            else if(table[index].value == -1){
                break;
            }
            else{
                if(avgProbe) doubleHashProbes++;
            }
        }
        return -1;
    }

    void deleteDoubleHash(string key){
        for(int i=0;i<tableSize;i++){
            int index = doubleHash(key,i);
            if(table[index].key == key){
                table[index].value = -1;
                table[index].key = "";
                return;
            }
        }
    }

    void insertCustomHash(string key, int value){
        for(int i=0;i<tableSize;i++){
            int index = customHash(key, i);
            if(table[index].value == -1){
                table[index].value = value;
                table[index].key = key;
                insertedWord++;
                if(i==0) uniqueHashValue++;
                break;
            }
            else{
                customHashCollision++;
            }
        }
    }

    int searchCustomHash(string key, bool avgProbe = false){
        for(int i=0;i<tableSize;i++){
            int index = customHash(key,i);
            if(table[index].key == key){
                if(avgProbe) customHashProbes++;
                return index;
            }
            else if(table[index].value == -1){
                break;
            }
            else{
                if(avgProbe) customHashProbes++;
            }
        }
        return -1;
    }
    void deleteCustomHash(string key){
        for(int i=0;i<tableSize;i++){
            int index = customHash(key,i);
            if(table[index].key == key){
                table[index].value = -1;
                table[index].key = "";
                return;
            }
        }
    }

    void insertChainingMethod(string key, int value){
        int index = chainingMethodIndex(key);
        if(table[index].value == -1){
            table[index].value = value;
            table[index].key = key;
            uniqueHashValue++;
        }
        else{
            chainingCollision++;
            if(table[index].next == nullptr){
                tableValue *next = new tableValue();
                next->value = value;
                next->key = key;
                table[index].next = next;
                next->prev = &table[index];
            }
            else{
                tableValue *next = table[index].next;
                tableValue *newValue = new tableValue();
                newValue->next = next;
                newValue->prev = &table[index];
                table[index].next = newValue;
                next->prev = newValue;
            }
        }
        insertedWord++;
    }

    int searchChainingMethod(string key, bool avgProbes = false){
        int index = chainingMethodIndex(key);
        if(table[index].key == key){
            if(avgProbes)chainingProbes++;
            return index;
        }
        else{
            tableValue *itr = table[index].next;
            while(itr != nullptr){
                if(itr->key == key){
                    if(avgProbes)chainingProbes++;
                    return index;
                }
                else{
                    if(avgProbes)chainingProbes++;
                }
                itr = itr->next;
            }
        }
        return -1;
    }

    void deleteChainingMethod(string key){
        int index = chainingMethodIndex(key);
        if(table[index].key == key && table[index].next != nullptr){
            tableValue *next = table[index].next;
            table[index].value = next->value;
            table[index].key = next->key;
            table[index].next = next->next;
            if(next->next != nullptr){
                next->next->prev = &table[index];
            }
            next->next = nullptr;
            next->prev = nullptr;

        }
        else if(table[index].key == key && table[index].next == nullptr){
            table[index].value = -1;
            table[index].key = "";
        }
        else{
            tableValue *itr = table[index].next;
            while(itr != nullptr){
                if(itr->key == key){
                    tableValue *prev = itr->prev;
                    tableValue *next = itr->next;
                    prev->next = next;
                    next->prev = prev;
                    itr->next = nullptr;
                    itr->prev = nullptr;
                    delete itr;
                    break;
                }
                itr = itr->next;
            }
        }
    }

    int getDoubleHashCollision(){
        return doubleHashCollision;
    }
    int getDoubleHashProbes(){
        return doubleHashProbes;
    }

    int getTotalWordCount(){
        return insertedWord;
    }

    int getCustomHashCollision(){
        return customHashCollision;
    }
    int getCustomHashProbes(){
        return customHashProbes;
    }

    int getChainingCollision(){
        return chainingCollision;
    }
    int getChainingProbes(){
        return chainingProbes;
    }

    int getUnique(){
        return uniqueHashValue;
    }

    void print(){
        for(int i=0;i<tableSize ; i++){
            cout << table[i].key << " " << table[i].value << endl;
        }
    }

};


int main(){
    int s;
    cout << "input table size: " ;
    cin >> s;
    srand(time(0));
    hashTable *table = new hashTable(s);
    string *keys = new string[10000];
    int entryNum = 0;
    int generatedWords = 0;
    while(generatedWords < 10000){
        string key = wordGenerator();
        int searchIndex = table->searchChainingMethod(key);
        if(searchIndex == -1){
            table->insertChainingMethod(key, entryNum+1);
            keys[entryNum] = key;
            entryNum++;
        }
        generatedWords++;
    }

    cout << "For chaining method: " <<endl;
    cout << "Total collision: " <<table->getChainingCollision() << endl;
    for(int i=0;i<1000;i++){
        table->searchChainingMethod(keys[rand()%entryNum], true);
    }
    cout << "Total words inserted: " <<table->getTotalWordCount() << endl;
    cout << "Unique hash value: " <<table->getUnique() << endl;
    cout << "Average probes: " <<table->getChainingProbes()/1000.0 << endl;

    delete table;
    delete []keys;


    table = new hashTable(s);
    keys = new string[10000];
    entryNum = 0;
    generatedWords = 0;
    while(generatedWords < 10000){
        string key = wordGenerator();
        int searchIndex = table->searchDoubleHash(key);
        if(searchIndex == -1){
            table->insertDoubleHash(key,entryNum+1);
            keys[entryNum] = key;
            entryNum++;
        }
        generatedWords++;
    }
    cout << endl << "For double hashing: " << endl;
    cout << "Total collision: " <<table->getDoubleHashCollision() << endl;
    for(int i=0;i<1000;i++){
        table->searchDoubleHash(keys[rand()%entryNum], true);
    }
    cout << "Total words inserted: " <<table->getTotalWordCount() << endl;
    cout << "Unique hash value: " <<table->getUnique() << endl;
    cout << "Average probes: " << table->getDoubleHashProbes()/1000.0 << endl;

    delete table;
    delete []keys;

    table = new hashTable(s);
    keys = new string[10000];
    entryNum = 0;
    generatedWords = 0;

    while(generatedWords < 10000){
        string key = wordGenerator();
        int searchIndex = table->searchCustomHash(key);
        if(searchIndex == -1){
            table->insertCustomHash(key,entryNum+1);
            keys[entryNum] = key;
            entryNum++;
        }
        generatedWords++;
    }
    cout << endl << "For custom hashing: " << endl;
    cout << "Total collision: " << table->getCustomHashCollision() << endl;
    for(int i=0;i<1000;i++){
        table->searchCustomHash(keys[rand()%entryNum], true);
    }
    cout << "Total words inserted: " << table->getTotalWordCount() << endl;
    cout << "Unique hash value: " << table->getUnique() << endl;
    cout << "Average probes: " << table->getCustomHashProbes()/1000.0 << endl;


    return 0;
}
