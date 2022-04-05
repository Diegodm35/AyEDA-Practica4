#include <iostream>
#include "../include/fdModule.h"
#include "../include/fdSum.h"
#include "../include/fdRandom.h"
#include "../include/feLineal.h"
#include "../include/feQuadratic.h"
#include "../include/feDispersion.h"
#include "../include/feRedispersion.h"
#include "../include/HashTable.h"


typedef long testType;

int main() {
    int tableSize, fd, td, blockSize, fe;;
    std::cout << "Introduce el tamano de la tabla:" << std::endl;
    std::cin >> tableSize;
    std::cout << "Seleccione una funcion de dispersion: \n"
                 "  1.- Modulo \n"
                 "  2.- Basada en la Suma \n"
                 "  3.- Pseudoaleatoria " << std::endl;
    std::cin >> fd;
    DispersionFunction<testType> *dispersionFunction;
    switch (fd) {
        case 1:
            dispersionFunction = new fdModule<testType>(tableSize);
            break;
        case 2:
            dispersionFunction = new fdSum<testType>(tableSize);
            break;
        case 3:
            dispersionFunction = new fdRandom<testType>(tableSize);
            break;
        default:
            std::cout << "Opcion invalida" << std::endl;
            return 1;
    };
    std::cout << "Seleccione una tecnica de dispersion: \n"
                 "  1.- Abierta \n"
                 "  2.- Cerrada" << std::endl;
    std::cin >> td;
    Sequence<testType> *sequence;
    HashTable<testType> *hashTable;
    switch (td) {
        case 1:
            sequence = new List<testType>();
            hashTable = new HashTable<testType>(tableSize, dispersionFunction);
            break;
        case 2:
            std::cout << "Introduce el tamano del bloque:" << std::endl;
            std::cin >> blockSize;
            sequence = new Block<testType>(blockSize);
            std::cout << "Seleccione una funcion de exploracion: \n"
                         "  1.- Lineal \n"
                         "  2.- Cuadratica \n"
                         "  3.- Doble dispersion \n"
                         "  4.- Redispersion " << std::endl;
            std::cin >> fe;
            ExplorationFunction<testType> *explorationFunction;
            switch (fe) {
                case 1:
                    explorationFunction = new feLineal<testType>();
                    break;
                case 2:
                    explorationFunction = new feQuadratic<testType>();
                    break;
                case 3:
                    explorationFunction = new feDispersion<testType>(dispersionFunction);
                    break;
                case 4:
                    explorationFunction = new feRedispersion<testType>();
                    break;
                default:
                    std::cout << "Opcion invalida" << std::endl;
                    return 1;
            }
            hashTable = new HashTable<testType>(tableSize, dispersionFunction, explorationFunction, blockSize);
            break;
        default:
            std::cout << "Opcion invalida" << std::endl;
            return 1;
    };
    while(true){
        std::cout << "Seleccione una opcion: \n"
                     "  1.- Insertar \n"
                     "  2.- Buscar \n"
                     "  3.- Salir" << std::endl;
        int option;
        std::cin >> option;
        switch (option) {
            case 1:
                std::cout << "Introduce el elemento a insertar:" << std::endl;
                testType element;
                std::cin >> element;
                hashTable->insert(element);
                break;
            case 2:
                std::cout << "Introduce el elemento a buscar:" << std::endl;
                testType element3;
                std::cin >> element3;
                std::cout << "El elemento se encuentra en la posicion: " << hashTable->search(element3) << std::endl;
                break;
            case 3:
                return 0;
            default:
                std::cout << "Opcion invalida" << std::endl;
                break;
        }
    }
    return 0;
}

