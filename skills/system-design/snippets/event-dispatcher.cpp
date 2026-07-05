#include <functional>
#include <vector>
#include <iostream>

struct Event {
    int type;
};

class EventDispatcher {
public:
    using Listener = std::function<void(const Event&)>;

    void RegisterListener(Listener listener) {
        listeners_.push_back(listener);
    }

    void Dispatch(const Event& event) {
        for (auto& listener : listeners_) {
            listener(event);
        }
    }

private:
    std::vector<Listener> listeners_;
};

int main() {
    EventDispatcher dispatcher;
    dispatcher.RegisterListener([](const Event& event) {
        std::cout << "Received event: " << event.type << "\n";
    });

    dispatcher.Dispatch({1});
    return 0;
}
