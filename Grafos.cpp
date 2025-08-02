#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

class GrafoTransporte {
private:
    unordered_map<string, vector<string>> lista_adyacencia;
    
public:
    void agregar_conexion(const string& estacionA, const string& estacionB) {
        lista_adyacencia[estacionA].push_back(estacionB);
        lista_adyacencia[estacionB].push_back(estacionA);
    }
    
    vector<string> encontrar_ruta_mas_corta(const string& inicio, const string& destino) {
      
        if (lista_adyacencia.find(inicio) == lista_adyacencia.end() || 
            lista_adyacencia.find(destino) == lista_adyacencia.end()) {
            return {};
        }
        
        queue<string> cola;
        unordered_map<string, bool> visitado;
        unordered_map<string, string> predecesor;
        
        cola.push(inicio);
        visitado[inicio] = true;
        predecesor[inicio] = "";
        
        while (!cola.empty()) {
            string actual = cola.front();
            cola.pop();
            
            if (actual == destino) {
                vector<string> camino;
                string nodo = destino;
                while (nodo != "") {
                    camino.push_back(nodo);
                    nodo = predecesor[nodo];
                }
                reverse(camino.begin(), camino.end());
                return camino;
            }
            
            for (const string& vecino : lista_adyacencia[actual]) {
                if (!visitado[vecino]) {
                    visitado[vecino] = true;
                    predecesor[vecino] = actual;
                    cola.push(vecino);
                }
            }
        }
        
        return {};
    }
    
    void mostrar_grafo() {
        for (const auto& par : lista_adyacencia) {
            cout << par.first << " -> ";
            for (const string& vecino : par.second) {
                cout << vecino << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    GrafoTransporte red_transporte;
    
    red_transporte.agregar_conexion("Centro", "Norte");
    red_transporte.agregar_conexion("Centro", "Sur");
    red_transporte.agregar_conexion("Norte", "Este");
    red_transporte.agregar_conexion("Norte", "Oeste");
    red_transporte.agregar_conexion("Sur", "Este");
    red_transporte.agregar_conexion("Sur", "Aeropuerto");
    red_transporte.agregar_conexion("Este", "Universidad");
    red_transporte.agregar_conexion("Oeste", "Playa");
    
    cout << "Red de transporte:" << endl;
    red_transporte.mostrar_grafo();
    cout << endl;
    
    string inicio = "Playa";
    string destino = "Aeropuerto";
    
    vector<string> ruta = red_transporte.encontrar_ruta_mas_corta(inicio, destino);
    
    if (!ruta.empty()) {
        cout << "Ruta mas corta de " << inicio << " a " << destino << ":" << endl;
        for (size_t i = 0; i < ruta.size(); ++i) {
            if (i != 0) cout << " -> ";
            cout << ruta[i];
        }
        cout << endl;
        cout << "Total de paradas: " << ruta.size() - 1 << endl;
    } else {
        cout << "No existe ruta entre " << inicio << " y " << destino << endl;
    }
    
    return 0;
}
