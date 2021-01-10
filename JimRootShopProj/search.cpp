#include "search.h"
#include "ui_search.h"
Search::Search(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Search)
{
    ui->setupUi(this);
    ui->brandBox->addItem("");
    ui->brandBox->addItem("Schecter");
    ui->brandBox->addItem("Ibanez");
    ui->brandBox->addItem("Fender");

    ui->shapeBox->addItem("");
    ui->shapeBox->addItem("Superstrat");
    ui->shapeBox->addItem("Iceman");
    ui->shapeBox->addItem("Stratocaster");

    ui->sortBox->addItem("");
    ui->sortBox->addItem("Ascending");
    ui->sortBox->addItem("Descending");

    ui->stackedWidget->addWidget(gtp);
    connect(this, SIGNAL(sendData(Instrument, User)), gtp, SLOT(recieveData(Instrument, User)));
    connect(gtp, SIGNAL(returnToKatalog()), this, SLOT(returnToSearch()));
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

    //сортировка пузырьком если она нужна
    Instrument temp_guitar;
    if(ui->sortBox->currentText() == "Ascending"){
        for (int i = 0; i < searched_guitars.size() - 1; i++) {
                for (int j = 0; j < searched_guitars.size() - i - 1; j++) {
                    if (searched_guitars[j].price > searched_guitars[j + 1].price) {
                        // меняем элементы местами
                        temp_guitar = searched_guitars[j];
                        searched_guitars[j] = searched_guitars[j + 1];
                        searched_guitars[j + 1] = temp_guitar;
                    }
                }
            }
    }

    if(ui->sortBox->currentText()=="Descending"){
        for (int i = 0; i < searched_guitars.size() - 1; i++) {
                for (int j = 0; j < searched_guitars.size() - i - 1; j++) {
                    if (searched_guitars[j].price < searched_guitars[j + 1].price) {
                        // меняем элементы местами
                        temp_guitar = searched_guitars[j];
                        searched_guitars[j] = searched_guitars[j + 1];
                        searched_guitars[j + 1] = temp_guitar;
                    }
                }
            }
    }

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
             btn->setText("Go");

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
    for(int i = 0; i < searched_guitars.size(); i++){
        QString buttonNum = QString::number(i);
        QPushButton *button = findChild<QPushButton*>("button" + buttonNum);
        if(button!=nullptr){
            //это нужно что бы в слоте получать номер гитары на которую нажали
            button->setProperty("index", i);
            connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
        }
    }

    current_searched_guitars = searched_guitars;
    scrollCont->setLayout(scrollingLayout);
    ui->searchScrollArea->setWidget(scrollCont);
}
User UserToSend;

void Search::buttonClicked()
{
    //получаем эту самую циферку, и открываем окно
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    // вот в этой переменной ты можешь найти интовую циферку, которую вместе с юзером нужно в гитарпейдж перекинуть
    int guitar_index = button->property("index").toInt();

    emit sendData(current_searched_guitars[guitar_index], UserToSend);
    ui->stackedWidget->setCurrentIndex(2);
}

void Search::returnToSearch()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Search::on_pushButton_clicked()
{
    emit returnToMenu();
}

void Search::recieveData(User user)
{
    UserToSend = user;
}
