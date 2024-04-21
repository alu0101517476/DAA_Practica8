#include "../include/AlgoritmoVoraz.h"

Solucion AlgoritmoVoraz::resolver() {
  std::vector<Punto> puntos_problema{problema_.getListaPuntos()};
  // Obtener sc = centro(Elem);
  Punto centroide{calcularCentro(puntos_problema)};
  do {
    // Obtener el elemento s∗ ∈ Elem más alejado de sc
    Punto punto_mas_lejano_centro{
        hallarPuntoMasLejanoCentro(centroide, puntos_problema)};
    // S = S ∪ {s∗};
    solucion_algoritmo_.agregarPunto(punto_mas_lejano_centro);
    // Elem = Elem − {s∗};
    auto iterador{std::find(puntos_problema.begin(), puntos_problema.end(),
                              punto_mas_lejano_centro)};
    puntos_problema.erase(iterador);
    // Obtener sc = centro(S);
    centroide = calcularCentro(solucion_algoritmo_.getSolucion());
  } while (solucion_algoritmo_.getSolucion().size() <
           problema_.getSizeSolucion());
  solucion_algoritmo_.setFuncionObjetivo(solucion_algoritmo_.calcularFuncionObjetivo());
  return solucion_algoritmo_;
}