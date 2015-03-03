#include "grabberbasedialog.h"

grabberBaseDialog::grabberBaseDialog() //:
    //QDialog ( NULL, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint | Qt::Popup )
{
    setMouseTracking ( true );
    setWindowModality ( Qt::WindowModal );
    setFixedSize ( 0, 0 );
}

grabberBaseDialog::~grabberBaseDialog()
{

}

