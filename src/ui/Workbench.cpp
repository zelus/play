#include "Workbench.h"

#include <QTextEdit>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QHBoxLayout>
#include <QSplitter>

Workbench::Workbench(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("play");

    QWidget* central = new QWidget(this);
    QHBoxLayout* central_layout = new QHBoxLayout;

    QTreeWidget* libTree = new QTreeWidget;
    libTree->setColumnCount(1);
    libTree->setHeaderLabel("name");
    QTreeWidgetItem* lib1 = new QTreeWidgetItem(QStringList("Lib1"));
    lib1->addChild(new QTreeWidgetItem(QStringList("mov1")));
    QList<QTreeWidgetItem*> topLevelItems;
    topLevelItems.append(lib1);
    topLevelItems.append(new QTreeWidgetItem(QStringList("B Lib")));
    topLevelItems.append(new QTreeWidgetItem(QStringList("A Lib")));
    libTree->insertTopLevelItems(0,topLevelItems);
    libTree->setSortingEnabled(true);
    QTextEdit* edit2 = new QTextEdit("main view");

    central_layout->addWidget(libTree);
    central_layout->addWidget(edit2);

    central->setLayout(central_layout);

    setCentralWidget(central);
}
