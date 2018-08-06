#include "Util/Random.h"
#include "Util/Config.h"
#include "App.h"
#include "GameOfLife/GameOfLife.h"
#include "WildFire/WildFire.h"

int main()
{
    Config config = {{ 1280, 720 }, 4 };
    App app(config);

    app.init<WildFire>();
    app.run();
    return 0;
}
