
#include <Application/Application.h>

using namespace WaterWays;

int main(int argc, char *argv[]) {
    Q_INIT_RESOURCE(images);

    auto app = Application{argc, argv};
    return app.exec();
}
