#pragma once

#include <chrono>
#include <vector>
#include <fstream>

#include "Solucion.h"
#include "Problema.h"
#include "Punto.h"

class Solucion;

double calcularDistanciaEuclidea(const Punto& punto1, const Punto& punto2);

Punto calcularCentro(const std::vector<Punto>& puntos);

Punto hallarPuntoMasLejanoCentro(const Punto& punto_central,
                                 const std::vector<Punto>& puntos);

void imprimirTablaResultados1(const std::string& nombre_problema);

std::string pasarPuntosString(const Solucion& solucion);

void imprimirDatosTabla(int size_solucion, const Solucion& solucion,
                              const Problema& problema,
                              const std::string& nombre_fichero,
                              int tiempo_ejecucion);