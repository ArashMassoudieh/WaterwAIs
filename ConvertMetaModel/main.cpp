#include <QCoreApplication>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>


int main(int argc, char *argv[])
{

    QDir directory("/home/arash/Dropbox/JsonFilesToBeCopiedtoWaterwAIs");
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
                QFile iconfile;
                qDebug()<<QString::fromStdString("/home/arash/Projects/QAquifolium/resources/Icons/")+outvar["icon"].toString();
                qDebug()<<iconfile.copy(QString::fromStdString("/home/arash/Projects/QAquifolium/resources/Icons/")+outvar["icon"].toString(), "/home/arash/Dropbox/JsonFilesToBeCopiedtoWaterwAIs/Icons/"+outvar["icon"].toString());
                qDebug()<<iconfile.errorString()<<iconfile.error();
                for (QString variablekey: vars.keys())
                {
                    QJsonObject var = vars[variablekey].toObject();
                    if (variablekey != "type" && variablekey != "name" && variablekey != "description" && variablekey != "icon" && variablekey != "typecategory")
                    {
                        QJsonObject outvariable;
                        outvariable["type"] = vars[variablekey].toObject()["type"].toString().trimmed();
                        outvariable["unit"] = vars[variablekey].toObject()["unit"].toString().trimmed();
                        outvariable["delegate"] = vars[variablekey].toObject()["delegate"].toString().trimmed();
                        outvariable["description"] = vars[variablekey].toObject()["description"].toString().trimmed();
                        if (vars[variablekey].toObject()["ask_user"].toString().trimmed()=="true" || vars[variablekey].toObject()["includeinoutput"].toString().trimmed()=="true")
                            outvar[variablekey.trimmed()] = outvariable;
                    }
                }
                out[key] = outvar;
            }
        }
    }
    QFile outfile("/home/arash/Dropbox/JsonFilesToBeCopiedtoWaterwAIs/WaterwAIs/MetaModel.json");
    outfile.open(QIODevice::WriteOnly);

    QJsonDocument outjsonDoc = QJsonDocument(out);
    outfile.write(outjsonDoc.toJson());
    outfile.close();


    //convert OHQ to WaterwAIs
    QFile ohqFile("/home/arash/Dropbox/Ahmed_simulation/Calibration/Calibration_10_24_2022_100_Ahmed.ohq");
    ohqFile.open(QIODevice::ReadOnly);
    QTextStream in(&ohqFile);
    QJsonObject model;
    while (!in.atEnd()) {
        QStringList line = in.readLine().split(";");
        if (line.size()==2)
        {
            QStringList command = line[0].split(" ");
            QStringList argumentsqlist = line[1].split(",");
            QMap<QString,QString> arguments;

            if (command[0]=="create")
            {
                for (int i=0; i<argumentsqlist.count(); i++)
                {
                    qDebug()<<argumentsqlist[i].split("=")[0]<<":"<<argumentsqlist[i].split("=")[1];
                    arguments[argumentsqlist[i].split("=")[0]]=argumentsqlist[i].split("=")[1].split("[")[0];
                }
                QString name = arguments["name"];
                QJsonObject item;
                for (QMap<QString,QString>::iterator it = arguments.begin(); it!=arguments.end(); it++)
                {
                    QJsonValue jsonarg = it.value();
                    item[it.key()]=jsonarg;
                }
                model[name] = item;
            }
        }
    }
    QFile modeloutfile("/home/arash/Dropbox/JsonFilesToBeCopiedtoWaterwAIs/WaterwAIs/Model.json");
    modeloutfile.open(QIODevice::WriteOnly);

    QJsonDocument modeloutjsonDoc = QJsonDocument(model);
    modeloutfile.write(modeloutjsonDoc.toJson());
    modeloutfile.close();


    QCoreApplication a(argc, argv);

    return a.exec();
}
