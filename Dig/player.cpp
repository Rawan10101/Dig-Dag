#include "player.h"
#include "woodenboxes.h"
#include <QGraphicsScene>
#include "rockboxes.h"

Player::Player() {

    Image = QPixmap("C:/Users/HP/Downloads/R1.png");
    setPixmap(Image);
    setPos(0, 0);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

void Player::setInitialPosition(int x, int y) {
    setPos(x, y);
}

void Player::moveLeft() {
    Image = QPixmap("C:/Users/HP/Downloads/L1.png");
    setPixmap(Image);

    if (x() > 0) {
        setPos(x() - 10, y());
          checkCollisions();

    }


}
void Player::setScenePointer(QGraphicsScene* scenePtr) {
    scenePointer = scenePtr;
}

void Player::moveRight() {
    Image = QPixmap("C:/Users/HP/Downloads/R1.png");
    setPixmap(Image);

    QRectF sceneRect = scenePointer->sceneRect();
    if (x() + pixmap().width() < sceneRect.width()) {
        setPos(x() + 10, y());
          checkCollisions();
    }


}

void Player::moveUp() {
    if (y() > 0) {
        setPos(x(), y() - 10);
          checkCollisions();
    }
}

void Player::moveDown() {

    QRectF sceneRect = scenePointer->sceneRect();
    if (y() + pixmap().height() < sceneRect.height()) {
        setPos(x(), y() + 10);
          checkCollisions();
    }

}

void Player::keyPressEvent(QKeyEvent *event) {

    switch (event->key()) {
    case Qt::Key_Left:
        moveLeft();
        break;
    case Qt::Key_Right:
        moveRight();
        break;
    case Qt::Key_Up:
        moveUp();
        break;
    case Qt::Key_Down:
        moveDown();
        break;
    default:
        QGraphicsPixmapItem::keyPressEvent(event);
        break;
    }
}

void Player::checkCollisions() {
    QList<QGraphicsItem *> collidingItemsList = collidingItems();
    for (QGraphicsItem *item : collidingItemsList) {
        WoodenBoxes *box = dynamic_cast<WoodenBoxes *>(item);
        if (box) {
            qDebug() << "Collided with WoodenBox at position:- " << box->pos();
            if (scene()) {
                scene()->removeItem(box);
                delete box;

            }
        }
        RockBoxes *rock = dynamic_cast<RockBoxes*>(item);
        if (rock) {
            qDebug() << "Collided with RockBox at position:" << rock->pos();
            return;
        }
    }
}



