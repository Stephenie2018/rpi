#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>

using namespace ftxui;

int main() {
    auto screen = ScreenInteractive::Fullscreen();

    int brightness = 50;
    bool system_on = false;

    // Knoppen definiëren
    auto btn_on = Button(" SYSTEEM AAN ", [&] { system_on = true; }, ButtonOption::Animated(Color::Green));
    auto btn_off = Button(" SYSTEEM UIT ", [&] { system_on = false; }, ButtonOption::Animated(Color::Red));
    auto slider = Slider("Helderheid:", &brightness, 0, 100, 5);

    // Groepeer de knoppen in containers voor interactie
    auto container = Container::Vertical({
        Container::Horizontal({btn_on, btn_off}),
        slider,
    });

    // De Renderer bouwt de visuele interface
    auto renderer = Renderer(container, [&] {
        // Hier zat de fout: we gebruiken hbox() om tekst naast elkaar te zetten
        // en we zorgen dat de types matchen.
        auto status_text = system_on ? text("ACTIEF") | color(Color::Green) 
                                     : text("STANDBY") | color(Color::Red);

        return vbox({
            text(" RASPBERRY PI CONTROL CENTER ") | bold | center | color(Color::Cyan),
            separator(),
            hbox({
                vbox({
                    hbox({ text("STATUS: "), status_text }), // Correcte manier om tekst te combineren
                    text("HELDERHEID: " + std::to_string(brightness) + "%"),
                }) | flex | border,
                
                vbox({
                    hbox({ btn_on->Render(), btn_off->Render() }) | center,
                    text(" "),
                    slider->Render()
                }) | flex | border
            }) | flex
        }) | border;
    });

    screen.Loop(renderer);
    return 0;
}
