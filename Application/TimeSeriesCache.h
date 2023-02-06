
#ifndef TIMESERIESCACHE_H_B0DBA0570D5FD14E
#define TIMESERIESCACHE_H_B0DBA0570D5FD14E

#include <Utilities/TimeSeries_s.h>

#include <Common/Downloader.h>
#include <Common/qstr_unordered_map.h>

#include <functional>
#include <memory>
#include <deque>

namespace WaterwAIs {

//////////////////////////////////////////////////////////////////////////
// TimeSeriesCache

class TimeSeriesCache {
public:
    using TimeSeries = CTimeSeries<double>;
    using TimeSeriesPtr = std::shared_ptr<const TimeSeries>;
    
    using EntryReadyFunc = std::function<void(TimeSeriesPtr)>;

    static constexpr size_t default_capacity = 50U;

    TimeSeriesCache(size_t capacity = default_capacity);

    void clear();
    bool empty() const { return tseries_map_.size(); }

    // Capacity
    void setCapacity(size_t capacity);
    size_t capacity() const { return capacity_; }

    // Returns TimeSeries entry by name.
    // if the entry is ready, it will be returned immediately.
    // 
    // Otherwise, it will be downloaded and delivered via a callback and the
    // function will return empty entry.
    // NOTE: If download fails then the callback will report an empty entry here.
    TimeSeriesPtr get(QStringView name, EntryReadyFunc callback = {});

    // Returns global cache instance
    static TimeSeriesCache& instance();

private:
    using TimeSeriesMap = qstr_unordered_map<TimeSeriesPtr>;

    void onEntryDownloaded(const QString& name, bool result, 
        const QString& text, EntryReadyFunc callback);

    void checkCapacity();

    size_t capacity_;

    std::deque<TimeSeriesMap::iterator> tseries_list_;
    TimeSeriesMap tseries_map_;    
};

} // namespace WaterwAIs


//////////////////////////////////////////////////////////////////////////
#endif // TIMESERIESCACHE_H_B0DBA0570D5FD14E
