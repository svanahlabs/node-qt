/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QCAMERA_P_H
#define QCAMERA_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API. It exists purely as an
// implementation detail. This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "qmediaobject_p.h"
#include "qvideosurfaceoutput_p.h"
#include "qcamera.h"

QT_BEGIN_NAMESPACE

class QMediaServiceProvider;
class QCameraControl;
class QVideoDeviceSelectorControl;
class QCameraLocksControl;
class QCameraInfoControl;

class QCameraPrivate : public QMediaObjectPrivate
{
    Q_DECLARE_NON_CONST_PUBLIC(QCamera)
public:
    QCameraPrivate():
        QMediaObjectPrivate(),
        provider(0),
        control(0),
        deviceControl(0),
        locksControl(0),
        infoControl(0),
        viewfinder(0),
        capture(0),
        state(QCamera::UnloadedState),
        error(QCamera::NoError),
        supportedLocks(QCamera::NoLock),
        requestedLocks(QCamera::NoLock),
        lockStatus(QCamera::Unlocked),
        lockChangeReason(QCamera::UserRequest),
        supressLockChangedSignal(false),
        restartPending(false)
    {
    }

    void init();
    void initControls();

    void clear();

    QMediaServiceProvider *provider;

    QCameraControl *control;
    QVideoDeviceSelectorControl *deviceControl;
    QCameraLocksControl *locksControl;
    QCameraInfoControl *infoControl;

    QCameraExposure *cameraExposure;
    QCameraFocus *cameraFocus;
    QCameraImageProcessing *imageProcessing;

    QObject *viewfinder;
    QObject *capture;

    QCamera::State state;

    QCamera::Error error;
    QString errorString;

    QCamera::LockTypes supportedLocks;
    QCamera::LockTypes requestedLocks;

    QCamera::LockStatus lockStatus;
    QCamera::LockChangeReason lockChangeReason;
    bool supressLockChangedSignal;

    bool restartPending;

    QVideoSurfaceOutput surfaceViewfinder;

    void _q_error(int error, const QString &errorString);
    void unsetError() { error = QCamera::NoError; errorString.clear(); }

    void setState(QCamera::State);

    void _q_updateLockStatus(QCamera::LockType, QCamera::LockStatus, QCamera::LockChangeReason);
    void _q_updateState(QCamera::State newState);
    void _q_preparePropertyChange(int changeType);
    void _q_restartCamera();
    void updateLockStatus();
};

QT_END_NAMESPACE

#endif // QCAMERA_P_H
