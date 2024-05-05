#pragma once

#include "Solucion.h"

class Nodo {
 public:
  Nodo() {}
  Nodo(double valor, double cota_superior)
      : valor_(valor),
        cota_superior_(cota_superior),
        esta_expandido_{false},
        esta_podado_{false},
        es_solucion_{false} {}
  void agregarPunto(const Punto& punto) {
    solucion_parcial_.agregarPunto(punto);
  }
  // getters
  double getValor() const { return valor_; }
  double getCotaSuperior() const { return cota_superior_; }
  Solucion getSolucionParcial() const { return solucion_parcial_; }
  bool getEstaPodado() const { return esta_podado_; }
  bool getEstaExpandido() const { return esta_expandido_; }
  bool getEsSolucion() const { return es_solucion_; }
  size_t getSizeSolucion() const { return solucion_parcial_.getSolucion().size(); }
  // setters
  void setSolucionParcial(const Solucion& solucion_parcial) { solucion_parcial_ = solucion_parcial; }
  void setEstaPodado(bool esta_podado) { esta_podado_ = esta_podado; }
  void setEstaExpandido(bool esta_expandido) { esta_expandido_ = esta_expandido; }
  void setEsSolucion(bool es_solucion) { es_solucion_ = es_solucion; }
  friend std::ostream& operator<<(std::ostream& os, const Nodo& nodo);

 private:
  Solucion solucion_parcial_;
  double valor_;
  double cota_superior_;
  bool esta_expandido_;
  bool esta_podado_;
  bool es_solucion_;
};

std::ostream& operator<<(std::ostream& os, const Nodo& nodo);
