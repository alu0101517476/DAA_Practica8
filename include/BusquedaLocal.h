#pragma once

#include <iostream>

#include "Problema.h"
#include "Solucion.h"

class BusquedaLocal {
 public:
  Solucion explorarVecindario(Solucion& solucion_actual, const Problema& problema);
  Solucion getSolucion() { return solucion_busqueda_local_; }

 private: 
  Solucion solucion_busqueda_local_;
};