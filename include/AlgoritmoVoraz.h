#pragma once

#include "Problema.h"
#include "Herramientas.h"
#include "Algoritmo.h"
#include "Solucion.h"
#include "BusquedaLocal.h"

class AlgoritmoVoraz : public Algoritmo {
 public:
  AlgoritmoVoraz(const std::string& nombre_fichero_puntos, int size_solucion)
      : problema_{nombre_fichero_puntos, size_solucion},
        solucion_algoritmo_{} {}
  Solucion resolver();
  Solucion getSolucion() const { return solucion_algoritmo_; }
  Solucion& getSolucion() { return solucion_algoritmo_; }
  Problema getProblema() const { return problema_; }
  Problema& getProblema() { return problema_; }

 private:
  Problema problema_;
  Solucion solucion_algoritmo_;
};