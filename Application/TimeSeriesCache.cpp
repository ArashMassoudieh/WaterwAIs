
#include "TimeSeriesCache.h"
#include "FileNameProcessor.h"

#include <QTextStream>

namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// TimeSeriesCache

TimeSeriesCache::TimeSeriesCache(size_t capacity)
    : capacity_{capacity} {
    Q_ASSERT(capacity_ > 0);
}

void TimeSeriesCache::clear() {
    tseries_map_ .clear();
    tseries_list_.clear();
}

void TimeSeriesCache::setCapacity(size_t capacity) {
    Q_ASSERT(capacity > 0);

    capacity_ = capacity;
    checkCapacity();
}

TimeSeriesCache::TimeSeriesPtr TimeSeriesCache::get(QStringView name,
    EntryReadyFunc callback) {
    auto entry = TimeSeriesPtr{};

    if (auto pos = tseries_map_.find(name.toString()); pos != tseries_map_.end()) {
        // We have an entry in the cache so let's report it.
        entry = pos->second;
    } else {
        // We don't have an entry in the cache and need to download it.
        auto name_str = name.toString();

        Downloader::instance().download<QString>(WW_HOST_PATH(name_str),
            [this, name_str, callback](auto result, const auto& text) {
                onEntryDownloaded(name_str, result, text, callback);
            });
    }
    return entry;
}

void TimeSeriesCache::onEntryDownloaded(const QString& name, bool result,
    const QString& text, EntryReadyFunc callback) {

    if (!result) {
        // Download failed
        qDebug() << "TimeSeriesCache, download for entry: " << name << " failed";

        if (callback)
            callback(TimeSeriesPtr{});
        return;
    }

    // Download succeeded, so let's add a new entry to the cache.
    auto entry = std::make_shared<TimeSeries>();
    auto text_data = QString{text};

    // Parsing time series in CSV format
    auto stream = QTextStream{&text_data, QIODevice::ReadOnly};
    auto line = QString{};

    while (stream.readLineInto(&line)) {
        auto parts = line.split(',', Qt::SkipEmptyParts);

        if (parts.size() == 2) {
            // We have both time and value
            auto time  = parts[0].trimmed().toDouble();
            auto value = parts[1].trimmed().toDouble();

            entry->append(time, value);
        }
    }

    auto insertion = tseries_map_.emplace(name, entry);

    if (insertion.second) {
        // Successfully added a new entry
        tseries_list_.emplace_back(insertion.first);
        checkCapacity();
    }    
     
    if (callback)
        callback(entry);
}

void TimeSeriesCache::checkCapacity() {
    // Check capacity
    while (tseries_list_.size() > capacity_) {
        tseries_map_.erase(tseries_list_.front());
        tseries_list_.pop_front();
    }
}

TimeSeriesCache& TimeSeriesCache::instance() {
    static auto ts_cache = TimeSeriesCache{};
    return ts_cache;
}


} // namespace WaterwAIs