#include "../include/Solucion.h"

void Solucion::agregarPunto(const Punto& punto) {
  solucion_.emplace_back(punto);
}

double Solucion::calcularFuncionObjetivo() {
  funcion_objetivo_ = 0;
  for (int i{0}; i < solucion_.size(); ++i) {
    for (int j{i + 1}; j < solucion_.size(); ++j) {
      funcion_objetivo_ +=
          calcularDistanciaEuclidea(solucion_[i], solucion_[j]);
    }
  }
  return funcion_objetivo_;
}

bool Solucion::seEncuentraEnLaSolucion(const Punto& punto) {
  auto iterador{std::find(solucion_.begin(), solucion_.end(), punto)};
  if (iterador != solucion_.end()) return true;
  return false;
}

void Solucion::eliminarPuntoSolucion(const Punto& punto) {
  auto iterador{std::find(solucion_.begin(), solucion_.end(), punto)};
  if (iterador != solucion_.end()) solucion_.erase(iterador);
}

void Solucion::agregarPuntoSolucion(const Punto& punto, const int& indice) {
  solucion_.emplace(solucion_.begin() + indice, punto);
}

void Solucion::setFuncionObjetivo(const double& funcion_objetivo) {
  funcion_objetivo_ = funcion_objetivo;
}

Punto Solucion::operator[](const int& indice) { return solucion_[indice]; }

bool Solucion::operator<(const Solucion& solucion) const {
  return funcion_objetivo_ < solucion.getFuncionObjetivo();
}

bool Solucion::operator>(const Solucion& solucion) const {
  return funcion_objetivo_ > solucion.getFuncionObjetivo();
}

std::ostream& operator<<(std::ostream& os, const Solucion& solucion) {
  os << solucion.funcion_objetivo_ << std::endl;
  for (const auto& punto : solucion.solucion_) {
    os << punto << std::endl;
  }
  return os;
}
