#ifndef ACR_TESTQT_H
#define ACR_TESTQT_H

#include <QWidget>

class QLabel;
class QPushButton;
class QTextEdit;
class QTreeWidget;

class ACR_TestQt : public QWidget
{
    Q_OBJECT

public:
    ACR_TestQt(QWidget *parent = nullptr);
    ~ACR_TestQt();

private:
    void runSuite(int suiteIndex);
    void runAllSuites();

    QTreeWidget *m_testTree;
    QTextEdit *m_output;
    QLabel *m_summary;
    QPushButton *m_runSelected;
};
#endif // ACR_TESTQT_H
