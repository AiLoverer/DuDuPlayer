#ifndef METADATA_H
#define METADATA_H

#include <string>
#include <map>
#include <memory>
#include <QtQml>

void registerQmlClasses(QQmlContext* context);
void registerCpp2Property(std::map<const char*, std::shared_ptr<QObject> >& properties, QQmlContext* ctx);
void regiserMetaData(std::map<const char*, std::shared_ptr<QObject> >& properties, QQmlContext* context);

#endif // METADATA_H
