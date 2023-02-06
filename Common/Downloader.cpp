
#include "Downloader.h"

namespace WaterwAIs {

Downloader& Downloader::instance() {
    static auto downloader = Downloader{};
    return downloader;
}

} // namespace WaterwAIs
