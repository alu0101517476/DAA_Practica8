#include "../include/RamificacionYPoda/Arbol.h"

Arbol::Arbol(const Problema &problema, const Solucion& solucion_inicial) {
  size_solucion_ = problema.getSizeSolucion();
  limite_inferior_ = solucion_inicial.getFuncionObjetivo();
  for (int i{0}; i < problema.getSizeSolucion(); ++i) {
    std::vector<Punto> lista_puntos{problema.getPunto(i)};
    Nodo nodo{0, calcularLimiteSuperior(problema, lista_puntos)};
    nodo.setSolucionParcial(Solucion{lista_puntos});
    nodos_.emplace_back(nodo);
  }
  for (int i{0}; i < nodos_.size(); ++i) {
    nodos_activos_.emplace_back(i);
  }
}

void Arbol::poda() {
  int indice{0};
  for (auto& nodo : nodos_) {
    if (nodo.getValor() + nodo.getCotaSuperior() < limite_inferior_) {
      nodo.setEstaPodado(true);
      if (std::find(nodos_activos_.begin(), nodos_activos_.end(), indice) !=
          nodos_activos_.end()) {
        nodos_activos_.erase(
            std::find(nodos_activos_.begin(), nodos_activos_.end(), indice));
      }
    }
    ++indice;
  }
}

double Arbol::calcularLimiteSuperior(
    const Problema& problema, const std::vector<Punto>& puntos_procesados) {
  std::vector<Punto> puntos_sin_procesar{
      problema.obtenerPuntosSinProcesar(puntos_procesados)};
  std::vector<double> limite_superior, limite_superior2;
  // Creamos la lista ordenada de distancias entre los puntos procesados y los
  // no procesados
  for (const auto& punto : puntos_procesados) {
    for (const auto& punto_no_procesado : puntos_sin_procesar) {
      double distancia{calcularDistanciaEuclidea(punto, punto_no_procesado)};
      int posicion{0};
      for (int i{0}; i < limite_superior.size(); ++i) {
        if (distancia < limite_superior[i]) {
          ++posicion;
        }
      }
      limite_superior.insert(limite_superior.begin() + posicion, distancia);
    }
  }
  // Calculamos la cota superior
  double valor_limite_superior = calcularLimiteSuperiorPuntosProcesados(
      puntos_procesados.size(), limite_superior);

  // Creamos la lista ordenada de distancias entre los puntos no procesados
  for (int i{0}; i < puntos_sin_procesar.size(); ++i) {
    for (int j{i + 1}; j < puntos_sin_procesar.size(); ++j) {
      double distancia{calcularDistanciaEuclidea(puntos_sin_procesar[i],
                                                 puntos_sin_procesar[j])};
      int posicion{0};
      for (int k{0}; k < limite_superior2.size(); ++k) {
        if (distancia < limite_superior2[k]) {
          ++posicion;
        }
      }
      limite_superior2.insert(limite_superior2.begin() + posicion, distancia);
    }
  }
  // Calculamos la cota superior
  double valor_limite_superior2 = calcularLimiteSuperiorPuntosNoProcesados(
      puntos_sin_procesar.size(), limite_superior2);
  return valor_limite_superior + valor_limite_superior2;
}

double Arbol::calcularLimiteSuperiorPuntosProcesados(
    int numero_puntos, const std::vector<double>& lista_distancias) {
  double limite_superior{0};
  // determinamos cuántos elementos del vector lista_distancias deben ser
  // sumados para calcular la cota. El tamaño se basa en el producto del número
  // de puntos procesados (lista_distancias) y la diferencia entre el tamaño
  // total de la solución deseada (numero_puntos) y el número de puntos
  // procesados, lo cual conceptualmente representa cuántas posibles conexiones
  // o interacciones hay entre puntos procesados y no procesados.

  int size{numero_puntos * (size_solucion_ - numero_puntos)};
  size = std::min(size, static_cast<int>(lista_distancias.size()));
  for (int i{0}; i < size; ++i) {
    limite_superior += lista_distancias[i];
  }
  return limite_superior;
}

double Arbol::calcularLimiteSuperiorPuntosNoProcesados(
    int numero_puntos, const std::vector<double>& lista_distancias) {
  double limite_superior{0};
  int size{numero_puntos * (size_solucion_ - numero_puntos)};
  size = std::min(size, static_cast<int>(lista_distancias.size()));
  for (int i{0}; i < size; ++i) {
    limite_superior += lista_distancias[i];
  }
  return limite_superior;
}

void Arbol::expandirNodo(int posicion_nodo, const Problema& problema) {
  nodos_[posicion_nodo].setEstaExpandido(true);
  nodos_activos_.erase(
      std::find(nodos_activos_.begin(), nodos_activos_.end(), posicion_nodo));
  int nivel_actual{nodos_[posicion_nodo].getSizeSolucion()};
  int ultimo_punto{nodos_[posicion_nodo].getSolucionParcial().getSolucion().back().getIdentificador() + 1};
  int numero_puntos{problema.getListaPuntos().size()};
  Solucion solucion_parcial{nodos_[posicion_nodo].getSolucionParcial()};
  for (int i{ultimo_punto}; i < (numero_puntos - (size_solucion_ - nivel_actual)); ++i) {
    Solucion solucion{solucion_parcial};
    solucion.agregarPunto(problema.getPunto(i));
    double valor_nodo{solucion.calcularFuncionObjetivo()};
    Nodo nodo{valor_nodo, calcularLimiteSuperior(problema, solucion.getSolucion())};
    nodo.setSolucionParcial(solucion);
    nodos_.emplace_back(nodo);
    nodos_activos_.emplace_back(nodos_.size() - 1);
  }
}

Solucion Arbol::revisarNodosArbol() {
  Solucion mejor_solucion_encontrada;
  for (const auto& nodo : nodos_) {
    std::cout << nodo.getSizeSolucion() << std::endl;
    if (nodo.getSizeSolucion() == size_solucion_ && !nodo.getEstaPodado() && nodo.getEsSolucion()) {
      Solucion solucion_actual{nodo.getSolucionParcial()};
      if (solucion_actual.getFuncionObjetivo() > mejor_solucion_encontrada.getFuncionObjetivo()) {
        mejor_solucion_encontrada = solucion_actual;
      }
    }
  }
  mejor_solucion_encontrada.setFuncionObjetivo(mejor_solucion_encontrada.calcularFuncionObjetivo());
  return mejor_solucion_encontrada;
}

std::ostream& operator<<(std::ostream& os, const Arbol& arbol) {
  os << "Size solucion: " << arbol.size_solucion_ << std::endl;
  os << "Limite inferior: " << arbol.limite_inferior_ << std::endl;
  os << "Nodos: " << std::endl; 
  for (const auto& nodo : arbol.nodos_) {
    os << nodo << std::endl;
  }
  os << "Nodos activos: " << std::endl;
  for (const auto& nodo_activo : arbol.nodos_activos_) {
    os << nodo_activo << " ";
  }
  os << std::endl;
  return os;
}
