/***************************************************************************
 *   Copyright (C) 2007 by Dukju Ahn                                       *
 *   dukjuahn@gmail.com                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "subversion_core.h"

extern "C" {
#include <apr_general.h>
#include <svn_opt.h>
#include <svn_auth.h>
#include <svn_wc.h>

}

#include "subversion_part.h"
#include "subversion_view.h"
#include "svn_revision.h"
#include "interthreadevents.h"
#include "svnkjobbase.h"
#include "subversionthreads.h"
#include "svn_models.h"
#include "ui_svnlogindialog.h"
#include "svn_authdialog.h"
#include "svn_commitwidgets.h"
#include <kmessagebox.h>
// #include <kprogressdialog.h>
#include <kuiserverjobtracker.h>
#include <QProgressDialog>

// //ThreadWeaver includes
// #include <State.h>
// #include <JobCollection.h>
// #include <DebuggingAids.h>
// #include <Thread.h>

#include <QPointer>
#include <QCoreApplication>

#include <klocale.h>


// using namespace ThreadWeaver;

SubversionCore::SubversionCore( KDevSubversionPart *part, QObject *parent )
    : QObject(parent) , m_part(part)
{
    apr_initialize();
	m_uiServer = new KUiServerJobTracker( this );
}

SubversionCore::~SubversionCore()
{
	delete m_uiServer;
    apr_terminate();
}

#define SVNCORE_SPAWN_COMMON( job, thread ) \
    job->setSvnThread( thread ); \
    connect( job, SIGNAL(result(KJob*)), this, SLOT(slotResult(KJob*)) ); \
    job->start();

void SubversionCore::spawnCheckoutThread( const KUrl &repos, const KUrl &path, const SvnRevision &peg,
                            const SvnRevision &revision, bool recurse, bool ignoreExternals )
{
    SvnKJobBase *job = new SvnKJobBase( SVN_CHECKOUT, this );
    SvnCheckoutJob *thread = new SvnCheckoutJob( repos, path, peg, revision,
                                            recurse, ignoreExternals, SVN_CHECKOUT, job );
    SVNCORE_SPAWN_COMMON( job, thread )
}
SvnKJobBase* SubversionCore::createCheckoutJob( const KUrl &repos, const KUrl &path,
                                            const SvnRevision &peg, const SvnRevision &revision,
                                            bool recurse, bool ignoreExternals )
{
    SvnKJobBase *job = new SvnKJobBase( SVN_CHECKOUT, this );
    SvnCheckoutJob *thread = new SvnCheckoutJob( repos, path, peg, revision,
            recurse, ignoreExternals, SVN_CHECKOUT, job );
    job->setSvnThread( thread );
    return job;
}

void SubversionCore::spawnAddThread( const KUrl::List &wcPaths, bool recurse, bool force, bool noIgnore )
{
    if( wcPaths.count() < 1 ) return;
    SvnKJobBase *job = new SvnKJobBase(SVN_ADD, this);
    SvnAddJob *thread = new SvnAddJob( wcPaths, recurse, force, noIgnore, SVN_ADD, job );

    SVNCORE_SPAWN_COMMON( job, thread )
}
SvnKJobBase* SubversionCore::createAddJob( const KUrl::List &wcPaths, bool recurse, bool force, bool noIgnore )
{
    SvnKJobBase *job = new SvnKJobBase( SVN_ADD, this );
    SvnAddJob *thread = new SvnAddJob( wcPaths, recurse, force, noIgnore, SVN_ADD, job );
    job->setSvnThread( thread );
    return job;
}

void SubversionCore::spawnRemoveThread( const KUrl::List &urls, bool force )
{
    if( urls.count() < 1 ) return;
    SvnKJobBase *job = new SvnKJobBase( SVN_DELETE, this );
    SvnDeleteJob *thread = new SvnDeleteJob( urls, force, SVN_DELETE, job );

    SVNCORE_SPAWN_COMMON( job, thread )
}
SvnKJobBase* SubversionCore::createRemoveJob( const KUrl::List &urls, bool force )
{
    SvnKJobBase *job = new SvnKJobBase( SVN_DELETE, this );
    SvnDeleteJob *thread = new SvnDeleteJob( urls, force, SVN_DELETE, job );
    job->setSvnThread( thread );
}

void SubversionCore::spawnCommitThread( const KUrl::List &urls, bool recurse, bool keepLocks )
{
    if( urls.count() < 1 ) return;
    SvnKJobBase *job = new SvnKJobBase( SVN_COMMIT, this );
    SvnCommitJob *thread = new SvnCommitJob( urls, QString(), recurse, keepLocks, SVN_COMMIT, job );

    SVNCORE_SPAWN_COMMON( job, thread )
    initProgressDlg( job );
}
SvnKJobBase* SubversionCore::createCommitJob( const KUrl::List &urls, const QString &msg,
                                              bool recurse, bool keepLocks )
{
    SvnKJobBase *job = new SvnKJobBase( SVN_COMMIT, this );
    SvnCommitJob *thread = new SvnCommitJob( urls, msg, recurse, keepLocks, SVN_COMMIT, job );
    job->setSvnThread( thread );
}
void SubversionCore::spawnUpdateThread( const KUrl::List &wcPaths,
                                        const SvnRevision &rev,
                                        bool recurse, bool ignoreExternals )
{
    if( wcPaths.count() < 1 ) return;
    SvnKJobBase *job = new SvnKJobBase( SVN_UPDATE, this );
    SvnUpdateJob *thread = new SvnUpdateJob( wcPaths, rev,
                                          recurse, ignoreExternals,
                                          SVN_UPDATE, job );
    SVNCORE_SPAWN_COMMON( job, thread )
    initProgressDlg( job );
}
SvnKJobBase* SubversionCore::createUpdateJob( const KUrl::List &wcPaths,
                                  const SvnRevision &rev,
                                  bool recurse, bool ignoreExternals )
{
    SvnKJobBase *job = new SvnKJobBase( SVN_UPDATE, this );
    SvnUpdateJob *thread = new SvnUpdateJob( wcPaths, rev,
                                             recurse, ignoreExternals,
                                             SVN_UPDATE, job );
    job->setSvnThread( thread );
}

void SubversionCore::spawnLogviewThread(const KUrl::List& list,
                                        const SvnRevision &rev1, const SvnRevision &rev2,
                                        int limit,
                                        bool discorverChangedPath, bool strictNodeHistory )
{
    // KUrl::List is handed. But only one Url will be used effectively.
    if( list.count() < 1 ) return;

    SvnKJobBase *job= new SvnKJobBase( SVN_LOGVIEW, this );
    SvnLogviewJob* thread = new SvnLogviewJob(
                            rev1, rev2,
                            limit,discorverChangedPath, strictNodeHistory, list,
                            SVN_LOGVIEW, job );
    job->setSvnThread( thread );

    // note: logview is testbed for all radical framework changes.
    // So please don't connect to slotResult as other methods.
    connect( job, SIGNAL(result(KJob*)), this, SLOT(slotLogResult(KJob*)) );

	job->start();

    initProgressDlg( job );
}

SvnKJobBase* SubversionCore::createLogviewJob( const KUrl::List& list,
                                   const SvnRevision &rev1, const SvnRevision &rev2,
                                    int limit, bool discorverChangedPath, bool strictNodeHistory )
{
    SvnKJobBase *job= new SvnKJobBase( SVN_LOGVIEW, this );
    SvnLogviewJob* thread = new SvnLogviewJob(
                            rev1, rev2,
                            limit,discorverChangedPath, strictNodeHistory, list,
                            SVN_LOGVIEW, job );
    job->setSvnThread( thread );
    return job;
}

void SubversionCore::spawnBlameThread( const KUrl &url,
                                       const SvnRevision &rev1, const SvnRevision &rev2 )
{
    SvnKJobBase *job = new SvnKJobBase( SVN_BLAME, this );
    SvnBlameJob *thread = new SvnBlameJob( url,
                               rev1, rev2,
                               SVN_BLAME, job );

    SVNCORE_SPAWN_COMMON( job, thread )
    initProgressDlg( job );
}
SvnKJobBase* SubversionCore::createBlameJob( const KUrl &url,
                                 const SvnRevision &rev1, const SvnRevision &rev2 )
{
    SvnKJobBase *job = new SvnKJobBase( SVN_BLAME, this );
    SvnBlameJob *thread = new SvnBlameJob( url,
                                           rev1, rev2,
                                           SVN_BLAME, job );
    return job;
}

const SvnKJobBase* SubversionCore::spawnStatusThread( const KUrl &wcPath, const SvnRevision &rev,
                bool recurse, bool getAll, bool update, bool noIgnore, bool ignoreExternals )
{
    SvnKJobBase *job = new SvnKJobBase( SVN_STATUS, this );
    SvnStatusJob *thread = new SvnStatusJob( wcPath, rev,
                    recurse, getAll, update, noIgnore, ignoreExternals, SVN_STATUS, job );

    SVNCORE_SPAWN_COMMON( job, thread )
    initProgressDlg( job );
    return job;
}

SvnKJobBase* SubversionCore::createStatusJob( const KUrl &wcPath, const SvnRevision &rev,
                                        bool recurse, bool getAll, bool update,
                                        bool noIgnore, bool ignoreExternals )
{
    SvnKJobBase *job = new SvnKJobBase( SVN_STATUS, this );
    SvnStatusJob *thread = new SvnStatusJob( wcPath, rev,
                    recurse, getAll, update, noIgnore, ignoreExternals, SVN_STATUS, job );
    job->setSvnThread( thread );
    return job;
}

void SubversionCore::spawnInfoThread( const KUrl &pathOrUrl,
                                      const SvnRevision &peg, const SvnRevision &revision,
                                      bool recurse )
{
    SvnKJobBase *job = new SvnKJobBase( SVN_INFO, this );
    SvnInfoJob *thread = new SvnInfoJob( pathOrUrl, peg, revision, recurse, SVN_INFO, job );

    SVNCORE_SPAWN_COMMON( job, thread )
    initProgressDlg( job );
}

SvnKJobBase* SubversionCore::createInfoJob( const KUrl &pathOrUrl,
                                const SvnRevision &peg, const SvnRevision &revision,
                                bool recurse )
{
    SvnKJobBase *job = new SvnKJobBase( SVN_INFO, this );
    SvnInfoJob *thread = new SvnInfoJob( pathOrUrl, peg, revision, recurse, SVN_INFO, job );
    job->setSvnThread( thread );
    return job;
}

void SubversionCore::spawnDiffThread( const KUrl &pathOrUrl1, const KUrl &pathOrUrl2, const SvnRevision &peg,
                                      const SvnRevision &rev1, const SvnRevision &rev2,
                                      bool recurse, bool ignoreAncestry, bool noDiffDeleted,
                                      bool ignoreContentType )
{
    SvnKJobBase *job = new SvnKJobBase( SVN_DIFF, this );
    SvnDiffJob *thread = new SvnDiffJob( pathOrUrl1, pathOrUrl2, peg, rev1, rev2,
                                      recurse, ignoreAncestry, noDiffDeleted, ignoreContentType,
                                      SVN_DIFF, job );
    SVNCORE_SPAWN_COMMON( job, thread )
    initProgressDlg( job );
}

SvnKJobBase *SubversionCore::createDiffJob( const KUrl &pathOrUrl1, const KUrl &pathOrUrl2,
                                            const SvnRevision &peg,
                                      const SvnRevision &rev1, const SvnRevision &rev2,
                                      bool recurse, bool ignoreAncestry, bool noDiffDeleted,
                                      bool ignoreContentType )
{
    SvnKJobBase *job = new SvnKJobBase( SVN_DIFF, this );
    SvnDiffJob *thread = new SvnDiffJob( pathOrUrl1, pathOrUrl2, peg, rev1, rev2,
                                      recurse, ignoreAncestry, noDiffDeleted, ignoreContentType,
                                      SVN_DIFF, job );
    job->setSvnThread( thread );
    return job;
}

void SubversionCore::spawnImportThread( const KUrl &path, const KUrl &url,
                                        bool nonRecurse, bool noIgnore )
{
    SvnKJobBase *job = new SvnKJobBase( SVN_IMPORT, this );
    SvnImportJob *thread = new SvnImportJob( path, url, nonRecurse, noIgnore, SVN_IMPORT, job );

    SVNCORE_SPAWN_COMMON( job, thread )
}

SvnKJobBase* SubversionCore::createImportJob( const KUrl &path, const KUrl &url,
                                      bool nonRecurse, bool noIgnore )
{
    SvnKJobBase *job = new SvnKJobBase( SVN_IMPORT, this );
    SvnImportJob *thread = new SvnImportJob( path, url, nonRecurse, noIgnore, SVN_IMPORT, job );
    job->setSvnThread( thread );
    return job;
}

void SubversionCore::spawnRevertThread( const KUrl::List &paths, bool recurse )
{
    SvnKJobBase *job = new SvnKJobBase( SVN_REVERT, this );
    SvnRevertJob *thread = new SvnRevertJob( paths, recurse, SVN_REVERT, job );

    SVNCORE_SPAWN_COMMON( job, thread )
}

SvnKJobBase* SubversionCore::createRevertJob( const KUrl::List &paths, bool recurse )
{
    SvnKJobBase *job = new SvnKJobBase( SVN_REVERT, this );
    SvnRevertJob *thread = new SvnRevertJob( paths, recurse, SVN_REVERT, job );
    job->setSvnThread( thread );
    return job;
}

void SubversionCore::spawnCopyThread( const KUrl &srcPathOrUrl,
                                      const SvnRevision &srcRev,
                                      const KUrl &dstPathOrUrl )
{
    SvnKJobBase *job = new SvnKJobBase( SVN_COPY, this );
    SvnCopyJob *thread = new SvnCopyJob( srcPathOrUrl, srcRev, dstPathOrUrl, SVN_COPY, job );

    SVNCORE_SPAWN_COMMON( job, thread )
}

SvnKJobBase* SubversionCore::createCopyJob( const KUrl &srcPathOrUrl,
                                    const SvnRevision &srcRev,
                                    const KUrl &dstPathOrUrl )
{
    SvnKJobBase *job = new SvnKJobBase( SVN_COPY, this );
    SvnCopyJob *thread = new SvnCopyJob( srcPathOrUrl, srcRev, dstPathOrUrl, SVN_COPY, job );
    job->setSvnThread( thread );
    return job;
}

void SubversionCore::spawnMoveThread( const KUrl &srcPathOrUrl, const KUrl &dstPathUrl, bool force )
{
    SvnKJobBase *job = new SvnKJobBase( SVN_MOVE, this );
    SvnMoveJob *thread = new SvnMoveJob( srcPathOrUrl, dstPathUrl, force, SVN_MOVE, job );

    SVNCORE_SPAWN_COMMON( job, thread )
}

SvnKJobBase* SubversionCore::createMoveJob( const KUrl &srcPathOrUrl, const KUrl &dstPathUrl, bool force )
{
    SvnKJobBase *job = new SvnKJobBase( SVN_MOVE, this );
    SvnMoveJob *thread = new SvnMoveJob( srcPathOrUrl, dstPathUrl, force, SVN_MOVE, job );
    job->setSvnThread( thread );
    return job;
}

///////////////////////     internals       ///////////////////////////////////////////////

void SubversionCore::slotLogResult( KJob *aJob )
{
    SvnKJobBase *job = dynamic_cast<SvnKJobBase*>( aJob );
    if( !job ) return;

    emit logFetched( job );
}

void SubversionCore::slotResult( KJob* aJob )
{
    SvnKJobBase *job = dynamic_cast<SvnKJobBase*> (aJob );
    if( !job ) return;

    if( job->type() == SVN_BLAME ){
        emit blameFetched( job );
    } else if( job->type() == SVN_DIFF ){
        emit diffFetched( job );
    } else if( job->type() == SVN_INFO ){
        emit infoFetched( job );
    } else if( job->type() == SVN_STATUS ){
        emit statusFetched( job );
    }
    else {
        emit jobFinished( job );
    }
}

void SubversionCore::customEvent( QEvent * event )
{
    int type = event->type();
    switch( type ){
        case SVNACTION_NOTIFICATION : {
            SvnNotificationEvent *ev = (SvnNotificationEvent*)event;
            emit svnNotify( ev->m_path, ev->m_msg );
            break;
        }
        case SVNLOGIN_SERVERTRUSTPROMPT : {
            SvnInterThreadPromptEvent *ev = (SvnInterThreadPromptEvent*)event;
            SvnServerCertInfo *certInfo= (SvnServerCertInfo *) ev->m_data;

            SvnSSLTrustDialog dialog;
            dialog.setFailedReasons( certInfo->fails );
            dialog.setCertInfos( certInfo->cert_info );
            dialog.exec();

            SvnInterThreadPromptEvent *reply = new SvnInterThreadPromptEvent(
                                               SVNLOGIN_SERVERTRUSTPROMPT, (void*)certInfo );
            certInfo->setData( dialog.userDecision() );
            QCoreApplication::postEvent( certInfo->origSender, reply );
            break;
        }
        case SVNLOGIN_IDPWDPROMPT: {
            SvnInterThreadPromptEvent *ev = (SvnInterThreadPromptEvent*)event;
            SvnLoginInfo *info = (SvnLoginInfo*) ev->m_data;

            SvnLoginDialog dlg;
            dlg.setRealm( info->realm );
            dlg.exec();

            SvnInterThreadPromptEvent *reply = new SvnInterThreadPromptEvent(
                                               SVNLOGIN_IDPWDPROMPT, (void*)info );
            info->setData( dlg.userName(), dlg.passWord(), dlg.save() );
            QCoreApplication::postEvent( info->origSender, reply );
            break;
        }
        case SVNCOMMIT_LOGMESSAGEPROMPT: {
            SvnInterThreadPromptEvent *ev = (SvnInterThreadPromptEvent*)event;
            SvnCommitLogInfo *info = (SvnCommitLogInfo*) ev->m_data;

            SvnCommitLogInputDlg dlg;
            dlg.setCommitItems( (apr_array_header_t*)info->m_commit_items );
            int ret = dlg.exec();

            if( ret == QDialog::Accepted ){
                info->setData( true, dlg.message() );
            } else {
                info->setData( false, "" );
            }
            SvnInterThreadPromptEvent *reply = new SvnInterThreadPromptEvent(
                                               SVNCOMMIT_LOGMESSAGEPROMPT, (void*)info );
            QCoreApplication::postEvent( info->origSender, reply );
            break;
        }
        default:
            break;
    }
}
// common routines to initiate progress dialog
void SubversionCore::initProgressDlg( SvnKJobBase *job )
{
	m_uiServer->registerJob( job );

//     SvnProgressDialog *dlg = new SvnProgressDialog( (QWidget*)NULL, caption );
//
//     dlg->setSource( src );
//     dlg->setDestination( dest );
//
//     QProgressBar *bar = dlg->progressBar();
//
//     dlg->setAttribute( Qt::WA_DeleteOnClose );
// //     connect( job, SIGNAL(finished()), dlg, SLOT(close()) );
// 	connect( dlg, SIGNAL(finished()), job, SLOT(requestKill()) );
//
//     // when QThread terminates, it emits terminated() first and finished() second.
//     // so I don't connect terminated() to any slot. Every work will be done in finished() signal
//     // connect( logJob, SIGNAL(terminated()), dlg, SLOT(close()) );
//     // connect( logJob, SIGNAL(terminated(SubversionJob*)), this, SLOT( slotTerminated(SubversionJob*)) );
//     dlg->show();
}

////////////////////////////////////////////////////////////////////////


#include "subversion_core.moc"




