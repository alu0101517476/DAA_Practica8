#pragma once

#include <cfloat>

#include "Algoritmo.h"
#include "Arbol.h"
#include "BusquedaLocal.h"
#include "Herramientas.h"
#include "Problema.h"
#include "Solucion.h"

class AlgoritmoRamificacionYPoda : public Algoritmo {
 public:
  AlgoritmoRamificacionYPoda(const std::string& nombre_fichero,
                             const Solucion& solucion_inicial,
                             int size_solucion, int estrategia)
      : problema_{nombre_fichero, size_solucion},
        arbol_{problema_, solucion_inicial},
        estrategia_{estrategia},
        solucion_algoritmo_{} {};
  Solucion resolver();
  int seleccionarSiguienteNodo();
  Arbol getArbol() const { return arbol_; }

 private:
  Problema problema_;
  Arbol arbol_;
  // 0 = expansion_cota_pequeña, 1 = expansion_profundidad
  int estrategia_;
  Solucion solucion_algoritmo_;
};