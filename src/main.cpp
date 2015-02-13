#include "core.h"

int main ( int argc, char *argv[] )
{
    system::setArgs ( argc, argv );
    core *c = system::getCore();
    int ret = c->exec();
    delete c;

    return ret;
}
