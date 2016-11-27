#ifndef MEDCERT_H
#define MEDCERT_H
#include "Medicion.h"


class MedCert
{
    public:
        enum {MEDICION,CERTIFICACION};
        /** Default constructor */
        MedCert();
        MedCert(float cantidad);
        MedCert(const MedCert& origen);
        //sobrecarga de =
        MedCert& operator=(const MedCert& origen);
        /***** Default destructor *****/
        ~MedCert();

        /*******consultores**********/
        const Medicion& LeeMedicion() const;
        const Medicion& LeeCertificacion() const;
        const Medicion& LeeMedCer(int n=MEDICION);
        Medicion& ModificaMedCer(int n=MEDICION);
        int NumCertificaciones() const;
        bool hayMedCert(int n=MEDICION);
        /******modificadores*********/
        void EscribeMedicion();
        void EscribeMedicion(const Medicion& m);
        void EscribeCertificacion();
        void EscribeCertificacion(const Medicion& c);
        void EscribeMedCer(int i);
        void escribeTotalMedCer(int i, float cantidad);

        void Ver();

    private:
    //un array de dos objetos Medicion...uno para la Medicion y otro para la Certificacion
    Medicion MC[2];

};

#endif // MEDCERT_H
