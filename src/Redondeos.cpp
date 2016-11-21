#include "../include/Redondeos.h"

Coeficientes::Coeficientes()
{
    RedCapitulo=0;
    RedCantidadConceptos=2;
    RedOtrasCantidades=3;
    RedPreciosCap=2;
    RedPreciosPart=2;
    RedPrecElementales=2;
    RedSubtotal=2;
    RedLineasMedicion=2;
    RedSuministros=2;

    Factores.push_back(std::make_pair("Redondeo de cantidades de un capítulo inferiores al raíz",RedCapitulo));
    Factores.push_back(std::make_pair("Redondeo de cantidades de conceptos inferiores a capítulos",RedCantidadConceptos));
    Factores.push_back(std::make_pair("Redondeo de cantidades del resto de conceptos",RedOtrasCantidades));
    Factores.push_back(std::make_pair("Redondeo de precios de capítulos",RedPreciosCap));
    Factores.push_back(std::make_pair("Redondeo de precios de partidas",RedPreciosPart));
    Factores.push_back(std::make_pair("Redondeo de precios de conceptos básicos",RedPrecElementales));
    Factores.push_back(std::make_pair("Redondeo de subtotales de descomposiciones",RedSubtotal));
    Factores.push_back(std::make_pair("Redondeo de parciales en líneas de medición",RedLineasMedicion));
    Factores.push_back(std::make_pair("Redondeo de importes en suministros",RedSuministros));
}
