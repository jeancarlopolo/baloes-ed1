#include "tipos.h"

struct formaGenerica
{
    enum TipoForma tipo;
};

enum TipoForma getTipoForma(void* forma)
{
    return ((struct formaGenerica*)forma)->tipo;
}