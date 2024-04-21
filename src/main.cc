#pragma once

#include "../include/AlgoritmoVoraz.h"
#include "../include/BusquedaLocal.h"
#include "../include/Problema.h"
#include "../include/Solucion.h"

void imprimirTablaResultados1Voraz(const std::string& nombre_problema) {
  for (int i{2}; i <= 5; ++i) {
    AlgoritmoVoraz voraz{nombre_problema, i};
    auto start{std::chrono::high_resolution_clock::now()};
    voraz.resolver();
    auto end{std::chrono::high_resolution_clock::now()};
    int duracion{
        std::chrono::duration_cast<std::chrono::microseconds>(end - start)
            .count()};
    imprimirDatosTabla(voraz.getProblema().getSizeSolucion(),
                       voraz.getSolucion(), voraz.getProblema(),
                       nombre_problema, duracion);
  }
  std::cout << "------------------------------------------------------------------------------------"
            << std::endl;
}

void imprimirTablaResultados1BusquedaLocal(const std::string& nombre_problema) {
  for (int i{2}; i <= 5; ++i) {
    AlgoritmoVoraz voraz{nombre_problema, i};
    voraz.resolver();
    BusquedaLocal busqueda_local;
    auto start{std::chrono::high_resolution_clock::now()};
    busqueda_local.explorarVecindario(voraz.getSolucion(), voraz.getProblema());
    auto end{std::chrono::high_resolution_clock::now()};
    int duracion{
        std::chrono::duration_cast<std::chrono::microseconds>(end - start)
            .count()};
    imprimirDatosTabla(voraz.getProblema().getSizeSolucion(),
                       voraz.getSolucion(), voraz.getProblema(),
                       nombre_problema, duracion);
  }
  std::cout << "------------------------------------------------------------------------------------"
            << std::endl;
}

int main() {
  std::cout << "\t\tAlgoritmo Voraz" << std::endl;
  printf("%-25s %-5s %-5s %-5s %-3s %6s %12s\n", "Problema", "n", "K", "m", "z",
         "S", "CPU");
  std::vector<std::string> problemas{
      "MAXDIV/max_div_15_2.txt", "MAXDIV/max_div_20_2.txt",
      "MAXDIV/max_div_30_2.txt", "MAXDIV/max_div_15_3.txt",
      "MAXDIV/max_div_20_3.txt", "MAXDIV/max_div_30_3.txt"};
  for (const auto& problema : problemas) {
    imprimirTablaResultados1Voraz(problema);
  }
  std::cout << "\t\tBusqueda Local" << std::endl;
  printf("%-25s %-5s %-5s %-5s %-3s %6s %12s\n", "Problema", "n", "K", "m", "z",
         "S", "CPU");
  for (const auto& problema : problemas) {
    imprimirTablaResultados1BusquedaLocal(problema);
  }
  return 0;
}
