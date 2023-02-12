
#include "Downloader.h"
#include <Application/Defs.h>

namespace WaterwAIs {

Downloader& Downloader::instance() {
    static auto downloader = Downloader{};

    return downloader;
}

} // namespace WaterwAIs
