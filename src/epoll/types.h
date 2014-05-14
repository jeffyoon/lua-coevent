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
 *  types.h
 *  lua-coevent
 *
 *  Created by Masatoshi Teruya on 14/05/14.
 *  Copyright 2014 Masatoshi Teruya. All rights reserved.
 *
 */

#ifndef ___COEVENT_TYPES___
#define ___COEVENT_TYPES___

#include <sys/epoll.h>

// event types
#define COEVT_READ      EPOLLIN
#define COEVT_WRITE     EPOLLOUT


typedef struct epoll_event  coevt_t;

typedef struct {
    // target fd for epoll
    int fd;
    // 1 = oneshot event
    int oneshot;
    // pointer that allocated data by some of sentry type.
    // this pointer must deallocate at gc.
    // this will be 0 if sentry used external fd. (e.g. reader/writer)
    uintptr_t data;
    size_t rsize;
} coevt_prop_t;

#endif