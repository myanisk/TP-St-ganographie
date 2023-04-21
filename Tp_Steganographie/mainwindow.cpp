#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Ajouter du texte par défaut à la QTextBrowser
    ui->textBrowser->setText("Mot de passe:\n");

    // Ouvrir le fichier texte ( Chemin à modifier !!!!!)
    QFile file("C:\\Users\\yanis\\Documents\\Tp_Steganographie\\texte.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    // Lire le fichier texte
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList words = line.split(" ");
        // Analyser chaque mot
        foreach(QString word, words) {
            if (word.endsWith("d")) {
                // Extraire la première lettre et afficher le mot résultant
                QString newWord = word.left(1) ;
                ui->textBrowser->append(newWord);
            }
        }
    }

    // Fermer le fichier texte
    file.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}
