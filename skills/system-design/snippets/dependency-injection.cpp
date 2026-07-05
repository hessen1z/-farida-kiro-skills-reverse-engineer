#include <iostream>
#include <memory>

struct ILogger {
    virtual ~ILogger() = default;
    virtual void Log(const std::string& message) = 0;
};

class ConsoleLogger : public ILogger {
public:
    void Log(const std::string& message) override {
        std::cout << message << "\n";
    }
};

class Application {
public:
    Application(std::unique_ptr<ILogger> logger)
        : logger_(std::move(logger)) {}

    void Run() {
        logger_->Log("Application started");
    }

private:
    std::unique_ptr<ILogger> logger_;
};

int main() {
    auto logger = std::make_unique<ConsoleLogger>();
    Application app(std::move(logger));
    app.Run();
    return 0;
}
