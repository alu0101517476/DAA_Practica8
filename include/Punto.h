#pragma once

#include <iostream>
#include <vector>
#include <cmath>

class Punto {
 public:
  Punto() = default;
  Punto(int identificador) : identificador_{identificador} {}
  Punto(int identificador, std::vector<double> coordenadas)
      : identificador_{identificador}, coordenadas_{coordenadas} {}
  void agregarCoordenada(const double& coordenada);
  std::vector<double> getCoordenadas() const { return coordenadas_; }
  int getIdentificador() const { return identificador_; }
  Punto operator=(const Punto& punto2);
  bool operator==(const Punto& punto2) const;
  friend std::ostream& operator<<(std::ostream& os, const Punto& punto);

 private:
  int identificador_;
  std::vector<double> coordenadas_;
};

std::ostream& operator<<(std::ostream& os, const Punto& punto);

