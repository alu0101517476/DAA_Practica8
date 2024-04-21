#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include "Herramientas.h"
#include "Punto.h"

class Solucion {
 public:
  Solucion() = default;
  Solucion(const std::vector<Punto>& puntos) : solucion_{puntos} {}
  void agregarPunto(const Punto& punto);
  double calcularFuncionObjetivo();
  std::vector<Punto> getSolucion() const { return solucion_; }
  double getFuncionObjetivo() const { return funcion_objetivo_; }
  bool seEncuentraEnLaSolucion(const Punto& punto);
  void eliminarPuntoSolucion(const Punto& punto);
  void agregarPuntoSolucion(const Punto& punto, const int& indice);
  void setFuncionObjetivo(const double& funcion_objetivo);
  Punto operator[](const int& indice);
  friend std::ostream& operator<<(std::ostream& os, const Solucion& solucion);

 private:
  double funcion_objetivo_{0.0};
  std::vector<Punto> solucion_;
};

std::ostream& operator<<(std::ostream& os, const Solucion& solucion);
