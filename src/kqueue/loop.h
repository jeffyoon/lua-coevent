/*
 *  Copyright (C) 2014 Masatoshi Teruya
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 *
 *
 *  loop.h
 *  lua-coevent
 *
 *  Created by Masatoshi Teruya on 14/05/13.
 *  Copyright 2014 Masatoshi Teruya. All rights reserved.
 *
 */

#ifndef ___LOOP_LUA___
#define ___LOOP_LUA___

#include "coevent.h"


// loop
typedef struct {
    lua_State *L;
    int fd;
    int state;
    int ref_fn;
    int nevs;
    int nreg;
    struct kevent *evs;
} loop_t;


// sentries
typedef struct {
    loop_t *loop;
    lua_State *L;
    // data references
    int ref;
    int ref_th;
    int ref_fn;
    int ref_ctx;
    uintptr_t ident;
} sentry_t;


void loop_error( loop_t *loop, int err, const char *msg, lua_State *L );


static inline int loop_register( loop_t *loop, sentry_t *s, struct kevent *evt )
{
    int rc = -1;
    // expand receive events container
    // no buffer
    if( loop->nreg == INT_MAX ){
        errno = ENOBUFS;
        return rc;
    }
    else if( ( loop->nreg + 1 ) > loop->nevs )
    {
        struct kevent *evs = prealloc( (size_t)loop->nevs + 1, struct kevent, 
                                       loop->evs );
        
        // realloc event container
        if( !evs ){
            return rc;
        }
        loop->nevs++;
        loop->evs = evs;
    }
    
    // register event
    rc = kevent( loop->fd, evt, 1, NULL, 0, NULL );
    if( rc == 0 ){
        loop->nreg++;
    }
    
    return rc;
}


static inline int loop_unregister( loop_t *loop, sentry_t *s, 
                                   struct kevent *evt )
{
    int rc = kevent( loop->fd, evt, 1, NULL, 0, NULL );
    
    if( rc == 0 ){
        loop->nreg--;
    }
    
    return rc;
}


#endif