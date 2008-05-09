//
//  libavg - Media Playback Engine. 
//  Copyright (C) 2003-2006 Ulrich von Zadow
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

#include "OGLImagingContext.h"

#include "OGLHelper.h"

#include "../base/Exception.h"

namespace avg {

OGLImagingContext::OGLImagingContext(const IntPoint & size)
    : m_Size(size)
{
    // Coordinates
    glViewport(0, 0, m_Size.x, m_Size.y);
    OGLErrorCheck(AVG_ERR_VIDEO_GENERAL, "glViewport()");
    glMatrixMode(GL_PROJECTION);
    OGLErrorCheck(AVG_ERR_VIDEO_GENERAL, "glMatrixMode()");
    glLoadIdentity();
    OGLErrorCheck(AVG_ERR_VIDEO_GENERAL, "glLoadIdentity()");
    gluOrtho2D(0, m_Size.y, m_Size.x, 0);
    OGLErrorCheck(AVG_ERR_VIDEO_GENERAL, "gluOrtho2D()");
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    OGLErrorCheck(AVG_ERR_VIDEO_GENERAL, "glLoadIdentity()");

    // Shading etc.
    glEnable(GL_BLEND);
    OGLErrorCheck(AVG_ERR_VIDEO_GENERAL, "glEnable(GL_BLEND)");
    glShadeModel(GL_FLAT);
    OGLErrorCheck(AVG_ERR_VIDEO_GENERAL, "glShadeModel(GL_FLAT)");
    glDisable(GL_DEPTH_TEST);
    OGLErrorCheck(AVG_ERR_VIDEO_GENERAL, "glDisable(GL_DEPTH_TEST)");
    glDisable(GL_STENCIL_TEST);
    OGLErrorCheck(AVG_ERR_VIDEO_GENERAL, "glDisable(GL_STENCIL_TEST)");

    // Texturing
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
    OGLErrorCheck(AVG_ERR_VIDEO_GENERAL, "glTexEnvf()");
    glBlendFunc(GL_ONE, GL_ZERO);
    OGLErrorCheck(AVG_ERR_VIDEO_GENERAL, "glBlendFunc()");
    glEnable(GL_TEXTURE_RECTANGLE_ARB);
    OGLErrorCheck(AVG_ERR_VIDEO_GENERAL, "glEnable(GL_TEXTURE_RECTANGLE_ARB);");
    glDisable(GL_MULTISAMPLE);
    OGLErrorCheck(AVG_ERR_VIDEO_GENERAL, "glDisable(GL_MULTISAMPLE);");

    // TODO: set up clamping.
}

OGLImagingContext::~OGLImagingContext()
{
}

void OGLImagingContext::activate()
{
}

}

