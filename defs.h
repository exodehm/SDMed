#ifndef DEFS_H
#define DEFS_H

#include <QString>

namespace tipoColumna {
    enum  {CODIGO, NATURALEZA, UD, RESUMEN, CANPRES, CANCERT, PORCERTPRES, PRPRES, PRCERT, IMPPRES, IMPCERT};
    enum  {FASE, COMENTARIO, N, LONGITUD, ANCHURA, ALTURA, FORMULA, PARCIAL, SUBTOTAL,ID};
}

namespace naturaleza {

    static const QString leyenda_nat[]={"Sin clasificar", "Mano de Obra", "Maquinaria", "Materiales", "Comp residuo", "Clasificacion residuo", "Capitulo", "Partida"};
}

#endif // DEFS_H
