#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>

int main() {
    using namespace ftxui;

    // We bouwen de interface op als een 'document'
    Element document = vbox({
        text(" Raspberry Pi Lite ") | bold | center | color(Color::Yellow) | bgcolor(Color::Blue),
        separator(),
        text("Hello, World!") | center | color(Color::Green),
        text("Dit is een moderne TUI in C++") | center,
    }) | borderDouble; // Geeft het een mooie dubbele rand

    // We maken een schermvullende weergave
    auto screen = Screen::Create(
        Dimension::Full(),       // Breedte
        Dimension::Fit(document) // Hoogte past zich aan aan de tekst
    );

    Render(screen, document);
    screen.Print();

    return 0;
}
