#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUCKET_SIZE 97

typedef struct HashNode
{
    char key[10];
    char value[50];

    struct HashNode* next;
}HashNode;

typedef struct HashTable
{
    int bucketGroupSize;

    // 버킷1, 버킷2, 버킷3....은 각각 연결리스트 포인터입니다
    // 연결리스트 포인터의 배열이기 때문에 이중포인터가 됩니다
    HashNode** bucket;
}HashTable;

int hashFunc(char* key, int tableSize)
{
    char letter = *key;
    int sum = 0;
    int i = 0;
    while(letter != 0)
    {
        sum += (sum << 3 ) + (int)letter;
        // sum += (int)letter;
        letter = *(key + ++i);
    }
    return sum % tableSize;
}

// 가중치가 7의 거듭제곱으로 증가합니다.  
// 각 문자의 ASCII 값에 곱해 누적한 후 모듈러 연산을 수행합니다.
int myHashFunc(char* key, int tableSize)
{
    char letter = *key;
    int sum = 0;
    int weight = 7;
    
    for(int i=0; key[i] != '\0'; i++)
    {
        int digit = (int)key[i];
        sum += digit * weight;
        weight *= 7;
    }
    return sum % tableSize;
}

HashTable* createHashTable(int size)
{
    HashTable* hashTable = (HashTable*) malloc(sizeof(HashTable));
    hashTable->bucket = (HashNode**)malloc(size*sizeof(HashNode*));
    memset(hashTable->bucket, 0x0, size*sizeof(HashNode*));
    hashTable->bucketGroupSize = size;

    return hashTable;
}

void insertIntoHashTable(HashTable* hashTable, char* key, char* value)
{
    // key 문자열을 이용해서 해시함수로부터 버킷 배열의 인덱스를 지정받습니다
    int bucketIndex = myHashFunc(key, hashTable->bucketGroupSize);

    // printf("bucketIndex %d for key %s/value %s\n", bucketIndex, key, value);

    // 해당 버킷 인덱스가 점유되지 않은 상태라면 NULL 포인터 상태입니다    
    if (hashTable->bucket[bucketIndex] == NULL)
    {
        hashTable->bucket[bucketIndex] = (HashNode*) malloc(sizeof(HashNode));
        strcpy(hashTable->bucket[bucketIndex]->value, value);
        strcpy(hashTable->bucket[bucketIndex]->key, key);
        hashTable->bucket[bucketIndex]->next = NULL;
    }
    // 해당 버킷 인덱스가 점유된 상태라면 어떠한 주소값이 있습니다(해시키 충돌, 또는 value 업데이트 상황)
    else
    {
        HashNode* currentNode = hashTable->bucket[bucketIndex];        
        HashNode* prevNode;

        // 파이썬 dict에서 key값이 동일하면 update를 하는것처럼, key값이 동일한 것이 있는지 찾습니다
        while (currentNode != NULL)
        {
            // 만약 연결리스트 내에서 key값이 동일한 것을 찾았다면 업데이트 하고 함수를 종료합니다
            if (strcmp(key, currentNode->key ) == 0)
            {
                printf("Found key update for bucketIndex %d, key %s\n", bucketIndex, key);
                strcpy(currentNode->value, value);
                strcpy(currentNode->key, key);
                return;
            }
            prevNode = currentNode;
            currentNode = currentNode->next;
        }

        // 만약 연결리스트 내에서 key값이 동일한 것이 없었다면 업데이트 상황이 아니라 key충돌 상황 입니다
        // 서로 다른 key에 대해 동일한 버킷 인덱스를 할당받은 것이기 때문입니다
        // 이 경우 연결리스트의 맨 끝에 key/value를 추가합니다
        if (currentNode == NULL)
        {
            printf("Found key conflict for bucketIndex %d, key %s\n", bucketIndex, key);
            currentNode = (HashNode*) malloc(sizeof(HashNode));
            strcpy(currentNode->value, value);
            strcpy(currentNode->key, key);
            currentNode->next = NULL;
            prevNode->next = currentNode;
        }
    }
}

char* getFromHashTable(HashTable* hashTable, char* key)
{
    // 버킷 배열의 인덱스를 해시함수가 정합니다
    int bucketIndex = myHashFunc(key, hashTable->bucketGroupSize);

    HashNode* currentNode = hashTable->bucket[bucketIndex];

    if (currentNode == NULL) return 0;

    // 지정된 인덱스에 있는 key가 검색하고자 하는 key와 일치하면 value를 반환합니다
    while (strcmp(key, currentNode->key ) != 0)
    {
        currentNode = currentNode->next;
    }

    // 검색하고자 하는 key와 일치하는 key가 발견되었으면 해당 value를 반환합니다
    if (currentNode != NULL) return currentNode->value;
    // 검색하고자 하는 key와 일치하는 key를 찾지 못했으면 저장되지 않은 key를 요청한 것입니다
    else return 0;
}

int main(int argc, char* argv[])
{
    HashTable* hashTable = createHashTable(BUCKET_SIZE);

    insertIntoHashTable(hashTable, "name", "apple");
    insertIntoHashTable(hashTable, "property", "red");
    insertIntoHashTable(hashTable, "kind", "fruit");
    insertIntoHashTable(hashTable, "origin", "Korea");
    insertIntoHashTable(hashTable, "name", "mango");
    insertIntoHashTable(hashTable, "eman", "orange");
    insertIntoHashTable(hashTable, "id", "123456");
    insertIntoHashTable(hashTable, "dnik", "fruit");
    insertIntoHashTable(hashTable, "nigiro", "Korea");
    insertIntoHashTable(hashTable, "dest", "USA");
    insertIntoHashTable(hashTable, "key1", "value1");
    insertIntoHashTable(hashTable, "key2", "value2");
    insertIntoHashTable(hashTable, "key3", "value3");

    printf("%s\n",getFromHashTable(hashTable, "origin"));
    printf("%s\n",getFromHashTable(hashTable, "property"));
    printf("%s\n",getFromHashTable(hashTable, "name"));
    printf("%s\n",getFromHashTable(hashTable, "kind"));
    printf("%s\n",getFromHashTable(hashTable, "eman"));
    printf("%s\n",getFromHashTable(hashTable, "id"));
    printf("%s\n",getFromHashTable(hashTable, "dnik"));
    printf("%s\n",getFromHashTable(hashTable, "nigiro"));
    printf("%s\n",getFromHashTable(hashTable, "dest"));

    return 0;
}