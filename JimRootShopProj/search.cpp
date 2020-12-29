#include "search.h"
#include "ui_search.h"
Search::Search(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Search)
{
    ui->setupUi(this);
    ui->brandBox->addItem("Schecter");
    ui->brandBox->addItem("Ibanez");
}

Search::~Search()
{
    delete ui;
}

void Search::on_applyBtn_clicked()
{
    std::vector <Instrument> all_guitars = ParseGuitars();
    std::vector <Instrument> searched_guitars = findGuitars(all_guitars, ui->keyWordEdit->text().toStdString(),
              ui->brandBox->currentText().toStdString(), ui->shapeBox->currentText().toStdString());

    QWidget *scrollCont = new QWidget();
    QGridLayout *scrollingLayout = new QGridLayout();

    for(int i = 0; i < searched_guitars.size(); i++){
        if(searched_guitars[i].name != " "){
            //Добавляю изображение, переменная path это путь только в qsring, дальше операции с пиксмапами что бы задать изображение
             QLabel *image = new QLabel();
             QString path = QString::fromUtf8(searched_guitars[i].img_path.c_str());
             QPixmap startImg("Images\\" + path);
             QPixmap finalImg =  startImg.scaled(100, 100);
             image->setPixmap(finalImg);

             //задаем имя
             QLabel *name = new QLabel();
             QString qName = QString::fromUtf8(searched_guitars[i].name.c_str());
             name->setText(qName);

             //задаем стоимость
             QLabel *price = new QLabel();
             QString qPrice = QString::number(searched_guitars[i].price);
             price->setText(qPrice + "$");

             //создаем кноп очку
             QPushButton *btn = new QPushButton(this);
             btn->setText("перейти");

             scrollingLayout->setHorizontalSpacing(50);
             scrollingLayout->setVerticalSpacing(70);

             QString buttonNum = QString::number(i);
             btn->setObjectName("button" + buttonNum);
             scrollingLayout->addWidget(image, i, 1);
             scrollingLayout->addWidget(name, i, 2);
             scrollingLayout->addWidget(price, i, 3);
             scrollingLayout->addWidget(btn, i, 4);
        }
    }
    scrollCont->setLayout(scrollingLayout);
    ui->searchScrollArea->setWidget(scrollCont);
}
