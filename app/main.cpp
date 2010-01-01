/***************************************************************************
 *   Copyright 2003-2009 Alexander Dymo <adymo@kdevelop.org>               *
 *   Copyright 2007 Ralf Habacker  <Ralf.Habacker@freenet.de>              *
 *   Copyright 2006-2007 Matt Rogers  <mattr@kde.org>                      *
 *   Copyright 2006-2007 Hamish Rodda <rodda@kde.org>                      *
 *   Copyright 2005-2007 Adam Treat <treat@kde.org>                        *
 *   Copyright 2003-2007 Jens Dagerbo <jens.dagerbo@swipnet.se>            *
 *   Copyright 2001-2002 Bernd Gehrmann <bernd@mail.berlios.de>            *
 *   Copyright 2001-2002 Matthias Hoelzer-Kluepfel <hoelzer@kde.org>       *
 *   Copyright 2003 Roberto Raggi <roberto@kdevelop.org>                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#include <config.h>

#include <kaboutdata.h>
#include <kapplication.h>
#include <kcmdlineargs.h>
#include <klocale.h>
#include <kxmlguiwindow.h>
#include <kstandarddirs.h>
#include <kdebug.h>
#include <ksplashscreen.h>
#include <ktexteditor/cursor.h>

#include <QFileInfo>
#include <QPixmap>
#include <QTimer>
#include <QDir>

#include <shell/core.h>
#include <shell/mainwindow.h>
#include <shell/projectcontroller.h>
#include <shell/documentcontroller.h>
#include <shell/plugincontroller.h>
#include <shell/sessioncontroller.h>

#include "kdevideextension.h"
#include <KMessageBox>
#include <KProcess>

using KDevelop::Core;

int main( int argc, char *argv[] )
{
    static const char description[] = I18N_NOOP( "The KDevelop Integrated Development Environment" );
    KAboutData aboutData( "kdevelop", 0, ki18n( "KDevelop" ),
                          i18n("%1 (using KDevPlatform %2)", QString(VERSION), Core::version()).toUtf8(), ki18n(description), KAboutData::License_GPL,
                          ki18n( "Copyright 1999-2009, The KDevelop developers" ), KLocalizedString(), "http://www.kdevelop.org" );
    aboutData.addAuthor( ki18n("Andreas Pakulat"), ki18n( "Maintainer, Architecture, VCS Support, Project Management Support, QMake Projectmanager" ), "apaku@gmx.de" );
    aboutData.addAuthor( ki18n("Alexander Dymo"), ki18n( "Architecture, Sublime UI, Ruby support" ), "adymo@kdevelop.org" );
    aboutData.addAuthor( ki18n("David Nolden"), ki18n( "Definition-Use Chain, C++ Support, Code Navigation, Code Completion, Coding Assistance, Refactoring" ), "david.nolden.kdevelop@art-master.de" );
    aboutData.addAuthor( ki18n("Aleix Pol Gonzalez"), ki18n( "CMake Support, Run Support, Kross Support" ), "aleixpol@gmail.com" );
    aboutData.addAuthor( ki18n("Vladimir Prus"), ki18n( "GDB integration" ), "ghost@cs.msu.su" );
    aboutData.addAuthor( ki18n("Hamish Rodda"), ki18n( "Text editor integration, definition-use chain" ), "rodda@kde.org" );
    aboutData.addAuthor( ki18n("Amilcar do Carmo Lucas"), ki18n( "Website admin, API documentation, Doxygen and autoproject patches" ), "amilcar@kdevelop.org" );

    aboutData.addCredit( ki18n("Matt Rogers"), KLocalizedString(), "mattr@kde.org");
    aboutData.addCredit( ki18n("Cédric Pasteur"), ki18n("astyle and indent support"), "cedric.pasteur@free.fr" );
    aboutData.addCredit( ki18n("Evgeniy Ivanov"), ki18n("Distributed VCS, Git, Mercurial"), "powerfox@kde.ru" );
    // QTest integration is separate in playground currently.
    //aboutData.addCredit( ki18n("Manuel Breugelmanns"), ki18n( "Veritas, QTest integration"), "mbr.nxi@gmail.com" );
    aboutData.addCredit( ki18n("Robert Gruber") , ki18n( "SnippetPart, debugger and usability patches" ), "rgruber@users.sourceforge.net" );
    aboutData.addCredit( ki18n("Dukju Ahn"), ki18n( "Subversion plugin, Custom Make Manager, Overall improvements" ), "dukjuahn@gmail.com" );
    aboutData.addCredit( ki18n("Harald Fernengel"), ki18n( "Ported to Qt 3, patches, valgrind, diff and perforce support" ), "harry@kdevelop.org" );
    aboutData.addCredit( ki18n("Roberto Raggi"), ki18n( "C++ parser" ), "roberto@kdevelop.org" );
    aboutData.addCredit( ki18n("The KWrite authors"), ki18n( "Kate editor component" ), "kwrite-devel@kde.org" );
    aboutData.addCredit( ki18n("Nokia Corporation/Qt Software"), ki18n( "Designer code" ), "qt-info@nokia.com" );
    
    aboutData.addCredit( ki18n("Contributors to older versions:"), KLocalizedString(), "" );
    aboutData.addCredit( ki18n("The KHTML authors"), ki18n( "HTML documentation component" ), "kfm-devel@kde.org" );
    aboutData.addCredit( ki18n("Bernd Gehrmann"), ki18n( "Initial idea, basic architecture, much initial source code" ), "bernd@kdevelop.org" );
    aboutData.addCredit( ki18n("Caleb Tennis"), ki18n( "KTabBar, bugfixes" ), "caleb@aei-tech.com" );
    aboutData.addCredit( ki18n("Richard Dale"), ki18n( "Java & Objective C support" ), "Richard_Dale@tipitina.demon.co.uk" );
    aboutData.addCredit( ki18n("John Birch"), ki18n( "Debugger frontend" ), "jbb@kdevelop.org" );
    aboutData.addCredit( ki18n("Sandy Meier"), ki18n( "PHP support, context menu stuff" ), "smeier@kdevelop.org" );
    aboutData.addCredit( ki18n("Kurt Granroth"), ki18n( "KDE application templates" ), "kurth@granroth.org" );
    aboutData.addCredit( ki18n("Ian Reinhart Geiser"), ki18n( "Dist part, bash support, application templates" ), "geiseri@yahoo.com" );
    aboutData.addCredit( ki18n("Matthias Hoelzer-Kluepfel"), ki18n( "Several components, htdig indexing" ), "hoelzer@kde.org" );
    aboutData.addCredit( ki18n("Victor Roeder"), ki18n( "Help with Automake manager and persistent class store" ), "victor_roeder@gmx.de" );
    aboutData.addCredit( ki18n("Simon Hausmann"), ki18n( "Help with KParts infrastructure" ), "hausmann@kde.org" );
    aboutData.addCredit( ki18n("Oliver Kellogg"), ki18n( "Ada support" ), "okellogg@users.sourceforge.net" );
    aboutData.addCredit( ki18n("Jakob Simon-Gaarde"), ki18n( "QMake projectmanager" ), "jsgaarde@tdcspace.dk" );
    aboutData.addCredit( ki18n("Falk Brettschneider"), ki18n( "MDI modes, QEditor, bugfixes" ), "falkbr@kdevelop.org" );
    aboutData.addCredit( ki18n("Mario Scalas"), ki18n( "PartExplorer, redesign of CvsPart, patches, bugs(fixes)" ), "mario.scalas@libero.it" );
    aboutData.addCredit( ki18n("Jens Dagerbo"), ki18n( "Replace, Bookmarks, FileList and CTags2 plugins. Overall improvements and patches" ), "jens.dagerbo@swipnet.se" );
    aboutData.addCredit( ki18n("Julian Rockey"), ki18n( "Filecreate part and other bits and patches" ), "linux@jrockey.com" );
    aboutData.addCredit( ki18n("Ajay Guleria"), ki18n( "ClearCase support" ), "ajay_guleria@yahoo.com" );
    aboutData.addCredit( ki18n("Marek Janukowicz"), ki18n( "Ruby support" ), "child@t17.ds.pwr.wroc.pl" );
    aboutData.addCredit( ki18n("Robert Moniot"), ki18n( "Fortran documentation" ), "moniot@fordham.edu" );
    aboutData.addCredit( ki18n("Ka-Ping Yee"), ki18n( "Python documentation utility" ), "ping@lfw.org" );
    aboutData.addCredit( ki18n("Dimitri van Heesch"), ki18n( "Doxygen wizard" ), "dimitri@stack.nl" );
    aboutData.addCredit( ki18n("Hugo Varotto"), ki18n( "Fileselector component" ), "hugo@varotto-usa.com" );
    aboutData.addCredit( ki18n("Matt Newell"), ki18n( "Fileselector component" ), "newellm@proaxis.com" );
    aboutData.addCredit( ki18n("Daniel Engelschalt"), ki18n( "C++ code completion, persistent class store" ), "daniel.engelschalt@gmx.net" );
    aboutData.addCredit( ki18n("Stephane Ancelot"), ki18n( "Patches" ), "sancelot@free.fr" );
    aboutData.addCredit( ki18n("Jens Zurheide"), ki18n( "Patches" ), "jens.zurheide@gmx.de" );
    aboutData.addCredit( ki18n("Luc Willems"), ki18n( "Help with Perl support" ), "Willems.luc@pandora.be" );
    aboutData.addCredit( ki18n("Marcel Turino"), ki18n( "Documentation index view" ), "M.Turino@gmx.de" );
    aboutData.addCredit( ki18n("Yann Hodique"), ki18n( "Patches" ), "Yann.Hodique@lifl.fr" );
    aboutData.addCredit( ki18n("Tobias Gl\303\244\303\237er") , ki18n( "Documentation Finder,  qmake projectmanager patches, usability improvements, bugfixes ... " ), "tobi.web@gmx.de" );
    aboutData.addCredit( ki18n("Andreas Koepfle") , ki18n( "QMake project manager patches" ), "koepfle@ti.uni-mannheim.de" );
    aboutData.addCredit( ki18n("Sascha Cunz") , ki18n( "Cleanup and bugfixes for qEditor, AutoMake and much other stuff" ), "mail@sacu.de" );
    aboutData.addCredit( ki18n("Zoran Karavla"), ki18n( "Artwork for the ruby language" ), "webmaster@the-error.net", "http://the-error.net" );

    KCmdLineArgs::init( argc, argv, &aboutData );
    KCmdLineOptions options;
    options.add("profile <profile>", ki18n( "Profile to load" ));
    options.add("s <session>", ki18n("Session to load" ));
    options.add("project <project>", ki18n( "Url to project to load" ));
    options.add("+files", ki18n( "Files to load" ));
    KCmdLineArgs::addCmdLineOptions( options );
    KCmdLineArgs* args = KCmdLineArgs::parsedArgs();

    KApplication app;
    KDevIDEExtension::init();

    ///Manage sessions: There always needs a KDEV_SESSION to be set, so the duchain can be stored in the session-specific directory
    QString session = args->getOption("s");
    if(!getenv("KDEV_SESSION"))
    {
        //No session is set, we have to pick one, then we restart kdevelop through kdev_starter, and forward all relevant arguments to it
        session = KDevelop::SessionController::defaultSessionId(session);

        kDebug() << "Starting with kdev_starter and default session" << session;
        
        QStringList args;
        
        args << QApplication::applicationFilePath() << session;
        
        //Forward all arguments, the session will be skipped automatically as KDEV_SESSION will be set
        for(uint a = 1; a < argc; ++a)
            args << QString(argv[a]);
        
        //@todo Eventually show a session-picking dialog
        KProcess::startDetached(QFileInfo(QApplication::applicationFilePath()).path() + "/kdev_starter", args);
        return 0;
    }
    
    KSplashScreen* splash = 0;
    QString splashFile = KStandardDirs::locate( "appdata", "pics/kdevelop-splash.png" );
    if( !splashFile.isEmpty() )
    {
        QPixmap pm;
        pm.load( splashFile );
        splash = new KSplashScreen( pm );
        splash->show();
    }

    Core::initialize(splash);
    KGlobal::locale()->insertCatalog( Core::self()->componentData().catalogName() );
    Core* core = Core::self();

    QStringList projectNames = args->getOptionList("project");
    if(!projectNames.isEmpty())
    {
        foreach(const QString& p, projectNames)
        {
            KUrl url(p);
            QString ext = QFileInfo( url.fileName() ).suffix();
            if( ext == "kdev4" )
            {
                core->projectController()->openProject( url );
            }
        }
    }

    int count=args->count();
    for(int i=0; i<count; ++i)
    {
        QString file=args->arg(i);
        //Allow opening specific lines in documents, like mydoc.cpp:10
        int lineNumberOffset = file.lastIndexOf(':');
        KTextEditor::Cursor line;
        if( lineNumberOffset != -1 )
        {
            bool isInt;
            int lineNr = file.mid(lineNumberOffset+1).toInt(&isInt);
            if (isInt)
            {
                file = file.left(lineNumberOffset);
                line = KTextEditor::Cursor(lineNr, 0);
            }
        }

        KUrl f(file);
        if( f.isRelative() )
            f=KUrl(QDir::currentPath(), file);
        
        if(!core->documentController()->openDocument(f, line))
            kWarning() << i18n("Could not open %1") << args->arg(i);
    }
    args->clear();

    return app.exec();
}

