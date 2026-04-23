#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

int main() {
    auto screen = ScreenInteractive::Fullscreen();

    // Data voor ons paneel
    int brightness = 50;
    bool system_on = false;

    // Componenten (Knoppen)
    auto btn_on = Button(" SYSTEEM AAN ", [&] { system_on = true; }, ButtonOption::Animated(Color::Green));
    auto btn_off = Button(" SYSTEEM UIT ", [&] { system_on = false; }, ButtonOption::Animated(Color::Red));
    
    auto slider = Slider("Helderheid:", &brightness, 0, 100, 5);

    // Layout van het paneel
    auto container = Container::Vertical({
        Container::Horizontal({btn_on, btn_off}),
        slider,
    });

    auto renderer = Renderer(container, [&] {
        return vbox({
            text(" RASPBERRY PI CONTROL CENTER ") | bold | center | color(Color::Cyan),
            separator(),
            hbox({
                vbox({
                    text("STATUS: ") + (system_on ? text("ACTIEF") | color(Color::Green) 
                                                 : text("STANDBY") | color(Color::Red)),
                    text("HELDERHEID: " + std::to_string(brightness) + "%"),
                }) | flex | border,
                
                // Onze knoppen in de UI plaatsen
                vbox({
                    hbox({ btn_on->Render(), btn_off->Render() }) | center,
                    text(" "),
                    slider->Render()
                }) | flex | border
            }) | flex
        });
    });

    // Start de interactieve loop (reageert op touch/muis)
    screen.Loop(renderer);

    return 0;
}
