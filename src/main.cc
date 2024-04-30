#pragma once

#include "../include/AlgoritmoBusquedaTabu.h"
#include "../include/AlgoritmoGrasp.h"
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
  std::cout << "---------------------------------------------------------------"
               "---------------------"
            << std::endl;
}

void imprimirTablaResultados1BusquedaLocal(const std::string& nombre_problema) {
  for (int i{2}; i <= 5; ++i) {
    AlgoritmoVoraz voraz{nombre_problema, i};
    voraz.resolver();
    BusquedaLocal busqueda_local;
    auto start{std::chrono::high_resolution_clock::now()};
    busqueda_local.explorarVecindarioIntercambio(voraz.getSolucion(),
                                                 voraz.getProblema());
    auto end{std::chrono::high_resolution_clock::now()};
    int duracion{
        std::chrono::duration_cast<std::chrono::microseconds>(end - start)
            .count()};
    imprimirDatosTabla(voraz.getProblema().getSizeSolucion(),
                       voraz.getSolucion(), voraz.getProblema(),
                       nombre_problema, duracion);
  }
  std::cout << "---------------------------------------------------------------"
               "---------------------"
            << std::endl;
}

void imprimirTablasResultados2y3GRASP(const std::string& nombre_problema) {
  int size_lrc, maximo_iteraciones;
  for (int i{2}; i <= 5; ++i) {
    for (int j{0}; j < 4; ++j) {
      (j % 2 == 0) ? size_lrc = 2 : size_lrc = 3;
      (j < 2 == 0) ? maximo_iteraciones = 10 : maximo_iteraciones = 20;
      AlgoritmoGrasp grasp{nombre_problema, i, size_lrc, maximo_iteraciones};
      auto start{std::chrono::high_resolution_clock::now()};
      grasp.resolver();
      auto end{std::chrono::high_resolution_clock::now()};
      int duracion{
          std::chrono::duration_cast<std::chrono::microseconds>(end - start)
              .count()};
      imprimirDatosTablas2y3(i, grasp.getSolucion(), grasp.getProblema(),
                             maximo_iteraciones, size_lrc, nombre_problema,
                             duracion);
    }
  }
  std::cout << "---------------------------------------------------------------"
               "------------------------------------------------"
            << std::endl;
}

void imprimirTablasResultados4y5BusquedaTabu(const std::string& nombre_problema) {
  int size_lrc, maximo_iteraciones;
  for (int i{2}; i <= 5; ++i) {
    for (int j{0}; j < 4; ++j) {
      (j % 2 == 0) ? size_lrc = 2 : size_lrc = 3;
      (j < 2 == 0) ? maximo_iteraciones = 10 : maximo_iteraciones = 20;
      AlgoritmoBusquedaTabu tabu{nombre_problema, i, size_lrc, maximo_iteraciones};
      auto start{std::chrono::high_resolution_clock::now()};
      tabu.resolver();
      auto end{std::chrono::high_resolution_clock::now()};
      int duracion{
          std::chrono::duration_cast<std::chrono::microseconds>(end - start)
              .count()};
      imprimirDatosTablas2y3(i, tabu.getSolucion(), tabu.getProblema(),
                             maximo_iteraciones, size_lrc, nombre_problema,
                             duracion);
    }
  }
  std::cout << "---------------------------------------------------------------"
               "------------------------------------------------"
            << std::endl;
}

void imprimirTablaResultados1BusquedaTabu(const std::string& nombre_problema) {
  for (int i{2}; i <= 5; ++i) {
    for (int j{0}; j < 4; ++j) {
      AlgoritmoBusquedaTabu busqueda_tabu{nombre_problema, i, 1000};
      auto start{std::chrono::high_resolution_clock::now()};
      busqueda_tabu.resolver();
      auto end{std::chrono::high_resolution_clock::now()};
      int duracion{
          std::chrono::duration_cast<std::chrono::microseconds>(end - start)
              .count()};
      imprimirDatosTabla(busqueda_tabu.getProblema().getSizeSolucion(),
                         busqueda_tabu.getSolucion(),
                         busqueda_tabu.getProblema(), nombre_problema,
                         duracion);
    }
  }
  std::cout << "---------------------------------------------------------------"
               "---------------------"
            << std::endl;
}

int main() {
  std::vector<std::string> problemas{
      "MAXDIV/max_div_15_2.txt", "MAXDIV/max_div_20_2.txt",
      "MAXDIV/max_div_30_2.txt", "MAXDIV/max_div_15_3.txt",
      "MAXDIV/max_div_20_3.txt", "MAXDIV/max_div_30_3.txt"};
  std::cout << "\t\tAlgoritmo Voraz" << std::endl;
  printf("%-25s %-5s %-5s %-5s %-3s %6s %12s\n", "Problema", "n", "K", "m", "z",
         "S", "CPU");
  for (const auto& problema : problemas) {
    imprimirTablaResultados1Voraz(problema);
  }
  std::cout << "\t\tBusqueda Local" << std::endl;
  printf("%-25s %-5s %-5s %-5s %-3s %6s %12s\n", "Problema", "n", "K", "m", "z",
         "S", "CPU");
  for (const auto& problema : problemas) {
    imprimirTablaResultados1BusquedaLocal(problema);
  }
  std::cout << "\t\tAlgoritmo GRASP" << std::endl;
  printf("%-25s %-5s %-5s %-5s %-3s %6s %5s %8s %21s\n", "Problema", "n", "K",
         "m", "ITER", "|LRC|", "z", "S", "CPU");
  for (const auto& problema : problemas) {
    imprimirTablasResultados2y3GRASP(problema);
  }
  std::cout << "\t\tAlgoritmo Búsqueda Tabú" << std::endl;
  printf("%-25s %-5s %-5s %-5s %-3s %6s %5s %8s %21s\n", "Problema", "n", "K",
         "m", "ITER", "Tabutenure", "z", "S", "CPU");
  for (const auto& problema : problemas) {
    imprimirTablasResultados4y5BusquedaTabu(problema);
  }
  return 0;
}
