#include "../include/Herramientas.h"

double calcularDistanciaEuclidea(const Punto& punto1, const Punto& punto2) {
  int distancia_euclidea{0};
  for (int i{0}; i < punto1.getCoordenadas().size(); ++i) {
    distancia_euclidea +=
        pow(punto1.getCoordenadas()[i] - punto2.getCoordenadas()[i], 2);
  }
  return sqrt(distancia_euclidea);
}

Punto calcularCentro(const std::vector<Punto>& puntos) {
  Punto centroide;
  int suma{0};
  for (const auto& punto : puntos) {
    for (int i{0}; i < punto.getCoordenadas().size(); ++i) {
      suma += punto.getCoordenadas()[i];
    }
    suma /= puntos.size();
    centroide.agregarCoordenada(suma);
  }
  return centroide;
}

Punto hallarPuntoMasLejanoCentro(const Punto& punto_central,
                                 const std::vector<Punto>& puntos) {
  Punto punto_mas_lejano;
  double distancia_mas_lejana{-999};
  for (const auto& punto : puntos) {
    double distancia{calcularDistanciaEuclidea(punto_central, punto)};
    if (distancia_mas_lejana < distancia) {
      distancia_mas_lejana = distancia;
      punto_mas_lejano = punto;
    }
  }
  return punto_mas_lejano;
}

std::string pasarPuntosString(const Solucion& solucion) {
  std::string puntos{""};
  for (const auto& punto : solucion.getSolucion()) {
    puntos += (' ' + std::to_string(punto.getIdentificador()));
  }
  return puntos;
}

void imprimirDatosTabla(int size_solucion, const Solucion& solucion,
                        const Problema& problema,
                        const std::string& nombre_fichero,
                        int tiempo_ejecucion) {
  printf("%-25s %-5d %-5d %-6d", nombre_fichero.c_str(),
         problema.getNumeroPuntos(), problema.getDimensionPuntos(),
         problema.getSizeSolucion());
  printf("%.4f %-11s %-2d\n", solucion.getFuncionObjetivo(),
         pasarPuntosString(solucion).c_str(), tiempo_ejecucion);
}