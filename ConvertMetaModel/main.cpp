#include <QCoreApplication>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>


int main(int argc, char *argv[])
{

    QDir directory("/Users/arash/Projects/OpenHydroQual/resources");
    QStringList jsonfiles = directory.entryList(QStringList() << "*.json",QDir::Files);
    QJsonObject out;
    foreach(QString filename, jsonfiles) {

        QFile file(directory.absolutePath()+"/" +filename);
        if (file.open(QIODevice::ReadOnly))
        {
            QJsonObject jsonobj = QJsonDocument().fromJson(file.readAll()).object();
            for(QString key: jsonobj.keys() ) {
                QJsonObject vars = jsonobj[key].toObject();
                QJsonObject outvar;
                if (vars["type"] == "block") outvar["type"] = "node";
                if (vars["type"] == "link") outvar["type"] = "link";
                outvar["description"] = vars["description"];
                outvar["icon"] = vars["icon"].toObject()["filename"].toString();
                for (QString variablekey: vars.keys())
                {
                    QJsonObject var = vars[variablekey].toObject();
                    if (variablekey != "type" && variablekey != "name" && variablekey != "description" && variablekey != "icon" && variablekey != "typecategory")
                    {
                        QJsonObject outvariable;
                        outvariable["type"] = vars[variablekey].toObject()["type"].toString().trimmed();
                        outvar[variablekey.trimmed()] = outvariable;
                    }
                }
                out[key] = outvar;
            }
        }
    }
    QFile outfile("/Users/arash/Projects/QMapViewer/Json/MetaModel.json");
    outfile.open(QIODevice::WriteOnly);

    QJsonDocument outjsonDoc = QJsonDocument(out);
    outfile.write(outjsonDoc.toJson());
    outfile.close();

    QCoreApplication a(argc, argv);

    return a.exec();
}
