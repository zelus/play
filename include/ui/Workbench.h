#ifndef WORKBENCH_H
#define WORKBENCH_H

#include <QMainWindow>
#include <QTreeView>

class Workbench : public QMainWindow
{
    Q_OBJECT
public:
    explicit Workbench(QWidget* parent = 0);
    QTreeView* getLibraryTreeView() const;

signals:
    
public slots:

private:
    QTreeView* libraryTreeView_;
    
};

#endif // WORKBENCH_H
