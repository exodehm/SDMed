#ifndef PRECIO_H
#define PRECIO_H


struct Precio
{
    //miembros:
    enum {NORMAL, BLOQUEADO};
    float precio[2];
    bool bloqueado;
    //constructores
    Precio(float P=0);
    Precio (const Precio& P);
    //destructor
    ~Precio();
    //funciones miembro:
    bool EsBloqueado() const;
    const float LeePrecio() const;
    void EscribePrecio (float p);
    void Bloquear();
    void Desbloquear();
    //operador de asignacion
    Precio& operator=(const Precio& P);
};
#endif // PRECIO_H
