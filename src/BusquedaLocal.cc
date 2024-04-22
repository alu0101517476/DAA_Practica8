#include "../include/BusquedaLocal.h"

Solucion BusquedaLocal::explorarVecindario(Solucion& solucion_actual,
                                           const Problema& problema) {
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
      if (funcion_objetivo_actual < funcion_objetivo_nueva && (solucion_actual.getSolucion().size() == problema.getSizeSolucion())) {
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
  solucion_actual.setFuncionObjetivo(funcion_objetivo_actual);
  return solucion_busqueda_local_;
}