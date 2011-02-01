//
//  libavg - Media Playback Engine. 
//  Copyright (C) 2003-2008 Ulrich von Zadow
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
//  Current versions can be found at www.libavg.de
//

#include "XInput21MTEventSource.h"

#include "TouchEvent.h"
#include "Player.h"
#include "AVGNode.h"
#include "TouchStatus.h"
#include "SDLDisplayEngine.h"

#include "../base/Logger.h"
#include "../base/Point.h"
#include "../base/ObjectCounter.h"
#include "../base/Exception.h"
#include "../base/OSHelper.h"
#include "../base/StringHelper.h"

#include <SDL/SDL_syswm.h>
#include <SDL/SDL.h>

#include <X11/extensions/XI.h>
#include <X11/extensions/XInput2.h>

using namespace std;

namespace avg {

XInput21MTEventSource::XInput21MTEventSource()
    : m_LastID(0)
{
}

XInput21MTEventSource::~XInput21MTEventSource()
{
}

void XInput21MTEventSource::start()
{
#ifdef XI_2_1_Minor
    SDL_SysWMinfo info;
    SDL_VERSION(&info.version);
    int rc = SDL_GetWMInfo(&info);
    AVG_ASSERT(rc != -1);
    m_pDisplay = info.info.x11.display;

    /* XInput Extension available? */
    int opcode, event, error;
    if (!XQueryExtension(m_pDisplay, "XInputExtension", &opcode, &event, &error)) {
        throw Exception(AVG_ERR_MT_INIT, 
                string("XInput 2.1 multitouch event source: X Input extension not available'"));
    }

    /* Which version of XI2? We need 2.1 */
    int major = 2, minor = 1;
    Status status = XIQueryVersion(m_pDisplay, &major, &minor);
    if (status == BadRequest) {
        throw Exception(AVG_ERR_MT_INIT, 
                "XInput 2.1 multitouch event source: Server does not support XI2");
    }
    if (major < 2 || minor < 1) {
        throw Exception(AVG_ERR_MT_INIT, 
                "XInput 2.1 multitouch event source: Supported version is "
                +toString(major)+"."+toString(minor)+". 2.1 is needed.");
    }
    SDLDisplayEngine * pEngine = dynamic_cast<SDLDisplayEngine *>(
            Player::get()->getDisplayEngine());
    if (pEngine->isFullscreen()) {
        m_Win = info.info.x11.fswindow;
    } else {
        m_Win = info.info.x11.wmwindow;
    }
    cerr << "Input window handle: " << m_Win << endl;

    XIEventMask mask;
    mask.deviceid = XIAllDevices;
    mask.mask_len = XIMaskLen(XI_LASTEVENT);
    mask.mask = (unsigned char *)calloc(mask.mask_len, sizeof(char));
    memset(mask.mask, 0, mask.mask_len);
    XISetMask(mask.mask, XI_TouchBegin);
    XISetMask(mask.mask, XI_TouchMotion);
    XISetMask(mask.mask, XI_TouchMotionUnowned);
    XISetMask(mask.mask, XI_TouchOwnership);
    XISetMask(mask.mask, XI_TouchEnd);

    XISelectEvents(info.info.x11.display, info.info.x11.window, &mask, 1);

    MultitouchEventSource::start();
    AVG_TRACE(Logger::CONFIG, "XInput 2.1 Multitouch event source created.");
#else
    throw Exception(AVG_ERR_MT_INIT, 
            string("XInput 2.1 multitouch event source: XInput 2.1 not available'"));
#endif
}

std::vector<EventPtr> XInput21MTEventSource::pollEvents()
{

    return MultitouchEventSource::pollEvents();
}

TouchEventPtr XInput21MTEventSource::createEvent(int id, Event::Type type, IntPoint pos)
{
/*
    DPoint size = getWindowSize();
    DPoint normPos = DPoint(double(pos.x-m_Dimensions.tl.x)/m_Dimensions.width(),
            double(pos.y-m_Dimensions.tl.y)/m_Dimensions.height());
    IntPoint screenPos(int(normPos.x*size.x+0.5), int(normPos.y*size.y+0.5));
    return TouchEventPtr(new TouchEvent(id, type, screenPos, Event::TOUCH, DPoint(0,0), 
            0, 20, 1, DPoint(5,0), DPoint(0,5)));
*/
}
           
}