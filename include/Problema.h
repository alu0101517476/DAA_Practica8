#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_set>

#include "Punto.h"

class Problema {
 public:
  Problema(const std::string& nombre_fichero_puntos, int size_solucion);
  Punto operator[](const int& identificador);
  std::vector<Punto> getListaPuntos() const { return lista_puntos_; }
  std::vector<Punto>& getListaPuntos() { return lista_puntos_; }
  std::vector<Punto> obtenerPuntosSinProcesar(const std::vector<Punto> puntos_procesados) const;
  int getSizeSolucion() const { return size_solucion_; }
  int getNumeroPuntos() const { return numero_puntos_; }
  int getDimensionPuntos() const { return dimension_puntos_; }
  Punto getPunto(int indice_punto) const { return lista_puntos_[indice_punto]; }
  friend std::ostream& operator<<(std::ostream& os, const Problema& problema);

 private:
  std::vector<Punto> lista_puntos_;
  int numero_puntos_;
  int dimension_puntos_;
  int size_solucion_;
};

std::ostream& operator<<(std::ostream& os, const Problema& problema);
