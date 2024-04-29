#include "../include/BusquedaLocal.h"

Solucion BusquedaLocal::explorarVecindarioReinsercion(
    Solucion& solucion_actual, const Problema& problema) {
  double funcion_objetivo_actual{solucion_actual.calcularFuncionObjetivo()};
  bool insercion_punto{false};
  for (int i{0}; i < solucion_actual.getSolucion().size(); ++i) {
    Punto punto_a_eliminar{solucion_actual.getSolucion()[i]};
    solucion_actual.eliminarPuntoSolucion(punto_a_eliminar);
    for (const auto& punto : problema.getListaPuntos()) {
      if (!solucion_actual.seEncuentraEnLaSolucion(punto)) {
        solucion_actual.agregarPuntoSolucion(punto, i);
        insercion_punto = true;
      }
      double funcion_objetivo_nueva{solucion_actual.calcularFuncionObjetivo()};
      if (funcion_objetivo_actual < funcion_objetivo_nueva &&
          (solucion_actual.getSolucion().size() ==
           problema.getSizeSolucion())) {
        solucion_actual.setFuncionObjetivo(funcion_objetivo_nueva);
        solucion_busqueda_local_ = solucion_actual;
        return solucion_busqueda_local_;
      }
      if (insercion_punto) {
        solucion_actual.eliminarPuntoSolucion(punto);
        insercion_punto = false;
      }
    }
    if (!insercion_punto) {
      solucion_actual.agregarPuntoSolucion(punto_a_eliminar, i);
    }
  }
  solucion_busqueda_local_ = solucion_actual;
  solucion_busqueda_local_.setFuncionObjetivo(funcion_objetivo_actual);
  return solucion_busqueda_local_;
}

Solucion BusquedaLocal::explorarVecindarioReinsercion(
    const Problema& problema) {
  double funcion_objetivo_actual{
      solucion_busqueda_local_.calcularFuncionObjetivo()};
  bool insercion_punto{false};
  for (int i{0}; i < solucion_busqueda_local_.getSolucion().size(); ++i) {
    Punto punto_a_eliminar{solucion_busqueda_local_.getSolucion()[i]};
    solucion_busqueda_local_.eliminarPuntoSolucion(punto_a_eliminar);
    for (const auto& punto : problema.getListaPuntos()) {
      if (!solucion_busqueda_local_.seEncuentraEnLaSolucion(punto)) {
        solucion_busqueda_local_.agregarPuntoSolucion(punto, i);
        insercion_punto = true;
      }
      double funcion_objetivo_nueva{
          solucion_busqueda_local_.calcularFuncionObjetivo()};
      if (funcion_objetivo_actual < funcion_objetivo_nueva &&
          (solucion_busqueda_local_.getSolucion().size() ==
           problema.getSizeSolucion())) {
        solucion_busqueda_local_.setFuncionObjetivo(funcion_objetivo_nueva);
        return solucion_busqueda_local_;
      }
      if (insercion_punto) {
        solucion_busqueda_local_.eliminarPuntoSolucion(punto);
        insercion_punto = false;
      }
    }
    if (!insercion_punto) {
      solucion_busqueda_local_.agregarPuntoSolucion(punto_a_eliminar, i);
    }
  }
  return solucion_busqueda_local_;
}

Solucion BusquedaLocal::explorarVecindarioIntercambio(Solucion& solucion_actual,
                                                      Problema& problema) {
  double funcion_objetivo_actual{solucion_actual.calcularFuncionObjetivo()};
  for (int i{0}; i < solucion_actual.getSolucion().size(); ++i) {
    Punto punto_a_eliminar{solucion_actual[i]};
    for (int j{0}; j < problema.getListaPuntos().size(); ++j) {
      if (!solucion_actual.seEncuentraEnLaSolucion(
              problema.getListaPuntos()[j])) {
        std::swap(solucion_actual.getSolucion()[i], problema.getListaPuntos()[j]);
      }
      double funcion_objetivo_nueva{solucion_actual.calcularFuncionObjetivo()};
      if (funcion_objetivo_actual < funcion_objetivo_nueva) {
        solucion_busqueda_local_ = solucion_actual;
        solucion_busqueda_local_.setFuncionObjetivo(funcion_objetivo_nueva);
        return solucion_busqueda_local_;
      }
      // Como no ha mejorado la solución, devolvemos el punto
      // a donde estaba
      solucion_actual.eliminarPuntoSolucion(solucion_actual[i]);
      solucion_actual.agregarPuntoSolucion(punto_a_eliminar, i);
    }
  }
  return solucion_busqueda_local_;
}

Solucion BusquedaLocal::explorarVecindarioIntercambio(Problema& problema) {
  double funcion_objetivo_actual{
      solucion_busqueda_local_.calcularFuncionObjetivo()};
  for (int i{0}; i < solucion_busqueda_local_.getSolucion().size(); ++i) {
    Punto punto_a_eliminar{solucion_busqueda_local_[i]};
    for (int j{0}; j < problema.getListaPuntos().size(); ++j) {
      if (!solucion_busqueda_local_.seEncuentraEnLaSolucion(
              problema.getListaPuntos()[j])) {
        std::swap(solucion_busqueda_local_.getSolucion()[i], problema.getListaPuntos()[j]);
      }
      double funcion_objetivo_nueva{solucion_busqueda_local_.calcularFuncionObjetivo()};
      if (funcion_objetivo_actual < funcion_objetivo_nueva) {
        solucion_busqueda_local_ = solucion_busqueda_local_;
        solucion_busqueda_local_.setFuncionObjetivo(funcion_objetivo_nueva);
        return solucion_busqueda_local_;
      }
      // Como no ha mejorado la solución, devolvemos el punto
      // a donde estaba
      solucion_busqueda_local_.eliminarPuntoSolucion(solucion_busqueda_local_[i]);
      solucion_busqueda_local_.agregarPuntoSolucion(punto_a_eliminar, i);
    }
  }
  return solucion_busqueda_local_;
}

std::vector<Solucion> BusquedaLocal::obtenerVecindarioIntercambio(Solucion& solucion_actual, Problema& problema) {
  std::vector<Solucion> vecindario;
  for (int i{0}; i < solucion_actual.getSolucion().size(); ++i) {
    Punto punto_a_eliminar{solucion_actual[i]};
    for (int j{0}; j < problema.getListaPuntos().size(); ++j) {
      if (!solucion_actual.seEncuentraEnLaSolucion(problema.getListaPuntos()[j])) {
        std::swap(solucion_actual.getSolucion()[i], problema.getListaPuntos()[j]);
        vecindario.emplace_back(solucion_actual);
        // Devolvemos el punto que eliminamos a su sitio
        solucion_actual.eliminarPuntoSolucion(solucion_actual[i]);
        solucion_actual.agregarPuntoSolucion(punto_a_eliminar, i);
      }
    }
  }
  return vecindario;
}
  
std::vector<Solucion> BusquedaLocal::obtenerVecindarioIntercambio(Problema& problema) {
  std::vector<Solucion> vecindario;
  for (int i{0}; i < solucion_busqueda_local_.getSolucion().size(); ++i) {
    Punto punto_a_eliminar{solucion_busqueda_local_[i]};
    for (int j{0}; j < problema.getListaPuntos().size(); ++j) {
      if (!solucion_busqueda_local_.seEncuentraEnLaSolucion(problema.getListaPuntos()[j])) {
        std::swap(solucion_busqueda_local_.getSolucion()[i], problema.getListaPuntos()[j]);
        vecindario.emplace_back(solucion_busqueda_local_);
        // Devolvemos el punto que eliminamos a su sitio
        solucion_busqueda_local_.eliminarPuntoSolucion(solucion_busqueda_local_[i]);
        solucion_busqueda_local_.agregarPuntoSolucion(punto_a_eliminar, i);
      }
    }
  }
  return vecindario;
}