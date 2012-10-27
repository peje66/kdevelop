/* This file is part of KDevelop
Copyright 2008 Andreas Pakulat <apaku@gmx.de>

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public License
along with this library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
Boston, MA 02110-1301, USA.
*/

#include "session.h"

#include <QtCore/QFileInfo>
#include <QtCore/QDir>

#include <kurl.h>
#include <kstandarddirs.h>
#include <kparts/mainwindow.h>
#include <kdebug.h>

#include <interfaces/iplugincontroller.h>
#include <interfaces/iuicontroller.h>
#include <interfaces/iplugin.h>
#include "core.h"
#include "sessioncontroller.h"
#include <interfaces/iprojectcontroller.h>
#include <interfaces/iproject.h>
#include <util/fileutils.h>

namespace KDevelop
{
const QString Session::cfgSessionNameEntry = "SessionName";
const QString Session::cfgSessionPrettyContentsEntry = "SessionPrettyContents";

class SessionPrivate
{
public:
    SessionInfo info;
    bool isTemporary;

    KUrl pluginArea( const IPlugin* plugin )
    {
        QString name = Core::self()->pluginController()->pluginInfo( plugin ).pluginName();
        KUrl url( info.path );
        url.addPath( name );
        if( !QFile::exists( url.toLocalFile() ) ) {
            QDir( info.path.toLocalFile() ).mkdir( name );
        }
        return url;
    }

    SessionPrivate( const QString& id )
        : info( Session::parse( id, true ) )
        , isTemporary( false )
    {
    }
};

Session::Session( const QString& id, QObject* parent )
        : ISession(parent)
        , d( new SessionPrivate( id ) )
{
}

Session::~Session()
{
    delete d;
}

QString Session::name() const
{
    return d->info.name;
}

KUrl::List Session::containedProjects() const
{
    return d->info.projects;
}

void Session::updateDescription()
{
    QString prettyContents = generatePrettyContents( d->info );
    d->info.description = generateDescription( d->info, prettyContents );

    d->info.config->group("").writeEntry( cfgSessionPrettyContentsEntry, prettyContents );
    d->info.config->group("").sync();
}

QString Session::description() const
{
    return d->info.description;
}

KUrl Session::pluginDataArea( const IPlugin* p )
{
    return d->pluginArea( p );
}

KSharedConfig::Ptr Session::config()
{
    return d->info.config;
}

QUuid Session::id() const
{
    return d->info.uuid;
}

void Session::deleteFromDisk()
{
    removeDirectory( d->info.path.toLocalFile() );
}

void Session::setName( const QString& newname )
{
    QString oldname = d->info.name;
    d->info.name = newname;
    emit nameChanged( newname, oldname );

    d->info.config->group("").writeEntry( cfgSessionNameEntry, newname );
    d->info.config->sync();
}

void Session::setTemporary(bool temp)
{
    d->isTemporary = temp;
}

bool Session::isTemporary() const
{
    return d->isTemporary;
}

QString Session::generatePrettyContents( const SessionInfo& info )
{
    if( info.projects.isEmpty() )
        return QString();

    QStringList projectNames;
    foreach( const KUrl& url, info.projects ) {
        IProject* project = ICore::self()->projectController()->findProjectForUrl(url);
        if(project) {
            projectNames << project->name();
        } else {
            QString projectName = url.fileName();
            projectName.remove( QRegExp( "\\.kdev4$", Qt::CaseInsensitive ) );
            projectNames << projectName;
        }
    }
    return projectNames.join( ", " );
}

QString Session::generateDescription( const SessionInfo& info, const QString& prettyContents )
{
    QString prettyContentsFormatted;
    if( prettyContents.isEmpty() ) {
        prettyContentsFormatted = i18n("(no projects)");
    } else {
        prettyContentsFormatted = prettyContents;
    }

    QString description;
    if( info.name.isEmpty() ) {
        description = prettyContentsFormatted;
    } else {
        description = info.name + ":  " + prettyContentsFormatted;
    }
    return description;
}

SessionInfo Session::parse( const QString& id, bool mkdir )
{
    SessionInfo ret;
    KUrl sessionPath = SessionController::sessionDirectory();
    sessionPath.addPath( id );

    QDir sessionDir( sessionPath.toLocalFile( KUrl::AddTrailingSlash ) );
    if( !sessionDir.exists() ) {
        if( mkdir ) {
            QDir( SessionController::sessionDirectory() ).mkdir( id );
            Q_ASSERT( sessionDir.exists() );
        } else {
            return ret;
        }
    }

    ret.uuid = id;
    ret.path = sessionPath;
    sessionPath.addPath( "sessionrc" );

    ret.config = KSharedConfig::openConfig( sessionPath.toLocalFile() );
    ret.name = ret.config->group( QString() ).readEntry( cfgSessionNameEntry, QString() );
    ret.projects = ret.config->group( "General Options" ).readEntry( "Open Projects", QStringList() );
    ret.description = generateDescription( ret, ret.config->group( QString() ).readEntry( "SessionPrettyContents", QString() ) );
    return ret;
}

}
#include "session.moc"

