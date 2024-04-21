#include "../include/Problema.h"

Problema::Problema(const std::string& nombre_fichero_puntos, int size_solucion) {
  size_solucion_ = size_solucion;
  std::ifstream fichero_puntos{nombre_fichero_puntos, std::ios::in};
  if (fichero_puntos.fail()) {
    std::cerr << "Error, no se pudo abrir el fichero correctamente"
              << std::endl;
    exit(1);
  }
  std::string linea, coordenada;
  std::getline(fichero_puntos, linea);
  numero_puntos_ = std::stoi(linea);
  std::getline(fichero_puntos, linea);
  dimension_puntos_ = std::stoi(linea);
  int identificador_punto{0};
  while (std::getline(fichero_puntos, linea)) {
    std::stringstream linea_aux{linea};
    lista_puntos_.emplace_back(Punto(identificador_punto));
    while (linea_aux >> coordenada) {
      // Reemplazamos las ',' por '.'
      size_t posicion_coma{coordenada.find(',')};
      coordenada.replace(posicion_coma, 1, 1, '.');
      lista_puntos_[identificador_punto].agregarCoordenada(std::stod(coordenada));
    }
    ++identificador_punto;
  }
  fichero_puntos.close();
}

Punto Problema::operator[](const int& identificador) {
  return lista_puntos_[identificador];
}

std::ostream& operator<<(std::ostream& os, const Problema& problema) {
  os << problema.numero_puntos_ << std::endl;
  os << problema.dimension_puntos_ << std::endl;
  for (const auto& punto : problema.lista_puntos_) {
    os << punto << std::endl;
  }
  return os;
}
