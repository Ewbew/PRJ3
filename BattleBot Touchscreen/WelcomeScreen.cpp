#include "WelcomeScreen.h" 
#include <QLabel>
#include <QVBoxLayout>

WelcomeScreen::WelcomeScreen(QWidget* parent) : QWidget(parent) {
    // Create layout
    QVBoxLayout* layout = new QVBoxLayout(this);

    // Welcome message
    QLabel* welcomeLabel = new QLabel("Welcome to SwEET BattleBot");
    welcomeLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(welcomeLabel);

    // Set layout for the widget
    setLayout(layout);
}

WelcomeScreen::~WelcomeScreen() {
    // Clean up resources if needed (nothing to do in this case)
}