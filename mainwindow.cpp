#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), n(0, 0, 0, 0, 0, 0, 0.0)
{
    ui->setupUi(this);

    // Inicializar la escena
        scene = new QGraphicsScene(this);

        // Asignar la escena a la vista
        ui->graphicsView->setScene(scene);

    n = Neurona(0, 0, 0, 0, 0, 0, 0.0);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(on_pushButton_2_clicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(on_pushButton_3_clicked()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(buscarPorNeurona()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(llenarTabla()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(dibujarNeurona()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(ordenarID()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(ordenarVOLT()));
    connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(puntosCercanos()));


    // Inicializar administrarNeuronas
    administrarNeuronas = administradora();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::wheelEvent(QWheelEvent* event) {
    QPoint numDegrees = event->angleDelta() / 8;

    if (!numDegrees.isNull()) {
        if (numDegrees.y() > 0) {
            ui->graphicsView->scale(1.2, 1.2);
        } else {
            ui->graphicsView->scale(0.8, 0.8);
        }
    }
}



void MainWindow::on_pushButton_clicked()
{
    QString valor1Str = ui->lineEdit->text();
    QString valor2Str = ui->lineEdit_2->text();
    QString valor3Str = ui->lineEdit_3->text();
    QString valor4Str = ui->lineEdit_4->text();
    QString valor5Str = ui->lineEdit_5->text();
    QString valor6Str = ui->lineEdit_6->text();
    QString valor7Str = ui->lineEdit_7->text();

    // Verificar si algún campo está vacío antes de continuar
    if (valor1Str.isEmpty() || valor2Str.isEmpty() || valor3Str.isEmpty() ||
        valor4Str.isEmpty() || valor5Str.isEmpty() || valor6Str.isEmpty() || valor7Str.isEmpty()) {
        QMessageBox::warning(this, "Campos Vacíos", "Por favor, complete todos los campos.");
        return;
    }

    // Convertir valores a números
    int valor1 = valor1Str.toInt();
    float valor2 = valor2Str.toFloat();
    int valor3 = valor3Str.toInt();
    int valor4 = valor4Str.toInt();
    int valor5 = valor5Str.toInt();
    int valor6 = valor6Str.toInt();
    int valor7 = valor7Str.toInt();

    n.setID(valor1);
    n.setVolt(valor2);
    n.setPX(valor3);
    n.setPY(valor4);
    n.setRed(valor5);
    n.setGreen(valor7);
    n.setBlue(valor6);

    administrarNeuronas.agregarInicio(n);

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
}


void MainWindow::on_pushButton_3_clicked()
{
    QString valor1Str = ui->lineEdit->text();
    QString valor2Str = ui->lineEdit_2->text();
    QString valor3Str = ui->lineEdit_3->text();
    QString valor4Str = ui->lineEdit_4->text();
    QString valor5Str = ui->lineEdit_5->text();
    QString valor6Str = ui->lineEdit_6->text();
    QString valor7Str = ui->lineEdit_7->text();

    // Verificar si algún campo está vacío antes de continuar
    if (valor1Str.isEmpty() || valor2Str.isEmpty() || valor3Str.isEmpty() ||
        valor4Str.isEmpty() || valor5Str.isEmpty() || valor6Str.isEmpty() || valor7Str.isEmpty()) {
        QMessageBox::warning(this, "Campos Vacíos", "Por favor, complete todos los campos.");
        return;
    }

    // Convertir valores a números
    int valor1 = valor1Str.toInt();
    float valor2 = valor2Str.toFloat();
    int valor3 = valor3Str.toInt();
    int valor4 = valor4Str.toInt();
    int valor5 = valor5Str.toInt();
    int valor6 = valor6Str.toInt();
    int valor7 = valor7Str.toInt();

    n.setID(valor1);
    n.setVolt(valor2);
    n.setPX(valor3);
    n.setPY(valor4);
    n.setRed(valor5);
    n.setGreen(valor7);
    n.setBlue(valor6);

    administrarNeuronas.agregarFinal(n);

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
}



void MainWindow::on_pushButton_2_clicked()
{
    QString contenido = QString::fromStdString(administrarNeuronas.mostrar());
    ui->plainTextEdit->setPlainText(contenido);
}

void MainWindow::on_actionOpen_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Abrir Archivo de Datos", "", "Archivos de Texto (*.txt);;Todos los Archivos (*.*)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);

            while (!in.atEnd()) {
                QString linea = in.readLine();
                QStringList tokens = linea.split(":");

                if (tokens.size() == 2) {
                    QString etiqueta = tokens[0].trimmed();
                    QString valorStr = tokens[1].trimmed();
                    bool conversionOk = false;
                    float valorFloat = valorStr.toFloat(&conversionOk);

                    if (conversionOk) {
                        if (etiqueta == "ID") {
                            int id = static_cast<int>(valorFloat);
                            n.setID(id);
                        }
                        else if (etiqueta == "Posicion x") {
                            int posX= static_cast<int>(valorFloat);
                            n.setPX(posX);
                        }
                        else if (etiqueta == "Posicion y") {
                            int posY= static_cast<int>(valorFloat);
                            n.setPY(posY);
                        }
                        else if (etiqueta == "Red") {
                            int r = static_cast<int>(valorFloat);
                            n.setRed(r);
                        }
                        else if (etiqueta == "Green") {
                            int g = static_cast<int>(valorFloat);
                            n.setGreen(g);
                        }
                        else if (etiqueta == "Blue") {
                            int b = static_cast<int>(valorFloat);
                            n.setBlue(b);
                        }
                        else if (etiqueta == "Voltaje") {
                            int v = static_cast<int>(valorFloat);
                            n.setVolt(v);
                            administrarNeuronas.agregarFinal(n);
                        }
                    }
                }
            }
            file.close();
        } else {
            qDebug() << "Error al abrir el archivo:" << file.errorString();
        }
    }
}


void MainWindow::on_actionSave_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Guardar Datos", "", "Archivos de Texto (*.txt);;Todos los Archivos (*.*)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            QString contenido =  QString::fromStdString(administrarNeuronas.mostrar());
            out << contenido;
            file.close();
        } else {
            qDebug() << "Error al abrir el archivo:" << file.errorString();
        }
    }
}

void MainWindow::llenarTabla(){
    // Limpiar la tabla antes de llenarla
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    // Obtener el número de neuronas en la lista administradora
    int neuronasCount = administrarNeuronas.numeroDeNeuronas();

    // Establecer el número de filas en la tabla
    ui->tableWidget->setRowCount(neuronasCount);

    // Recorrer las neuronas y agregar cada neurona a la tabla
    for (int i = 0; i < neuronasCount; i++) {
        Neurona* neurona = administrarNeuronas.obtenerNeuronaEnPosicion(i);

        // Configurar celdas de la fila con los valores de la neurona
        QTableWidgetItem *itemID = new QTableWidgetItem(QString::number(neurona->getID()));
        QTableWidgetItem *itemPosX = new QTableWidgetItem(QString::number(neurona->getPX()));
        QTableWidgetItem *itemPosY = new QTableWidgetItem(QString::number(neurona->getPY()));
        QTableWidgetItem *itemRed = new QTableWidgetItem(QString::number(neurona->getRed()));
        QTableWidgetItem *itemGreen = new QTableWidgetItem(QString::number(neurona->getGreen()));
        QTableWidgetItem *itemBlue = new QTableWidgetItem(QString::number(neurona->getBlue()));
        QTableWidgetItem *itemVoltaje = new QTableWidgetItem(QString::number(neurona->getaVolt()));

        ui->tableWidget->setItem(i, 0, itemID);
         ui->tableWidget->setItem(i, 1, itemVoltaje);
        ui->tableWidget->setItem(i, 2, itemPosX);
        ui->tableWidget->setItem(i, 3, itemPosY);
        ui->tableWidget->setItem(i, 4, itemRed);
        ui->tableWidget->setItem(i, 5, itemGreen);
        ui->tableWidget->setItem(i, 6, itemBlue);
    }
}

void MainWindow::buscarPorNeurona() {
    QString idBuscado = ui->lineEdit_8->text();
    // Convierte el ID buscado de QString a int
    int id = idBuscado.toInt();
    llenarTabla();

    // Recorre todas las filas de la tabla
    bool encontrado = false;
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        qDebug() << "Dentro del bucle, fila:" << row;
        Neurona* neurona = administrarNeuronas.obtenerNeuronaEnPosicion(row);
        if (neurona && neurona->getID() == id) {
            // Si la neurona coincide con la búsqueda, muestra la fila
            ui->tableWidget->setRowHidden(row, false);
            encontrado = true;
            qDebug() << "ID encontrado en fila:" << row;
        } else {
            // Si no coincide, oculta la fila
            ui->tableWidget->setRowHidden(row, true);
        }
   }
    if(encontrado){
        qDebug () <<"a";
        QMessageBox::information(this, "ID no encontrado", "No se encontró una neurona con ese ID.");
    }
}

void MainWindow::dibujarNeurona() {
    QGraphicsScene *scene = ui->graphicsView->scene();
        scene->clear();

        // Dibuja las neuronas en la escena
        for (int i = 0; i < administrarNeuronas.numeroDeNeuronas(); i++) {
            Neurona *neurona = administrarNeuronas.obtenerNeuronaEnPosicion(i);
            float x = neurona->getPX();
            float y = neurona->getPY();
            int red = neurona->getRed();
            int blue = neurona->getBlue();
            int green = neurona->getGreen();
            float radio = 4.0; // Ajusta el radio según tus necesidades

            QGraphicsEllipseItem *ellipse = scene->addEllipse(x - radio, y - radio, 2 * radio, 2 * radio);
            // Establece el color según el valor de los componentes RGB
            ellipse->setBrush(QColor(red, green, blue));
            ellipse->setFlag(QGraphicsItem::ItemIsMovable);

            QGraphicsTextItem *text = scene->addText(QString::number(neurona->getID()));
            text->setPos(x - 4, y - 5);
        }
    }


void MainWindow::ordenarID() {
    administrarNeuronas.ordenarPorID();
    llenarTabla(); // Vuelve a llenar la tabla después de ordenar
}

void MainWindow::ordenarVOLT() {
    administrarNeuronas.ordenarPorVoltaje();
    llenarTabla(); // Vuelve a llenar la tabla después de ordenar
}


// Agrega una estructura para la lista de adyacencia
struct ListaAdyacencia {
    int id;
    std::vector<int> conexiones;
};

// Modifica la función de puntosCercanos para construir la lista de adyacencia
void MainWindow::puntosCercanos() {
    int numNeuronas = administrarNeuronas.numeroDeNeuronas();
    if (numNeuronas < 2) {
        QMessageBox::warning(this, "Advertencia", "No hay suficientes neuronas para calcular los puntos más cercanos.");
        return;
    }

    QGraphicsScene *scene = ui->graphicsView->scene();
    QPen pen(Qt::red);
    pen.setWidth(2);

    std::unordered_map<int, ListaAdyacencia> listaAdyacencia;

    for (int i = 0; i < numNeuronas; i++) {
        Neurona *neuronaA = administrarNeuronas.obtenerNeuronaEnPosicion(i);
        float min = 1000;
        Neurona *neuronaBMin = nullptr;

        for (int j = i + 1; j < numNeuronas; j++) {
            Neurona *neuronaB = administrarNeuronas.obtenerNeuronaEnPosicion(j);
            float distancia = sqrt(pow(neuronaA->getPX() - neuronaB->getPX(), 2) + pow(neuronaA->getPY() - neuronaB->getPY(), 2));
            if (distancia < min) {
                min = distancia;
                neuronaBMin = neuronaB;
            }
        }

        if (neuronaBMin != nullptr) {
            QLineF line(neuronaA->getPX(), neuronaA->getPY(), neuronaBMin->getPX(), neuronaBMin->getPY());
            scene->addLine(line, pen);

            // Calcular el ángulo para dibujar la flecha
            double angle = std::atan2(-line.dy(), line.dx());

            // Añadir la flecha
            float arrowSize = 5.0;
            QPointF arrowP1 = line.p2() - QPointF(arrowSize * std::cos(angle + M_PI / 3), arrowSize * std::sin(angle + M_PI / 3));
            QPointF arrowP2 = line.p2() - QPointF(arrowSize * std::cos(angle - M_PI / 3), arrowSize * std::sin(angle - M_PI / 3));
            QPen pen2(Qt::green);
            QGraphicsPolygonItem *arrowHead = scene->addPolygon(QPolygonF() << line.p2() << arrowP1 << arrowP2, pen2.color());
            arrowHead->setBrush(pen2.color());

            // Agrega la conexión a la lista de adyacencia
            int idA = neuronaA->getID();
            int idB = neuronaBMin->getID();
            listaAdyacencia[idA].id = idA;
            listaAdyacencia[idA].conexiones.push_back(idB);
        }
    }

    // Imprime la lista de adyacencia en la consola para verificar
    for (const auto& entrada : listaAdyacencia) {
        std::cout << "N" << entrada.first << " -> N";
        for (int conexion : entrada.second.conexiones) {
            std::cout << conexion << " ";
        }
        std::cout << std::endl;
    }
    // Formatea la lista de adyacencia en un QString
    QString listaAdyacenciaStr;
    QTextStream stream(&listaAdyacenciaStr);
    for (const auto& entrada : listaAdyacencia) {
        stream << "N" << entrada.first << " -> N";
        for (int conexion : entrada.second.conexiones) {
            stream << conexion << " ";
        }
        stream << "\n";
    }

    // Establece el texto formateado en el QPlainTextEdit
    ui->plainTextEdit->setPlainText(listaAdyacenciaStr);
}




