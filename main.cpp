#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong Game");
    window.setFramerateLimit(60);

    // Definir las paletas y la pelota
    sf::RectangleShape paddle1(sf::Vector2f(10, 80));
    sf::RectangleShape paddle2(sf::Vector2f(10, 80));
    sf::RectangleShape ball(sf::Vector2f(10, 10));

    paddle1.setPosition(10, 260);
    paddle2.setPosition(780, 260);
    ball.setPosition(395, 295);

    // Velocidad de la pelota
    sf::Vector2f ballVelocity(5, 5);

    // Puntuación
    int score1 = 0;
    int score2 = 0;

    // Fuentes de sonido
    sf::SoundBuffer buffer;
    buffer.loadFromFile("paddle.wav");
    sf::Sound paddleSound(buffer);

    // Bucle principal
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Movimiento de las paletas
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && paddle1.getPosition().y > 0)
            paddle1.move(0, -5);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && paddle1.getPosition().y < 520)
            paddle1.move(0, 5);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && paddle2.getPosition().y > 0)
            paddle2.move(0, -5);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && paddle2.getPosition().y < 520)
            paddle2.move(0, 5);

        // Movimiento de la pelota
        ball.move(ballVelocity);

        // Colisiones con las paredes
        if (ball.getPosition().y < 0 || ball.getPosition().y > 590)
            ballVelocity.y = -ballVelocity.y;

        // Colisión con las paletas
        if (ball.getGlobalBounds().intersects(paddle1.getGlobalBounds()) || ball.getGlobalBounds().intersects(paddle2.getGlobalBounds()))
        {
            ballVelocity.x = -ballVelocity.x;
            paddleSound.play();
        }

        // Punto anotado
        if (ball.getPosition().x < 0)
        {
            ball.setPosition(395, 295);
            ballVelocity.x = 5;
            ballVelocity.y = 5;
            score2++;
        }
        if (ball.getPosition().x > 800)
        {
            ball.setPosition(395, 295);
            ballVelocity.x = -5;
            ballVelocity.y = -5;
            score1++;
        }

        // Limpiar la ventana
        window.clear();

        // Dibujar las paletas y la pelota
        window.draw(paddle1);
        window.draw(paddle2);
        window.draw(ball);

        // Dibujar la puntuación
        sf::Font font;
        font.loadFromFile("arial.ttf");
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(30);
        text.setString(std::to_string(score1) + " - " + std::to_string(score2));
        text.setPosition(370, 20);
        window.draw(text);

        // Mostrar en pantalla
        window.display();
    }

    return 0;
}
