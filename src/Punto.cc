#include "../include/Punto.h"

void Punto::agregarCoordenada(const double& coordenada) {
  coordenadas_.emplace_back(coordenada);
}

bool Punto::operator==(const Punto& punto2) const {
  return (coordenadas_ == punto2.coordenadas_);
}


Punto Punto::operator=(const Punto& punto2) {
  identificador_ = punto2.identificador_;
  coordenadas_ = punto2.coordenadas_;
  return *this;
}

std::ostream& operator<<(std::ostream& os, const Punto& punto) {
  os << punto.identificador_ << ": ";
  for (const auto& coordenada : punto.coordenadas_) {
    os << coordenada << ' ';
  }
  return os;
}