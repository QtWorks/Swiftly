#include "StaticFileServer.h"
#include <QFile>
#include <QFileInfo>

void StaticFileServer::registerPathHandlers()
{
   addGetHandler("/", "handleFileGet");
}

void StaticFileServer::handleFileGet(HttpRequest &request, HttpResponse &response)
{
    qDebug() << "-----------%%%" << request.getHeader().getPath();

    QFile file(QString("./Html").append(request.getHeader().getPath()));
    if (file.exists())
    {
        if (file.open(QFile::ReadOnly))
        {
            response << file.readAll();

            QFileInfo fileInfo(file);
           // qDebug() << fileInfo.completeSuffix() << fileInfo.fileName() ;
           // if (fileInfo.completeSuffix() == "html" || fileInfo.completeSuffix() == "htm")
            {
                response.finish(HttpResponse::TEXT);
            }
            //else
            {
              //  response.finish(HttpResponse::BINARY);
            }
            file.close();
        }
    }
    else
    {
        response.setStatusCode(404);
        response << "can't find the file!\n";
    }
}
