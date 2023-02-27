#ifndef METACOMPONENTITEM_H_B311B90CD98008C4
#define METACOMPONENTITEM_H_B311B90CD98008C4

#include "Variable.h"
#include <QJsonObject>
#include <QPixmap>

namespace WaterwAIs {


//////////////////////////////////////////////////////////////////////////
// MetaComponentItem
//
// This class represents a "Component" data item stored in MetaModel.

class MetaComponentItem {
public:
    using IconDownloadedFunc = std::function<void(const QPixmap&)>;

    MetaComponentItem() = default;
    ~MetaComponentItem();

    enum class Type {
        Unknown = 0,
        Node,
        Link,
        Entity
    };
    
    MetaComponentItem(const QJsonObject& json_object);
    
    // Name
    QString name() const { return name_; }
    void setName(QStringView name) { name_ = name.toString(); }

    // Type
    Type type() const { return type_; }
    void setType(Type type) { type_ = type; }

    // Icon file name
    QString iconPath() const { return icon_path_; }
    void setIconPath(QStringView icon_path);

    // Icon
    const QPixmap& icon() const { return icon_; }

    // Width/Height for display in the Map view
    double width () const { return width_; }
    double height() const { return height_; }

    // Downloads item icon asynchronously and calls a callback when it is done.
    void downloadIcon(IconDownloadedFunc callback);

    // Properties
    const VariableMap& properties() const { return properties_; }
          VariableMap& properties()       { return properties_; }

    static QString typeToSting(Type type);

private:
    QString      name_;
    Type         type_;
    QString      icon_path_;
    QPixmap      icon_;

    double       width_  = 0.0;
    double       height_ = 0.0;

    VariableMap  properties_;

    class IconDownloader;
    std::unique_ptr<IconDownloader> icon_downloader_;
};

} // namespace WaterwAIs

//////////////////////////////////////////////////////////////////////////
#endif // METACOMPONENTITEM_H_B311B90CD98008C4
