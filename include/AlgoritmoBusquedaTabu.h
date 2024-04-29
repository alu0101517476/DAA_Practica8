#pragma once

#include <map>

#include "Algoritmo.h"
#include "AlgoritmoGrasp.h"
#include "BusquedaLocal.h"
#include "Problema.h"
#include "Solucion.h"

class AlgoritmoBusquedaTabu : public Algoritmo {
 public:
  AlgoritmoBusquedaTabu(const std::string& nombre_fichero_puntos,
                        int size_solucion, int tenencia_tabu = 10,
                        int maximo_iteraciones = 200)
      : problema_{nombre_fichero_puntos, size_solucion},
        solucion_algoritmo_{},
        maximo_iteraciones_{maximo_iteraciones},
        nombre_fichero_puntos_{nombre_fichero_puntos},
        contador_antiguedad_{size_solucion, -1} {}

  // Método que simboliza el paso 1 del algoritmo
  void inicializar(Solucion& mejor_solucion, Solucion& solucion_actual);
  Solucion resolver();
  Solucion obtenerMejorVecino(std::vector<Solucion> vecindario,
                              const std::map<Solucion, int>& lista_tabu,
                              const Solucion& mejor_solucion);
  void decrementarTenenciaTabu(int iteracion_actual);
  Solucion& getSolucion() { return solucion_algoritmo_; }
  Problema getProblema() { return problema_; }

 private:
  // Solucion y tenencia
  std::map<Solucion, int> lista_tabu_;
  Problema problema_;
  Solucion solucion_algoritmo_;
  // Un registro de la "antigüedad" de los movimientos para cada componente de
  // la solución.
  std::vector<int> contador_antiguedad_;
  int tenencia_tabu_;
  int maximo_iteraciones_;
  std::string nombre_fichero_puntos_;
};