#include "Simbolo.h"
#include <stdlib.h>
#include <string.h>

int indParametros = -1;

Simbolo::Simbolo() throw()
{
    this->nome = (char*)malloc(31 * sizeof (char));
    //ctor
}

Simbolo::Simbolo(TipoPedaco tp, char* nm, int lvl, int ret, int qts, char** params) throw()
{
    this->qtsParametros = qts;
    this->parametros = (char**)malloc(30*sizeof(char*));
    //int i;
    //for (i=0;i<31;i++)
      //  this->parametros[i] = (char*)malloc(10*sizeof(char));
    this->parametros = params;
    this->nome = (char*)malloc(31 * sizeof (char));
    strcpy(this->nome, nm);
    this->tipo = tp;
    this->nivel = lvl;
    this->retorno = ret;
}

int Simbolo::getQtsParams() throw()
{
    int ret = this->qtsParametros;
    return ret;
}

char* Simbolo::getProximoParametro() throw()
{
    indParametros++;
    return this->parametros[indParametros];
}

char* Simbolo::getNome() throw()
{
    char* ret = (char*)malloc(strlen(this->nome) * sizeof(char));
    strcpy(ret, this->nome);
    return ret;
}

void Simbolo::setTipo(TipoPedaco tipo) throw()
{
    //delete (&this->tipo);
    this->tipo = tipo;
}

TipoPedaco Simbolo::getTipo() const throw()
{
    return (TipoPedaco)this->tipo;
}

int Simbolo::getNivel() const throw()
{
    return this->nivel;
}

int Simbolo::getRetorno() const throw()
{
    return this->retorno;
}

Simbolo::~Simbolo() throw()
{
    free(this->nome);
    //delete this->parametros;
}

Simbolo& Simbolo::operator=(const Simbolo &outro) throw()
{
    this->nome = (char*)malloc(31 * sizeof (char));
    this->nivel = outro.nivel;
    this->retorno = outro.retorno;
    this->tipo = outro.tipo;
    this->qtsParametros = outro.qtsParametros;
    this->parametros = (char**)malloc(30*sizeof(char*));
    //int i;
    //for (i=0;i<31;i++)
      //  this->parametros[i] = (char*)malloc(10*sizeof(char));
    this->parametros = outro.parametros;
    strcpy(this->nome, outro.nome);

    return *this;
}

Simbolo::Simbolo(const Simbolo &outro) throw()
{
    *this = outro;
}

