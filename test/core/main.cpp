#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

#include <QApplication>
#include <QtGui>
#include <qxcppunit/testrunner.h>

int main( int argc, char **argv )
{
    QApplication app(argc, argv);
    QxCppUnit::TestRunner runner;
    runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() );
    runner.run( );
}
