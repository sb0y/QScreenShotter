#include "grabberbase.h"

grabberBase::grabberBase() :
    QDialog ( NULL, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint | Qt::Popup )
{
    setMouseTracking ( true );
    setWindowModality( Qt::WindowModal );
    setFixedSize ( 0, 0 );
}

grabberBase::~grabberBase()
{

}
