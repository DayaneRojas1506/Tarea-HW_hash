
#include <forward_list>
using namespace std;

const int MAX_COLISION = 10;

template<typename TK>
class Set
{
private:
    forward_list<TK> *array;//array de listas enlazadas
    int capacity;//tamanio del array
    int size;//cantidad de elementos totales

public:
    Set(int _cap = 4){
        // TODO: asignar un tamanio inicial al array
        capacity = _cap;
        array = new forward_list<TK>[capacity];
        size = 0;
    }

    void insert(TK key){
        size_t hashcode = getHashCode(key);
        int index = hashcode % capacity;
        int num_colision = 0;
        bool existe = false;
        for(auto ite=array[index].begin(); ite != array[index].end(); ++ite)
        {
            if(*ite == key){
                existe = true;
                break;
            }
            ++num_colision;
        }
        if(!existe){
            array[index].push_front(key);
            if(num_colision == MAX_COLISION) rehashing();
        }

    }

    bool find(TK key){
        size_t hashcode = getHashCode(key);
        int index = hashcode % capacity;

        for (auto ite = array[index].begin(); ite != array[index].end(); ++ite)
        {
            if(*ite == key){
                return true;
            }
        }

        return false;

    }
    Set Union(const Set<TK> &otro){
     Set<TK> resultSet(capacity + otro.capacity);

     for (int i = 0; i < capacity; ++i) {
        for (const auto &element : array[i]) {
            resultSet.insert(element);
        }
    }

    for (int i = 0; i < otro.capacity; ++i) {
        for (const auto &element : otro.array[i]) {
            resultSet.insert(element);
        }
    }
    return resultSet;
}

    void display() {
        for (int i = 0; i < capacity; ++i) {
            for (const auto &element: array[i]) {
                cout << element << " ";
            }
        }
        cout << endl;
    }

private:


    size_t getHashCode(TK key){
        std::hash<TK> f_hash;
        return f_hash(key);
    }

    void rehashing(){
         int new_capacity = capacity * 2;
         for (int i =0 ; i< capacity; ++i)
         {
             for(auto ite=array[i].begin(); ite != array[i].end(); ++ite)
             {
                 size_t hashcode = getHashCode(*ite);
                 int index = hashcode % new_capacity;
                 array[index].push_front(*ite);
             }
         }
    }
    

        delete[] array;
        array = newArray;
        capacity = newCapacity;
    }
};
