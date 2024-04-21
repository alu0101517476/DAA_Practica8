#include "../include/BusquedaLocal.h"

Solucion BusquedaLocal::explorarVecindario(Solucion& solucion_actual,
                                           const Problema& problema) {
  double funcion_objetivo_actual{solucion_actual.calcularFuncionObjetivo()};
  for (int i{0}; i < solucion_actual.getSolucion().size(); ++i) {
    solucion_actual.eliminarPuntoSolucion(solucion_actual.getSolucion()[i]);
    for (const auto& punto : problema.getListaPuntos()) {
      if (!solucion_actual.seEncuentraEnLaSolucion(punto)) {
        solucion_actual.agregarPuntoSolucion(punto, i);
      }
      double funcion_objetivo_nueva{solucion_actual.calcularFuncionObjetivo()};
      if (funcion_objetivo_actual < funcion_objetivo_nueva) {
        solucion_actual.setFuncionObjetivo(funcion_objetivo_nueva);
        solucion_busqueda_local_ = solucion_actual;
        return solucion_busqueda_local_;
      }
    }
  }
  solucion_busqueda_local_ = solucion_actual;
  return solucion_busqueda_local_;
}