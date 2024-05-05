#pragma once

#include <iostream>
#include <vector>

#include "Nodo.h"
#include "Problema.h"
#include "Solucion.h"
#include "Punto.h"
#include "Herramientas.h"

class Arbol {
 public:
  // Constructor por parámetros que genera el primer nivel del árbol
  Arbol(const Problema &problema, const Solucion& solucion_inicial);
  void poda();
  void expandirNodo(int posicion_nodo, const Problema &problema);
  Solucion revisarNodosArbol();
  double calcularLimiteSuperior(const Problema& problema, const std::vector<Punto>& lista_puntos);
  double calcularLimiteSuperiorPuntosProcesados(int numero_puntos, const std::vector<double>& lista_distancias);
  double calcularLimiteSuperiorPuntosNoProcesados(int numero_puntos, const std::vector<double>& lista_distancias);
  std::vector<Nodo> getNodos() const { return nodos_; } 
  std::vector<Nodo>& getNodos() { return nodos_; } 
  double getLimiteInferior() const { return limite_inferior_; }
  std::vector<int> getNodosActivos() const { return nodos_activos_; }
  bool todosLosNodosProcesados() const { return nodos_activos_.empty(); }
  void setLimiteInferior(const double& limite_inferior) { limite_inferior_ = limite_inferior; }
  friend std::ostream& operator<<(std::ostream& os, const Arbol& arbol);

 private:
  int size_solucion_;
  std::vector<Nodo> nodos_;
  std::vector<int> nodos_activos_;
  double limite_inferior_;
};

std::ostream& operator<<(std::ostream& os, const Arbol& arbol);
