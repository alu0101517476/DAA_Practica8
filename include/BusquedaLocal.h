#pragma once

#include <iostream>
#include <algorithm>

#include "Problema.h"
#include "Solucion.h"

class BusquedaLocal {
 public:
  BusquedaLocal() {}
  BusquedaLocal(const Solucion& solucion)
      : solucion_busqueda_local_{solucion} {}
  Solucion explorarVecindarioReinsercion(Solucion& solucion_actual,
                                         const Problema& problema);
  Solucion explorarVecindarioReinsercion(const Problema& problema);
  Solucion explorarVecindarioIntercambio(Solucion& solucion_actual, Problema& problema);
  Solucion explorarVecindarioIntercambio(Problema& problema);
  std::vector<Solucion> obtenerVecindarioIntercambio(Solucion& solucion_actual, Problema& problema);
  std::vector<Solucion> obtenerVecindarioIntercambio(Problema& problema);
  Solucion getSolucion() { return solucion_busqueda_local_; }

 private:
  Solucion solucion_busqueda_local_;
};