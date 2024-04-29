#include "../include/Herramientas.h"

double calcularDistanciaEuclidea(const Punto& punto1, const Punto& punto2) {
  double distancia_euclidea{0};
  for (int i{0}; i < punto1.getCoordenadas().size(); ++i) {
    distancia_euclidea +=
        pow(punto1.getCoordenadas()[i] - punto2.getCoordenadas()[i], 2);
  }
  return sqrt(distancia_euclidea);
}

Punto calcularCentro(const std::vector<Punto>& puntos) {
  Punto centroide;
  double suma{0}, dimension{puntos[0].getCoordenadas().size()};
  for (int i{0}; i < dimension; ++i) {
    for (int j{0}; j < puntos.size(); ++j) {
      suma += puntos[j].getCoordenadas()[i];
    }
    centroide.agregarCoordenada((suma / puntos.size()));
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
  printf("%.4f %-11s %-5ldµs\n", solucion.getFuncionObjetivo(),
         pasarPuntosString(solucion).c_str(), tiempo_ejecucion);
}

void imprimirDatosTablas2y3(int size_solucion, const Solucion& solucion,
                            const Problema& problema, int maximo_iteraciones,
                            int size_lrc, const std::string& nombre_fichero,
                            int tiempo_ejecucion) {
  //  Problema   n    k    m   ITER |LRC|  z    S     CPU
  printf("%-25s %-5d %-5d %-6d %-6d %-6d  %.4lf %-20s %-5ldµs\n",
         nombre_fichero.c_str(), problema.getNumeroPuntos(),
         problema.getDimensionPuntos(), size_solucion, maximo_iteraciones,
         size_lrc, solucion.getFuncionObjetivo(),
         pasarPuntosString(solucion).c_str(), tiempo_ejecucion);
}
