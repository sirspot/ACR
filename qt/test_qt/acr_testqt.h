#ifndef ACR_TESTQT_H
#define ACR_TESTQT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class ACR_TestQt; }
QT_END_NAMESPACE

class ACR_TestQt : public QWidget
{
    Q_OBJECT

public:
    ACR_TestQt(QWidget *parent = nullptr);
    ~ACR_TestQt();

private:
    Ui::ACR_TestQt *ui;
};
#endif // ACR_TESTQT_H
