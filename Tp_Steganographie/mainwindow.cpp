#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connecter le signal "clicked" du bouton "Analyser" à la fonction "analyserFichier"
    connect(ui->analyserButton, SIGNAL(clicked()), this, SLOT(analyserFichier()));

    // Connecter le signal "clicked" du bouton "Parcourir" à la fonction "onBrowseButtonClicked"
    connect(ui->browseButton, SIGNAL(clicked()), this, SLOT(onBrowseButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onBrowseButtonClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Ouvrir un fichier"), QDir::homePath(), tr("Fichiers texte (*.txt)"));
    if (!fileName.isEmpty()) {
        ui->filePathLineEdit->setText(fileName);
    }
}

void MainWindow::analyserFichier()
{
    // Récupérer le chemin du fichier à analyser depuis le QLineEdit "filePathLineEdit"
    QString filePath = ui->filePathLineEdit->text();

    // Ouvrir le fichier en lecture seule
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'ouvrir le fichier."));
        return;
    }

    // Lire le contenu du fichier ligne par ligne et analyser chaque mot
    QTextStream in(&file);
    QString line;
    QString resultat;
    while (!in.atEnd()) {
        line = in.readLine();
        QStringList words = line.split(" ", Qt::SkipEmptyParts);
        for (const QString& word : words) {
            if (word.endsWith("d")) {
                resultat.append(word[0]).append(" ");
            }
        }
    }

    // Afficher le résultat dans le QTextBrowser "resultatTextBrowser"
    ui->resultTextBrowser->setText(resultat);

    // Fermer le fichier
    file.close();
}
