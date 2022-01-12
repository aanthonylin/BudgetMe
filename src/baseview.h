#ifndef BASEVIEW_H
#define BASEVIEW_H

#include <QString>
#include <QVBoxLayout>
#include <QWidget>


class BaseView : public QWidget
{
  Q_OBJECT
public:
  explicit BaseView(QString);
  virtual ~BaseView();
	void addToView(QWidget *);
	void removeFromView(QWidget *);
	void addToView(QLayout *);
	void addToFooter(QWidget *);
	void addToFooter(QLayout *);
private:
	QVBoxLayout *m_outer;
	QVBoxLayout *m_center;
};
#endif // BASEVIEW_H
