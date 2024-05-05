#include "../include/RamificacionYPoda/Nodo.h"

std::ostream& operator<<(std::ostream& os, const Nodo& nodo) {
  os << "Valor: " << nodo.valor_ << std::endl;
  os << "Cota superior: " << nodo.cota_superior_ << std::endl;
  if (nodo.esta_expandido_) os << "Esta expandido" << std::endl;
  if (nodo.esta_podado_) os << "Esta podado" << std::endl;
  if (nodo.es_solucion_) os << "Es solución" << std::endl;
  os << nodo.solucion_parcial_ << std::endl;
  return os;
}
