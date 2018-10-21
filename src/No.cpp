#include "No.h"
#include <stdlib.h>

No::No(Simbolo s)
{
    this->valor = s;
    this->proximo = NULL;
}

No::~No()
{

    if (this->proximo != NULL)
    {

        delete this->proximo;
    }

}



