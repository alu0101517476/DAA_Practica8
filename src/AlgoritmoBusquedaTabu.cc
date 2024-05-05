#include "../include/AlgoritmoBusquedaTabu.h"

void AlgoritmoBusquedaTabu::inicializar(Solucion& mejor_solucion,
                                        Solucion& solucion_actual) {
  AlgoritmoGrasp grasp{nombre_fichero_puntos_, problema_.getSizeSolucion(), 3};
  solucion_actual = grasp.resolver();
  mejor_solucion = solucion_actual;
}

Solucion AlgoritmoBusquedaTabu::obtenerMejorVecino(
    std::vector<Solucion> vecindario, const std::map<Solucion, int>& lista_tabu,
    const Solucion& mejor_solucion) {

  Solucion mejor_vecino{vecindario[0]};
  for (const auto& vecino : vecindario) {
    if (vecino < mejor_vecino && lista_tabu.find(vecino) == lista_tabu.end()) {
      mejor_vecino = vecino;
    }
  }
  return mejor_vecino;
}

void AlgoritmoBusquedaTabu::decrementarTenenciaTabu(int iteracion_actual) {
    for (auto it = lista_tabu_.begin(); it != lista_tabu_.end();) {
    bool eliminar = true;
    for (int i = 0; i < it->first.getSolucion().size(); ++i) {
      if (contador_antiguedad_[i] + tenencia_tabu_ > iteracion_actual) {
        eliminar = false;
        break;
      }
    }
    if (eliminar) {
      it = lista_tabu_.erase(it);
    } else {
      ++it;
    }
  }
}


Solucion AlgoritmoBusquedaTabu::resolver() {
  // Paso 1: Inicializar la solución actual y la mejor solución
  Solucion mejor_solucion, solucion_actual;
  inicializar(mejor_solucion, solucion_actual);
  int iteraciones{0};
  // Paso 2:
  do {
    BusquedaLocal busqueda_local{solucion_actual};
    std::vector<Solucion> vecindario{
        busqueda_local.obtenerVecindarioIntercambio(problema_)};
    Solucion mejor_vecino{
        obtenerMejorVecino(vecindario, lista_tabu_, mejor_solucion)};
    solucion_actual = mejor_vecino;
    lista_tabu_[mejor_vecino] = tenencia_tabu_;
    if (mejor_vecino > mejor_solucion) {
      mejor_solucion = mejor_vecino;
      iteraciones = 0;
    } else {
      ++iteraciones;
    }
    decrementarTenenciaTabu(iteraciones);
  } while (iteraciones < maximo_iteraciones_);
  solucion_algoritmo_ = mejor_solucion;
  return solucion_algoritmo_;
}