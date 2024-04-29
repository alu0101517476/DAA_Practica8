#include "../include/AlgoritmoGrasp.h"

Punto AlgoritmoGrasp::escogerCandidatoLRC(
    const Punto& punto_central, const std::vector<Punto>& puntos) {
  std::vector<std::pair<double, Punto>> puntos_lejanos;
  for (const auto& punto : puntos) {
    double distancia{calcularDistanciaEuclidea(punto_central, punto)};
    puntos_lejanos.emplace_back(distancia, punto);
  }
  std::sort(puntos_lejanos.begin(), puntos_lejanos.end(),
            [](const std::pair<double, Punto>& candidato1,
               const std::pair<double, Punto>& candidato2) {
              return candidato1.first < candidato2.first;
            });
  // Construimos la lista con los 3 mejores candidatos
  int inicio_indice_aleatorio{puntos_lejanos.size() - 1};
  if (puntos_lejanos.size() >= 3) {
    inicio_indice_aleatorio = puntos_lejanos.size() - size_lrc_;
  } else if (puntos_lejanos.size() == 2) {
    inicio_indice_aleatorio = puntos_lejanos.size() - size_lrc_;
  }
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(inicio_indice_aleatorio, puntos_lejanos.size() - 1);
  // Devolvemos el candidato escogido aleatoriamente
  return puntos_lejanos[distrib(gen)].second;
}

Solucion AlgoritmoGrasp::faseConstructiva() {
  std::vector<Punto> puntos_problema{problema_.getListaPuntos()};
  // Obtener sc = centro(Elem);
  Punto centroide{calcularCentro(puntos_problema)};
  Solucion solucion_fase_constructiva;
  do {
    // Obtener el elemento s∗ ∈ Elem más alejado de sc
    Punto punto_mas_lejano_centro{escogerCandidatoLRC(centroide, puntos_problema)};
    // S = S ∪ {s∗};
    solucion_fase_constructiva.agregarPunto(punto_mas_lejano_centro);
    // Elem = Elem − {s∗};
    auto iterador{std::find(puntos_problema.begin(), puntos_problema.end(),
                            punto_mas_lejano_centro)};
    puntos_problema.erase(iterador);
    // Obtener sc = centro(S);
    centroide = calcularCentro(solucion_fase_constructiva.getSolucion());
  } while (solucion_fase_constructiva.getSolucion().size() <
           problema_.getSizeSolucion());
  solucion_fase_constructiva.setFuncionObjetivo(
      solucion_fase_constructiva.calcularFuncionObjetivo());
  return solucion_fase_constructiva;
}

Solucion AlgoritmoGrasp::resolver() {
  solucion_algoritmo_ = faseConstructiva();
  int numero_intentos{0};
  for (int i{0}; i < 1000; ++i) {
    BusquedaLocal busqueda_local{faseConstructiva()};
    busqueda_local.explorarVecindarioIntercambio(problema_);
    double funcion_objetivo_busqueda{busqueda_local.getSolucion().calcularFuncionObjetivo()};
    if (solucion_algoritmo_.calcularFuncionObjetivo() < funcion_objetivo_busqueda) {
      solucion_algoritmo_ = busqueda_local.getSolucion();
      numero_intentos = 0;
    } else {
      ++numero_intentos;
    }
    if (numero_intentos == maximo_iteraciones_) break;
  }
  return solucion_algoritmo_;
}