#include "mainwindow.h"
#include "ui_mainwindow.h"

int isCon=0;
void SendMassageToServer();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->beforeWork();
    QDir dir("Files");
    if(!dir.exists()){
         QDir dir1(".");
        qDebug() << "files";
        dir1.mkdir("Files");
    }
    this->trail = ".//Files//";

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushSend_clicked()
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("cp866"));

    QString temp1 = ui->lineEdit->text();
    ui->lineEdit->clear();
    QByteArray data(temp1.toUtf8());
    char *am = data.data();

    if(this->workWindow == this->numberOfGtntralStory){

        char inf1[10] = "01";
        send(my_sock, inf1, 10, 0);

    }
    else{

        char t[150];
        strcpy(t,this->nameP);
        strcat(t,">>");
        strcat(t,am);
        this->WriteMassageToServer(t);
        char inf1[10] = "06";
         send(my_sock, inf1, 10, 0);

        QString number = QString::number(this->workWindow);

        send(my_sock, number.toStdString().data(), 10, 0);

    }
    send(my_sock, am, 1024, 0);
}



void MainWindow::WriteMassageToServer(char * massage){

   ui->listWidget->addItem(massage);
   this->listOfStory.getStory(this->workWindow).add(massage);   
   qDebug() << this->listOfStory.getStory(this->workWindow).size();
}

void MainWindow::WriteMassageToServerWithoutStory(char * massage){
    ui->listWidget->addItem(massage);
}
void MainWindow::StoryMassageToServer(char *massage){
    this->listOfStory.getStory(this->workWindow).add(massage);
}

void MainWindow::WriteName(char * massage){
    ui->lustOfPeople->addItem(massage);
}



void MainWindow::on_pushButton_clicked()
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("cp866"));

    QString filename = QFileDialog::getOpenFileName(this,tr("Open File"),"D://Тест//","All files (*.*)");

    if(filename.isEmpty()){
        return;
    }
    QString dot;
    QString inform;
    int size;

    QFile in (filename);
    in.open(QIODevice::ReadOnly);

    size = in.size();
    QString sizeF = QString::number(size);

    int countPac = size/1024+1;
    QString countP = QString::number(countPac);

    int i;
    for(i=filename.size()-1;filename[i]!='/';i--);
    i++;
    for(;i<filename.size();i++){
        dot+=filename[i];
    }
    inform+=sizeF+'/'+countP+'/'+dot+'/';

    if(this->workWindow == this->numberOfGtntralStory){
        char inf[10] = "03";
        if(send(my_sock, inf, 10, 0)== SOCKET_ERROR)
            return;
    }
    else{
        char inf1[10] = "07";
        this->ui->lisfFiles->addItem(dot);
        if(send(my_sock, inf1, 10, 0)== SOCKET_ERROR)
            return;

        QString number = QString::number(this->workWindow);

        if(send(my_sock, number.toStdString().data(), 10, 0)== SOCKET_ERROR)
            return;
    }

    QByteArray strBa(inform.toUtf8());
    char *am = new char[150];
    am = strBa.data();

    if(send(my_sock, am, 150, 0)== SOCKET_ERROR)
        return;


    char tempC[1024];
    while(!in.atEnd()){
         int nBloc = in.read(tempC,sizeof(tempC));
         send(my_sock,tempC, nBloc, 0);
    }
    in.close();
}



void MainWindow::AddNameFile(char * nameFile){
    ui->lisfFiles->addItem(nameFile);
}

void MainWindow::closeEvent(QCloseEvent *event){

    char inf[10] = "05";
    if(send(my_sock, inf, 10, 0)== SOCKET_ERROR)
        return;
    this->writeListOfFiles();
    this->listOfStory.close();
    event->accept();
}

void MainWindow::beforeWork(){

    QFile nameFile;
    nameFile.setFileName("name.txt");
    if (!nameFile.exists()){
        InChat *inC = new InChat(this);
        inC->exec();
    }

    if(!nameFile.open(QIODevice::ReadOnly))
    {
        return;
    }

    int t = nameFile.read(nameP,sizeof(nameP));
    nameP[t] = '\0';
    ui->name->setText(nameP);
    ui->name->setStyleSheet("QLabel { color : green; }");

    QFile infoFile;
    infoFile.setFileName("info.txt");
    if (!infoFile.exists()){
        infoFile.open(QIODevice::WriteOnly);
        infoFile.close();
    }
    infoFile.open(QIODevice::ReadOnly);
    int t1 = infoFile.read(this->SERVERADDR,sizeof(this->SERVERADDR));

    this->SERVERADDR[t1] = '\0';
    ui->server->setText(this->SERVERADDR);
    ui->server->setStyleSheet("QLabel { color : blue; }");
    infoFile.close();
}


void MainWindow::on_lisfFiles_doubleClicked(const QModelIndex &index)
{
    if( !index.isValid() ) {
                return;
    }
    if( QListWidget* listWgt = dynamic_cast< QListWidget* >( sender() ) ) {

        if( QListWidgetItem* item = listWgt->item(index.row())) {

            qDebug() << item->text() << "04";

            char inf[10] = "04";
            if(send(my_sock, inf, 10, 0)== SOCKET_ERROR)
                return;

            if(send(my_sock, item->text().toStdString().data(), 150, 0)== SOCKET_ERROR)
                return;
        }
    }
}

void MainWindow::on_lustOfPeople_doubleClicked(const QModelIndex &index)
{
    if( !index.isValid() ) {
                return;
    }    

    if( QListWidgetItem* item = this->ui->lustOfPeople->item(index.row())) {

        if(this->numberOfGtntralStory!=index.row()){
            item->setBackgroundColor(Qt::GlobalColor::white);
        }
        else{
            item->setBackgroundColor(Qt::GlobalColor::yellow);
        }

        item->setTextColor(Qt::GlobalColor::black);
        this->workWindow = this->listOfStory.find(item->text());
         ui->listWidget->clear();

        for(int i=0;i<this->listOfStory.getStory(workWindow).size();i++){
            ui->listWidget->addItem(this->listOfStory.getStory(workWindow).gerStr(i));
        }
    }
}

void MainWindow::setColor(int row){

    if( QListWidgetItem* item = this->ui->lustOfPeople->item(row)) {

        qDebug() << item->text() << "story";
        item->setTextColor(Qt::GlobalColor::darkGreen);
    }
}


void MainWindow::setBackgroundNamePeople(){

    QListWidgetItem* itemBefore = this->ui->lustOfPeople->item(this->workWindow);
    itemBefore->setBackgroundColor(Qt::GlobalColor::yellow);
}

void con(SOCKET soc, sockaddr * socddr, int size){
    connect(soc, socddr,size);
}



SOCKET MainWindow::startConnect(){

    setlocale(LC_ALL, "russian");
    char buff[1024];
    printf("TCP DEMO CLIENT\n");


    // Шаг 1 - инициализация библиотеки Winsock
    if (WSAStartup(0x202, (WSADATA *)&buff[0]))
    {
        printf("WSAStart error %d\n", WSAGetLastError());
        return -1;
    }

    // Шаг 2 - создание сокета
    this->my_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (this->my_sock < 0)
    {
        printf("Socket() error %d\n", WSAGetLastError());
        return -1;
    }

    // Шаг 3 - установка соединения

    // заполнение структуры sockaddr_in
    // указание адреса и порта сервера
    sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(PORT);
    HOSTENT *hst;

    // преобразование IP адреса из символьного в
    // сетевой формат
    if (inet_addr(SERVERADDR) != INADDR_NONE)
        dest_addr.sin_addr.s_addr = inet_addr(SERVERADDR);
    else
        // попытка получить IP адрес по доменному
        // имени сервера
        if (hst = gethostbyname(SERVERADDR))
            // hst->h_addr_list содержит не массив адресов,
            // а массив указателей на адреса
            ((unsigned long *)&dest_addr.sin_addr)[0] =
            ((unsigned long **)hst->h_addr_list)[0][0];
        else
        {
            printf("Invalid address %s\n", SERVERADDR);
            closesocket(this->my_sock);
            WSACleanup();
            return -1;
        }

    // адрес сервера получен – пытаемся установить
    // соединение
    con(this->my_sock, (sockaddr *)&dest_addr,
         sizeof(dest_addr));

    if(send(this->my_sock, this->nameP, 150, 0)==SOCKET_ERROR){
        return -1;
    }
    qDebug() << "Connected...";

    ui->server->setText(this->SERVERADDR);
    ui->server->setStyleSheet("QLabel { color : blue; }");

    CreateThread(NULL, NULL,(LPTHREAD_START_ROUTINE)SendMassageToServer, NULL, NULL, NULL);
    this->ui->listWidget->addItem("Connected...");

    return this->my_sock;
}

void MainWindow::readListOfFiles(){
    QFile inform ("files.txt");
    if (!inform.exists()){
        inform.open(QIODevice::WriteOnly);
        int i=0;
        inform.write(QString::number(i).toStdString().data(),sizeof(int));
        inform.close();
        return;
    }

    inform.open(QIODevice::ReadOnly);
    char tempC[150];
    memset(tempC, 0, sizeof(tempC));
    int n;
    inform.read(tempC,sizeof(int));
    n = atoi(tempC);
    while(n>0){
        memset(tempC, 0, sizeof(tempC));

        inform.read(tempC,sizeof(int));
        int a = atoi(tempC);
        inform.read(tempC,a);
        this->ui->lisfFiles->addItem(tempC);
        memset(tempC, 0, sizeof(tempC));

        n--;
    }

    inform.close();
}

void MainWindow::writeListOfFiles(){
    QFile inform ("files.txt");
    inform.open(QIODevice::WriteOnly);
    int i=0;

    inform.write(QString::number(this->ui->lisfFiles->count()).toStdString().data(),sizeof(int));
    while(i<this->ui->lisfFiles->count()){
        inform.write(QString::number(this->ui->lisfFiles->item(i)->text().toStdString().size()).toStdString().data(),sizeof(int));
        inform.write(this->ui->lisfFiles->item(i)->text().toStdString().data(),this->ui->lisfFiles->item(i)->text().toStdString().size());
        qDebug() << "size"<< this->ui->lisfFiles->item(i)->text().toStdString().size();
        i++;
    }
    inform.close();
}

void MainWindow::on_connect_clicked()
{
//    this->SERVERADDR = "127.0.0.1";
    if(isCon==1){
        return;
    }
    if(this->startConnect()==-1){
        ui->server->setText("Сервер не найден");
        ui->server->setStyleSheet("QLabel { color : red; }");
    }
    else{
        isCon = 1;
    }
}

void MainWindow::on_actionIP_triggered()
{
    QFile nameFile;
    nameFile.setFileName("info.txt");
    ChServer *chS = new ChServer(this);
    chS->exec();

    if(!nameFile.open(QIODevice::ReadOnly))
    {
        return;
    }

    int t = nameFile.read(this->SERVERADDR,sizeof(this->SERVERADDR));
    this->SERVERADDR[t] = '\0';
    ui->server->setText(this->SERVERADDR);
    ui->server->setStyleSheet("QLabel { color : blue; }");
    nameFile.close();
}

int MainWindow::isNeed(QString isNeed){
    for(int i=0;i<this->ui->lisfFiles->count();i++){
        QListWidgetItem* item = this->ui->lisfFiles->item(i);
        if(item->text()==isNeed){
            return 1;
        }
    }
    return 0;
}
