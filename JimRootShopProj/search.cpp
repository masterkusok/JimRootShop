#include "search.h"
#include "ui_search.h"
Search::Search(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Search)
{
    ui->setupUi(this);

    //тут добавление 2-х сортировок, 1 - по возрастанию а 2 - по убыванию
    ui->sortBox->addItem("");
    ui->sortBox->addItem("Ascending");
    ui->sortBox->addItem("Descending");
    //добавление брендов в фильтры
    ui->brandBox->clear();
    ui->brandBox->addItem("");
    std::vector<std::string> brands = getAllGuitarBrands();


    for(int i = 0; i < brands.size(); i++){
        ui->brandBox->addItem(QString::fromUtf8(brands[i].c_str()));
    }
    //добавление форм в фильтры
    ui->shapeBox->clear();
    ui->shapeBox->addItem("");
    std::vector<std::string> shapes = getAllGuitarShapes();
    for(int i = 0; i < shapes.size(); i++){
        ui->shapeBox->addItem(QString::fromUtf8(shapes[i].c_str()));
    }
    ui->stackedWidget->addWidget(gtp);
    connect(this, SIGNAL(sendData(Instrument, User)), gtp, SLOT(recieveData(Instrument, User)));
    connect(gtp, SIGNAL(returnToKatalog()), this, SLOT(returnToSearch()));

    update();
}

Search::~Search()
{
    delete ui;
}


void Search::on_applyBtn_clicked()
{
   update();
}

User UserToSend;

void Search::buttonClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    int guitar_index = button->property("index").toInt();

    emit sendData(current_searched_guitars[guitar_index], UserToSend);
    ui->stackedWidget->setCurrentIndex(2);
}

void Search::returnToSearch()
{
    ui->stackedWidget->setCurrentIndex(0);
    update();
}

void Search::on_pushButton_clicked()
{
    emit returnToMenu();
    update();
}

void Search::recieveData(User user)
{
    UserToSend = user;

    update();
}

void Search::update()
{

    std::vector <Instrument> all_guitars = ParseGuitars();
    std::vector <Instrument> searched_guitars = findGuitars(all_guitars, ui->keyWordEdit->text().toStdString(),
              ui->brandBox->currentText().toStdString(), ui->shapeBox->currentText().toStdString());



    QWidget *scrollCont = new QWidget();
    QGridLayout *scrollingLayout = new QGridLayout();

    //сортировка пузырьком если она нужна
    if(ui->sortBox->currentText() == "Ascending"){
        Instrument temp_guitar;
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
        Instrument temp_guitar;
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
            //Добавляем нужный шрифт
            const QFont font = QFont("Segoe UI Black",10,10,false);
            const QFont fontitalic = QFont("Segoe UI Black", 10, 10,true);

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
             name->setFont(font);

             //задаем стоимость
             QLabel *price = new QLabel();
             QString qPrice = QString::number(searched_guitars[i].price);
             price->setText(qPrice + "$");
             price->setFont(fontitalic);

             //создаем кноп очку
             QPushButton *btn = new QPushButton(this);
             btn->setText("Go");
             btn->setFont(font);
             btn->setCursor(Qt::PointingHandCursor);
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
    //привязываю клик к каждой кнопке
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
