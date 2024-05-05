#include "../include/RamificacionYPoda/AlgoritmoRamificacionYPoda.h"

int AlgoritmoRamificacionYPoda::seleccionarSiguienteNodo() {
  int posicion_nodo{-1};
  if (estrategia_ == 0) {
    double distancia_minima{DBL_MAX};
    int indice{0};
    for (const auto& nodo : arbol_.getNodos()) {
      if (!nodo.getEstaPodado() && !nodo.getEstaExpandido() &&
          !nodo.getEsSolucion() && nodo.getCotaSuperior() < distancia_minima) {
        distancia_minima = nodo.getCotaSuperior();
        posicion_nodo = indice;
      }
      ++indice;
    }
  } else {  // Estrategia = 1, profundidad
    int nivel_maximo{-1}, indice{0};
    for (const auto& nodo : arbol_.getNodos()) {
      if (!nodo.getEstaPodado() && !nodo.getEstaExpandido() &&
          !nodo.getEsSolucion() && nodo.getSizeSolucion() > nivel_maximo) {
        nivel_maximo = nodo.getSizeSolucion();
        posicion_nodo = indice;
      }
      ++indice;
    }
  }
  return posicion_nodo;
}

Solucion AlgoritmoRamificacionYPoda::resolver() {
  int contador{0};
  while (!arbol_.todosLosNodosProcesados()) {
    arbol_.poda();
    int posicion_nodo{seleccionarSiguienteNodo()};
    if (posicion_nodo != -1) {
      arbol_.expandirNodo(posicion_nodo, problema_);
      for (auto& nodo : arbol_.getNodos()) {
        if (nodo.getSizeSolucion() == problema_.getSizeSolucion()) {
          nodo.setEsSolucion(true);
          
          Solucion solucion{nodo.getSolucionParcial()};

          if (solucion.getFuncionObjetivo() >=
              arbol_.getLimiteInferior()) {
            arbol_.setLimiteInferior(solucion.getFuncionObjetivo());
            solucion_algoritmo_ = nodo.getSolucionParcial();
          }
        }
      }
    } else {
      break;
    }
  }
  return solucion_algoritmo_;
}
