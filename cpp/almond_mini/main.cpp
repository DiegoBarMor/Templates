#include <SFML/Graphics.hpp>

#include "almond.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "ALMOND Template");
    window.setFramerateLimit(60);

    nd::App gui = nd::App(window);
    gui.setup("layout.ndg");

    ////// Callbacks
    nd::Widget* root = gui.get_widget("root");
    root->link_on_closed([&gui](const std::optional<sf::Event> event) {
        gui.get_window().close();
        return true;
    });
    root->link_on_key_pressed([&gui](const std::optional<sf::Event> event) {
        const auto* keyPress = event->getIf<sf::Event::KeyPressed>();
        if (keyPress && keyPress->code == sf::Keyboard::Key::Escape) {
            gui.get_window().close();
            return true;
        }
        return false;
    });

    ////// Main loop
    while (window.isOpen()) {
        gui.manage_events();
        window.clear(sf::Color::Black);
        gui.draw();
        window.display();
    }
    return 0;
}
