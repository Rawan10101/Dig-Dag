#include "MainWindow.h"
#include "woodenboxes.h"
#include "rockboxes.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);

    setCentralWidget(view);

    tileWidth = 55;
    tileHeight = 39;
    loadGrid("C:/Users/HP/OneDrive/Desktop/Level one.txt");

    player = new Player();
    player->setScenePointer(scene);
    scene->addItem(player);
    view->setSceneRect(scene->sceneRect());

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFocusPolicy(Qt::StrongFocus);

    view->show();
}


MainWindow::~MainWindow() {
     delete player;
}
void MainWindow::loadGrid(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Unable to open the file.";
        return;
    }

    QTextStream in(&file);
    int y = 0;
    int gridWidth = 0;
    int gridHeight = 0;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList numbers = line.split(" ");
        gridWidth = numbers.size();

        for (int x = 0; x < numbers.size(); ++x) {
            int Type = numbers[x].toInt();
            QPixmap Image;

            switch (Type) {
            case 0:
                Image = QPixmap("");
                break;
            case 1:
                Image = QPixmap("C:/Users/HP/Downloads/horror_brick_09-512x512.png");
                break;
            case 2:
                Image = QPixmap(":/images/gem.png");
                break;
            case 3:
                Image = QPixmap("C:/Users/HP/Downloads/rock.gif");
                break;
            default:
                Image = QPixmap("");
                break;
            }

            Image = Image.scaled(tileWidth, tileHeight);

            if (Type == 1) {
                WoodenBoxes *box = new WoodenBoxes();
                box->setPixmap(Image);
                box->setPos(x * tileWidth, y * tileHeight);
                scene->addItem(box);
            } else if(Type==3){
                RockBoxes *rock = new RockBoxes();
                rock->setPixmap(Image);
                rock->setPos(x * tileWidth, y * tileHeight);
                scene->addItem(rock);
            }
            else {
                QGraphicsPixmapItem *Item = new QGraphicsPixmapItem(Image);
                Item->setPos(x * tileWidth, y * tileHeight);
                scene->addItem(Item);
            }
        }
        y++;
    }

    gridHeight = y;

    scene->setSceneRect(0, 0, gridWidth * tileWidth, gridHeight * tileHeight);
}


