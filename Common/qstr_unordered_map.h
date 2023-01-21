
#ifndef QSTR_UNORDERED_MAP_H_9D520E82BFD7F6CF
#define QSTR_UNORDERED_MAP_H_9D520E82BFD7F6CF

#include <QString>
#include <QStringView>
#include <unordered_map>

namespace WaterWays {

// Helper wrapper around std::unordered_map<QString, T>, allowing to use
// QStringView in some operations instead of QString which is more efficient.

struct qstring_hash {
    using hash_type = std::hash<QStringView>;
    using is_transparent = void;

    std::size_t operator()  (const QChar* str) const { return hash_type{}(str); }
    std::size_t operator()   (QStringView str) const { return hash_type{}(str); }
    std::size_t operator()(QString const& str) const { return hash_type{}(str); }
};



#ifdef Q_OS_WASM
template <typename T>
class qstr_unordered_map:
    public std::unordered_map<QString, T, qstring_hash, std::equal_to<>> {
public:
    using Base = std::unordered_map<QString, T, qstring_hash, std::equal_to<>>;

    qstr_unordered_map() = default;

    auto find(QStringView key) { return Base::find(key.toString()); }

    auto find(QStringView key) const
        { return Base::find(key.toString()); }

    bool contains(QStringView key) const {
        auto pos = find(key);
        return pos != Base::end();
    }
};
#else
template <typename T>
    using qstr_unordered_map =
    std::unordered_map<QString, T, qstring_hash, std::equal_to<>>;
#endif

} // namespace WaterWays

//////////////////////////////////////////////////////////////////////////
#endif //QSTR_UNORDERED_MAP_H_9D520E82BFD7F6CF
