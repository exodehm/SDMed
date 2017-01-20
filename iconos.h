#ifndef ICONOS_H
#define ICONOS_H

#include <map>
#include <QIcon>

enum class Naturaleza{Sin_clasificar, Mano_de_Obra, Maquinaria, Materiales, Comp_residuo,Clasificacion_residuo, Capitulo, Partida};
using IconsMap = std::map<Naturaleza,QIcon>;

class RepoIconos
{

private:
    static IconsMap _iconos;
    static IconsMap initMap()
    {
        return
        {
            std::make_pair(Naturaleza::Sin_clasificar, QIcon(QStringLiteral("../PruebasInterfazObra/Iconos/trucking.png"))),
            std::make_pair(Naturaleza::Mano_de_Obra, QIcon(QStringLiteral("../PruebasInterfazObra/Iconos/engineer.png"))),
            std::make_pair(Naturaleza::Maquinaria, QIcon(QStringLiteral("../PruebasInterfazObra/Iconos/trucking.png"))),
            std::make_pair(Naturaleza::Materiales, QIcon(QStringLiteral("../PruebasInterfazObra/Iconos/brick.png"))),
            std::make_pair(Naturaleza::Comp_residuo, QIcon(QStringLiteral("../PruebasInterfazObra/Iconos/delete.png"))),
            std::make_pair(Naturaleza::Clasificacion_residuo, QIcon(QStringLiteral("../PruebasInterfazObra/Iconos/delete.png"))),
            std::make_pair(Naturaleza::Capitulo, QIcon(QStringLiteral("../PruebasInterfazObra/Iconos/folder.png"))),
            std::make_pair(Naturaleza::Partida, QIcon(QStringLiteral("../PruebasInterfazObra/Iconos/file.png")))
        };
    }

public:
    RepoIconos()=delete;//no debe haber constructor disponible al ser clase estática
    static QIcon GetIcon(Naturaleza type)
    {
        if(_iconos.empty())
        {
            _iconos = initMap();
        }
        auto it = _iconos.find(type);
        if(it == _iconos.end())
        {
            it = _iconos.find(Naturaleza::Sin_clasificar);
        }
        return it->second;
    }

    static QIcon GetIcon(int pos)
    {
        auto it = _iconos.begin();
        for (int i=0;i<pos;i++)
        {
            it++;
        }
        return it->second;
    }

    static int tam()
    {
        if(_iconos.empty())
        {
            _iconos = initMap();
        }
        return _iconos.size();
    }
 };

namespace DatosIconos
{
    static const int ImageIndexRole = Qt::UserRole+1;
}
#endif // ICONOS_H
