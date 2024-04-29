#pragma once

#include <algorithm>
#include <random>

#include "Algoritmo.h"
#include "BusquedaLocal.h"
#include "Problema.h"
#include "Solucion.h"

class AlgoritmoGrasp : public Algoritmo {
 public:
  AlgoritmoGrasp(const std::string& nombre_fichero_puntos, int size_solucion,
                 int size_lrc, int maximo_iteraciones = 200)
      : problema_{nombre_fichero_puntos, size_solucion},
        solucion_algoritmo_{},
        maximo_iteraciones_{maximo_iteraciones},
        size_lrc_{size_lrc} {}
  Solucion faseConstructiva();
  Punto escogerCandidatoLRC(const Punto& punto_central,
                            const std::vector<Punto>& puntos);
  Solucion resolver();
  Solucion& getSolucion() { return solucion_algoritmo_; }
  Solucion getSolucion() const { return solucion_algoritmo_; }
  Problema getProblema() const { return problema_; }
  int getMaximoIteraciones() const { return maximo_iteraciones_; }
  int getSizeLRC() const { return size_lrc_; }

 private:
  Problema problema_;
  Solucion solucion_algoritmo_;
  int size_lrc_;
  int maximo_iteraciones_;
};