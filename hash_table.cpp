
#include <vector>
#include <forward_list>

using namespace std;

const int maxColision = 3;
const float maxFillFactor = 0.5;

template<typename TK, typename TV>
class ChainHash
{
private:
    struct Entry{
        TK key;
        TV value;
        size_t hashcode;
    };

    forward_list<Entry> *array; // array de listas enlazadas
    int capacity; // tamaño del array
    int size; // cantidad de elementos totales

public:
    ChainHash(int _cap = 10){
        // TODO: asignar un tamaño inicial al array
        capacity = _cap;
        array = new forward_list<Entry>[capacity];
        size = 0;
    }

    void insert(TK key, TV value){
        if(fillFactor() >= maxFillFactor) rehashing();
        size_t hashcode = getHashCode(key);
        int index = hashcode % capacity;

        // Verificar si la clave ya existe en la lista
        auto it = find_if(array[index].begin(), array[index].end(),
                          [key](const Entry& entry) { return entry.key == key; });

        // Si la clave ya existe, actualizar el valor
        if (it != array[index].end()) {
            it->value = value;
        } else {
            // Si la clave no existe, agregar un nuevo Entry
            Entry newEntry = {key, value, hashcode};
            array[index].push_front(newEntry);
            size++;
        }
    }

    TV find(TK key){
        size_t hashcode = getHashCode(key);
        int index = hashcode % capacity;

        // Buscar la clave en la lista correspondiente
        auto it = find_if(array[index].begin(), array[index].end(),
                          [key](const Entry& entry) { return entry.key == key; });

        // Devolver el valor si se encuentra, o un valor por defecto si no
        return (it != array[index].end()) ? it->value : TV();
    }

    void remove(TK key){
        size_t hashcode = getHashCode(key);
        int index = hashcode % capacity;

        // Eliminar la clave de la lista si existe
        array[index].remove_if([key](const Entry& entry) { return entry.key == key; });
        size--;
    }

    // Implementación del operador corchete []
    TV operator[](TK key){
        return find(key);
    }

private:
    double fillFactor(){
        return static_cast<double>(size) / (capacity * maxColision);
    }

    size_t getHashCode(TK key){
        hash<TK> ptr_hash;
        return ptr_hash(key);
    }

    void rehashing(){
        // Duplicar la capacidad del array y reorganizar los elementos
        int newCapacity = capacity * 2;
        auto newArray = new forward_list<Entry>[newCapacity];

        for (int i = 0; i < capacity; ++i) {
            for (const auto& entry : array[i]) {
                size_t hashcode = entry.hashcode;
                int index = hashcode % newCapacity;
                newArray[index].push_front(entry);
            }
        }

        delete[] array; // Liberar la memoria del antiguo array
        array = newArray; // Apuntar al nuevo array
        capacity = newCapacity; // Actualizar la capacidad
    }
};
